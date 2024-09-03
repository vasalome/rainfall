# Bonus0

> login:password -> *`bonus0:f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728`*
```
:~$ su bonus0
Password:f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```
---

```
:~$ pwd
/home/user/bonus0
```

```
:~$ ls -la
dr-xr-x---+ 1 level9 level9   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level9 level9  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level9 level9 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 bonus0 users  6720 Mar  6  2016 level9
-rw-r--r--+ 1 level9 level9   65 Sep 23  2015 .pass
-rw-r--r--  1 level9 level9  675 Apr  3  2012 .profile
```

Le Home contient un binaire `level9` :

```
:~$ ./level9

:~$ ./level9 test

:~$ ./level9 test test
```

Avec ou sans paramètre, le binaire ne donne rien

```
:~$
```