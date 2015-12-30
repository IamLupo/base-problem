#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gmp.h"

char *buffer;
mpz_t current_max;
mpz_t current;
mpz_t tmp;
mpz_t tmp2;
mpz_t power;


int next_option(int max_base)
{
    unsigned int i;
    unsigned int j;
    unsigned long long length = 0;
    long long lowest_mismatch;  

    mpz_set_ui(current_max, 0);

    for(i = 3; i <= max_base; i++)
    {
        lowest_mismatch = -1;
        mpz_get_str(buffer, i, current);

        length = strlen(buffer);

        for(j = 0; j < length; j++)
        {
            if(!(buffer[j] == '0' || buffer[j] == '1'))
            {
                lowest_mismatch = j;
                break;
            }
        }

        if(lowest_mismatch != -1)
        {
            mpz_ui_pow_ui(power, i, length - lowest_mismatch);
            mpz_div(tmp, current, power);
            mpz_add_ui(tmp, tmp, 1);
            mpz_mul(tmp, tmp, power);

            if(mpz_cmp(tmp, current_max) > 0)
                mpz_set(current_max, tmp);
        }
    }

    if(mpz_cmp_ui(current_max, 0) > 0)
    {
        mpz_set(current, current_max);
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char *argv[])
{
    int done = 0;
    int max_base = 5;
    int counter = 0;
    FILE* out;

    buffer = (char*)malloc(2*1024*1024);

    out = fopen("log.txt", "w");

    mpz_init(tmp);
    mpz_init(tmp2);
    mpz_init(power);
    mpz_init(current);
    mpz_set_ui(current, 2);
    mpz_init(current_max);
    mpz_set_ui(current_max, 0);

    while(next_option(max_base))
    {
        if(++counter > 1000)
        {
            counter = 0;
            mpz_get_str(buffer, 10, current);
			fprintf(out, "value = %s\n", buffer);
            fprintf(out, "10**%d\n", strlen(buffer));
            fflush(out);
        }
    }
	
	mpz_add_ui(current, current, 1);
	while(next_option(max_base))
    {
        if(++counter > 1000)
        {
            counter = 0;
            mpz_get_str(buffer, 10, current);
			fprintf(out, "value = %s\n", buffer);
            fprintf(out, "10**%d\n", strlen(buffer));
            fflush(out);
        }
    }

    mpz_get_str(buffer, 10, current);
    fprintf(out, "%s\n", buffer);

    fflush(out);
    fclose(out);
    for(;;);

    return 0;
}