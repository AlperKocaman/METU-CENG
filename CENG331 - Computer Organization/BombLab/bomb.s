
bomb:     file format elf64-x86-64


Disassembly of section .init:

0000000000001818 <_init>:
    1818:	48 83 ec 08          	sub    $0x8,%rsp
    181c:	48 8b 05 c5 37 20 00 	mov    0x2037c5(%rip),%rax        # 204fe8 <__gmon_start__>
    1823:	48 85 c0             	test   %rax,%rax
    1826:	74 02                	je     182a <_init+0x12>
    1828:	ff d0                	callq  *%rax
    182a:	48 83 c4 08          	add    $0x8,%rsp
    182e:	c3                   	retq   

Disassembly of section .plt:

0000000000001830 <.plt>:
    1830:	ff 35 b2 36 20 00    	pushq  0x2036b2(%rip)        # 204ee8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1836:	ff 25 b4 36 20 00    	jmpq   *0x2036b4(%rip)        # 204ef0 <_GLOBAL_OFFSET_TABLE_+0x10>
    183c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001840 <__strcat_chk@plt>:
    1840:	ff 25 b2 36 20 00    	jmpq   *0x2036b2(%rip)        # 204ef8 <__strcat_chk@GLIBC_2.3.4>
    1846:	68 00 00 00 00       	pushq  $0x0
    184b:	e9 e0 ff ff ff       	jmpq   1830 <.plt>

0000000000001850 <getenv@plt>:
    1850:	ff 25 aa 36 20 00    	jmpq   *0x2036aa(%rip)        # 204f00 <getenv@GLIBC_2.2.5>
    1856:	68 01 00 00 00       	pushq  $0x1
    185b:	e9 d0 ff ff ff       	jmpq   1830 <.plt>

0000000000001860 <strcasecmp@plt>:
    1860:	ff 25 a2 36 20 00    	jmpq   *0x2036a2(%rip)        # 204f08 <strcasecmp@GLIBC_2.2.5>
    1866:	68 02 00 00 00       	pushq  $0x2
    186b:	e9 c0 ff ff ff       	jmpq   1830 <.plt>

0000000000001870 <__errno_location@plt>:
    1870:	ff 25 9a 36 20 00    	jmpq   *0x20369a(%rip)        # 204f10 <__errno_location@GLIBC_2.2.5>
    1876:	68 03 00 00 00       	pushq  $0x3
    187b:	e9 b0 ff ff ff       	jmpq   1830 <.plt>

0000000000001880 <strcpy@plt>:
    1880:	ff 25 92 36 20 00    	jmpq   *0x203692(%rip)        # 204f18 <strcpy@GLIBC_2.2.5>
    1886:	68 04 00 00 00       	pushq  $0x4
    188b:	e9 a0 ff ff ff       	jmpq   1830 <.plt>

0000000000001890 <puts@plt>:
    1890:	ff 25 8a 36 20 00    	jmpq   *0x20368a(%rip)        # 204f20 <puts@GLIBC_2.2.5>
    1896:	68 05 00 00 00       	pushq  $0x5
    189b:	e9 90 ff ff ff       	jmpq   1830 <.plt>

00000000000018a0 <write@plt>:
    18a0:	ff 25 82 36 20 00    	jmpq   *0x203682(%rip)        # 204f28 <write@GLIBC_2.2.5>
    18a6:	68 06 00 00 00       	pushq  $0x6
    18ab:	e9 80 ff ff ff       	jmpq   1830 <.plt>

00000000000018b0 <__stack_chk_fail@plt>:
    18b0:	ff 25 7a 36 20 00    	jmpq   *0x20367a(%rip)        # 204f30 <__stack_chk_fail@GLIBC_2.4>
    18b6:	68 07 00 00 00       	pushq  $0x7
    18bb:	e9 70 ff ff ff       	jmpq   1830 <.plt>

00000000000018c0 <alarm@plt>:
    18c0:	ff 25 72 36 20 00    	jmpq   *0x203672(%rip)        # 204f38 <alarm@GLIBC_2.2.5>
    18c6:	68 08 00 00 00       	pushq  $0x8
    18cb:	e9 60 ff ff ff       	jmpq   1830 <.plt>

00000000000018d0 <close@plt>:
    18d0:	ff 25 6a 36 20 00    	jmpq   *0x20366a(%rip)        # 204f40 <close@GLIBC_2.2.5>
    18d6:	68 09 00 00 00       	pushq  $0x9
    18db:	e9 50 ff ff ff       	jmpq   1830 <.plt>

00000000000018e0 <read@plt>:
    18e0:	ff 25 62 36 20 00    	jmpq   *0x203662(%rip)        # 204f48 <read@GLIBC_2.2.5>
    18e6:	68 0a 00 00 00       	pushq  $0xa
    18eb:	e9 40 ff ff ff       	jmpq   1830 <.plt>

00000000000018f0 <fgets@plt>:
    18f0:	ff 25 5a 36 20 00    	jmpq   *0x20365a(%rip)        # 204f50 <fgets@GLIBC_2.2.5>
    18f6:	68 0b 00 00 00       	pushq  $0xb
    18fb:	e9 30 ff ff ff       	jmpq   1830 <.plt>

0000000000001900 <signal@plt>:
    1900:	ff 25 52 36 20 00    	jmpq   *0x203652(%rip)        # 204f58 <signal@GLIBC_2.2.5>
    1906:	68 0c 00 00 00       	pushq  $0xc
    190b:	e9 20 ff ff ff       	jmpq   1830 <.plt>

0000000000001910 <gethostbyname@plt>:
    1910:	ff 25 4a 36 20 00    	jmpq   *0x20364a(%rip)        # 204f60 <gethostbyname@GLIBC_2.2.5>
    1916:	68 0d 00 00 00       	pushq  $0xd
    191b:	e9 10 ff ff ff       	jmpq   1830 <.plt>

0000000000001920 <__memmove_chk@plt>:
    1920:	ff 25 42 36 20 00    	jmpq   *0x203642(%rip)        # 204f68 <__memmove_chk@GLIBC_2.3.4>
    1926:	68 0e 00 00 00       	pushq  $0xe
    192b:	e9 00 ff ff ff       	jmpq   1830 <.plt>

0000000000001930 <strtol@plt>:
    1930:	ff 25 3a 36 20 00    	jmpq   *0x20363a(%rip)        # 204f70 <strtol@GLIBC_2.2.5>
    1936:	68 0f 00 00 00       	pushq  $0xf
    193b:	e9 f0 fe ff ff       	jmpq   1830 <.plt>

0000000000001940 <fflush@plt>:
    1940:	ff 25 32 36 20 00    	jmpq   *0x203632(%rip)        # 204f78 <fflush@GLIBC_2.2.5>
    1946:	68 10 00 00 00       	pushq  $0x10
    194b:	e9 e0 fe ff ff       	jmpq   1830 <.plt>

0000000000001950 <__isoc99_sscanf@plt>:
    1950:	ff 25 2a 36 20 00    	jmpq   *0x20362a(%rip)        # 204f80 <__isoc99_sscanf@GLIBC_2.7>
    1956:	68 11 00 00 00       	pushq  $0x11
    195b:	e9 d0 fe ff ff       	jmpq   1830 <.plt>

0000000000001960 <__printf_chk@plt>:
    1960:	ff 25 22 36 20 00    	jmpq   *0x203622(%rip)        # 204f88 <__printf_chk@GLIBC_2.3.4>
    1966:	68 12 00 00 00       	pushq  $0x12
    196b:	e9 c0 fe ff ff       	jmpq   1830 <.plt>

0000000000001970 <fopen@plt>:
    1970:	ff 25 1a 36 20 00    	jmpq   *0x20361a(%rip)        # 204f90 <fopen@GLIBC_2.2.5>
    1976:	68 13 00 00 00       	pushq  $0x13
    197b:	e9 b0 fe ff ff       	jmpq   1830 <.plt>

0000000000001980 <gethostname@plt>:
    1980:	ff 25 12 36 20 00    	jmpq   *0x203612(%rip)        # 204f98 <gethostname@GLIBC_2.2.5>
    1986:	68 14 00 00 00       	pushq  $0x14
    198b:	e9 a0 fe ff ff       	jmpq   1830 <.plt>

0000000000001990 <exit@plt>:
    1990:	ff 25 0a 36 20 00    	jmpq   *0x20360a(%rip)        # 204fa0 <exit@GLIBC_2.2.5>
    1996:	68 15 00 00 00       	pushq  $0x15
    199b:	e9 90 fe ff ff       	jmpq   1830 <.plt>

00000000000019a0 <connect@plt>:
    19a0:	ff 25 02 36 20 00    	jmpq   *0x203602(%rip)        # 204fa8 <connect@GLIBC_2.2.5>
    19a6:	68 16 00 00 00       	pushq  $0x16
    19ab:	e9 80 fe ff ff       	jmpq   1830 <.plt>

00000000000019b0 <__fprintf_chk@plt>:
    19b0:	ff 25 fa 35 20 00    	jmpq   *0x2035fa(%rip)        # 204fb0 <__fprintf_chk@GLIBC_2.3.4>
    19b6:	68 17 00 00 00       	pushq  $0x17
    19bb:	e9 70 fe ff ff       	jmpq   1830 <.plt>

00000000000019c0 <sleep@plt>:
    19c0:	ff 25 f2 35 20 00    	jmpq   *0x2035f2(%rip)        # 204fb8 <sleep@GLIBC_2.2.5>
    19c6:	68 18 00 00 00       	pushq  $0x18
    19cb:	e9 60 fe ff ff       	jmpq   1830 <.plt>

00000000000019d0 <__ctype_b_loc@plt>:
    19d0:	ff 25 ea 35 20 00    	jmpq   *0x2035ea(%rip)        # 204fc0 <__ctype_b_loc@GLIBC_2.3>
    19d6:	68 19 00 00 00       	pushq  $0x19
    19db:	e9 50 fe ff ff       	jmpq   1830 <.plt>

00000000000019e0 <__sprintf_chk@plt>:
    19e0:	ff 25 e2 35 20 00    	jmpq   *0x2035e2(%rip)        # 204fc8 <__sprintf_chk@GLIBC_2.3.4>
    19e6:	68 1a 00 00 00       	pushq  $0x1a
    19eb:	e9 40 fe ff ff       	jmpq   1830 <.plt>

00000000000019f0 <socket@plt>:
    19f0:	ff 25 da 35 20 00    	jmpq   *0x2035da(%rip)        # 204fd0 <socket@GLIBC_2.2.5>
    19f6:	68 1b 00 00 00       	pushq  $0x1b
    19fb:	e9 30 fe ff ff       	jmpq   1830 <.plt>

Disassembly of section .plt.got:

0000000000001a00 <__cxa_finalize@plt>:
    1a00:	ff 25 f2 35 20 00    	jmpq   *0x2035f2(%rip)        # 204ff8 <__cxa_finalize@GLIBC_2.2.5>
    1a06:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000001a10 <_start>:
    1a10:	31 ed                	xor    %ebp,%ebp
    1a12:	49 89 d1             	mov    %rdx,%r9
    1a15:	5e                   	pop    %rsi
    1a16:	48 89 e2             	mov    %rsp,%rdx
    1a19:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1a1d:	50                   	push   %rax
    1a1e:	54                   	push   %rsp
    1a1f:	4c 8d 05 4a 1a 00 00 	lea    0x1a4a(%rip),%r8        # 3470 <__libc_csu_fini>
    1a26:	48 8d 0d d3 19 00 00 	lea    0x19d3(%rip),%rcx        # 3400 <__libc_csu_init>
    1a2d:	48 8d 3d e6 00 00 00 	lea    0xe6(%rip),%rdi        # 1b1a <main>
    1a34:	ff 15 a6 35 20 00    	callq  *0x2035a6(%rip)        # 204fe0 <__libc_start_main@GLIBC_2.2.5>
    1a3a:	f4                   	hlt    
    1a3b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001a40 <deregister_tm_clones>:
    1a40:	48 8d 3d 39 3c 20 00 	lea    0x203c39(%rip),%rdi        # 205680 <stdout@@GLIBC_2.2.5>
    1a47:	55                   	push   %rbp
    1a48:	48 8d 05 31 3c 20 00 	lea    0x203c31(%rip),%rax        # 205680 <stdout@@GLIBC_2.2.5>
    1a4f:	48 39 f8             	cmp    %rdi,%rax
    1a52:	48 89 e5             	mov    %rsp,%rbp
    1a55:	74 19                	je     1a70 <deregister_tm_clones+0x30>
    1a57:	48 8b 05 7a 35 20 00 	mov    0x20357a(%rip),%rax        # 204fd8 <_ITM_deregisterTMCloneTable>
    1a5e:	48 85 c0             	test   %rax,%rax
    1a61:	74 0d                	je     1a70 <deregister_tm_clones+0x30>
    1a63:	5d                   	pop    %rbp
    1a64:	ff e0                	jmpq   *%rax
    1a66:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    1a6d:	00 00 00 
    1a70:	5d                   	pop    %rbp
    1a71:	c3                   	retq   
    1a72:	0f 1f 40 00          	nopl   0x0(%rax)
    1a76:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    1a7d:	00 00 00 

0000000000001a80 <register_tm_clones>:
    1a80:	48 8d 3d f9 3b 20 00 	lea    0x203bf9(%rip),%rdi        # 205680 <stdout@@GLIBC_2.2.5>
    1a87:	48 8d 35 f2 3b 20 00 	lea    0x203bf2(%rip),%rsi        # 205680 <stdout@@GLIBC_2.2.5>
    1a8e:	55                   	push   %rbp
    1a8f:	48 29 fe             	sub    %rdi,%rsi
    1a92:	48 89 e5             	mov    %rsp,%rbp
    1a95:	48 c1 fe 03          	sar    $0x3,%rsi
    1a99:	48 89 f0             	mov    %rsi,%rax
    1a9c:	48 c1 e8 3f          	shr    $0x3f,%rax
    1aa0:	48 01 c6             	add    %rax,%rsi
    1aa3:	48 d1 fe             	sar    %rsi
    1aa6:	74 18                	je     1ac0 <register_tm_clones+0x40>
    1aa8:	48 8b 05 41 35 20 00 	mov    0x203541(%rip),%rax        # 204ff0 <_ITM_registerTMCloneTable>
    1aaf:	48 85 c0             	test   %rax,%rax
    1ab2:	74 0c                	je     1ac0 <register_tm_clones+0x40>
    1ab4:	5d                   	pop    %rbp
    1ab5:	ff e0                	jmpq   *%rax
    1ab7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
    1abe:	00 00 
    1ac0:	5d                   	pop    %rbp
    1ac1:	c3                   	retq   
    1ac2:	0f 1f 40 00          	nopl   0x0(%rax)
    1ac6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    1acd:	00 00 00 

0000000000001ad0 <__do_global_dtors_aux>:
    1ad0:	80 3d d1 3b 20 00 00 	cmpb   $0x0,0x203bd1(%rip)        # 2056a8 <completed.7696>
    1ad7:	75 2f                	jne    1b08 <__do_global_dtors_aux+0x38>
    1ad9:	48 83 3d 17 35 20 00 	cmpq   $0x0,0x203517(%rip)        # 204ff8 <__cxa_finalize@GLIBC_2.2.5>
    1ae0:	00 
    1ae1:	55                   	push   %rbp
    1ae2:	48 89 e5             	mov    %rsp,%rbp
    1ae5:	74 0c                	je     1af3 <__do_global_dtors_aux+0x23>
    1ae7:	48 8b 3d 1a 35 20 00 	mov    0x20351a(%rip),%rdi        # 205008 <__dso_handle>
    1aee:	e8 0d ff ff ff       	callq  1a00 <__cxa_finalize@plt>
    1af3:	e8 48 ff ff ff       	callq  1a40 <deregister_tm_clones>
    1af8:	c6 05 a9 3b 20 00 01 	movb   $0x1,0x203ba9(%rip)        # 2056a8 <completed.7696>
    1aff:	5d                   	pop    %rbp
    1b00:	c3                   	retq   
    1b01:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1b08:	f3 c3                	repz retq 
    1b0a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001b10 <frame_dummy>:
    1b10:	55                   	push   %rbp
    1b11:	48 89 e5             	mov    %rsp,%rbp
    1b14:	5d                   	pop    %rbp
    1b15:	e9 66 ff ff ff       	jmpq   1a80 <register_tm_clones>

