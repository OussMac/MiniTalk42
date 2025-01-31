#include <signal.h>
#include <stdio.h>
#include <stdlib.h>




/*+--------------------------------------+
    Program To Know More About Signals
+--------------------------------------+*/




int main(void)
{

    printf("The SIGINT number %d\n", SIGINT);
    printf("(ctrl + c)\n");
    return (EXIT_SUCCESS);
}