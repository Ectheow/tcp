#include <stdio.h>

/*
 * Celsius-Fahrenheit table: 
 * print a table of two columns, one celsius, the other fahrenheit.
 */

main()
{
    int lower = 0;
    int upper = 300;
    int step = 20;

    float celsius,fahrenheit;

    celsius = lower;

    printf("Celsius\tFahrenheit\n");
    while (celsius <= upper) {
        fahrenheit = ((9.0/5.0)*celsius) + 32.0;
        printf("%3.0f    \t%6.2f\n",celsius,fahrenheit);
        celsius += step;
    }
}