0000000000001b1a <main>:
    1b1a:	53                   	push   %rbx
    1b1b:	83 ff 01             	cmp    $0x1,%edi
    1b1e:	0f 84 f8 00 00 00    	je     1c1c <main+0x102>
    1b24:	48 89 f3             	mov    %rsi,%rbx
    1b27:	83 ff 02             	cmp    $0x2,%edi
    1b2a:	0f 85 21 01 00 00    	jne    1c51 <main+0x137>
    1b30:	48 8b 7e 08          	mov    0x8(%rsi),%rdi
    1b34:	48 8d 35 6a 22 00 00 	lea    0x226a(%rip),%rsi        # 3da5 <array.3434+0x745>
    1b3b:	e8 30 fe ff ff       	callq  1970 <fopen@plt>
    1b40:	48 89 05 69 3b 20 00 	mov    %rax,0x203b69(%rip)        # 2056b0 <infile>
    1b47:	48 85 c0             	test   %rax,%rax
    1b4a:	0f 84 df 00 00 00    	je     1c2f <main+0x115>
    1b50:	e8 ac 07 00 00       	callq  2301 <initialize_bomb>
    1b55:	48 8d 3d ac 19 00 00 	lea    0x19ac(%rip),%rdi        # 3508 <_IO_stdin_used+0x88>
    1b5c:	e8 2f fd ff ff       	callq  1890 <puts@plt>
    1b61:	48 8d 3d e0 19 00 00 	lea    0x19e0(%rip),%rdi        # 3548 <_IO_stdin_used+0xc8>
    1b68:	e8 23 fd ff ff       	callq  1890 <puts@plt>
    1b6d:	e8 a9 0a 00 00       	callq  261b <read_line>
    1b72:	48 89 c7             	mov    %rax,%rdi
    1b75:	e8 fa 00 00 00       	callq  1c74 <phase_1>
    1b7a:	e8 e0 0b 00 00       	callq  275f <phase_defused>
    1b7f:	48 8d 3d f2 19 00 00 	lea    0x19f2(%rip),%rdi        # 3578 <_IO_stdin_used+0xf8>
    1b86:	e8 05 fd ff ff       	callq  1890 <puts@plt>
    1b8b:	e8 8b 0a 00 00       	callq  261b <read_line>
    1b90:	48 89 c7             	mov    %rax,%rdi
    1b93:	e8 9e 01 00 00       	callq  1d36 <phase_2>
    1b98:	e8 c2 0b 00 00       	callq  275f <phase_defused>
    1b9d:	48 8d 3d 17 19 00 00 	lea    0x1917(%rip),%rdi        # 34bb <_IO_stdin_used+0x3b>
    1ba4:	e8 e7 fc ff ff       	callq  1890 <puts@plt>
    1ba9:	e8 6d 0a 00 00       	callq  261b <read_line>
    1bae:	48 89 c7             	mov    %rax,%rdi
    1bb1:	e8 ef 01 00 00       	callq  1da5 <phase_3>
    1bb6:	e8 a4 0b 00 00       	callq  275f <phase_defused>
    1bbb:	48 8d 3d 17 19 00 00 	lea    0x1917(%rip),%rdi        # 34d9 <_IO_stdin_used+0x59>
    1bc2:	e8 c9 fc ff ff       	callq  1890 <puts@plt>
    1bc7:	e8 4f 0a 00 00       	callq  261b <read_line>
    1bcc:	48 89 c7             	mov    %rax,%rdi
    1bcf:	e8 c0 02 00 00       	callq  1e94 <phase_4>
    1bd4:	e8 86 0b 00 00       	callq  275f <phase_defused>
    1bd9:	48 8d 3d c8 19 00 00 	lea    0x19c8(%rip),%rdi        # 35a8 <_IO_stdin_used+0x128>
    1be0:	e8 ab fc ff ff       	callq  1890 <puts@plt>
    1be5:	e8 31 0a 00 00       	callq  261b <read_line>
    1bea:	48 89 c7             	mov    %rax,%rdi
    1bed:	e8 39 03 00 00       	callq  1f2b <phase_5>
    1bf2:	e8 68 0b 00 00       	callq  275f <phase_defused>
    1bf7:	48 8d 3d ea 18 00 00 	lea    0x18ea(%rip),%rdi        # 34e8 <_IO_stdin_used+0x68>
    1bfe:	e8 8d fc ff ff       	callq  1890 <puts@plt>
    1c03:	e8 13 0a 00 00       	callq  261b <read_line>
    1c08:	48 89 c7             	mov    %rax,%rdi
    1c0b:	e8 89 03 00 00       	callq  1f99 <phase_6>
    1c10:	e8 4a 0b 00 00       	callq  275f <phase_defused>
    1c15:	b8 00 00 00 00       	mov    $0x0,%eax
    1c1a:	5b                   	pop    %rbx
    1c1b:	c3                   	retq   
    1c1c:	48 8b 05 6d 3a 20 00 	mov    0x203a6d(%rip),%rax        # 205690 <stdin@@GLIBC_2.2.5>
    1c23:	48 89 05 86 3a 20 00 	mov    %rax,0x203a86(%rip)        # 2056b0 <infile>
    1c2a:	e9 21 ff ff ff       	jmpq   1b50 <main+0x36>
    1c2f:	48 8b 4b 08          	mov    0x8(%rbx),%rcx
    1c33:	48 8b 13             	mov    (%rbx),%rdx
    1c36:	48 8d 35 47 18 00 00 	lea    0x1847(%rip),%rsi        # 3484 <_IO_stdin_used+0x4>
    1c3d:	bf 01 00 00 00       	mov    $0x1,%edi
    1c42:	e8 19 fd ff ff       	callq  1960 <__printf_chk@plt>
    1c47:	bf 08 00 00 00       	mov    $0x8,%edi
    1c4c:	e8 3f fd ff ff       	callq  1990 <exit@plt>
    1c51:	48 8b 16             	mov    (%rsi),%rdx
    1c54:	48 8d 35 46 18 00 00 	lea    0x1846(%rip),%rsi        # 34a1 <_IO_stdin_used+0x21>
    1c5b:	bf 01 00 00 00       	mov    $0x1,%edi
    1c60:	b8 00 00 00 00       	mov    $0x0,%eax
    1c65:	e8 f6 fc ff ff       	callq  1960 <__printf_chk@plt>
    1c6a:	bf 08 00 00 00       	mov    $0x8,%edi
    1c6f:	e8 1c fd ff ff       	callq  1990 <exit@plt>

0000000000001c74 <phase_1>:
    1c74:	55                   	push   %rbp
    1c75:	53                   	push   %rbx
    1c76:	48 83 ec 68          	sub    $0x68,%rsp
    1c7a:	48 89 fd             	mov    %rdi,%rbp
    1c7d:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1c84:	00 00 
    1c86:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
    1c8b:	31 c0                	xor    %eax,%eax
    1c8d:	48 b8 4d 79 20 74 65 	movabs $0x207478657420794d,%rax
    1c94:	78 74 20 
    1c97:	ba 69 73 20 00       	mov    $0x207369,%edx
    1c9c:	48 89 04 24          	mov    %rax,(%rsp)
    1ca0:	48 89 54 24 08       	mov    %rdx,0x8(%rsp)
    1ca5:	48 c7 44 24 10 00 00 	movq   $0x0,0x10(%rsp)
    1cac:	00 00 
    1cae:	48 c7 44 24 18 00 00 	movq   $0x0,0x18(%rsp)
    1cb5:	00 00 
    1cb7:	48 c7 44 24 20 00 00 	movq   $0x0,0x20(%rsp)
    1cbe:	00 00 
    1cc0:	48 c7 44 24 28 00 00 	movq   $0x0,0x28(%rsp)
    1cc7:	00 00 
    1cc9:	48 c7 44 24 30 00 00 	movq   $0x0,0x30(%rsp)
    1cd0:	00 00 
    1cd2:	48 c7 44 24 38 00 00 	movq   $0x0,0x38(%rsp)
    1cd9:	00 00 
    1cdb:	48 c7 44 24 40 00 00 	movq   $0x0,0x40(%rsp)
    1ce2:	00 00 
    1ce4:	48 c7 44 24 48 00 00 	movq   $0x0,0x48(%rsp)
    1ceb:	00 00 
    1ced:	48 89 e3             	mov    %rsp,%rbx
    1cf0:	ba 50 00 00 00       	mov    $0x50,%edx
    1cf5:	48 8d 35 d4 18 00 00 	lea    0x18d4(%rip),%rsi        # 35d0 <_IO_stdin_used+0x150>
    1cfc:	48 89 df             	mov    %rbx,%rdi
    1cff:	e8 3c fb ff ff       	callq  1840 <__strcat_chk@plt>
    1d04:	48 89 de             	mov    %rbx,%rsi
    1d07:	48 89 ef             	mov    %rbp,%rdi
    1d0a:	e8 6f 05 00 00       	callq  227e <strings_not_equal>
    1d0f:	85 c0                	test   %eax,%eax
    1d11:	75 17                	jne    1d2a <phase_1+0xb6>
    1d13:	48 8b 44 24 58       	mov    0x58(%rsp),%rax
    1d18:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
    1d1f:	00 00 
    1d21:	75 0e                	jne    1d31 <phase_1+0xbd>
    1d23:	48 83 c4 68          	add    $0x68,%rsp
    1d27:	5b                   	pop    %rbx
    1d28:	5d                   	pop    %rbp
    1d29:	c3                   	retq   
    1d2a:	e8 6f 08 00 00       	callq  259e <explode_bomb>
    1d2f:	eb e2                	jmp    1d13 <phase_1+0x9f>
    1d31:	e8 7a fb ff ff       	callq  18b0 <__stack_chk_fail@plt>

0000000000001d36 <phase_2>:
    1d36:	55                   	push   %rbp
    1d37:	53                   	push   %rbx
    1d38:	48 83 ec 28          	sub    $0x28,%rsp
    1d3c:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1d43:	00 00 
    1d45:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
    1d4a:	31 c0                	xor    %eax,%eax
    1d4c:	48 89 e6             	mov    %rsp,%rsi
    1d4f:	e8 86 08 00 00       	callq  25da <read_six_numbers>
    1d54:	83 3c 24 00          	cmpl   $0x0,(%rsp)
    1d58:	78 0a                	js     1d64 <phase_2+0x2e>
    1d5a:	bb 01 00 00 00       	mov    $0x1,%ebx
    1d5f:	48 89 e5             	mov    %rsp,%rbp
    1d62:	eb 11                	jmp    1d75 <phase_2+0x3f>
    1d64:	e8 35 08 00 00       	callq  259e <explode_bomb>
    1d69:	eb ef                	jmp    1d5a <phase_2+0x24>
    1d6b:	48 83 c3 01          	add    $0x1,%rbx
    1d6f:	48 83 fb 06          	cmp    $0x6,%rbx
    1d73:	74 14                	je     1d89 <phase_2+0x53>
    1d75:	89 d8                	mov    %ebx,%eax
    1d77:	0f af 44 9d fc       	imul   -0x4(%rbp,%rbx,4),%eax
    1d7c:	39 44 9d 00          	cmp    %eax,0x0(%rbp,%rbx,4)
    1d80:	74 e9                	je     1d6b <phase_2+0x35>
    1d82:	e8 17 08 00 00       	callq  259e <explode_bomb>
    1d87:	eb e2                	jmp    1d6b <phase_2+0x35>
    1d89:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
    1d8e:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
    1d95:	00 00 
    1d97:	75 07                	jne    1da0 <phase_2+0x6a>
    1d99:	48 83 c4 28          	add    $0x28,%rsp
    1d9d:	5b                   	pop    %rbx
    1d9e:	5d                   	pop    %rbp
    1d9f:	c3                   	retq   
    1da0:	e8 0b fb ff ff       	callq  18b0 <__stack_chk_fail@plt>

0000000000001da5 <phase_3>:
    1da5:	48 83 ec 28          	sub    $0x28,%rsp
    1da9:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1db0:	00 00 
    1db2:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
    1db7:	31 c0                	xor    %eax,%eax
    1db9:	48 8d 4c 24 10       	lea    0x10(%rsp),%rcx
    1dbe:	48 8d 54 24 0c       	lea    0xc(%rsp),%rdx
    1dc3:	4c 8d 44 24 14       	lea    0x14(%rsp),%r8
    1dc8:	48 8d 35 1b 1b 00 00 	lea    0x1b1b(%rip),%rsi        # 38ea <array.3434+0x28a>
    1dcf:	e8 7c fb ff ff       	callq  1950 <__isoc99_sscanf@plt>
    1dd4:	83 f8 02             	cmp    $0x2,%eax
    1dd7:	7e 1b                	jle    1df4 <phase_3+0x4f>
    1dd9:	83 7c 24 0c 07       	cmpl   $0x7,0xc(%rsp)
    1dde:	77 4c                	ja     1e2c <phase_3+0x87>
    1de0:	8b 44 24 0c          	mov    0xc(%rsp),%eax
    1de4:	48 8d 15 55 18 00 00 	lea    0x1855(%rip),%rdx        # 3640 <_IO_stdin_used+0x1c0>
    1deb:	48 63 04 82          	movslq (%rdx,%rax,4),%rax
    1def:	48 01 d0             	add    %rdx,%rax
    1df2:	ff e0                	jmpq   *%rax
    1df4:	e8 a5 07 00 00       	callq  259e <explode_bomb>
    1df9:	eb de                	jmp    1dd9 <phase_3+0x34>
    1dfb:	be af 02 00 00       	mov    $0x2af,%esi
    1e00:	eb 3b                	jmp    1e3d <phase_3+0x98>
    1e02:	be 0b 02 00 00       	mov    $0x20b,%esi
    1e07:	eb 34                	jmp    1e3d <phase_3+0x98>
    1e09:	be 4f 02 00 00       	mov    $0x24f,%esi
    1e0e:	eb 2d                	jmp    1e3d <phase_3+0x98>
    1e10:	be 96 00 00 00       	mov    $0x96,%esi
    1e15:	eb 26                	jmp    1e3d <phase_3+0x98>
    1e17:	be cc 00 00 00       	mov    $0xcc,%esi
    1e1c:	eb 1f                	jmp    1e3d <phase_3+0x98>
    1e1e:	be 00 02 00 00       	mov    $0x200,%esi
    1e23:	eb 18                	jmp    1e3d <phase_3+0x98>
    1e25:	be 0c 01 00 00       	mov    $0x10c,%esi
    1e2a:	eb 11                	jmp    1e3d <phase_3+0x98>
    1e2c:	e8 6d 07 00 00       	callq  259e <explode_bomb>
    1e31:	be 00 00 00 00       	mov    $0x0,%esi
    1e36:	eb 05                	jmp    1e3d <phase_3+0x98>
    1e38:	be 74 00 00 00       	mov    $0x74,%esi
    1e3d:	8b 54 24 14          	mov    0x14(%rsp),%edx
    1e41:	8b 7c 24 10          	mov    0x10(%rsp),%edi
    1e45:	e8 d1 03 00 00       	callq  221b <check_multiplication_equal>
    1e4a:	85 c0                	test   %eax,%eax
    1e4c:	74 15                	je     1e63 <phase_3+0xbe>
    1e4e:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
    1e53:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
    1e5a:	00 00 
    1e5c:	75 0c                	jne    1e6a <phase_3+0xc5>
    1e5e:	48 83 c4 28          	add    $0x28,%rsp
    1e62:	c3                   	retq   
    1e63:	e8 36 07 00 00       	callq  259e <explode_bomb>
    1e68:	eb e4                	jmp    1e4e <phase_3+0xa9>
    1e6a:	e8 41 fa ff ff       	callq  18b0 <__stack_chk_fail@plt>

0000000000001e6f <func4>:
    1e6f:	89 f0                	mov    %esi,%eax
    1e71:	39 f7                	cmp    %esi,%edi
    1e73:	74 1d                	je     1e92 <func4+0x23>
    1e75:	48 83 ec 08          	sub    $0x8,%rsp
    1e79:	39 f7                	cmp    %esi,%edi
    1e7b:	7f 0c                	jg     1e89 <func4+0x1a>
    1e7d:	29 fe                	sub    %edi,%esi
    1e7f:	e8 eb ff ff ff       	callq  1e6f <func4>
    1e84:	48 83 c4 08          	add    $0x8,%rsp
    1e88:	c3                   	retq   
    1e89:	29 f7                	sub    %esi,%edi
    1e8b:	e8 df ff ff ff       	callq  1e6f <func4>
    1e90:	eb f2                	jmp    1e84 <func4+0x15>
    1e92:	f3 c3                	repz retq 

