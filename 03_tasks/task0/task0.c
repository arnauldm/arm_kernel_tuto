

void __attribute__ ((noreturn)) c_entry ()
{
    char *hello = "[task0]\n";

    while (1) {
        asm volatile
         ("mov r0, %[msg]\n" "svc #0x1\n"::[msg] "r" (hello)
          :"r0", "memory");
        for (int i = 0; i < 400000000; i++);
    }

    while (1);
}
