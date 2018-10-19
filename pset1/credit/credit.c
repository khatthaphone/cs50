#include<stdio.h>
#include<cs50.h>
#include<string.h>

// return amount of digits in number
// eg. 123 = 3, 456789 = 6
int get_num_size(long long num);

// convert char to int
int charToInt(char c);

int main(void)
{
    // get number from user input
    long long num = get_long_long("Number: ");

    // get num size for creating string size of the number
    int s_num_size = get_num_size(num);

    // create a string of the number
    char s_num[s_num_size];

    // copy num to s_num (convert to string)
    sprintf(s_num, "%lld", num);

    // find out how many even position from last numbers
    int chk_num_size = 0;
    int not_chk_num_size = 0;

    if (sizeof(s_num) >= 13 && sizeof(s_num) <= 16)
    {
        chk_num_size = (sizeof(s_num) / 2);
        not_chk_num_size = chk_num_size;

        // if amount of number is odd, there will be last one which is at the odd position on the left
        if (sizeof(s_num) % 2 != 0)
        {
            not_chk_num_size = chk_num_size + 1;
        }
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }

    // array for each number of even position numbers
    int chk_num[chk_num_size];
    // array for each number of odd position numbers
    int not_chk_num[not_chk_num_size];


    //inject each number into designated array
    int i, j = 0, k = 0;
    for (i = s_num_size - 1; i >= 0; i--)
    {
        int i_num = s_num[i] - '0';

        if (((s_num_size - 1) % 2) == 0)
        {
            if ((i % 2) == 1)
            {
                chk_num[j] = i_num;
                j++;
            }
            else if ((i % 2) == 0)
            {
                not_chk_num[k] = i_num;
                k++;
            }
        }
        else if (((s_num_size - 1) % 2) == 1)
        {
            if ((i % 2) == 0)
            {
                chk_num[j] = i_num;
                j++;
            }
            else if ((i % 2) == 1)
            {
                not_chk_num[k] = i_num;
                k++;
            }
        }
    }

    // multiply each even position number by 2
    int chk_num2[chk_num_size];
    for (i = 0; i < chk_num_size; i++)
    {
        chk_num2[i] = chk_num[i] * 2;
    }

    // find new amount of array to store new number after multiply by 2
    // eg. 7*2 = 14, there for 7 2 9 4 3 5 0 2 will become 14 4 18 8 6 10 0 4 (more digits to work with)
    int s_chk_num2_size = 0;
    for (i = 0; i < chk_num_size; i++)
    {
        s_chk_num2_size += (chk_num2[i] > 9) ? 2 : 1;
    }

    // array for keeping number after multiplication (with new array size)
    char s_chk_num2[s_chk_num2_size];

    // assign each degit to new array
    // j will continue to add up until finish (sizeof(s_chk_num2))
    j = 0;
    for (i = 0; i < chk_num_size; i++)
    {
        // inject int to char array of s_chk_num2
        // if number is larger than 9, will assign 1
        sprintf(&s_chk_num2[j], "%d", chk_num2[i]);
        j++;

        // if the number is larger than 9 (has two digits, eg. 10, 11, 2)
        // assign the next position with -10
        // eg. previous already assign 1, now 10 => 10-10 = 0, 15-10 = 5
        if (chk_num2[i] > 9)
        {
            sprintf(&s_chk_num2[j], "%d", (chk_num2[i] - 10));
            j++;
        }
    }

    // sum those digits in array together
    int chk_sum = 0;
    for (i = 0; i < s_chk_num2_size; i++)
    {
        chk_sum += charToInt(s_chk_num2[i]);
    }

    // sum odd position numbers (those are not multiplied by 2)
    int not_chk_sum = 0;
    for (i = 0; i < not_chk_num_size; i++)
    {
        not_chk_sum += not_chk_num[i];
    }

    // sum those two and determine credit card
    if ((chk_sum + not_chk_sum) % 10 == 0)
    {
        int first_two_digit = (charToInt(s_num[0]) * 10) + charToInt(s_num[1]);

        if (charToInt(s_num[0]) == 4)
        {
            printf("VISA\n");
            return 0;
        }
        switch (first_two_digit)
        {
            case 34:
            case 37:
                printf("AMEX\n");
                return 0;
                break;
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                printf("MASTERCARD\n");
                return 0;
                break;
            default:
                printf("INVALID\n");
                return 0;
                break;
        }

        return 0;

    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}

int get_num_size(long long num)
{

    int count = 0;
    while (num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

int charToInt(char c)
{
    return c - '0';
}