0000000000001e94 <phase_4>:
    1e94:	53                   	push   %rbx
    1e95:	48 83 ec 10          	sub    $0x10,%rsp
    1e99:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1ea0:	00 00 
    1ea2:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
    1ea7:	31 c0                	xor    %eax,%eax
    1ea9:	48 8d 4c 24 04       	lea    0x4(%rsp),%rcx
    1eae:	48 89 e2             	mov    %rsp,%rdx
    1eb1:	48 8d 35 35 1a 00 00 	lea    0x1a35(%rip),%rsi        # 38ed <array.3434+0x28d>
    1eb8:	e8 93 fa ff ff       	callq  1950 <__isoc99_sscanf@plt>
    1ebd:	83 f8 02             	cmp    $0x2,%eax
    1ec0:	75 0d                	jne    1ecf <phase_4+0x3b>
    1ec2:	83 3c 24 01          	cmpl   $0x1,(%rsp)
    1ec6:	7e 07                	jle    1ecf <phase_4+0x3b>
    1ec8:	83 7c 24 04 01       	cmpl   $0x1,0x4(%rsp)
    1ecd:	7f 05                	jg     1ed4 <phase_4+0x40>
    1ecf:	e8 ca 06 00 00       	callq  259e <explode_bomb>
    1ed4:	81 3c 24 cf 02 00 00 	cmpl   $0x2cf,(%rsp)
    1edb:	7f 0a                	jg     1ee7 <phase_4+0x53>
    1edd:	81 7c 24 04 cf 02 00 	cmpl   $0x2cf,0x4(%rsp)
    1ee4:	00 
    1ee5:	7e 05                	jle    1eec <phase_4+0x58>
    1ee7:	e8 b2 06 00 00       	callq  259e <explode_bomb>
    1eec:	8b 3c 24             	mov    (%rsp),%edi
    1eef:	8b 74 24 04          	mov    0x4(%rsp),%esi
    1ef3:	89 fb                	mov    %edi,%ebx
    1ef5:	0f af de             	imul   %esi,%ebx
    1ef8:	e8 72 ff ff ff       	callq  1e6f <func4>
    1efd:	89 c1                	mov    %eax,%ecx
    1eff:	89 d8                	mov    %ebx,%eax
    1f01:	99                   	cltd   
    1f02:	f7 f9                	idiv   %ecx
    1f04:	3d d0 02 00 00       	cmp    $0x2d0,%eax
    1f09:	74 05                	je     1f10 <phase_4+0x7c>
    1f0b:	e8 8e 06 00 00       	callq  259e <explode_bomb>
    1f10:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
    1f15:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
    1f1c:	00 00 
    1f1e:	75 06                	jne    1f26 <phase_4+0x92>
    1f20:	48 83 c4 10          	add    $0x10,%rsp
    1f24:	5b                   	pop    %rbx
    1f25:	c3                   	retq   
    1f26:	e8 85 f9 ff ff       	callq  18b0 <__stack_chk_fail@plt>

0000000000001f2b <phase_5>:
    1f2b:	41 55                	push   %r13
    1f2d:	41 54                	push   %r12
    1f2f:	55                   	push   %rbp
    1f30:	53                   	push   %rbx
    1f31:	48 83 ec 08          	sub    $0x8,%rsp
    1f35:	49 89 fd             	mov    %rdi,%r13
    1f38:	e8 b1 02 00 00       	callq  21ee <string_length>
    1f3d:	83 f8 06             	cmp    $0x6,%eax
    1f40:	75 10                	jne    1f52 <phase_5+0x27>
    1f42:	4c 89 eb             	mov    %r13,%rbx
    1f45:	49 83 c5 05          	add    $0x5,%r13
    1f49:	4c 8d 25 10 17 00 00 	lea    0x1710(%rip),%r12        # 3660 <array.3434>
    1f50:	eb 10                	jmp    1f62 <phase_5+0x37>
    1f52:	e8 47 06 00 00       	callq  259e <explode_bomb>
    1f57:	eb e9                	jmp    1f42 <phase_5+0x17>
    1f59:	48 83 c3 01          	add    $0x1,%rbx
    1f5d:	4c 39 eb             	cmp    %r13,%rbx
    1f60:	74 2c                	je     1f8e <phase_5+0x63>
    1f62:	0f be 7b 01          	movsbl 0x1(%rbx),%edi
    1f66:	e8 7a 03 00 00       	callq  22e5 <from_char_to_int>
    1f6b:	89 c5                	mov    %eax,%ebp
    1f6d:	0f be 3b             	movsbl (%rbx),%edi
    1f70:	e8 70 03 00 00       	callq  22e5 <from_char_to_int>
    1f75:	83 e5 0f             	and    $0xf,%ebp
    1f78:	89 c2                	mov    %eax,%edx
    1f7a:	83 e2 0f             	and    $0xf,%edx
    1f7d:	41 8b 04 94          	mov    (%r12,%rdx,4),%eax
    1f81:	41 39 04 ac          	cmp    %eax,(%r12,%rbp,4)
    1f85:	7d d2                	jge    1f59 <phase_5+0x2e>
    1f87:	e8 12 06 00 00       	callq  259e <explode_bomb>
    1f8c:	eb cb                	jmp    1f59 <phase_5+0x2e>
    1f8e:	48 83 c4 08          	add    $0x8,%rsp
    1f92:	5b                   	pop    %rbx
    1f93:	5d                   	pop    %rbp
    1f94:	41 5c                	pop    %r12
    1f96:	41 5d                	pop    %r13
    1f98:	c3                   	retq   

0000000000001f99 <phase_6>:
    1f99:	41 55                	push   %r13
    1f9b:	41 54                	push   %r12
    1f9d:	55                   	push   %rbp
    1f9e:	53                   	push   %rbx
    1f9f:	48 83 ec 68          	sub    $0x68,%rsp
    1fa3:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1faa:	00 00 
    1fac:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
    1fb1:	31 c0                	xor    %eax,%eax
    1fb3:	49 89 e4             	mov    %rsp,%r12
    1fb6:	4c 89 e6             	mov    %r12,%rsi
    1fb9:	e8 1c 06 00 00       	callq  25da <read_six_numbers>
    1fbe:	41 bd 00 00 00 00    	mov    $0x0,%r13d
    1fc4:	eb 25                	jmp    1feb <phase_6+0x52>
    1fc6:	e8 d3 05 00 00       	callq  259e <explode_bomb>
    1fcb:	eb 2d                	jmp    1ffa <phase_6+0x61>
    1fcd:	83 c3 01             	add    $0x1,%ebx
    1fd0:	83 fb 05             	cmp    $0x5,%ebx
    1fd3:	7f 12                	jg     1fe7 <phase_6+0x4e>
    1fd5:	48 63 c3             	movslq %ebx,%rax
    1fd8:	8b 04 84             	mov    (%rsp,%rax,4),%eax
    1fdb:	39 45 00             	cmp    %eax,0x0(%rbp)
    1fde:	75 ed                	jne    1fcd <phase_6+0x34>
    1fe0:	e8 b9 05 00 00       	callq  259e <explode_bomb>
    1fe5:	eb e6                	jmp    1fcd <phase_6+0x34>
    1fe7:	49 83 c4 04          	add    $0x4,%r12
    1feb:	4c 89 e5             	mov    %r12,%rbp
    1fee:	41 8b 04 24          	mov    (%r12),%eax
    1ff2:	83 e8 01             	sub    $0x1,%eax
    1ff5:	83 f8 05             	cmp    $0x5,%eax
    1ff8:	77 cc                	ja     1fc6 <phase_6+0x2d>
    1ffa:	41 83 c5 01          	add    $0x1,%r13d
    1ffe:	41 83 fd 06          	cmp    $0x6,%r13d
    2002:	74 35                	je     2039 <phase_6+0xa0>
    2004:	44 89 eb             	mov    %r13d,%ebx
    2007:	eb cc                	jmp    1fd5 <phase_6+0x3c>
    2009:	48 8b 52 08          	mov    0x8(%rdx),%rdx
    200d:	83 c0 01             	add    $0x1,%eax
    2010:	39 c8                	cmp    %ecx,%eax
    2012:	75 f5                	jne    2009 <phase_6+0x70>
    2014:	48 89 54 f4 20       	mov    %rdx,0x20(%rsp,%rsi,8)
    2019:	48 83 c6 01          	add    $0x1,%rsi
    201d:	48 83 fe 06          	cmp    $0x6,%rsi
    2021:	74 1d                	je     2040 <phase_6+0xa7>
    2023:	8b 0c b4             	mov    (%rsp,%rsi,4),%ecx
    2026:	b8 01 00 00 00       	mov    $0x1,%eax
    202b:	48 8d 15 fe 31 20 00 	lea    0x2031fe(%rip),%rdx        # 205230 <node1>
    2032:	83 f9 01             	cmp    $0x1,%ecx
    2035:	7f d2                	jg     2009 <phase_6+0x70>
    2037:	eb db                	jmp    2014 <phase_6+0x7b>
    2039:	be 00 00 00 00       	mov    $0x0,%esi
    203e:	eb e3                	jmp    2023 <phase_6+0x8a>
    2040:	48 8b 5c 24 20       	mov    0x20(%rsp),%rbx
    2045:	48 8b 44 24 28       	mov    0x28(%rsp),%rax
    204a:	48 89 43 08          	mov    %rax,0x8(%rbx)
    204e:	48 8b 54 24 30       	mov    0x30(%rsp),%rdx
    2053:	48 89 50 08          	mov    %rdx,0x8(%rax)
    2057:	48 8b 44 24 38       	mov    0x38(%rsp),%rax
    205c:	48 89 42 08          	mov    %rax,0x8(%rdx)
    2060:	48 8b 54 24 40       	mov    0x40(%rsp),%rdx
    2065:	48 89 50 08          	mov    %rdx,0x8(%rax)
    2069:	48 8b 44 24 48       	mov    0x48(%rsp),%rax
    206e:	48 89 42 08          	mov    %rax,0x8(%rdx)
    2072:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
    2079:	00 
    207a:	bd 00 00 00 00       	mov    $0x0,%ebp
    207f:	eb 16                	jmp    2097 <phase_6+0xfe>
    2081:	48 8b 43 08          	mov    0x8(%rbx),%rax
    2085:	8b 00                	mov    (%rax),%eax
    2087:	39 03                	cmp    %eax,(%rbx)
    2089:	7c 23                	jl     20ae <phase_6+0x115>
    208b:	48 8b 5b 08          	mov    0x8(%rbx),%rbx
    208f:	83 c5 01             	add    $0x1,%ebp
    2092:	83 fd 05             	cmp    $0x5,%ebp
    2095:	74 1e                	je     20b5 <phase_6+0x11c>
    2097:	40 f6 c5 01          	test   $0x1,%bpl
    209b:	75 e4                	jne    2081 <phase_6+0xe8>
    209d:	48 8b 43 08          	mov    0x8(%rbx),%rax
    20a1:	8b 00                	mov    (%rax),%eax
    20a3:	39 03                	cmp    %eax,(%rbx)
    20a5:	7e e4                	jle    208b <phase_6+0xf2>
    20a7:	e8 f2 04 00 00       	callq  259e <explode_bomb>
    20ac:	eb dd                	jmp    208b <phase_6+0xf2>
    20ae:	e8 eb 04 00 00       	callq  259e <explode_bomb>
    20b3:	eb d6                	jmp    208b <phase_6+0xf2>
    20b5:	48 8b 44 24 58       	mov    0x58(%rsp),%rax
    20ba:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
    20c1:	00 00 
    20c3:	75 0b                	jne    20d0 <phase_6+0x137>
    20c5:	48 83 c4 68          	add    $0x68,%rsp
    20c9:	5b                   	pop    %rbx
    20ca:	5d                   	pop    %rbp
    20cb:	41 5c                	pop    %r12
    20cd:	41 5d                	pop    %r13
    20cf:	c3                   	retq   
    20d0:	e8 db f7 ff ff       	callq  18b0 <__stack_chk_fail@plt>

00000000000020d5 <fun7>:
    20d5:	48 85 ff             	test   %rdi,%rdi
    20d8:	74 34                	je     210e <fun7+0x39>
    20da:	48 83 ec 08          	sub    $0x8,%rsp
    20de:	8b 17                	mov    (%rdi),%edx
    20e0:	39 f2                	cmp    %esi,%edx
    20e2:	7f 0e                	jg     20f2 <fun7+0x1d>
    20e4:	b8 00 00 00 00       	mov    $0x0,%eax
    20e9:	39 f2                	cmp    %esi,%edx
    20eb:	75 12                	jne    20ff <fun7+0x2a>
    20ed:	48 83 c4 08          	add    $0x8,%rsp
    20f1:	c3                   	retq   
    20f2:	48 8b 7f 08          	mov    0x8(%rdi),%rdi
    20f6:	e8 da ff ff ff       	callq  20d5 <fun7>
    20fb:	01 c0                	add    %eax,%eax
    20fd:	eb ee                	jmp    20ed <fun7+0x18>
    20ff:	48 8b 7f 10          	mov    0x10(%rdi),%rdi
    2103:	e8 cd ff ff ff       	callq  20d5 <fun7>
    2108:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
    210c:	eb df                	jmp    20ed <fun7+0x18>
    210e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2113:	c3                   	retq   

0000000000002114 <secret_phase>:
    2114:	53                   	push   %rbx
    2115:	e8 01 05 00 00       	callq  261b <read_line>
    211a:	ba 0a 00 00 00       	mov    $0xa,%edx
    211f:	be 00 00 00 00       	mov    $0x0,%esi
    2124:	48 89 c7             	mov    %rax,%rdi
    2127:	e8 04 f8 ff ff       	callq  1930 <strtol@plt>
    212c:	48 89 c3             	mov    %rax,%rbx
    212f:	8d 40 ff             	lea    -0x1(%rax),%eax
    2132:	3d e8 03 00 00       	cmp    $0x3e8,%eax
    2137:	77 2b                	ja     2164 <secret_phase+0x50>
    2139:	89 de                	mov    %ebx,%esi
    213b:	48 8d 3d 0e 30 20 00 	lea    0x20300e(%rip),%rdi        # 205150 <n1>
    2142:	e8 8e ff ff ff       	callq  20d5 <fun7>
    2147:	83 f8 01             	cmp    $0x1,%eax
    214a:	74 05                	je     2151 <secret_phase+0x3d>
    214c:	e8 4d 04 00 00       	callq  259e <explode_bomb>
    2151:	48 8d 3d b0 14 00 00 	lea    0x14b0(%rip),%rdi        # 3608 <_IO_stdin_used+0x188>
    2158:	e8 33 f7 ff ff       	callq  1890 <puts@plt>
    215d:	e8 fd 05 00 00       	callq  275f <phase_defused>
    2162:	5b                   	pop    %rbx
    2163:	c3                   	retq   
    2164:	e8 35 04 00 00       	callq  259e <explode_bomb>
    2169:	eb ce                	jmp    2139 <secret_phase+0x25>

000000000000216b <sig_handler>:
    216b:	48 83 ec 08          	sub    $0x8,%rsp
    216f:	48 8d 3d 2a 15 00 00 	lea    0x152a(%rip),%rdi        # 36a0 <array.3434+0x40>
    2176:	e8 15 f7 ff ff       	callq  1890 <puts@plt>
    217b:	bf 03 00 00 00       	mov    $0x3,%edi
    2180:	e8 3b f8 ff ff       	callq  19c0 <sleep@plt>
    2185:	48 8d 35 dd 16 00 00 	lea    0x16dd(%rip),%rsi        # 3869 <array.3434+0x209>
    218c:	bf 01 00 00 00       	mov    $0x1,%edi
    2191:	b8 00 00 00 00       	mov    $0x0,%eax
    2196:	e8 c5 f7 ff ff       	callq  1960 <__printf_chk@plt>
    219b:	48 8b 3d de 34 20 00 	mov    0x2034de(%rip),%rdi        # 205680 <stdout@@GLIBC_2.2.5>
    21a2:	e8 99 f7 ff ff       	callq  1940 <fflush@plt>
    21a7:	bf 01 00 00 00       	mov    $0x1,%edi
    21ac:	e8 0f f8 ff ff       	callq  19c0 <sleep@plt>
    21b1:	48 8d 3d b9 16 00 00 	lea    0x16b9(%rip),%rdi        # 3871 <array.3434+0x211>
    21b8:	e8 d3 f6 ff ff       	callq  1890 <puts@plt>
    21bd:	bf 10 00 00 00       	mov    $0x10,%edi
    21c2:	e8 c9 f7 ff ff       	callq  1990 <exit@plt>

