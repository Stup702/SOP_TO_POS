#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*ANIMESHGPT GENERATED CODE*/
/*Changes the SOP format to POS format in boolean algebra
A test case:   AB~C + ABC + ~A~B~C
Should return (A+B+~C)(A+~B+C)(A+~B+~C)(~A+B+C)(~A+B+~C)
*/

int var_freq[27] = {0};

char variable[6];

char bin[10];

int _2pow(int n)
{
    int out = 1;
    for (int i = 0; i < n; i++)
    {
        out *= 2;
    }
    return out;
}

int bin_to_dec(char bin[])
{
    int dec = 0;

    int len = strlen(bin) - 1;
    for (int i = len; i >= 0; i--)
    {
        if (bin[i] == '1')
        {
            dec += _2pow((len - i));
        }
    }
    return dec;
}

int dec_to_bin(int n)
{

    int len = strlen(variable);
    int i = len - 1;

    while (n != 0)
    {

        if (n % 2 == 1)
        {
            bin[i--] = '1';
        }
        else
        {
            bin[i--] = '0';
        }
        n /= 2;
    }

    bin[len + 1] = '\0';
}

// transforms the read and tokenized string snippet ito its binary format
// keeps the binary form in a gloabal variable bin
char *arr_to_bin(char *snip)
{

    int v_ar_size = strlen(variable);

    int snip_size = strlen(snip);

    ;

    int bin_in = 0;

    for (int j = 0; j < v_ar_size; j++)
    {
        for (int i = 0; i < snip_size; i++)
        {
            if (snip[i] == variable[j])
            {
                bin[bin_in++] = '1';
                break;
            }
            else if (snip[i] == '~' && snip[i + 1] == variable[j])
            {
                bin[bin_in++] = '0';
                break;
            }
        }
    }
}

// counts the number of variables and keeps them inside the variable char array
// returns the number of variables
int var_cnt(char array[])
{
    int len = strlen(array);

    int cnt = 0;

    for (int i = 0; i < len; i++)
    {
        if (isalpha(array[i]) && var_freq[array[i] - 'A'] == 0)
        {
            var_freq[array[i] - 'A']++;
            variable[cnt] = array[i];
            cnt++;
        }
    }
    return cnt;
}

int main()
{

    char input[1000];

    scanf("%[^\n]s", input);

    int var_num = var_cnt(input); // total variable count.Could have just strlen'ed it, but eh

    int total = _2pow(var_num); // total number of cases

    int dec_freq[total]; // keeps track of which numbers are in sop

    memset(dec_freq, 0, sizeof(dec_freq)); // initializes to 0

    // for (int i = 0; i < strlen(variable); i++)
    // {
    //     printf("%c", variable[i]); // variable checking
    // }

    char *token = strtok(input, "+");

    int taken[100] = {0}, taken_in = 0;

    while (token != NULL)
    {
        arr_to_bin(token);

        taken[taken_in++] = bin_to_dec(bin);

        // printf("\n%s ", bin);

        token = strtok(NULL, "+");
    }

    for (int i = 0; i < taken_in; i++)
    {
        dec_freq[taken[i]]++;
        printf("%d ", taken[i]);
    }

    printf("\n");

    for (int i = 0; i < total; i++)
    {
        printf("%d ", dec_freq[i]);
    }

    printf("\n\n");
    for (int i = 0; i < total; i++)
    {
        if (dec_freq[i] == 0)
        {
            dec_to_bin(i);
            // printf("%d ",i);
            // printf("%s\n",bin);
            printf("(");
            for (int j = 0; j < var_num; j++)
            {

                if (bin[j] == '0')
                {
                    printf("%c ", variable[j]);
                }
                else
                {
                    printf("~");
                    printf("%c ", variable[j]);
                }
                if (j < var_num - 1)
                {
                    printf("+ ");
                }
            }
            printf(")");
        }
    }
}