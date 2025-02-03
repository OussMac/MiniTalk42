#include <signal.h>
#include <stdio.h>
#include <stdlib.h>




/*+--------------------------------------+
    Program To Know More About Signals
+--------------------------------------+*/




int main(void)
{

    printf("The SIGINT number %d\n", SIGINT);
    printf("(ctrl + c) interrupts the process from the keyboard, it's action is Term for Terminate\n");

    puts("\n\n");
    printf("The SIGINT number %d\n", SIGTERM);
    printf("(kill -TERM <pid>)' terminates the process, it's action is Term\n");

    puts("\n\n");
    printf("The SIGINT number %d\n", SIGKILL);
    printf("(kill -KILL <pid>) terminates the process, it's action is Term, and can't be caught it's an order.\n");
    return (EXIT_SUCCESS);
}