00000000000021c7 <invalid_phase>:
    21c7:	48 83 ec 08          	sub    $0x8,%rsp
    21cb:	48 89 fa             	mov    %rdi,%rdx
    21ce:	48 8d 35 a4 16 00 00 	lea    0x16a4(%rip),%rsi        # 3879 <array.3434+0x219>
    21d5:	bf 01 00 00 00       	mov    $0x1,%edi
    21da:	b8 00 00 00 00       	mov    $0x0,%eax
    21df:	e8 7c f7 ff ff       	callq  1960 <__printf_chk@plt>
    21e4:	bf 08 00 00 00       	mov    $0x8,%edi
    21e9:	e8 a2 f7 ff ff       	callq  1990 <exit@plt>

00000000000021ee <string_length>:
    21ee:	80 3f 00             	cmpb   $0x0,(%rdi)
    21f1:	74 12                	je     2205 <string_length+0x17>
    21f3:	48 89 fa             	mov    %rdi,%rdx
    21f6:	48 83 c2 01          	add    $0x1,%rdx
    21fa:	89 d0                	mov    %edx,%eax
    21fc:	29 f8                	sub    %edi,%eax
    21fe:	80 3a 00             	cmpb   $0x0,(%rdx)
    2201:	75 f3                	jne    21f6 <string_length+0x8>
    2203:	f3 c3                	repz retq 
    2205:	b8 00 00 00 00       	mov    $0x0,%eax
    220a:	c3                   	retq   

000000000000220b <check_division_equal>:
    220b:	89 f8                	mov    %edi,%eax
    220d:	89 d1                	mov    %edx,%ecx
    220f:	99                   	cltd   
    2210:	f7 fe                	idiv   %esi
    2212:	39 c8                	cmp    %ecx,%eax
    2214:	0f 94 c0             	sete   %al
    2217:	0f b6 c0             	movzbl %al,%eax
    221a:	c3                   	retq   

000000000000221b <check_multiplication_equal>:
    221b:	0f af fe             	imul   %esi,%edi
    221e:	39 d7                	cmp    %edx,%edi
    2220:	0f 94 c0             	sete   %al
    2223:	0f b6 c0             	movzbl %al,%eax
    2226:	c3                   	retq   

0000000000002227 <check_substraction_equal>:
    2227:	29 f7                	sub    %esi,%edi
    2229:	39 d7                	cmp    %edx,%edi
    222b:	0f 94 c0             	sete   %al
    222e:	0f b6 c0             	movzbl %al,%eax
    2231:	c3                   	retq   

0000000000002232 <reverse_string>:
    2232:	48 89 fe             	mov    %rdi,%rsi
    2235:	48 85 ff             	test   %rdi,%rdi
    2238:	74 40                	je     227a <reverse_string+0x48>
    223a:	80 3f 00             	cmpb   $0x0,(%rdi)
    223d:	74 3b                	je     227a <reverse_string+0x48>
    223f:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
    2246:	b8 00 00 00 00       	mov    $0x0,%eax
    224b:	f2 ae                	repnz scas %es:(%rdi),%al
    224d:	48 89 ca             	mov    %rcx,%rdx
    2250:	48 f7 d2             	not    %rdx
    2253:	48 8d 4c 16 fe       	lea    -0x2(%rsi,%rdx,1),%rcx
    2258:	48 39 ce             	cmp    %rcx,%rsi
    225b:	73 1d                	jae    227a <reverse_string+0x48>
    225d:	48 89 f2             	mov    %rsi,%rdx
    2260:	0f b6 02             	movzbl (%rdx),%eax
    2263:	32 01                	xor    (%rcx),%al
    2265:	88 02                	mov    %al,(%rdx)
    2267:	32 01                	xor    (%rcx),%al
    2269:	88 01                	mov    %al,(%rcx)
    226b:	30 02                	xor    %al,(%rdx)
    226d:	48 83 c2 01          	add    $0x1,%rdx
    2271:	48 83 e9 01          	sub    $0x1,%rcx
    2275:	48 39 ca             	cmp    %rcx,%rdx
    2278:	72 e6                	jb     2260 <reverse_string+0x2e>
    227a:	48 89 f0             	mov    %rsi,%rax
    227d:	c3                   	retq   

000000000000227e <strings_not_equal>:
    227e:	41 54                	push   %r12
    2280:	55                   	push   %rbp
    2281:	53                   	push   %rbx
    2282:	48 89 fb             	mov    %rdi,%rbx
    2285:	48 89 f5             	mov    %rsi,%rbp
    2288:	e8 61 ff ff ff       	callq  21ee <string_length>
    228d:	41 89 c4             	mov    %eax,%r12d
    2290:	48 89 ef             	mov    %rbp,%rdi
    2293:	e8 56 ff ff ff       	callq  21ee <string_length>
    2298:	ba 01 00 00 00       	mov    $0x1,%edx
    229d:	41 39 c4             	cmp    %eax,%r12d
    22a0:	74 07                	je     22a9 <strings_not_equal+0x2b>
    22a2:	89 d0                	mov    %edx,%eax
    22a4:	5b                   	pop    %rbx
    22a5:	5d                   	pop    %rbp
    22a6:	41 5c                	pop    %r12
    22a8:	c3                   	retq   
    22a9:	0f b6 03             	movzbl (%rbx),%eax
    22ac:	84 c0                	test   %al,%al
    22ae:	74 27                	je     22d7 <strings_not_equal+0x59>
    22b0:	3a 45 00             	cmp    0x0(%rbp),%al
    22b3:	75 29                	jne    22de <strings_not_equal+0x60>
    22b5:	48 83 c3 01          	add    $0x1,%rbx
    22b9:	48 83 c5 01          	add    $0x1,%rbp
    22bd:	0f b6 03             	movzbl (%rbx),%eax
    22c0:	84 c0                	test   %al,%al
    22c2:	74 0c                	je     22d0 <strings_not_equal+0x52>
    22c4:	38 45 00             	cmp    %al,0x0(%rbp)
    22c7:	74 ec                	je     22b5 <strings_not_equal+0x37>
    22c9:	ba 01 00 00 00       	mov    $0x1,%edx
    22ce:	eb d2                	jmp    22a2 <strings_not_equal+0x24>
    22d0:	ba 00 00 00 00       	mov    $0x0,%edx
    22d5:	eb cb                	jmp    22a2 <strings_not_equal+0x24>
    22d7:	ba 00 00 00 00       	mov    $0x0,%edx
    22dc:	eb c4                	jmp    22a2 <strings_not_equal+0x24>
    22de:	ba 01 00 00 00       	mov    $0x1,%edx
    22e3:	eb bd                	jmp    22a2 <strings_not_equal+0x24>

00000000000022e5 <from_char_to_int>:
    22e5:	40 0f be c7          	movsbl %dil,%eax
    22e9:	40 80 ff 69          	cmp    $0x69,%dil
    22ed:	7f 0e                	jg     22fd <from_char_to_int+0x18>
    22ef:	83 ef 33             	sub    $0x33,%edi
    22f2:	8d 50 fd             	lea    -0x3(%rax),%edx
    22f5:	40 80 ff 0a          	cmp    $0xa,%dil
    22f9:	0f 42 c2             	cmovb  %edx,%eax
    22fc:	c3                   	retq   
    22fd:	83 e8 09             	sub    $0x9,%eax
    2300:	c3                   	retq   

0000000000002301 <initialize_bomb>:
    2301:	55                   	push   %rbp
    2302:	53                   	push   %rbx
    2303:	48 81 ec 58 20 00 00 	sub    $0x2058,%rsp
    230a:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2311:	00 00 
    2313:	48 89 84 24 48 20 00 	mov    %rax,0x2048(%rsp)
    231a:	00 
    231b:	31 c0                	xor    %eax,%eax
    231d:	48 8d 35 47 fe ff ff 	lea    -0x1b9(%rip),%rsi        # 216b <sig_handler>
    2324:	bf 02 00 00 00       	mov    $0x2,%edi
    2329:	e8 d2 f5 ff ff       	callq  1900 <signal@plt>
    232e:	48 89 e7             	mov    %rsp,%rdi
    2331:	be 40 00 00 00       	mov    $0x40,%esi
    2336:	e8 45 f6 ff ff       	callq  1980 <gethostname@plt>
    233b:	85 c0                	test   %eax,%eax
    233d:	75 45                	jne    2384 <initialize_bomb+0x83>
    233f:	48 8b 3d 3a 2f 20 00 	mov    0x202f3a(%rip),%rdi        # 205280 <host_table>
    2346:	48 8d 1d 3b 2f 20 00 	lea    0x202f3b(%rip),%rbx        # 205288 <host_table+0x8>
    234d:	48 89 e5             	mov    %rsp,%rbp
    2350:	48 85 ff             	test   %rdi,%rdi
    2353:	74 19                	je     236e <initialize_bomb+0x6d>
    2355:	48 89 ee             	mov    %rbp,%rsi
    2358:	e8 03 f5 ff ff       	callq  1860 <strcasecmp@plt>
    235d:	85 c0                	test   %eax,%eax
    235f:	74 5e                	je     23bf <initialize_bomb+0xbe>
    2361:	48 83 c3 08          	add    $0x8,%rbx
    2365:	48 8b 7b f8          	mov    -0x8(%rbx),%rdi
    2369:	48 85 ff             	test   %rdi,%rdi
    236c:	75 e7                	jne    2355 <initialize_bomb+0x54>
    236e:	48 8d 3d 9b 13 00 00 	lea    0x139b(%rip),%rdi        # 3710 <array.3434+0xb0>
    2375:	e8 16 f5 ff ff       	callq  1890 <puts@plt>
    237a:	bf 08 00 00 00       	mov    $0x8,%edi
    237f:	e8 0c f6 ff ff       	callq  1990 <exit@plt>
    2384:	48 8d 3d 4d 13 00 00 	lea    0x134d(%rip),%rdi        # 36d8 <array.3434+0x78>
    238b:	e8 00 f5 ff ff       	callq  1890 <puts@plt>
    2390:	bf 08 00 00 00       	mov    $0x8,%edi
    2395:	e8 f6 f5 ff ff       	callq  1990 <exit@plt>
    239a:	48 8d 54 24 40       	lea    0x40(%rsp),%rdx
    239f:	48 8d 35 e4 14 00 00 	lea    0x14e4(%rip),%rsi        # 388a <array.3434+0x22a>
    23a6:	bf 01 00 00 00       	mov    $0x1,%edi
    23ab:	b8 00 00 00 00       	mov    $0x0,%eax
    23b0:	e8 ab f5 ff ff       	callq  1960 <__printf_chk@plt>
    23b5:	bf 08 00 00 00       	mov    $0x8,%edi
    23ba:	e8 d1 f5 ff ff       	callq  1990 <exit@plt>
    23bf:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
    23c4:	e8 b2 0d 00 00       	callq  317b <init_driver>
    23c9:	85 c0                	test   %eax,%eax
    23cb:	78 cd                	js     239a <initialize_bomb+0x99>
    23cd:	48 8b 84 24 48 20 00 	mov    0x2048(%rsp),%rax
    23d4:	00 
    23d5:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
    23dc:	00 00 
    23de:	75 0a                	jne    23ea <initialize_bomb+0xe9>
    23e0:	48 81 c4 58 20 00 00 	add    $0x2058,%rsp
    23e7:	5b                   	pop    %rbx
    23e8:	5d                   	pop    %rbp
    23e9:	c3                   	retq   
    23ea:	e8 c1 f4 ff ff       	callq  18b0 <__stack_chk_fail@plt>

00000000000023ef <initialize_bomb_solve>:
    23ef:	f3 c3                	repz retq 

00000000000023f1 <blank_line>:
    23f1:	55                   	push   %rbp
    23f2:	53                   	push   %rbx
    23f3:	48 83 ec 08          	sub    $0x8,%rsp
    23f7:	48 89 fd             	mov    %rdi,%rbp
    23fa:	0f b6 5d 00          	movzbl 0x0(%rbp),%ebx
    23fe:	84 db                	test   %bl,%bl
    2400:	74 1e                	je     2420 <blank_line+0x2f>
    2402:	e8 c9 f5 ff ff       	callq  19d0 <__ctype_b_loc@plt>
    2407:	48 83 c5 01          	add    $0x1,%rbp
    240b:	48 0f be db          	movsbq %bl,%rbx
    240f:	48 8b 00             	mov    (%rax),%rax
    2412:	f6 44 58 01 20       	testb  $0x20,0x1(%rax,%rbx,2)
    2417:	75 e1                	jne    23fa <blank_line+0x9>
    2419:	b8 00 00 00 00       	mov    $0x0,%eax
    241e:	eb 05                	jmp    2425 <blank_line+0x34>
    2420:	b8 01 00 00 00       	mov    $0x1,%eax
    2425:	48 83 c4 08          	add    $0x8,%rsp
    2429:	5b                   	pop    %rbx
    242a:	5d                   	pop    %rbp
    242b:	c3                   	retq   

000000000000242c <skip>:
    242c:	55                   	push   %rbp
    242d:	53                   	push   %rbx
    242e:	48 83 ec 08          	sub    $0x8,%rsp
    2432:	48 8d 2d 87 32 20 00 	lea    0x203287(%rip),%rbp        # 2056c0 <input_strings>
    2439:	48 63 05 6c 32 20 00 	movslq 0x20326c(%rip),%rax        # 2056ac <num_input_strings>
    2440:	48 8d 3c 80          	lea    (%rax,%rax,4),%rdi
    2444:	48 c1 e7 04          	shl    $0x4,%rdi
    2448:	48 01 ef             	add    %rbp,%rdi
    244b:	48 8b 15 5e 32 20 00 	mov    0x20325e(%rip),%rdx        # 2056b0 <infile>
    2452:	be 50 00 00 00       	mov    $0x50,%esi
    2457:	e8 94 f4 ff ff       	callq  18f0 <fgets@plt>
    245c:	48 89 c3             	mov    %rax,%rbx
    245f:	48 85 c0             	test   %rax,%rax
    2462:	74 0c                	je     2470 <skip+0x44>
    2464:	48 89 c7             	mov    %rax,%rdi
    2467:	e8 85 ff ff ff       	callq  23f1 <blank_line>
    246c:	85 c0                	test   %eax,%eax
    246e:	75 c9                	jne    2439 <skip+0xd>
    2470:	48 89 d8             	mov    %rbx,%rax
    2473:	48 83 c4 08          	add    $0x8,%rsp
    2477:	5b                   	pop    %rbx
    2478:	5d                   	pop    %rbp
    2479:	c3                   	retq   

