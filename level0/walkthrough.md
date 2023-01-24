# Level0

```
ℹ️ Astuce - Se connecter à la VM en local

Utilisez une connection ssh :
:~$ ssh XXX.XXX.XX.XXX -p 4242

Par exemple: 
:~$ ssh 192.168.56.102 -p 4242 -l level0
```

> login:password -> *`level0:level0`*
```
:~$ su level0
Password:level0
```
---

```
:~$ pwd
/home/user/level0
```

```
:~$ ls -la
dr-xr-x---+ 1 level0 level0     60 Mar  6  2016 .
dr-x--x--x  1 root   root      340 Sep 23  2015 ..
-rw-r--r--  1 level0 level0    220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level0 level0   3530 Sep 23  2015 .bashrc
-rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0
-rw-r--r--  1 level0 level0    675 Apr  3  2012 .profile
```

Le Home contient un binaire `level0` :

```
:~$ ./level0
Segmentation fault (core dumped)

:~$ ./level0 test
No !
```

Sans paramètre le binaire segfault.
Avec un ou plusieurs paramètres, il affiche un simple `No !`

```
:~$ gdb level0
...

(gdb) disas main
Dump of assembler code for function main:
...
   0x08048ed4 <+20>:	   call   0x8049710 <atoi>
   0x08048ed9 <+25>:	   cmp    $0x1a7,%eax
   (...)
   0x08048ef8 <+56>:	   call   0x8054680 <getegid>
   0x08048f01 <+65>:	   call   0x8054670 <geteuid>
   0x08048f21 <+97>:	   call   0x8054700 <setresgid>
   0x08048f3d <+125>:	call   0x8054690 <setresuid>
   0x08048f51 <+145>:	call   0x8054640 <execv>
   (...)
...
End of assembler dump.

(gdb) quit
```

Le binaire appel un simple `atoi` et le `cmp` avec `0x1a7 = 423`

```
:~$ ./level0 423
```

(...) -> Après sa comparaison, le programme appelle un setuid, un getuid puis un execv pour lancer un nouveau process /bin/sh

```
$ pwd
/home/user/level0

$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a

$ exit

```
