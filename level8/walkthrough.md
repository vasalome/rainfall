# Level8

> login:password -> *`level8:5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9`*
```
:~$ su level8
Password:5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
```
---

```
:~$ pwd
/home/user/level8
```

```
:~$ ls -la
total 17
dr-xr-x---+ 1 level8 level8   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level8 level8  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level8 level8 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level9 users  6057 Mar  6  2016 level8
-rw-r--r--+ 1 level8 level8   65 Sep 23  2015 .pass
-rw-r--r--  1 level8 level8  675 Apr  3  2012 .profile
```

Le Home contient un binaire `level8` :

```
:~$ ./level8
(nil), (nil)
(input) test
(nil), (nil)

:~$ ./level8 test
(nil), (nil)
(input)
```

Avec ou sans paramètre le binaire renvoie `(nil), (nil)` et attends un input.

```
:~$ gdb level7
...

(gdb) disas main
Dump of assembler code for function main:
```