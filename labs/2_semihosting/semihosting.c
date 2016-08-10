#include "my_utils.h"

#define GREETING_STR  "Hello World\n\r"
#define PROMPT_STR    "\r> "
#define LINE_MAX_CHAR (64)

int main(int argc, char **argv)
{
    char line[LINE_MAX_CHAR];

    /* Greeting */
    host_write(STDOUT, GREETING_STR, strlen(GREETING_STR));
    host_write(STDOUT, PROMPT_STR, strlen(PROMPT_STR));
    while(1) {
        memset(line, 0x00, LINE_MAX_CHAR);
        host_read(STDIN, line, LINE_MAX_CHAR);
        host_write(STDOUT, line, strlen(line));

        /* Show prompt */
        host_write(STDOUT, PROMPT_STR, strlen(PROMPT_STR));
    }

    return 0;
}

