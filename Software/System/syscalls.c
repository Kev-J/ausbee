/*********************************************************/
/* Syscalls implementation for STM32 Low density devices */
/*                                                       */
/* Author: Kevin JOLY joly.kevin25@gmail.com             */
/* Largely inspired by libc doc                          */
/* "Definitions for OS interface" section                */
/*                                                       */
/*********************************************************/
#include <errno.h>
#include <sys/types.h>
int _getpid(void)
{
    return 1;
}

void _exit(int status)
{
    while (1)
        ;
}

void _kill(int pid, int sig)
{
    errno = EINVAL;
    return (-1);
}

caddr_t _sbrk(int incr)
{
    extern char _bss_end;       /* Defined by the linker */
    extern char _stack_begin;
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_bss_end;
    }
    prev_heap_end = heap_end;
    if (heap_end + incr > _stack_begin) {
        //write (1, "Heap and stack collision\n", 25);
        abort ();
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}
