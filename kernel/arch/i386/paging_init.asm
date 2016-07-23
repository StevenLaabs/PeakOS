section .text
GLOBAL load_page_dir
GLOBAL enable_paging

load_page_dir:
	mov eax, [esp+4]
	lea ecx, [eax]
	mov cr3, ecx
	ret

enable_paging:
	mov eax, cr0
	or ecx, 0x80000000
	mov cr0, ecx
	ret