000000000000247a <send_msg>:
    247a:	53                   	push   %rbx
    247b:	48 81 ec 10 40 00 00 	sub    $0x4010,%rsp
    2482:	41 89 f8             	mov    %edi,%r8d
    2485:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    248c:	00 00 
    248e:	48 89 84 24 08 40 00 	mov    %rax,0x4008(%rsp)
    2495:	00 
    2496:	31 c0                	xor    %eax,%eax
    2498:	8b 35 0e 32 20 00    	mov    0x20320e(%rip),%esi        # 2056ac <num_input_strings>
    249e:	8d 46 ff             	lea    -0x1(%rsi),%eax
    24a1:	48 98                	cltq   
    24a3:	48 8d 14 80          	lea    (%rax,%rax,4),%rdx
    24a7:	48 c1 e2 04          	shl    $0x4,%rdx
    24ab:	48 8d 05 0e 32 20 00 	lea    0x20320e(%rip),%rax        # 2056c0 <input_strings>
    24b2:	48 01 c2             	add    %rax,%rdx
    24b5:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
    24bc:	b8 00 00 00 00       	mov    $0x0,%eax
    24c1:	48 89 d7             	mov    %rdx,%rdi
    24c4:	f2 ae                	repnz scas %es:(%rdi),%al
    24c6:	48 89 c8             	mov    %rcx,%rax
    24c9:	48 f7 d0             	not    %rax
    24cc:	48 83 c0 63          	add    $0x63,%rax
    24d0:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
    24d6:	0f 87 86 00 00 00    	ja     2562 <send_msg+0xe8>
    24dc:	45 85 c0             	test   %r8d,%r8d
    24df:	4c 8d 0d be 13 00 00 	lea    0x13be(%rip),%r9        # 38a4 <array.3434+0x244>
    24e6:	48 8d 05 bf 13 00 00 	lea    0x13bf(%rip),%rax        # 38ac <array.3434+0x24c>
    24ed:	4c 0f 44 c8          	cmove  %rax,%r9
    24f1:	48 89 e3             	mov    %rsp,%rbx
    24f4:	52                   	push   %rdx
    24f5:	56                   	push   %rsi
    24f6:	44 8b 05 47 2c 20 00 	mov    0x202c47(%rip),%r8d        # 205144 <bomb_id>
    24fd:	48 8d 0d b1 13 00 00 	lea    0x13b1(%rip),%rcx        # 38b5 <array.3434+0x255>
    2504:	ba 00 20 00 00       	mov    $0x2000,%edx
    2509:	be 01 00 00 00       	mov    $0x1,%esi
    250e:	48 89 df             	mov    %rbx,%rdi
    2511:	b8 00 00 00 00       	mov    $0x0,%eax
    2516:	e8 c5 f4 ff ff       	callq  19e0 <__sprintf_chk@plt>
    251b:	4c 8d 84 24 10 20 00 	lea    0x2010(%rsp),%r8
    2522:	00 
    2523:	b9 00 00 00 00       	mov    $0x0,%ecx
    2528:	48 89 da             	mov    %rbx,%rdx
    252b:	48 8d 35 ee 2b 20 00 	lea    0x202bee(%rip),%rsi        # 205120 <user_password>
    2532:	48 8d 3d ff 2b 20 00 	lea    0x202bff(%rip),%rdi        # 205138 <userid>
    2539:	e8 46 0e 00 00       	callq  3384 <driver_post>
    253e:	48 83 c4 10          	add    $0x10,%rsp
    2542:	85 c0                	test   %eax,%eax
    2544:	78 3c                	js     2582 <send_msg+0x108>
    2546:	48 8b 84 24 08 40 00 	mov    0x4008(%rsp),%rax
    254d:	00 
    254e:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
    2555:	00 00 
    2557:	75 40                	jne    2599 <send_msg+0x11f>
    2559:	48 81 c4 10 40 00 00 	add    $0x4010,%rsp
    2560:	5b                   	pop    %rbx
    2561:	c3                   	retq   
    2562:	48 8d 35 df 11 00 00 	lea    0x11df(%rip),%rsi        # 3748 <array.3434+0xe8>
    2569:	bf 01 00 00 00       	mov    $0x1,%edi
    256e:	b8 00 00 00 00       	mov    $0x0,%eax
    2573:	e8 e8 f3 ff ff       	callq  1960 <__printf_chk@plt>
    2578:	bf 08 00 00 00       	mov    $0x8,%edi
    257d:	e8 0e f4 ff ff       	callq  1990 <exit@plt>
    2582:	48 8d bc 24 00 20 00 	lea    0x2000(%rsp),%rdi
    2589:	00 
    258a:	e8 01 f3 ff ff       	callq  1890 <puts@plt>
    258f:	bf 00 00 00 00       	mov    $0x0,%edi
    2594:	e8 f7 f3 ff ff       	callq  1990 <exit@plt>
    2599:	e8 12 f3 ff ff       	callq  18b0 <__stack_chk_fail@plt>

000000000000259e <explode_bomb>:
    259e:	48 83 ec 08          	sub    $0x8,%rsp
    25a2:	48 8d 3d 18 13 00 00 	lea    0x1318(%rip),%rdi        # 38c1 <array.3434+0x261>
    25a9:	e8 e2 f2 ff ff       	callq  1890 <puts@plt>
    25ae:	48 8d 3d 15 13 00 00 	lea    0x1315(%rip),%rdi        # 38ca <array.3434+0x26a>
    25b5:	e8 d6 f2 ff ff       	callq  1890 <puts@plt>
    25ba:	bf 00 00 00 00       	mov    $0x0,%edi
    25bf:	e8 b6 fe ff ff       	callq  247a <send_msg>
    25c4:	48 8d 3d a5 11 00 00 	lea    0x11a5(%rip),%rdi        # 3770 <array.3434+0x110>
    25cb:	e8 c0 f2 ff ff       	callq  1890 <puts@plt>
    25d0:	bf 08 00 00 00       	mov    $0x8,%edi
    25d5:	e8 b6 f3 ff ff       	callq  1990 <exit@plt>

00000000000025da <read_six_numbers>:
    25da:	48 83 ec 08          	sub    $0x8,%rsp
    25de:	48 89 f2             	mov    %rsi,%rdx
    25e1:	48 8d 4e 04          	lea    0x4(%rsi),%rcx
    25e5:	48 8d 46 14          	lea    0x14(%rsi),%rax
    25e9:	50                   	push   %rax
    25ea:	48 8d 46 10          	lea    0x10(%rsi),%rax
    25ee:	50                   	push   %rax
    25ef:	4c 8d 4e 0c          	lea    0xc(%rsi),%r9
    25f3:	4c 8d 46 08          	lea    0x8(%rsi),%r8
    25f7:	48 8d 35 e3 12 00 00 	lea    0x12e3(%rip),%rsi        # 38e1 <array.3434+0x281>
    25fe:	b8 00 00 00 00       	mov    $0x0,%eax
    2603:	e8 48 f3 ff ff       	callq  1950 <__isoc99_sscanf@plt>
    2608:	48 83 c4 10          	add    $0x10,%rsp
    260c:	83 f8 05             	cmp    $0x5,%eax
    260f:	7e 05                	jle    2616 <read_six_numbers+0x3c>
    2611:	48 83 c4 08          	add    $0x8,%rsp
    2615:	c3                   	retq   
    2616:	e8 83 ff ff ff       	callq  259e <explode_bomb>

000000000000261b <read_line>:
    261b:	48 83 ec 08          	sub    $0x8,%rsp
    261f:	b8 00 00 00 00       	mov    $0x0,%eax
    2624:	e8 03 fe ff ff       	callq  242c <skip>
    2629:	48 85 c0             	test   %rax,%rax
    262c:	74 6f                	je     269d <read_line+0x82>
    262e:	8b 35 78 30 20 00    	mov    0x203078(%rip),%esi        # 2056ac <num_input_strings>
    2634:	48 63 c6             	movslq %esi,%rax
    2637:	48 8d 14 80          	lea    (%rax,%rax,4),%rdx
    263b:	48 c1 e2 04          	shl    $0x4,%rdx
    263f:	48 8d 05 7a 30 20 00 	lea    0x20307a(%rip),%rax        # 2056c0 <input_strings>
    2646:	48 01 c2             	add    %rax,%rdx
    2649:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
    2650:	b8 00 00 00 00       	mov    $0x0,%eax
    2655:	48 89 d7             	mov    %rdx,%rdi
    2658:	f2 ae                	repnz scas %es:(%rdi),%al
    265a:	48 f7 d1             	not    %rcx
    265d:	48 83 e9 01          	sub    $0x1,%rcx
    2661:	83 f9 4e             	cmp    $0x4e,%ecx
    2664:	0f 8f ab 00 00 00    	jg     2715 <read_line+0xfa>
    266a:	83 e9 01             	sub    $0x1,%ecx
    266d:	48 63 c9             	movslq %ecx,%rcx
    2670:	48 63 c6             	movslq %esi,%rax
    2673:	48 8d 04 80          	lea    (%rax,%rax,4),%rax
    2677:	48 c1 e0 04          	shl    $0x4,%rax
    267b:	48 89 c7             	mov    %rax,%rdi
    267e:	48 8d 05 3b 30 20 00 	lea    0x20303b(%rip),%rax        # 2056c0 <input_strings>
    2685:	48 01 f8             	add    %rdi,%rax
    2688:	c6 04 08 00          	movb   $0x0,(%rax,%rcx,1)
    268c:	83 c6 01             	add    $0x1,%esi
    268f:	89 35 17 30 20 00    	mov    %esi,0x203017(%rip)        # 2056ac <num_input_strings>
    2695:	48 89 d0             	mov    %rdx,%rax
    2698:	48 83 c4 08          	add    $0x8,%rsp
    269c:	c3                   	retq   
    269d:	48 8b 05 ec 2f 20 00 	mov    0x202fec(%rip),%rax        # 205690 <stdin@@GLIBC_2.2.5>
    26a4:	48 39 05 05 30 20 00 	cmp    %rax,0x203005(%rip)        # 2056b0 <infile>
    26ab:	74 1b                	je     26c8 <read_line+0xad>
    26ad:	48 8d 3d 5d 12 00 00 	lea    0x125d(%rip),%rdi        # 3911 <array.3434+0x2b1>
    26b4:	e8 97 f1 ff ff       	callq  1850 <getenv@plt>
    26b9:	48 85 c0             	test   %rax,%rax
    26bc:	74 20                	je     26de <read_line+0xc3>
    26be:	bf 00 00 00 00       	mov    $0x0,%edi
    26c3:	e8 c8 f2 ff ff       	callq  1990 <exit@plt>
    26c8:	48 8d 3d 24 12 00 00 	lea    0x1224(%rip),%rdi        # 38f3 <array.3434+0x293>
    26cf:	e8 bc f1 ff ff       	callq  1890 <puts@plt>
    26d4:	bf 08 00 00 00       	mov    $0x8,%edi
    26d9:	e8 b2 f2 ff ff       	callq  1990 <exit@plt>
    26de:	48 8b 05 ab 2f 20 00 	mov    0x202fab(%rip),%rax        # 205690 <stdin@@GLIBC_2.2.5>
    26e5:	48 89 05 c4 2f 20 00 	mov    %rax,0x202fc4(%rip)        # 2056b0 <infile>
    26ec:	b8 00 00 00 00       	mov    $0x0,%eax
    26f1:	e8 36 fd ff ff       	callq  242c <skip>
    26f6:	48 85 c0             	test   %rax,%rax
    26f9:	0f 85 2f ff ff ff    	jne    262e <read_line+0x13>
    26ff:	48 8d 3d ed 11 00 00 	lea    0x11ed(%rip),%rdi        # 38f3 <array.3434+0x293>
    2706:	e8 85 f1 ff ff       	callq  1890 <puts@plt>
    270b:	bf 00 00 00 00       	mov    $0x0,%edi
    2710:	e8 7b f2 ff ff       	callq  1990 <exit@plt>
    2715:	48 8d 3d 00 12 00 00 	lea    0x1200(%rip),%rdi        # 391c <array.3434+0x2bc>
    271c:	e8 6f f1 ff ff       	callq  1890 <puts@plt>
    2721:	8b 05 85 2f 20 00    	mov    0x202f85(%rip),%eax        # 2056ac <num_input_strings>
    2727:	8d 50 01             	lea    0x1(%rax),%edx
    272a:	89 15 7c 2f 20 00    	mov    %edx,0x202f7c(%rip)        # 2056ac <num_input_strings>
    2730:	48 98                	cltq   
    2732:	48 6b c0 50          	imul   $0x50,%rax,%rax
    2736:	48 8d 15 83 2f 20 00 	lea    0x202f83(%rip),%rdx        # 2056c0 <input_strings>
    273d:	48 be 2a 2a 2a 74 72 	movabs $0x636e7572742a2a2a,%rsi
    2744:	75 6e 63 
    2747:	48 bf 61 74 65 64 2a 	movabs $0x2a2a2a64657461,%rdi
    274e:	2a 2a 00 
    2751:	48 89 34 02          	mov    %rsi,(%rdx,%rax,1)
    2755:	48 89 7c 02 08       	mov    %rdi,0x8(%rdx,%rax,1)
    275a:	e8 3f fe ff ff       	callq  259e <explode_bomb>

000000000000275f <phase_defused>:
    275f:	48 83 ec 78          	sub    $0x78,%rsp
    2763:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    276a:	00 00 
    276c:	48 89 44 24 68       	mov    %rax,0x68(%rsp)
    2771:	31 c0                	xor    %eax,%eax
    2773:	bf 01 00 00 00       	mov    $0x1,%edi
    2778:	e8 fd fc ff ff       	callq  247a <send_msg>
    277d:	83 3d 28 2f 20 00 06 	cmpl   $0x6,0x202f28(%rip)        # 2056ac <num_input_strings>
    2784:	74 19                	je     279f <phase_defused+0x40>
    2786:	48 8b 44 24 68       	mov    0x68(%rsp),%rax
    278b:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
    2792:	00 00 
    2794:	0f 85 84 00 00 00    	jne    281e <phase_defused+0xbf>
    279a:	48 83 c4 78          	add    $0x78,%rsp
    279e:	c3                   	retq   
    279f:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
    27a4:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
    27a9:	4c 8d 44 24 10       	lea    0x10(%rsp),%r8
    27ae:	48 8d 35 82 11 00 00 	lea    0x1182(%rip),%rsi        # 3937 <array.3434+0x2d7>
    27b5:	48 8d 3d f4 2f 20 00 	lea    0x202ff4(%rip),%rdi        # 2057b0 <input_strings+0xf0>
    27bc:	b8 00 00 00 00       	mov    $0x0,%eax
    27c1:	e8 8a f1 ff ff       	callq  1950 <__isoc99_sscanf@plt>
    27c6:	83 f8 03             	cmp    $0x3,%eax
    27c9:	74 1a                	je     27e5 <phase_defused+0x86>
    27cb:	48 8d 3d 26 10 00 00 	lea    0x1026(%rip),%rdi        # 37f8 <array.3434+0x198>
    27d2:	e8 b9 f0 ff ff       	callq  1890 <puts@plt>
    27d7:	48 8d 3d 4a 10 00 00 	lea    0x104a(%rip),%rdi        # 3828 <array.3434+0x1c8>
    27de:	e8 ad f0 ff ff       	callq  1890 <puts@plt>
    27e3:	eb a1                	jmp    2786 <phase_defused+0x27>
    27e5:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
    27ea:	48 8d 35 4f 11 00 00 	lea    0x114f(%rip),%rsi        # 3940 <array.3434+0x2e0>
    27f1:	e8 88 fa ff ff       	callq  227e <strings_not_equal>
    27f6:	85 c0                	test   %eax,%eax
    27f8:	75 d1                	jne    27cb <phase_defused+0x6c>
    27fa:	48 8d 3d 97 0f 00 00 	lea    0xf97(%rip),%rdi        # 3798 <array.3434+0x138>
    2801:	e8 8a f0 ff ff       	callq  1890 <puts@plt>
    2806:	48 8d 3d b3 0f 00 00 	lea    0xfb3(%rip),%rdi        # 37c0 <array.3434+0x160>
    280d:	e8 7e f0 ff ff       	callq  1890 <puts@plt>
    2812:	b8 00 00 00 00       	mov    $0x0,%eax
    2817:	e8 f8 f8 ff ff       	callq  2114 <secret_phase>
    281c:	eb ad                	jmp    27cb <phase_defused+0x6c>
    281e:	e8 8d f0 ff ff       	callq  18b0 <__stack_chk_fail@plt>

0000000000002823 <sigalrm_handler>:
    2823:	48 83 ec 08          	sub    $0x8,%rsp
    2827:	b9 00 00 00 00       	mov    $0x0,%ecx
    282c:	48 8d 15 65 14 00 00 	lea    0x1465(%rip),%rdx        # 3c98 <array.3434+0x638>
    2833:	be 01 00 00 00       	mov    $0x1,%esi
    2838:	48 8b 3d 61 2e 20 00 	mov    0x202e61(%rip),%rdi        # 2056a0 <stderr@@GLIBC_2.2.5>
    283f:	b8 00 00 00 00       	mov    $0x0,%eax
    2844:	e8 67 f1 ff ff       	callq  19b0 <__fprintf_chk@plt>
    2849:	bf 01 00 00 00       	mov    $0x1,%edi
    284e:	e8 3d f1 ff ff       	callq  1990 <exit@plt>

