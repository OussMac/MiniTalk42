
#include <stdio.h>


void recursive_fun()
{
    size_t a = 100000;
    recursive_fun();
}

int main(void)
{
    recursive_fun();
    return (0);
}