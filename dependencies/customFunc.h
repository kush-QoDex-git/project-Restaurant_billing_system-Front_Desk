#include <math.h>
#include <stdlib.h>
#include <string.h>
void print_sufficient_spaces_in_ui(int str_len, int n)
{
    for (int i = 0; i < n - str_len; i++)
    {
        printf(" ");
    }
}
void strLower(char *str)
{
    int i = 0;
    while (str[i] != '\n' && str[i] != '\0')
    {
        if (((int)str[i] > 64) && ((int)str[i] < 91))
        {
            str[i] = (char)((int)str[i] + 32);
        }
        i++;
    }
}
void strUpper(char *str)
{
    int i = 0;
    while (str[i] != '\n' && str[i] != '\0')
    {
        if (((int)str[i] > 96) && ((int)str[i] < 123))
        {
            str[i] = (char)((int)str[i] - 32);
        }
        i++;
    }
}
int strcmp_ig_case(char *str1, char *str2)
{
    char sstr1[100] = "\0";
    char sstr2[100] = "\0";
    strcpy(sstr1, str1);
    strcpy(sstr2, str2);
    strLower(sstr1);
    strLower(sstr2);
    return strcmp(sstr1, sstr2);
}
int string_to_int(char *str)
{
    int i = 0, digit, plc = 1;
    int num = 0;
    char ch = str[i];
    while (ch != '\0')
    {
        digit = (int)ch - 48;
        num *= plc;
        num += digit;
        i++;
        plc *= 10;
        ch = str[i];
    }
    return num;
}
void int_to_item_id(int num, char *id)
{
    int plc = 1000, digit;
    for (int i = 0; i < 4; i++)
    {
        digit = (num / plc) % 10;
        id[i] = (char)(digit + 48);
        plc = plc / 10;
    }
    id[4] = '\0';
}

void str_slice_cat(char *to_str, char *from_str, int start_index_of_from, int num_of_char)
{
    int start_index_of_to = 0;
    while (to_str[start_index_of_to] != '\0')
    {
        start_index_of_to++;
    }
    for (int i = 0; i < num_of_char; i++)
    {
        to_str[start_index_of_to + i] = from_str[start_index_of_from + i];
    }
    to_str[start_index_of_to + num_of_char] = '\0';
}
void remove_fgets_newline(char *str)
{
    int i = 0;
    while (1)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
        i++;
    }
}
int num_of_digits_in_int(int num)
{
    int nof = 0, d = 1;
    while (num / d > 0)
    {
        nof++;
        d *= 10;
    }
    return nof;
}
void int_to_str(int num, char *str)
{
    int nof = num_of_digits_in_int(num);
    int d = pow(10, nof - 1), digit;
    for (int i = 0; i < nof; i++)
    {
        digit = (num / d) % 10;
        str[i] = (char)(48 + digit);
        d = d / 10;
    }
    str[nof] = '\0';
}