GLOBAL outb
outb:
  mov edx, [esp + 4] ; port param
  mov al, [esp + 8]  ; value param
  out dx, al         ; output al to port dx
  ret

GLOBAL inb
inb:
  mov edx, [esp + 4] ; port param
  in al, dx          ; read port dx into the al register
  ret
