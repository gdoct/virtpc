# virtpc
This is a highly configurable virtual machine in c++ in progress

The project emulates an 8 bit system with 16 bit addressing.
currently it has 8 registers: acc, x, y, status, mem_low, mem_high, pc_low and pc_high

the default instruction set for the machine is defined in a simple text format in the file rom/microcode.dat.
with the default instruction set, a rom dump from a c64 or compatible machine can be loaded into memory.

roadmap

* implement instruction set
* enable video output
* make byte and word size of the vm configurable (from 4/8 to 128/128)
* move machine configuration to file