0000000000002853 <rio_readlineb>:
    2853:	41 56                	push   %r14
    2855:	41 55                	push   %r13
    2857:	41 54                	push   %r12
    2859:	55                   	push   %rbp
    285a:	53                   	push   %rbx
    285b:	48 89 fb             	mov    %rdi,%rbx
    285e:	49 89 f4             	mov    %rsi,%r12
    2861:	49 89 d6             	mov    %rdx,%r14
    2864:	41 bd 01 00 00 00    	mov    $0x1,%r13d
    286a:	48 8d 6f 10          	lea    0x10(%rdi),%rbp
    286e:	48 83 fa 01          	cmp    $0x1,%rdx
    2872:	77 0c                	ja     2880 <rio_readlineb+0x2d>
    2874:	eb 60                	jmp    28d6 <rio_readlineb+0x83>
    2876:	e8 f5 ef ff ff       	callq  1870 <__errno_location@plt>
    287b:	83 38 04             	cmpl   $0x4,(%rax)
    287e:	75 67                	jne    28e7 <rio_readlineb+0x94>
    2880:	8b 43 04             	mov    0x4(%rbx),%eax
    2883:	85 c0                	test   %eax,%eax
    2885:	7f 20                	jg     28a7 <rio_readlineb+0x54>
    2887:	ba 00 20 00 00       	mov    $0x2000,%edx
    288c:	48 89 ee             	mov    %rbp,%rsi
    288f:	8b 3b                	mov    (%rbx),%edi
    2891:	e8 4a f0 ff ff       	callq  18e0 <read@plt>
    2896:	89 43 04             	mov    %eax,0x4(%rbx)
    2899:	85 c0                	test   %eax,%eax
    289b:	78 d9                	js     2876 <rio_readlineb+0x23>
    289d:	85 c0                	test   %eax,%eax
    289f:	74 4f                	je     28f0 <rio_readlineb+0x9d>
    28a1:	48 89 6b 08          	mov    %rbp,0x8(%rbx)
    28a5:	eb d9                	jmp    2880 <rio_readlineb+0x2d>
    28a7:	48 8b 53 08          	mov    0x8(%rbx),%rdx
    28ab:	0f b6 0a             	movzbl (%rdx),%ecx
    28ae:	48 83 c2 01          	add    $0x1,%rdx
    28b2:	48 89 53 08          	mov    %rdx,0x8(%rbx)
    28b6:	83 e8 01             	sub    $0x1,%eax
    28b9:	89 43 04             	mov    %eax,0x4(%rbx)
    28bc:	49 83 c4 01          	add    $0x1,%r12
    28c0:	41 88 4c 24 ff       	mov    %cl,-0x1(%r12)
    28c5:	80 f9 0a             	cmp    $0xa,%cl
    28c8:	74 0c                	je     28d6 <rio_readlineb+0x83>
    28ca:	41 83 c5 01          	add    $0x1,%r13d
    28ce:	49 63 c5             	movslq %r13d,%rax
    28d1:	4c 39 f0             	cmp    %r14,%rax
    28d4:	72 aa                	jb     2880 <rio_readlineb+0x2d>
    28d6:	41 c6 04 24 00       	movb   $0x0,(%r12)
    28db:	49 63 c5             	movslq %r13d,%rax
    28de:	5b                   	pop    %rbx
    28df:	5d                   	pop    %rbp
    28e0:	41 5c                	pop    %r12
    28e2:	41 5d                	pop    %r13
    28e4:	41 5e                	pop    %r14
    28e6:	c3                   	retq   
    28e7:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
    28ee:	eb 05                	jmp    28f5 <rio_readlineb+0xa2>
    28f0:	b8 00 00 00 00       	mov    $0x0,%eax
    28f5:	85 c0                	test   %eax,%eax
    28f7:	75 0d                	jne    2906 <rio_readlineb+0xb3>
    28f9:	b8 00 00 00 00       	mov    $0x0,%eax
    28fe:	41 83 fd 01          	cmp    $0x1,%r13d
    2902:	75 d2                	jne    28d6 <rio_readlineb+0x83>
    2904:	eb d8                	jmp    28de <rio_readlineb+0x8b>
    2906:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
    290d:	eb cf                	jmp    28de <rio_readlineb+0x8b>

