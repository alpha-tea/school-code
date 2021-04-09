;Welcome to 8-Bit Tea Party!
;
;Assembler, Intel 8086/8088, IBM PC.
;
;Grabbag (Duke Nukem Theme).
;Composed by Lee Jackson.

;Процессор Intel 8086\8088, 5 Мгц.
;Разрядность АЛУ: 16 бит.
;Шина данных: 16 бит.
;Шина адреса: 20 бит, 1 Мбайт.
;Рельный режим адресации, DOS 5.0.
;Основная память: 640 Кбайт.
;Системная память: 384 Кбайт.

;Основные регистры процессора 8086.
;AX[ah,al] основной аккумулятор;
;BX[bh,bl] база, смещение данных;
;CX[ch,cl] счётчик для комманд;
;DX[dh,dl] данные, порты ввода-вывода,"часть аккумулятора".
;SI        индекс источника, 16 бит.
;DI        индекс приёмника, 16 бит.
;BP        база, смещение стека.
;SP        указатель вершины стека.
;CS:IP     адрес сегмента кода.
;DS:[offs] сегмент данных.
;ES:[offs] сегмент данных, дополнительно.
;SS:SP     сегмент стека, с вершиной.
;IP        указатель на текущую комманду.

;Регистр флагов, 16 бит, флаги:
;CF        флаг переноса;
;ZF        флаг нуля.
;OF        флаг переполнения.
;SF        флаг знака.

;Регистр   сегмент   замена
;  IP        CS        -
;  SP        SS        -
;BP+SI[DI]   SS     CS,DS,ES
;  BX        DS     CS,SS,ES
;SI,DI[base] DS     CS,SS,ES
;SI -> DI   DS,ES      -
;Модели памяти:
;tiny
;small
;compact
;medium
;large
;flat



CPU 8086        ;только команды процессора 8086.

;Глобальные константы.

SCR_BUFFER      equ 0xB800

        ;Начало программы.
        org 0x100
        push ax
        push bx
        push cx
        push dx

;Вещание №4. Инструкции арифметики и флаги.
        mov dl,0x34
        mov dh,0x12
        add dl,dh  ;reg:reg, 3 clk;
        add dl,byte [byte_a] ;reg:mem, 9 clk+EA;
        add dl,0x03     ;reg:imm, 4 clk;
        mov al,[byte_a]
        add [byte_a],dl ;mem:reg, 9 clk+EA;
        mov al,byte [byte_a]
        mov ah,0x00    ;add 16 bit, using 8 bit operands;
        mov al,0x81
        mov bl,0xA9
        mov bh,0x0A
        add al,bl      ;флаг переноса включен
        adc ah,bh      ;используем флаг переноса
        pushf
        mov ah,0x00
        sahf       ;обнулим флаги.
        mov al,-0x50
        mov ah,-0x40
        add ah,al  ;флаг переполнения влючен и установлен флаг знака
        popf
        mov al,[byte_a]
        inc al         ;увеличение на 1, 3 такта.
        inc dx         ;2 такта
        inc byte [byte_a]   ;15+ЕА тактов
        add ax,word [byte_a]
        mov al,[byte_a]
;BCD - двоично-десятичный код, в каждом полубайте хранится цифра от 0 до 9.
;пример: 74 = 0111 0100 - двоичный вид(битовое представление)
        mov al,0x30
        aaa        ;из упакованного в десятичное число
        add al,0x05
        daa        ;из двоичного в упакованное.

        jmp return

;Вещание №3.
;Архитектура 8086, типы адресации и инструкции перемещения данных.
;Комманды общего назначения.
        mov al,0x01  ;immed, 4 clk
        mov ah,al    ;reg:reg, 2 clk
        mov ax,[word_c] ;10 clk
        mov dl,[byte_a] ;8 clk+EA
        mov [word_c],word 0xABCD ;10 clk+EA
        mov bx,[addr_segm]
        mov es,bx
        mov es,[addr_segm]  ;8 clk+EA
        push cs             ;11 clk
        push word [addr_segm];17 clk
        pushf
        lahf    ;load flag to ah
        sahf    ;store ah to flag
        popf
        pop bx
        pop ax
        xchg ax,bx   ;acc-reg, 3 clk
        xchg dx,[word_b]; reg-mem, 17 clk+EA
        xchg bx,dx      ;reg-reg, 4 clk
        mov al,0x03
        lea bx,bytes_t
        xlat
;Вычисление эффективного адреса объекта.
        lea si,[bytes_t]    ;2 clk+EA
        mov al,[si+3]
        les di,ds:[words_t]
        mov [addr_offs],si
        mov ax,ds
        mov [addr_segm],ax
        lds bx,ds:[addr_offs]
        mov al,[bx]
;
        jmp return
byte_a      db 0x01
byte_b      db 0x02
word_b      dw 0x1A2B
word_c      dw 0x3C4D
addr_offs   dw 0x0505
addr_segm   dw 0x6060
bytes_t     db 0x01, 0x02, 0x03, 0x04
words_t     dw 0x1A1B, 0x2C2D, 0x3E4F

;Вещание №2.
;Архитектура 8086, типы адрессации и инструкции перемещения данных.
;Методы и типы аресации данных.

        mov dx,0x0101;Непосредственная адресация.
        mov ax,dx    ;Регистровая адресация, 2 такта.
        mov bx,ds:[bytes_table]     ;Прамая адресация из памяти, 8 тактов.
        mov ax,ds:0x0100
        mov bx,bytes_table
        mov dh,[bx]       ;ds сегмент по умолчанию.
        mov dl,ds:[bx+2]  ;база + смещение
        mov di,0x003
lab_1:  mov cl,es:[di]
        mov bp,words_table
        mov ax,cs:[bp+di] ;Изменение сегмента + 2 такта, база + индекс.
        ;База + индекс + смещение, ооочень долго по тактам.
        mov ax,ds:[bp+di+1] ;Для базы только регистры: BX, BP, SI, DI.
;Переходим к общим инструкция перемещения данных
        jmp return

bytes_table     db 0x01, 0x02, 0x03, 0x04
words_table     dw 0x1A1B, 0x2C2D, 0x3E4F


;Вещание №1. Архитектура 8086 и программа "Привет Мир!", с БИОСом и буфером.
        ;Установим курсор в позицию.
        mov ah,02h
        mov bh,0x00
        mov dx,0x0A08
        int 10h

        ;Печатаем отдельный символ.
        mov cx,0x05
        mov ah,0x0A
        mov al,0x43
        xor bh,bh
        int 10h

        ;Печатаем строку с БИОСом
        mov ax,0x1300
        xor bh,bh
        mov bl,00011111b
        mov cx,0x000C
        mov bp,string
        int 10h

        ;Вывод строки в буффер экрана.
        mov ax,SCR_BUFFER
        mov es,ax
        mov di,0x0100
        mov si,string
        mov bh,00101111b
Prt_1:  mov bl,ds:[si]
        or bl,bl
        jz Prt_2
        mov es:[di],bx
        inc si
        add di,0x02
        jmp Prt_1
Prt_2:  mov ah,0x09
        mov dx,string
        push cs
        pop ds
        int 21h
return:

        pop dx
        pop cx
        pop bx
        pop ax
        ret


string  db 'Hello World!&', 0
word_a  dw 0x1111
dword_b dd 0x11111111
reserv  db 32 dup (0)

