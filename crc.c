
#include <stdio.h>
#include <string.h>

int main()
{
    char data[100], gen[100], temp[100], code[100];
    int i, j, n, m, error = 0;

    // SENDER SIDE
    printf("----- SENDER SIDE -----\n");

    printf("Enter data bits: ");
    scanf("%s", data);

    printf("Enter generator bits: ");
    scanf("%s", gen);

    n = strlen(data);
    m = strlen(gen);

    strcpy(temp, data);

    // Append zeros
    for(i = 0; i < m - 1; i++)
        temp[n+i] = '0';

    temp[n+m-1] = '\0';

    // XOR division
    for(i = 0; i < n; i++)
    {
        if(temp[i] == '1')
        {
            for(j = 0; j < m; j++)
            {
                temp[i+j] =
                (temp[i+j] == gen[j]) ? '0' : '1';
            }
        }
    }

    // Generate codeword
    strcpy(code, data);

    for(i = 0; i < m - 1; i++)
        code[n+i] = temp[n+i];

    code[n+m-1] = '\0';

    printf("CRC Remainder: %s\n", temp+n);
    printf("Transmitted Codeword: %s\n", code);


    // RECEIVER SIDE
    printf("\n----- RECEIVER SIDE -----\n");

    strcpy(temp, code);

    // XOR division
    for(i = 0; i <= n-1; i++)
    {
        if(temp[i] == '1')
        {
            for(j = 0; j < m; j++)
            {
                temp[i+j] =
                (temp[i+j] == gen[j]) ? '0' : '1';
            }
        }
    }

    // Check remainder
    for(i = n; i < n+m-1; i++)
    {
        if(temp[i] == '1')
        {
            error = 1;
            break;
        }
    }

    if(error == 0)
        printf("No Error Detected\n");
    else
        printf("Error Detected\n");

    return 0;
}