000000000000290f <submitr>:
    290f:	41 57                	push   %r15
    2911:	41 56                	push   %r14
    2913:	41 55                	push   %r13
    2915:	41 54                	push   %r12
    2917:	55                   	push   %rbp
    2918:	53                   	push   %rbx
    2919:	48 81 ec 78 a0 00 00 	sub    $0xa078,%rsp
    2920:	49 89 fd             	mov    %rdi,%r13
    2923:	89 f5                	mov    %esi,%ebp
    2925:	48 89 54 24 08       	mov    %rdx,0x8(%rsp)
    292a:	48 89 4c 24 10       	mov    %rcx,0x10(%rsp)
    292f:	4c 89 44 24 20       	mov    %r8,0x20(%rsp)
    2934:	4c 89 4c 24 18       	mov    %r9,0x18(%rsp)
    2939:	48 8b 9c 24 b0 a0 00 	mov    0xa0b0(%rsp),%rbx
    2940:	00 
    2941:	4c 8b bc 24 b8 a0 00 	mov    0xa0b8(%rsp),%r15
    2948:	00 
    2949:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2950:	00 00 
    2952:	48 89 84 24 68 a0 00 	mov    %rax,0xa068(%rsp)
    2959:	00 
    295a:	31 c0                	xor    %eax,%eax
    295c:	c7 44 24 3c 00 00 00 	movl   $0x0,0x3c(%rsp)
    2963:	00 
    2964:	ba 00 00 00 00       	mov    $0x0,%edx
    2969:	be 01 00 00 00       	mov    $0x1,%esi
    296e:	bf 02 00 00 00       	mov    $0x2,%edi
    2973:	e8 78 f0 ff ff       	callq  19f0 <socket@plt>
    2978:	85 c0                	test   %eax,%eax
    297a:	0f 88 35 01 00 00    	js     2ab5 <submitr+0x1a6>
    2980:	41 89 c4             	mov    %eax,%r12d
    2983:	4c 89 ef             	mov    %r13,%rdi
    2986:	e8 85 ef ff ff       	callq  1910 <gethostbyname@plt>
    298b:	48 85 c0             	test   %rax,%rax
    298e:	0f 84 71 01 00 00    	je     2b05 <submitr+0x1f6>
    2994:	4c 8d 6c 24 40       	lea    0x40(%rsp),%r13
    2999:	48 c7 44 24 42 00 00 	movq   $0x0,0x42(%rsp)
    29a0:	00 00 
    29a2:	c7 44 24 4a 00 00 00 	movl   $0x0,0x4a(%rsp)
    29a9:	00 
    29aa:	66 c7 44 24 4e 00 00 	movw   $0x0,0x4e(%rsp)
    29b1:	66 c7 44 24 40 02 00 	movw   $0x2,0x40(%rsp)
    29b8:	48 63 50 14          	movslq 0x14(%rax),%rdx
    29bc:	48 8b 40 18          	mov    0x18(%rax),%rax
    29c0:	48 8d 7c 24 44       	lea    0x44(%rsp),%rdi
    29c5:	b9 0c 00 00 00       	mov    $0xc,%ecx
    29ca:	48 8b 30             	mov    (%rax),%rsi
    29cd:	e8 4e ef ff ff       	callq  1920 <__memmove_chk@plt>
    29d2:	66 c1 cd 08          	ror    $0x8,%bp
    29d6:	66 89 6c 24 42       	mov    %bp,0x42(%rsp)
    29db:	ba 10 00 00 00       	mov    $0x10,%edx
    29e0:	4c 89 ee             	mov    %r13,%rsi
    29e3:	44 89 e7             	mov    %r12d,%edi
    29e6:	e8 b5 ef ff ff       	callq  19a0 <connect@plt>
    29eb:	85 c0                	test   %eax,%eax
    29ed:	0f 88 7d 01 00 00    	js     2b70 <submitr+0x261>
    29f3:	49 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%r9
    29fa:	b8 00 00 00 00       	mov    $0x0,%eax
    29ff:	4c 89 c9             	mov    %r9,%rcx
    2a02:	48 89 df             	mov    %rbx,%rdi
    2a05:	f2 ae                	repnz scas %es:(%rdi),%al
    2a07:	48 89 ce             	mov    %rcx,%rsi
    2a0a:	48 f7 d6             	not    %rsi
    2a0d:	4c 89 c9             	mov    %r9,%rcx
    2a10:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
    2a15:	f2 ae                	repnz scas %es:(%rdi),%al
    2a17:	49 89 c8             	mov    %rcx,%r8
    2a1a:	4c 89 c9             	mov    %r9,%rcx
    2a1d:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
    2a22:	f2 ae                	repnz scas %es:(%rdi),%al
    2a24:	48 89 ca             	mov    %rcx,%rdx
    2a27:	48 f7 d2             	not    %rdx
    2a2a:	4c 89 c9             	mov    %r9,%rcx
    2a2d:	48 8b 7c 24 18       	mov    0x18(%rsp),%rdi
    2a32:	f2 ae                	repnz scas %es:(%rdi),%al
    2a34:	4c 29 c2             	sub    %r8,%rdx
    2a37:	48 29 ca             	sub    %rcx,%rdx
    2a3a:	48 8d 44 76 fd       	lea    -0x3(%rsi,%rsi,2),%rax
    2a3f:	48 8d 44 02 7b       	lea    0x7b(%rdx,%rax,1),%rax
    2a44:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
    2a4a:	0f 87 7d 01 00 00    	ja     2bcd <submitr+0x2be>
    2a50:	48 8d 94 24 60 40 00 	lea    0x4060(%rsp),%rdx
    2a57:	00 
    2a58:	b9 00 04 00 00       	mov    $0x400,%ecx
    2a5d:	b8 00 00 00 00       	mov    $0x0,%eax
    2a62:	48 89 d7             	mov    %rdx,%rdi
    2a65:	f3 48 ab             	rep stos %rax,%es:(%rdi)
    2a68:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
    2a6f:	48 89 df             	mov    %rbx,%rdi
    2a72:	f2 ae                	repnz scas %es:(%rdi),%al
    2a74:	48 89 ca             	mov    %rcx,%rdx
    2a77:	48 f7 d2             	not    %rdx
    2a7a:	48 89 d1             	mov    %rdx,%rcx
    2a7d:	48 83 e9 01          	sub    $0x1,%rcx
    2a81:	85 c9                	test   %ecx,%ecx
    2a83:	0f 84 3f 06 00 00    	je     30c8 <submitr+0x7b9>
    2a89:	8d 41 ff             	lea    -0x1(%rcx),%eax
    2a8c:	4c 8d 74 03 01       	lea    0x1(%rbx,%rax,1),%r14
    2a91:	48 8d ac 24 60 40 00 	lea    0x4060(%rsp),%rbp
    2a98:	00 
    2a99:	48 8d 84 24 60 80 00 	lea    0x8060(%rsp),%rax
    2aa0:	00 
    2aa1:	48 89 44 24 28       	mov    %rax,0x28(%rsp)
    2aa6:	49 bd d9 ff 00 00 00 	movabs $0x2000000000ffd9,%r13
    2aad:	00 20 00 
    2ab0:	e9 a6 01 00 00       	jmpq   2c5b <submitr+0x34c>
    2ab5:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    2abc:	3a 20 43 
    2abf:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    2ac6:	20 75 6e 
    2ac9:	49 89 07             	mov    %rax,(%r15)
    2acc:	49 89 57 08          	mov    %rdx,0x8(%r15)
    2ad0:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    2ad7:	74 6f 20 
    2ada:	48 ba 63 72 65 61 74 	movabs $0x7320657461657263,%rdx
    2ae1:	65 20 73 
    2ae4:	49 89 47 10          	mov    %rax,0x10(%r15)
    2ae8:	49 89 57 18          	mov    %rdx,0x18(%r15)
    2aec:	41 c7 47 20 6f 63 6b 	movl   $0x656b636f,0x20(%r15)
    2af3:	65 
    2af4:	66 41 c7 47 24 74 00 	movw   $0x74,0x24(%r15)
    2afb:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2b00:	e9 9a 04 00 00       	jmpq   2f9f <submitr+0x690>
    2b05:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
    2b0c:	3a 20 44 
    2b0f:	48 ba 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rdx
    2b16:	20 75 6e 
    2b19:	49 89 07             	mov    %rax,(%r15)
    2b1c:	49 89 57 08          	mov    %rdx,0x8(%r15)
    2b20:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    2b27:	74 6f 20 
    2b2a:	48 ba 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rdx
    2b31:	76 65 20 
    2b34:	49 89 47 10          	mov    %rax,0x10(%r15)
    2b38:	49 89 57 18          	mov    %rdx,0x18(%r15)
    2b3c:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
    2b43:	72 20 61 
    2b46:	49 89 47 20          	mov    %rax,0x20(%r15)
    2b4a:	41 c7 47 28 64 64 72 	movl   $0x65726464,0x28(%r15)
    2b51:	65 
    2b52:	66 41 c7 47 2c 73 73 	movw   $0x7373,0x2c(%r15)
    2b59:	41 c6 47 2e 00       	movb   $0x0,0x2e(%r15)
    2b5e:	44 89 e7             	mov    %r12d,%edi
    2b61:	e8 6a ed ff ff       	callq  18d0 <close@plt>
    2b66:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2b6b:	e9 2f 04 00 00       	jmpq   2f9f <submitr+0x690>
    2b70:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
    2b77:	3a 20 55 
    2b7a:	48 ba 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rdx
    2b81:	20 74 6f 
    2b84:	49 89 07             	mov    %rax,(%r15)
    2b87:	49 89 57 08          	mov    %rdx,0x8(%r15)
    2b8b:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
    2b92:	65 63 74 
    2b95:	48 ba 20 74 6f 20 74 	movabs $0x20656874206f7420,%rdx
    2b9c:	68 65 20 
    2b9f:	49 89 47 10          	mov    %rax,0x10(%r15)
    2ba3:	49 89 57 18          	mov    %rdx,0x18(%r15)
    2ba7:	41 c7 47 20 73 65 72 	movl   $0x76726573,0x20(%r15)
    2bae:	76 
    2baf:	66 41 c7 47 24 65 72 	movw   $0x7265,0x24(%r15)
    2bb6:	41 c6 47 26 00       	movb   $0x0,0x26(%r15)
    2bbb:	44 89 e7             	mov    %r12d,%edi
    2bbe:	e8 0d ed ff ff       	callq  18d0 <close@plt>
    2bc3:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2bc8:	e9 d2 03 00 00       	jmpq   2f9f <submitr+0x690>
    2bcd:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
    2bd4:	3a 20 52 
    2bd7:	48 ba 65 73 75 6c 74 	movabs $0x747320746c757365,%rdx
    2bde:	20 73 74 
    2be1:	49 89 07             	mov    %rax,(%r15)
    2be4:	49 89 57 08          	mov    %rdx,0x8(%r15)
    2be8:	48 b8 72 69 6e 67 20 	movabs $0x6f6f7420676e6972,%rax
    2bef:	74 6f 6f 
    2bf2:	48 ba 20 6c 61 72 67 	movabs $0x202e656772616c20,%rdx
    2bf9:	65 2e 20 
    2bfc:	49 89 47 10          	mov    %rax,0x10(%r15)
    2c00:	49 89 57 18          	mov    %rdx,0x18(%r15)
    2c04:	48 b8 49 6e 63 72 65 	movabs $0x6573616572636e49,%rax
    2c0b:	61 73 65 
    2c0e:	48 ba 20 53 55 42 4d 	movabs $0x5254494d42555320,%rdx
    2c15:	49 54 52 
    2c18:	49 89 47 20          	mov    %rax,0x20(%r15)
    2c1c:	49 89 57 28          	mov    %rdx,0x28(%r15)
    2c20:	48 b8 5f 4d 41 58 42 	movabs $0x46554258414d5f,%rax
    2c27:	55 46 00 
    2c2a:	49 89 47 30          	mov    %rax,0x30(%r15)
    2c2e:	44 89 e7             	mov    %r12d,%edi
    2c31:	e8 9a ec ff ff       	callq  18d0 <close@plt>
    2c36:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2c3b:	e9 5f 03 00 00       	jmpq   2f9f <submitr+0x690>
    2c40:	49 0f a3 c5          	bt     %rax,%r13
    2c44:	73 21                	jae    2c67 <submitr+0x358>
    2c46:	44 88 45 00          	mov    %r8b,0x0(%rbp)
    2c4a:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
    2c4e:	48 83 c3 01          	add    $0x1,%rbx
    2c52:	4c 39 f3             	cmp    %r14,%rbx
    2c55:	0f 84 6d 04 00 00    	je     30c8 <submitr+0x7b9>
    2c5b:	44 0f b6 03          	movzbl (%rbx),%r8d
    2c5f:	41 8d 40 d6          	lea    -0x2a(%r8),%eax
    2c63:	3c 35                	cmp    $0x35,%al
    2c65:	76 d9                	jbe    2c40 <submitr+0x331>
    2c67:	44 89 c0             	mov    %r8d,%eax
    2c6a:	83 e0 df             	and    $0xffffffdf,%eax
    2c6d:	83 e8 41             	sub    $0x41,%eax
    2c70:	3c 19                	cmp    $0x19,%al
    2c72:	76 d2                	jbe    2c46 <submitr+0x337>
    2c74:	41 80 f8 20          	cmp    $0x20,%r8b
    2c78:	74 60                	je     2cda <submitr+0x3cb>
    2c7a:	41 8d 40 e0          	lea    -0x20(%r8),%eax
    2c7e:	3c 5f                	cmp    $0x5f,%al
    2c80:	76 0a                	jbe    2c8c <submitr+0x37d>
    2c82:	41 80 f8 09          	cmp    $0x9,%r8b
    2c86:	0f 85 af 03 00 00    	jne    303b <submitr+0x72c>
    2c8c:	45 0f b6 c0          	movzbl %r8b,%r8d
    2c90:	48 8d 0d d9 10 00 00 	lea    0x10d9(%rip),%rcx        # 3d70 <array.3434+0x710>
    2c97:	ba 08 00 00 00       	mov    $0x8,%edx
    2c9c:	be 01 00 00 00       	mov    $0x1,%esi
    2ca1:	48 8b 7c 24 28       	mov    0x28(%rsp),%rdi
    2ca6:	b8 00 00 00 00       	mov    $0x0,%eax
    2cab:	e8 30 ed ff ff       	callq  19e0 <__sprintf_chk@plt>
    2cb0:	0f b6 84 24 60 80 00 	movzbl 0x8060(%rsp),%eax
    2cb7:	00 
    2cb8:	88 45 00             	mov    %al,0x0(%rbp)
    2cbb:	0f b6 84 24 61 80 00 	movzbl 0x8061(%rsp),%eax
    2cc2:	00 
    2cc3:	88 45 01             	mov    %al,0x1(%rbp)
    2cc6:	0f b6 84 24 62 80 00 	movzbl 0x8062(%rsp),%eax
    2ccd:	00 
    2cce:	88 45 02             	mov    %al,0x2(%rbp)
    2cd1:	48 8d 6d 03          	lea    0x3(%rbp),%rbp
    2cd5:	e9 74 ff ff ff       	jmpq   2c4e <submitr+0x33f>
    2cda:	c6 45 00 2b          	movb   $0x2b,0x0(%rbp)
    2cde:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
    2ce2:	e9 67 ff ff ff       	jmpq   2c4e <submitr+0x33f>
    2ce7:	49 01 c5             	add    %rax,%r13
    2cea:	48 29 c5             	sub    %rax,%rbp
    2ced:	74 26                	je     2d15 <submitr+0x406>
    2cef:	48 89 ea             	mov    %rbp,%rdx
    2cf2:	4c 89 ee             	mov    %r13,%rsi
    2cf5:	44 89 e7             	mov    %r12d,%edi
    2cf8:	e8 a3 eb ff ff       	callq  18a0 <write@plt>
    2cfd:	48 85 c0             	test   %rax,%rax
    2d00:	7f e5                	jg     2ce7 <submitr+0x3d8>
    2d02:	e8 69 eb ff ff       	callq  1870 <__errno_location@plt>
    2d07:	83 38 04             	cmpl   $0x4,(%rax)
    2d0a:	0f 85 31 01 00 00    	jne    2e41 <submitr+0x532>
    2d10:	4c 89 f0             	mov    %r14,%rax
    2d13:	eb d2                	jmp    2ce7 <submitr+0x3d8>
    2d15:	48 85 db             	test   %rbx,%rbx
    2d18:	0f 88 23 01 00 00    	js     2e41 <submitr+0x532>
    2d1e:	44 89 64 24 50       	mov    %r12d,0x50(%rsp)
    2d23:	c7 44 24 54 00 00 00 	movl   $0x0,0x54(%rsp)
    2d2a:	00 
    2d2b:	48 8d 7c 24 50       	lea    0x50(%rsp),%rdi
    2d30:	48 8d 47 10          	lea    0x10(%rdi),%rax
    2d34:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
    2d39:	48 8d b4 24 60 20 00 	lea    0x2060(%rsp),%rsi
    2d40:	00 
    2d41:	ba 00 20 00 00       	mov    $0x2000,%edx
    2d46:	e8 08 fb ff ff       	callq  2853 <rio_readlineb>
    2d4b:	48 85 c0             	test   %rax,%rax
    2d4e:	0f 8e 4c 01 00 00    	jle    2ea0 <submitr+0x591>
    2d54:	48 8d 4c 24 3c       	lea    0x3c(%rsp),%rcx
    2d59:	48 8d 94 24 60 60 00 	lea    0x6060(%rsp),%rdx
    2d60:	00 
    2d61:	48 8d bc 24 60 20 00 	lea    0x2060(%rsp),%rdi
    2d68:	00 
    2d69:	4c 8d 84 24 60 80 00 	lea    0x8060(%rsp),%r8
    2d70:	00 
    2d71:	48 8d 35 ff 0f 00 00 	lea    0xfff(%rip),%rsi        # 3d77 <array.3434+0x717>
    2d78:	b8 00 00 00 00       	mov    $0x0,%eax
    2d7d:	e8 ce eb ff ff       	callq  1950 <__isoc99_sscanf@plt>
    2d82:	44 8b 44 24 3c       	mov    0x3c(%rsp),%r8d
    2d87:	41 81 f8 c8 00 00 00 	cmp    $0xc8,%r8d
    2d8e:	0f 85 80 01 00 00    	jne    2f14 <submitr+0x605>
    2d94:	48 8d 9c 24 60 20 00 	lea    0x2060(%rsp),%rbx
    2d9b:	00 
    2d9c:	48 8d 2d e5 0f 00 00 	lea    0xfe5(%rip),%rbp        # 3d88 <array.3434+0x728>
    2da3:	4c 8d 6c 24 50       	lea    0x50(%rsp),%r13
    2da8:	b9 03 00 00 00       	mov    $0x3,%ecx
    2dad:	48 89 de             	mov    %rbx,%rsi
    2db0:	48 89 ef             	mov    %rbp,%rdi
    2db3:	f3 a6                	repz cmpsb %es:(%rdi),%ds:(%rsi)
    2db5:	0f 97 c0             	seta   %al
    2db8:	1c 00                	sbb    $0x0,%al
    2dba:	84 c0                	test   %al,%al
    2dbc:	0f 84 89 01 00 00    	je     2f4b <submitr+0x63c>
    2dc2:	ba 00 20 00 00       	mov    $0x2000,%edx
    2dc7:	48 89 de             	mov    %rbx,%rsi
    2dca:	4c 89 ef             	mov    %r13,%rdi
    2dcd:	e8 81 fa ff ff       	callq  2853 <rio_readlineb>
    2dd2:	48 85 c0             	test   %rax,%rax
    2dd5:	7f d1                	jg     2da8 <submitr+0x499>
    2dd7:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    2dde:	3a 20 43 
    2de1:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    2de8:	20 75 6e 
    2deb:	49 89 07             	mov    %rax,(%r15)
    2dee:	49 89 57 08          	mov    %rdx,0x8(%r15)
    2df2:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    2df9:	74 6f 20 
    2dfc:	48 ba 72 65 61 64 20 	movabs $0x6165682064616572,%rdx
    2e03:	68 65 61 
    2e06:	49 89 47 10          	mov    %rax,0x10(%r15)
    2e0a:	49 89 57 18          	mov    %rdx,0x18(%r15)
    2e0e:	48 b8 64 65 72 73 20 	movabs $0x6f72662073726564,%rax
    2e15:	66 72 6f 
    2e18:	48 ba 6d 20 73 65 72 	movabs $0x726576726573206d,%rdx
    2e1f:	76 65 72 
    2e22:	49 89 47 20          	mov    %rax,0x20(%r15)
    2e26:	49 89 57 28          	mov    %rdx,0x28(%r15)
    2e2a:	41 c6 47 30 00       	movb   $0x0,0x30(%r15)
    2e2f:	44 89 e7             	mov    %r12d,%edi
    2e32:	e8 99 ea ff ff       	callq  18d0 <close@plt>
    2e37:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2e3c:	e9 5e 01 00 00       	jmpq   2f9f <submitr+0x690>
    2e41:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    2e48:	3a 20 43 
    2e4b:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    2e52:	20 75 6e 
    2e55:	49 89 07             	mov    %rax,(%r15)
    2e58:	49 89 57 08          	mov    %rdx,0x8(%r15)
    2e5c:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    2e63:	74 6f 20 
    2e66:	48 ba 77 72 69 74 65 	movabs $0x6f74206574697277,%rdx
    2e6d:	20 74 6f 
    2e70:	49 89 47 10          	mov    %rax,0x10(%r15)
    2e74:	49 89 57 18          	mov    %rdx,0x18(%r15)
    2e78:	48 b8 20 74 68 65 20 	movabs $0x7265732065687420,%rax
    2e7f:	73 65 72 
    2e82:	49 89 47 20          	mov    %rax,0x20(%r15)
    2e86:	41 c7 47 28 76 65 72 	movl   $0x726576,0x28(%r15)
    2e8d:	00 
    2e8e:	44 89 e7             	mov    %r12d,%edi
    2e91:	e8 3a ea ff ff       	callq  18d0 <close@plt>
    2e96:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2e9b:	e9 ff 00 00 00       	jmpq   2f9f <submitr+0x690>
    2ea0:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    2ea7:	3a 20 43 
    2eaa:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    2eb1:	20 75 6e 
    2eb4:	49 89 07             	mov    %rax,(%r15)
    2eb7:	49 89 57 08          	mov    %rdx,0x8(%r15)
    2ebb:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    2ec2:	74 6f 20 
    2ec5:	48 ba 72 65 61 64 20 	movabs $0x7269662064616572,%rdx
    2ecc:	66 69 72 
    2ecf:	49 89 47 10          	mov    %rax,0x10(%r15)
    2ed3:	49 89 57 18          	mov    %rdx,0x18(%r15)
    2ed7:	48 b8 73 74 20 68 65 	movabs $0x6564616568207473,%rax
    2ede:	61 64 65 
    2ee1:	48 ba 72 20 66 72 6f 	movabs $0x73206d6f72662072,%rdx
    2ee8:	6d 20 73 
    2eeb:	49 89 47 20          	mov    %rax,0x20(%r15)
    2eef:	49 89 57 28          	mov    %rdx,0x28(%r15)
    2ef3:	41 c7 47 30 65 72 76 	movl   $0x65767265,0x30(%r15)
    2efa:	65 
    2efb:	66 41 c7 47 34 72 00 	movw   $0x72,0x34(%r15)
    2f02:	44 89 e7             	mov    %r12d,%edi
    2f05:	e8 c6 e9 ff ff       	callq  18d0 <close@plt>
    2f0a:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2f0f:	e9 8b 00 00 00       	jmpq   2f9f <submitr+0x690>
    2f14:	4c 8d 8c 24 60 80 00 	lea    0x8060(%rsp),%r9
    2f1b:	00 
    2f1c:	48 8d 0d 9d 0d 00 00 	lea    0xd9d(%rip),%rcx        # 3cc0 <array.3434+0x660>
    2f23:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
    2f2a:	be 01 00 00 00       	mov    $0x1,%esi
    2f2f:	4c 89 ff             	mov    %r15,%rdi
    2f32:	b8 00 00 00 00       	mov    $0x0,%eax
    2f37:	e8 a4 ea ff ff       	callq  19e0 <__sprintf_chk@plt>
    2f3c:	44 89 e7             	mov    %r12d,%edi
    2f3f:	e8 8c e9 ff ff       	callq  18d0 <close@plt>
    2f44:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    2f49:	eb 54                	jmp    2f9f <submitr+0x690>
    2f4b:	48 8d b4 24 60 20 00 	lea    0x2060(%rsp),%rsi
    2f52:	00 
    2f53:	48 8d 7c 24 50       	lea    0x50(%rsp),%rdi
    2f58:	ba 00 20 00 00       	mov    $0x2000,%edx
    2f5d:	e8 f1 f8 ff ff       	callq  2853 <rio_readlineb>
    2f62:	48 85 c0             	test   %rax,%rax
    2f65:	7e 61                	jle    2fc8 <submitr+0x6b9>
    2f67:	48 8d b4 24 60 20 00 	lea    0x2060(%rsp),%rsi
    2f6e:	00 
    2f6f:	4c 89 ff             	mov    %r15,%rdi
    2f72:	e8 09 e9 ff ff       	callq  1880 <strcpy@plt>
    2f77:	44 89 e7             	mov    %r12d,%edi
    2f7a:	e8 51 e9 ff ff       	callq  18d0 <close@plt>
    2f7f:	b9 03 00 00 00       	mov    $0x3,%ecx
    2f84:	48 8d 3d 00 0e 00 00 	lea    0xe00(%rip),%rdi        # 3d8b <array.3434+0x72b>
    2f8b:	4c 89 fe             	mov    %r15,%rsi
    2f8e:	f3 a6                	repz cmpsb %es:(%rdi),%ds:(%rsi)
    2f90:	0f 97 c0             	seta   %al
    2f93:	1c 00                	sbb    $0x0,%al
    2f95:	84 c0                	test   %al,%al
    2f97:	0f 95 c0             	setne  %al
    2f9a:	0f b6 c0             	movzbl %al,%eax
    2f9d:	f7 d8                	neg    %eax
    2f9f:	48 8b 94 24 68 a0 00 	mov    0xa068(%rsp),%rdx
    2fa6:	00 
    2fa7:	64 48 33 14 25 28 00 	xor    %fs:0x28,%rdx
    2fae:	00 00 
    2fb0:	0f 85 95 01 00 00    	jne    314b <submitr+0x83c>
    2fb6:	48 81 c4 78 a0 00 00 	add    $0xa078,%rsp
    2fbd:	5b                   	pop    %rbx
    2fbe:	5d                   	pop    %rbp
    2fbf:	41 5c                	pop    %r12
    2fc1:	41 5d                	pop    %r13
    2fc3:	41 5e                	pop    %r14
    2fc5:	41 5f                	pop    %r15
    2fc7:	c3                   	retq   
    2fc8:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    2fcf:	3a 20 43 
    2fd2:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    2fd9:	20 75 6e 
    2fdc:	49 89 07             	mov    %rax,(%r15)
    2fdf:	49 89 57 08          	mov    %rdx,0x8(%r15)
    2fe3:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    2fea:	74 6f 20 
    2fed:	48 ba 72 65 61 64 20 	movabs $0x6174732064616572,%rdx
    2ff4:	73 74 61 
    2ff7:	49 89 47 10          	mov    %rax,0x10(%r15)
    2ffb:	49 89 57 18          	mov    %rdx,0x18(%r15)
    2fff:	48 b8 74 75 73 20 6d 	movabs $0x7373656d20737574,%rax
    3006:	65 73 73 
    3009:	48 ba 61 67 65 20 66 	movabs $0x6d6f726620656761,%rdx
    3010:	72 6f 6d 
    3013:	49 89 47 20          	mov    %rax,0x20(%r15)
    3017:	49 89 57 28          	mov    %rdx,0x28(%r15)
    301b:	48 b8 20 73 65 72 76 	movabs $0x72657672657320,%rax
    3022:	65 72 00 
    3025:	49 89 47 30          	mov    %rax,0x30(%r15)
    3029:	44 89 e7             	mov    %r12d,%edi
    302c:	e8 9f e8 ff ff       	callq  18d0 <close@plt>
    3031:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    3036:	e9 64 ff ff ff       	jmpq   2f9f <submitr+0x690>
    303b:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
    3042:	3a 20 52 
    3045:	48 ba 65 73 75 6c 74 	movabs $0x747320746c757365,%rdx
    304c:	20 73 74 
    304f:	49 89 07             	mov    %rax,(%r15)
    3052:	49 89 57 08          	mov    %rdx,0x8(%r15)
    3056:	48 b8 72 69 6e 67 20 	movabs $0x6e6f6320676e6972,%rax
    305d:	63 6f 6e 
    3060:	48 ba 74 61 69 6e 73 	movabs $0x6e6120736e696174,%rdx
    3067:	20 61 6e 
    306a:	49 89 47 10          	mov    %rax,0x10(%r15)
    306e:	49 89 57 18          	mov    %rdx,0x18(%r15)
    3072:	48 b8 20 69 6c 6c 65 	movabs $0x6c6167656c6c6920,%rax
    3079:	67 61 6c 
    307c:	48 ba 20 6f 72 20 75 	movabs $0x72706e7520726f20,%rdx
    3083:	6e 70 72 
    3086:	49 89 47 20          	mov    %rax,0x20(%r15)
    308a:	49 89 57 28          	mov    %rdx,0x28(%r15)
    308e:	48 b8 69 6e 74 61 62 	movabs $0x20656c6261746e69,%rax
    3095:	6c 65 20 
    3098:	48 ba 63 68 61 72 61 	movabs $0x6574636172616863,%rdx
    309f:	63 74 65 
    30a2:	49 89 47 30          	mov    %rax,0x30(%r15)
    30a6:	49 89 57 38          	mov    %rdx,0x38(%r15)
    30aa:	66 41 c7 47 40 72 2e 	movw   $0x2e72,0x40(%r15)
    30b1:	41 c6 47 42 00       	movb   $0x0,0x42(%r15)
    30b6:	44 89 e7             	mov    %r12d,%edi
    30b9:	e8 12 e8 ff ff       	callq  18d0 <close@plt>
    30be:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    30c3:	e9 d7 fe ff ff       	jmpq   2f9f <submitr+0x690>
    30c8:	48 8d 9c 24 60 20 00 	lea    0x2060(%rsp),%rbx
    30cf:	00 
    30d0:	48 83 ec 08          	sub    $0x8,%rsp
    30d4:	48 8d 84 24 68 40 00 	lea    0x4068(%rsp),%rax
    30db:	00 
    30dc:	50                   	push   %rax
    30dd:	ff 74 24 28          	pushq  0x28(%rsp)
    30e1:	ff 74 24 38          	pushq  0x38(%rsp)
    30e5:	4c 8b 4c 24 30       	mov    0x30(%rsp),%r9
    30ea:	4c 8b 44 24 28       	mov    0x28(%rsp),%r8
    30ef:	48 8d 0d fa 0b 00 00 	lea    0xbfa(%rip),%rcx        # 3cf0 <array.3434+0x690>
    30f6:	ba 00 20 00 00       	mov    $0x2000,%edx
    30fb:	be 01 00 00 00       	mov    $0x1,%esi
    3100:	48 89 df             	mov    %rbx,%rdi
    3103:	b8 00 00 00 00       	mov    $0x0,%eax
    3108:	e8 d3 e8 ff ff       	callq  19e0 <__sprintf_chk@plt>
    310d:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
    3114:	b8 00 00 00 00       	mov    $0x0,%eax
    3119:	48 89 df             	mov    %rbx,%rdi
    311c:	f2 ae                	repnz scas %es:(%rdi),%al
    311e:	48 f7 d1             	not    %rcx
    3121:	48 89 cb             	mov    %rcx,%rbx
    3124:	48 83 eb 01          	sub    $0x1,%rbx
    3128:	48 83 c4 20          	add    $0x20,%rsp
    312c:	48 89 dd             	mov    %rbx,%rbp
    312f:	4c 8d ac 24 60 20 00 	lea    0x2060(%rsp),%r13
    3136:	00 
    3137:	41 be 00 00 00 00    	mov    $0x0,%r14d
    313d:	48 85 db             	test   %rbx,%rbx
    3140:	0f 85 a9 fb ff ff    	jne    2cef <submitr+0x3e0>
    3146:	e9 d3 fb ff ff       	jmpq   2d1e <submitr+0x40f>
    314b:	e8 60 e7 ff ff       	callq  18b0 <__stack_chk_fail@plt>

