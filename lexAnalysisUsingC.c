#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = {"int", "float", "return", "if", "else", "while", "for", "void"};
int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

int isKeywords(const char *str)
{
    for (int i = 0; i < numKeywords; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int isArithmeticOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
int isOtherOperator(char ch)
{
    return ch == '=' || ch == '>' || ch == '<' || ch == '!';
}

void analyzeToken(const char *token)
{
    if (isKeywords(token))
    {
        printf("kwd: %s\n", token);
    }
    else if (isalpha(token[0]) || token[0] == '_')
    {
        printf("id: %s\n", token);
    }
}

void lexAnalyzer(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("error: could not open the file");
        return;
    }

    char ch;
    char buffer[100];
    int index = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        if (isalnum(ch) || ch == '_')
        {
            buffer[index++] = ch;
        }
        else
        {
            if (index > 0)
            {
                buffer[index] = '\0';
                analyzeToken(buffer);
                index = 0;
            }

            if (isArithmeticOperator(ch))
            {
                switch (ch)
                {
                case '+':
                    printf("op-plus\n");
                    break;
                case '-':
                    printf("op-sub\n");
                    break;
                case '*':
                    printf("op-mul\n");
                    break;
                case '/':
                    printf("op-div\n");
                    break;
                }
            }
            else if (isOtherOperator(ch))
            {
                printf("op-%c\n", ch);
            }
        }
    }
        if (index > 0) {
        buffer[index] = '\0';
        analyzeToken(buffer);
    }

    fclose(file);
}

int main() {
    lexAnalyzer("input.txt");
    return 0;
}
/*
 * open input.txt in read mode
 * if file not found -> display error message
 * else
 *   scan and analyse each component ch
 *   if ch is a keyword -> display kwd
 *   if ch is an identifier -> display id
 *   if ch is an arith operator -> display op-plus/sub/mul/div
 *   if ch is any other operator -> display same
 * stop and close the file
 */