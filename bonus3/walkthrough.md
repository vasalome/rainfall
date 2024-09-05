# Bonus3

> login:password -> *`bonus3:71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587`*
```
:~$ su bonus3
Password:71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```
---

```
:~$ pwd
/home/user/bonus3
```

```
:~$ ls -la
total 17
dr-xr-x---+ 1 bonus3 bonus3   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 bonus3 bonus3  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 bonus3 bonus3 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 end    users  5595 Mar  6  2016 bonus3
-rw-r--r--+ 1 bonus3 bonus3   65 Sep 23  2015 .pass
-rw-r--r--  1 bonus3 bonus3  675 Apr  3  2012 .profile
```

Le Home contient un binaire `bonus3` :

```
:~$ ./bonus3

:~$ ./bonus3 test
(...)

:~$ ./bonus3 test1 test2
```

Quand le binaire a 1 paramètre, il nous affiche une reponse

```
:~$ gdb bonus3
...

(gdb) disas main
Dump of assembler code for function main:
   0x080484f4 <+0>:	push   %ebp
   0x080484f5 <+1>:	mov    %esp,%ebp
   0x080484f7 <+3>:	push   %edi
   0x080484f8 <+4>:	push   %ebx
   0x080484f9 <+5>:	and    $0xfffffff0,%esp
   0x080484fc <+8>:	sub    $0xa0,%esp
   0x08048502 <+14>:	mov    $0x80486f0,%edx
   0x08048507 <+19>:	mov    $0x80486f2,%eax
   0x0804850c <+24>:	mov    %edx,0x4(%esp)
   0x08048510 <+28>:	mov    %eax,(%esp)
   0x08048513 <+31>:	call   0x8048410 <fopen@plt>
   0x08048518 <+36>:	mov    %eax,0x9c(%esp)
   0x0804851f <+43>:	lea    0x18(%esp),%ebx
   0x08048523 <+47>:	mov    $0x0,%eax
   0x08048528 <+52>:	mov    $0x21,%edx
   0x0804852d <+57>:	mov    %ebx,%edi
   0x0804852f <+59>:	mov    %edx,%ecx
   0x08048531 <+61>:	rep stos %eax,%es:(%edi)
   0x08048533 <+63>:	cmpl   $0x0,0x9c(%esp)
   0x0804853b <+71>:	je     0x8048543 <main+79>
   0x0804853d <+73>:	cmpl   $0x2,0x8(%ebp)
   0x08048541 <+77>:	je     0x804854d <main+89>
   0x08048543 <+79>:	mov    $0xffffffff,%eax
   0x08048548 <+84>:	jmp    0x8048615 <main+289>
   0x0804854d <+89>:	lea    0x18(%esp),%eax
   0x08048551 <+93>:	mov    0x9c(%esp),%edx
   0x08048558 <+100>:	mov    %edx,0xc(%esp)
   0x0804855c <+104>:	movl   $0x42,0x8(%esp)
   0x08048564 <+112>:	movl   $0x1,0x4(%esp)
   0x0804856c <+120>:	mov    %eax,(%esp)
   0x0804856f <+123>:	call   0x80483d0 <fread@plt>
   0x08048574 <+128>:	movb   $0x0,0x59(%esp)
   0x08048579 <+133>:	mov    0xc(%ebp),%eax
   0x0804857c <+136>:	add    $0x4,%eax
   0x0804857f <+139>:	mov    (%eax),%eax
   0x08048581 <+141>:	mov    %eax,(%esp)
   0x08048584 <+144>:	call   0x8048430 <atoi@plt>
   0x08048589 <+149>:	movb   $0x0,0x18(%esp,%eax,1)
   0x0804858e <+154>:	lea    0x18(%esp),%eax
   0x08048592 <+158>:	lea    0x42(%eax),%edx
   0x08048595 <+161>:	mov    0x9c(%esp),%eax
   0x0804859c <+168>:	mov    %eax,0xc(%esp)
   0x080485a0 <+172>:	movl   $0x41,0x8(%esp)
   0x080485a8 <+180>:	movl   $0x1,0x4(%esp)
   0x080485b0 <+188>:	mov    %edx,(%esp)
   0x080485b3 <+191>:	call   0x80483d0 <fread@plt>
   0x080485b8 <+196>:	mov    0x9c(%esp),%eax
   0x080485bf <+203>:	mov    %eax,(%esp)
   0x080485c2 <+206>:	call   0x80483c0 <fclose@plt>
   0x080485c7 <+211>:	mov    0xc(%ebp),%eax
   0x080485ca <+214>:	add    $0x4,%eax
   0x080485cd <+217>:	mov    (%eax),%eax
   0x080485cf <+219>:	mov    %eax,0x4(%esp)
   0x080485d3 <+223>:	lea    0x18(%esp),%eax
   0x080485d7 <+227>:	mov    %eax,(%esp)
   0x080485da <+230>:	call   0x80483b0 <strcmp@plt>
   0x080485df <+235>:	test   %eax,%eax
   0x080485e1 <+237>:	jne    0x8048601 <main+269>
   0x080485e3 <+239>:	movl   $0x0,0x8(%esp)
   0x080485eb <+247>:	movl   $0x8048707,0x4(%esp)
   0x080485f3 <+255>:	movl   $0x804870a,(%esp)
   0x080485fa <+262>:	call   0x8048420 <execl@plt>
   0x080485ff <+267>:	jmp    0x8048610 <main+284>
   0x08048601 <+269>:	lea    0x18(%esp),%eax
   0x08048605 <+273>:	add    $0x42,%eax
   0x08048608 <+276>:	mov    %eax,(%esp)
   0x0804860b <+279>:	call   0x80483e0 <puts@plt>
   0x08048610 <+284>:	mov    $0x0,%eax
   0x08048615 <+289>:	lea    -0x8(%ebp),%esp
   0x08048618 <+292>:	pop    %ebx
   0x08048619 <+293>:	pop    %edi
   0x0804861a <+294>:	pop    %ebp
   0x0804861b <+295>:	ret    
End of assembler dump.
```