0000000000003150 <init_timeout>:
    3150:	85 ff                	test   %edi,%edi
    3152:	74 25                	je     3179 <init_timeout+0x29>
    3154:	53                   	push   %rbx
    3155:	89 fb                	mov    %edi,%ebx
    3157:	48 8d 35 c5 f6 ff ff 	lea    -0x93b(%rip),%rsi        # 2823 <sigalrm_handler>
    315e:	bf 0e 00 00 00       	mov    $0xe,%edi
    3163:	e8 98 e7 ff ff       	callq  1900 <signal@plt>
    3168:	85 db                	test   %ebx,%ebx
    316a:	bf 00 00 00 00       	mov    $0x0,%edi
    316f:	0f 49 fb             	cmovns %ebx,%edi
    3172:	e8 49 e7 ff ff       	callq  18c0 <alarm@plt>
    3177:	5b                   	pop    %rbx
    3178:	c3                   	retq   
    3179:	f3 c3                	repz retq 

000000000000317b <init_driver>:
    317b:	41 54                	push   %r12
    317d:	55                   	push   %rbp
    317e:	53                   	push   %rbx
    317f:	48 83 ec 20          	sub    $0x20,%rsp
    3183:	49 89 fc             	mov    %rdi,%r12
    3186:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    318d:	00 00 
    318f:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
    3194:	31 c0                	xor    %eax,%eax
    3196:	be 01 00 00 00       	mov    $0x1,%esi
    319b:	bf 0d 00 00 00       	mov    $0xd,%edi
    31a0:	e8 5b e7 ff ff       	callq  1900 <signal@plt>
    31a5:	be 01 00 00 00       	mov    $0x1,%esi
    31aa:	bf 1d 00 00 00       	mov    $0x1d,%edi
    31af:	e8 4c e7 ff ff       	callq  1900 <signal@plt>
    31b4:	be 01 00 00 00       	mov    $0x1,%esi
    31b9:	bf 1d 00 00 00       	mov    $0x1d,%edi
    31be:	e8 3d e7 ff ff       	callq  1900 <signal@plt>
    31c3:	ba 00 00 00 00       	mov    $0x0,%edx
    31c8:	be 01 00 00 00       	mov    $0x1,%esi
    31cd:	bf 02 00 00 00       	mov    $0x2,%edi
    31d2:	e8 19 e8 ff ff       	callq  19f0 <socket@plt>
    31d7:	85 c0                	test   %eax,%eax
    31d9:	0f 88 a3 00 00 00    	js     3282 <init_driver+0x107>
    31df:	89 c3                	mov    %eax,%ebx
    31e1:	48 8d 3d a6 0b 00 00 	lea    0xba6(%rip),%rdi        # 3d8e <array.3434+0x72e>
    31e8:	e8 23 e7 ff ff       	callq  1910 <gethostbyname@plt>
    31ed:	48 85 c0             	test   %rax,%rax
    31f0:	0f 84 df 00 00 00    	je     32d5 <init_driver+0x15a>
    31f6:	48 89 e5             	mov    %rsp,%rbp
    31f9:	48 c7 44 24 02 00 00 	movq   $0x0,0x2(%rsp)
    3200:	00 00 
    3202:	c7 45 0a 00 00 00 00 	movl   $0x0,0xa(%rbp)
    3209:	66 c7 45 0e 00 00    	movw   $0x0,0xe(%rbp)
    320f:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
    3215:	48 63 50 14          	movslq 0x14(%rax),%rdx
    3219:	48 8b 40 18          	mov    0x18(%rax),%rax
    321d:	48 8d 7d 04          	lea    0x4(%rbp),%rdi
    3221:	b9 0c 00 00 00       	mov    $0xc,%ecx
    3226:	48 8b 30             	mov    (%rax),%rsi
    3229:	e8 f2 e6 ff ff       	callq  1920 <__memmove_chk@plt>
    322e:	66 c7 44 24 02 3c 9a 	movw   $0x9a3c,0x2(%rsp)
    3235:	ba 10 00 00 00       	mov    $0x10,%edx
    323a:	48 89 ee             	mov    %rbp,%rsi
    323d:	89 df                	mov    %ebx,%edi
    323f:	e8 5c e7 ff ff       	callq  19a0 <connect@plt>
    3244:	85 c0                	test   %eax,%eax
    3246:	0f 88 fb 00 00 00    	js     3347 <init_driver+0x1cc>
    324c:	89 df                	mov    %ebx,%edi
    324e:	e8 7d e6 ff ff       	callq  18d0 <close@plt>
    3253:	66 41 c7 04 24 4f 4b 	movw   $0x4b4f,(%r12)
    325a:	41 c6 44 24 02 00    	movb   $0x0,0x2(%r12)
    3260:	b8 00 00 00 00       	mov    $0x0,%eax
    3265:	48 8b 4c 24 18       	mov    0x18(%rsp),%rcx
    326a:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
    3271:	00 00 
    3273:	0f 85 06 01 00 00    	jne    337f <init_driver+0x204>
    3279:	48 83 c4 20          	add    $0x20,%rsp
    327d:	5b                   	pop    %rbx
    327e:	5d                   	pop    %rbp
    327f:	41 5c                	pop    %r12
    3281:	c3                   	retq   
    3282:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
    3289:	3a 20 43 
    328c:	48 ba 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rdx
    3293:	20 75 6e 
    3296:	49 89 04 24          	mov    %rax,(%r12)
    329a:	49 89 54 24 08       	mov    %rdx,0x8(%r12)
    329f:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    32a6:	74 6f 20 
    32a9:	48 ba 63 72 65 61 74 	movabs $0x7320657461657263,%rdx
    32b0:	65 20 73 
    32b3:	49 89 44 24 10       	mov    %rax,0x10(%r12)
    32b8:	49 89 54 24 18       	mov    %rdx,0x18(%r12)
    32bd:	41 c7 44 24 20 6f 63 	movl   $0x656b636f,0x20(%r12)
    32c4:	6b 65 
    32c6:	66 41 c7 44 24 24 74 	movw   $0x74,0x24(%r12)
    32cd:	00 
    32ce:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    32d3:	eb 90                	jmp    3265 <init_driver+0xea>
    32d5:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
    32dc:	3a 20 44 
    32df:	48 ba 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rdx
    32e6:	20 75 6e 
    32e9:	49 89 04 24          	mov    %rax,(%r12)
    32ed:	49 89 54 24 08       	mov    %rdx,0x8(%r12)
    32f2:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
    32f9:	74 6f 20 
    32fc:	48 ba 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rdx
    3303:	76 65 20 
    3306:	49 89 44 24 10       	mov    %rax,0x10(%r12)
    330b:	49 89 54 24 18       	mov    %rdx,0x18(%r12)
    3310:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
    3317:	72 20 61 
    331a:	49 89 44 24 20       	mov    %rax,0x20(%r12)
    331f:	41 c7 44 24 28 64 64 	movl   $0x65726464,0x28(%r12)
    3326:	72 65 
    3328:	66 41 c7 44 24 2c 73 	movw   $0x7373,0x2c(%r12)
    332f:	73 
    3330:	41 c6 44 24 2e 00    	movb   $0x0,0x2e(%r12)
    3336:	89 df                	mov    %ebx,%edi
    3338:	e8 93 e5 ff ff       	callq  18d0 <close@plt>
    333d:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    3342:	e9 1e ff ff ff       	jmpq   3265 <init_driver+0xea>
    3347:	4c 8d 05 40 0a 00 00 	lea    0xa40(%rip),%r8        # 3d8e <array.3434+0x72e>
    334e:	48 8d 0d f3 09 00 00 	lea    0x9f3(%rip),%rcx        # 3d48 <array.3434+0x6e8>
    3355:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
    335c:	be 01 00 00 00       	mov    $0x1,%esi
    3361:	4c 89 e7             	mov    %r12,%rdi
    3364:	b8 00 00 00 00       	mov    $0x0,%eax
    3369:	e8 72 e6 ff ff       	callq  19e0 <__sprintf_chk@plt>
    336e:	89 df                	mov    %ebx,%edi
    3370:	e8 5b e5 ff ff       	callq  18d0 <close@plt>
    3375:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    337a:	e9 e6 fe ff ff       	jmpq   3265 <init_driver+0xea>
    337f:	e8 2c e5 ff ff       	callq  18b0 <__stack_chk_fail@plt>

0000000000003384 <driver_post>:
    3384:	53                   	push   %rbx
    3385:	4c 89 c3             	mov    %r8,%rbx
    3388:	85 c9                	test   %ecx,%ecx
    338a:	75 17                	jne    33a3 <driver_post+0x1f>
    338c:	48 85 ff             	test   %rdi,%rdi
    338f:	74 05                	je     3396 <driver_post+0x12>
    3391:	80 3f 00             	cmpb   $0x0,(%rdi)
    3394:	75 33                	jne    33c9 <driver_post+0x45>
    3396:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
    339b:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
    339f:	89 c8                	mov    %ecx,%eax
    33a1:	5b                   	pop    %rbx
    33a2:	c3                   	retq   
    33a3:	48 8d 35 fd 09 00 00 	lea    0x9fd(%rip),%rsi        # 3da7 <array.3434+0x747>
    33aa:	bf 01 00 00 00       	mov    $0x1,%edi
    33af:	b8 00 00 00 00       	mov    $0x0,%eax
    33b4:	e8 a7 e5 ff ff       	callq  1960 <__printf_chk@plt>
    33b9:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
    33be:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
    33c2:	b8 00 00 00 00       	mov    $0x0,%eax
    33c7:	eb d8                	jmp    33a1 <driver_post+0x1d>
    33c9:	41 50                	push   %r8
    33cb:	52                   	push   %rdx
    33cc:	4c 8d 0d eb 09 00 00 	lea    0x9eb(%rip),%r9        # 3dbe <array.3434+0x75e>
    33d3:	49 89 f0             	mov    %rsi,%r8
    33d6:	48 89 f9             	mov    %rdi,%rcx
    33d9:	48 8d 15 e2 09 00 00 	lea    0x9e2(%rip),%rdx        # 3dc2 <array.3434+0x762>
    33e0:	be 9a 3c 00 00       	mov    $0x3c9a,%esi
    33e5:	48 8d 3d a2 09 00 00 	lea    0x9a2(%rip),%rdi        # 3d8e <array.3434+0x72e>
    33ec:	e8 1e f5 ff ff       	callq  290f <submitr>
    33f1:	48 83 c4 10          	add    $0x10,%rsp
    33f5:	eb aa                	jmp    33a1 <driver_post+0x1d>
    33f7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
    33fe:	00 00 

0000000000003400 <__libc_csu_init>:
    3400:	41 57                	push   %r15
    3402:	41 56                	push   %r14
    3404:	49 89 d7             	mov    %rdx,%r15
    3407:	41 55                	push   %r13
    3409:	41 54                	push   %r12
    340b:	4c 8d 25 ce 18 20 00 	lea    0x2018ce(%rip),%r12        # 204ce0 <__frame_dummy_init_array_entry>
    3412:	55                   	push   %rbp
    3413:	48 8d 2d ce 18 20 00 	lea    0x2018ce(%rip),%rbp        # 204ce8 <__init_array_end>
    341a:	53                   	push   %rbx
    341b:	41 89 fd             	mov    %edi,%r13d
    341e:	49 89 f6             	mov    %rsi,%r14
    3421:	4c 29 e5             	sub    %r12,%rbp
    3424:	48 83 ec 08          	sub    $0x8,%rsp
    3428:	48 c1 fd 03          	sar    $0x3,%rbp
    342c:	e8 e7 e3 ff ff       	callq  1818 <_init>
    3431:	48 85 ed             	test   %rbp,%rbp
    3434:	74 20                	je     3456 <__libc_csu_init+0x56>
    3436:	31 db                	xor    %ebx,%ebx
    3438:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
    343f:	00 
    3440:	4c 89 fa             	mov    %r15,%rdx
    3443:	4c 89 f6             	mov    %r14,%rsi
    3446:	44 89 ef             	mov    %r13d,%edi
    3449:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
    344d:	48 83 c3 01          	add    $0x1,%rbx
    3451:	48 39 dd             	cmp    %rbx,%rbp
    3454:	75 ea                	jne    3440 <__libc_csu_init+0x40>
    3456:	48 83 c4 08          	add    $0x8,%rsp
    345a:	5b                   	pop    %rbx
    345b:	5d                   	pop    %rbp
    345c:	41 5c                	pop    %r12
    345e:	41 5d                	pop    %r13
    3460:	41 5e                	pop    %r14
    3462:	41 5f                	pop    %r15
    3464:	c3                   	retq   
    3465:	90                   	nop
    3466:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    346d:	00 00 00 

0000000000003470 <__libc_csu_fini>:
    3470:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000003474 <_fini>:
    3474:	48 83 ec 08          	sub    $0x8,%rsp
    3478:	48 83 c4 08          	add    $0x8,%rsp
    347c:	c3                   	retq   
