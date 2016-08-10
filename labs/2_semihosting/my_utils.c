#include "my_utils.h"

int strlen(char *str)
{
    assert_param(str);

    int len = 0;
    while(*str) {
        str++;
        len++;
    }

    return len;
}

void memset(void *s, int c, int n)
{
    int i = 0;
    uint8_t *p = (uint8_t *)s;

    assert_param(s);

    for(i = 0; i < n; i++) {
        *p = 0;
        p++;
    }
}

/* Semihosting starts here */
enum HOST_SYSCALL {
    HOSTCALL_WRITE       = 0x05,
    HOSTCALL_READ        = 0x06,
};

/* Semihost system call parameters */
union param_t
{
    int   pdInt;
    void *pdPtr;
};

typedef union param_t param;
static int host_call(enum HOST_SYSCALL action, void *arg) __attribute__ ((naked));
static int host_call(enum HOST_SYSCALL action, void *arg)
{
    /* For Thumb-2 code use the BKPT instruction instead of SWI.
     * Refer to:
     * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0471c/Bgbjhiea.html
     * http://en.wikipedia.org/wiki/ARM_Cortex-M#Cortex-M4 */
    int result;
    __asm__( \
      "bkpt 0xAB\n"\
      "nop\n" \
      "bx lr\n"\
        :"=r" (result) ::\
    );
    return result;
}

size_t host_read(int fd, void *buf, size_t count)
{
    param semi_param[3] = {
        { .pdInt = fd },
        { .pdPtr = buf },
        { .pdInt = count }
    };

    return host_call(HOSTCALL_READ, semi_param);
}

size_t host_write(int fd, const void *buf, size_t count)
{
    param semi_param[3] = {
        { .pdInt = fd },
        { .pdPtr = (void *) buf },
        { .pdInt = count }
    };

    return host_call(HOSTCALL_WRITE, semi_param);
}


/* Trap here for gdb if asserted */
void assert_failed(uint8_t* file, uint32_t line)
{
    while(1);
}