On remarque 














as we notice after creat the stack function they try to read a file by fopen we check the params they give to fopen we found r read mode, /home/user/end/.pass.

when we try with gdb we can't read the file /home/user/end/.pass so we try to set a file to understand what happend next.

(gdb) set $eax="/home/user/bonus3/test"
(gdb) in r
Ambiguous command "in r": inf, inferior, info, init-if-undefined, inspect, internals, interpreter-exec, interrupt.
(gdb) i r
eax            0x804a008	134520840
ecx            0xbffff7a4	-1073743964
edx            0x80486f0	134514416
ebx            0xb7fd0ff4	-1208152076
esp            0xbffff660	0xbffff660
ebp            0xbffff708	0xbffff708
esi            0x0	0
edi            0x0	0
eip            0x8048513	0x8048513 <main+31>
eflags         0x200286	[ PF SF IF ID ]
cs             0x73	115
ss             0x7b	123
ds             0x7b	123
es             0x7b	123
fs             0x0	0
gs             0x33	51
(gdb) x/s 0x804a008
0x804a008:	 "/home/user/bonus3/test"
   0x08048551 <+93>:	mov    edx,DWORD PTR [esp+0x9c]
   0x08048558 <+100>:	mov    DWORD PTR [esp+0xc],edx
   0x0804855c <+104>:	mov    DWORD PTR [esp+0x8],0x42
   0x08048564 <+112>:	mov    DWORD PTR [esp+0x4],0x1
   0x0804856c <+120>:	mov    DWORD PTR [esp],eax
   0x0804856f <+123>:	call   0x80483d0 <fread@plt>
in this part we read the file and we store it into esp+0x18 then we found call atoi (av[1]) and set 0 to [esp+eax*1+0x18].

call fread again and then call strcmp compare between [esp+0x18] and argv[1] so if we give a as argument 0 will set on [esp + 0 * 1 + 0x18] = '\0' and compare it with [esp+0x18] as we know when we give a string to atoi return 0 but 0 != '\0' so we give it a empty string and we got :

bonus3@RainFall:~$ ./bonus3 ''
$ whoami
end
$
