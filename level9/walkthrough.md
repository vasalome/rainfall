# Level9

> login:password -> *`level9:c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a`*
```
:~$ su level9
Password:c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```
---

```
:~$ pwd
/home/user/level9
```

```
:~$ ls -la
BLABLABLA
```

Le Home contient un binaire `level9` :

```
:~$ ./level9

:~$ ./level9 test

:~$ ./level9 test test
```

Avec ou sans paramètre, le binaire ne donne rien

```
:~$ gdb level9
...

(gdb) disas main
Dump of assembler code for function main:

```
