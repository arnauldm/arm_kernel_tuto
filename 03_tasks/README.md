
That simple kernel is much like the one in `02_simple_kernel/` with only few
differences. There's a running task (named *task0*). Beware that it's not a
user task in the same way we usually see in operating systems. That code
executes in USER mode but there's currently no memory isolation.

The big deal here is to "launch" that user task. The *task0* code is compiled 
and copied raw in the kernel ELF file. 
