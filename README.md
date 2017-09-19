# Virtual CPU
This my attempt at building a virtual CPU.  This is just for fun and learning.
The entire virtual machine will be implemented in sofware.

#### Extra Features

##### Multicore/Coprocessors:
*Allow multiple CPUs to be added to the same VM (multicore)
  * Could allow for a FORK instruction

*Allow (smaller, supplemental) CPUs to added to bigger (main) CPUs (coprocessors)
  * Think, creating a small CPU which only does IN/OUT and
  adding that to an otherwise complete CPU

##### Flexible Address/Register Width
* Allow the CPU to switch from 16 to 32 bit mode (for example) and back again
  * Like modern CPUs allow for 32-bit threads in 64-bit mode
  (probably with page attributes)

## JFF (Just For Fun) CPU architecture v0.2

* Register width
  * 16-bit

* Flags:
  * 0 - Carry (CF)
  * 1 - Zero (ZF)
  * 2 - Sign (SF)
  * 3 - Trap (TF)
  * 4 - Interrupt (IF)
  * 5 - Overflow (OF)
  * 6 - User Flag A (AF)
  * 7 - User Flag B (BF)
  * 8 - Not Used
  * 9 - Not Used
  * A - Not Used
  * B - Not Used
  * C - Not Used
  * D - Not Used
  * E - Not Used
  * F - Not Used

* Bit ordering
  * LSB

* Reserved Regisers:
  * Instruction Pointer (IP)

* Special Regisers:
  * Reserved (R8)
  * Reserved (R9)
  * Reserved (R10)
  * Reserved (R11)
  * Base Pointer (BP/R12)
  * Stack Pointer (SP/R13)
  * Flags (FR/R14)
  * Vector Table (VT/R15)

* General Purpose Registers:
  * R0-R7

* Number of Interrupts
  * 32

* Reset Vector
  * IP=0
  * R8-R11=0
  * BP=0xFFFF
  * SP=0xFFFF
  * Flags=0
  * VT=0xEDFF

* CPU Interrupts:
  * 0 - Double Fault
  * 1 - Bad opcode
  * 2 - Bad operand (eg: memory out of range, invalid register id)
  * 3 - Debug
  * 4 - Divide By Zero
  * 5 - Reserved
  * 6 - Reserved
  * 7 - Reserved

* 0 operand instructions (8-bits)
  * Debugging Options
    * BREAK (INT 3)
    * NOP
  * Hardware Operations
    * HLT
    * RST (Restore Reset Vector)
    * STOP (hard lock cpu)
  * Program Operations
    * IRET (POPA, POPF, RET)
    * RET
  * Stack Operations
    * POPA (POP RF, POP R7-R0)
    * PUSHA (PUSH R0-R7, PUSH FR)

* 1 operand instructions (16-bits)
  * Arithmetic Operations
    * DEC
    * INC
  * Bitwise Operations
    * NOT
  * Program Operations
    * CALL
    * CLR (clear flag)
    * INT
    * JMP
    * SET (set flag)
  * Stack Operations
    * POP
    * PUSH

* 2 operand instructions (24-bits)
  * Arithmetic Operations
    * ADD
    * DIV
    * MUL
    * SUB
  * Bitwise Operations
    * AND
    * OR
    * ROL
    * ROR
    * SHL
    * SHR
    * XOR
  * Hardware Operations
    * IN
    * OUT
  * Mulipurpose Operations
    * MOV
    * XCHG
  * Program Operations
    * CMP (logical SUB)
    * JF (Jump if Flag)
    * TEST (logical AND)

* Opcode notation
  * The form of notation should be
    * Instruction ([I][M][R],[I][M][R],...) - Opcode [operand-code [...]]
  * Where I, M, and R denote that the positional operand
  may be an immediate value, memory address, or register index
  * Where operand-code (from the table below) explains to the CPU
  how to interpret the operands

* Operand Codes (xx)
  * 00 - Register
  * 01 - Memory
  * 02 - Immediate

* Opcodes
  * BREAK CC
  * NOP 00/FF
  * HLT FC
  * RST FD
  * STOP FE
  * IRET 01
  * RET 02
  * POPA 05
  * PUSHA 06

  * DEC (MR) 0Axx
  * INC (MR) 0Bxx
  * NOT (MR) 0Exx
  * CALL (IMR) 10xx
  * CLR (I) 12xx
  * INT (IMR) 14xx
  * JMP(Near)(IMR) 20xx
  * JMP(Far)(IMR)  21xx
  * SET (I) 24xx
  * POP (MR) 28xx
  * PUSH (IMR) 29xx

  * ADD (IM,IR,MM,MR,RM,RR) 2Bxx xx
  * DIV (IM,IR,MM,MR,RM,RR) 2Exx xx
  * MOD (IM,IR,MM,MR,RM,RR) 2Fxx xx
  * MUL (IM,IR,MM,MR,RM,RR) 2Dxx xx
  * SUB (IM,IR,MM,MR,RM,RR) 2Cxx xx
  * AND (IM,IR,MM,MR,RM,RR) 30xx xx
  * OR (IM,IR,MM,MR,RM,RR) 31xx xx
  * ROL (IM,IR,MM,MR,RM,RR) 35xx xx
  * ROR (IM,IR,MM,MR,RM,RR) 36xx xx
  * SHL (IM,IR,MM,MR,RM,RR) 33xx xx
  * SHR (IM,IR,MM,MR,RM,RR) 34xx xx
  * XOR (IM,IR,MM,MR,RM,RR) 32xx xx
  * IN (IM,IR,MM,MR,RM,RR) 3Axx xx
  * OUT ([IMR][IMR]) 3Bxx xx
  * MOV (IM,IR,MM,MR,RM,RR) 3Exx xx
  * XCHG (IM,IR,MM,MR,RM,RR) 3Fxx xx
  * CMP ([IMR][IMR]) 40xx xx
  * JF (I,IMR) 44xx xx
  * TEST ([IMR][IMR]) 41xx xx
