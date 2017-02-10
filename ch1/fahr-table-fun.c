#include <stdio.h>

float fahrenheit_to_celsius(float fahrenheit);

/* print Fahrenheit-Celsius table
 * for fahr = 0,20,...,300; floating-point version */
main()
{
    float fahr,celsius;
    int lower,upper,step;

    lower = 0; /* lower limit of temperature table */
    upper = 300; /* upper limit */
    step = 20; /* step size */

    fahr = lower;
    printf("Fahrenheit\tCelsius\n");
    while (fahr <= upper) {
        celsius = fahrenheit_to_celsius(fahr);
        printf("%3.0f       \t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

float fahrenheit_to_celsius(float fahrenheit)
{
    return (5.0/9.0)*(fahrenheit - 32.0);
}

