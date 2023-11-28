#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 50

char operatorStack[MAX_STACK_SIZE];
int top = -1;
void pushOperator(char op);
int popOp();
int precedence(char op);
void InfixtoPrefix(const char *infix, char *prefix);
void ReverseString(char *str);
double EvaluatePrefix(const char *prefix);
void pushOperator(char op)
{
    if (top < MAX_STACK_SIZE - 1)
    {
        operatorStack[++top] = op;
    }
    else
    {
        printf("Stack overflow");
        exit(1);
    }
}
int popOp()
{
    if (top >= 0)
    {
        return operatorStack[top--];
    }
    else
    {
        printf("Stack underflow");
        exit(1);
    }
}
int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    return 0;
}
void ReverseString(char *str)
{
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right)
    {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}
void InfixtoPrefix(const char *infix, char *prefix)
{
    int i, j = 0;
    char reversedInfix[50];
    ReverseString(strcpy(reversedInfix, infix));
    for (i = 0; reversedInfix[i]; i++)
    {
        if (reversedInfix[i] == '(')
        {
            reversedInfix[i] == ')';
            i++;
        }
        else if (reversedInfix[i] == ')')
        {
            reversedInfix[i] = '(';
            i++;
        }
    }
    for (i = 0; reversedInfix[i]; i++)
    {
        if (isdigit(reversedInfix[i]))
        {
            while (isdigit(reversedInfix[i]) || reversedInfix[i] == '.')
            {
                prefix[j++] = reversedInfix[i++];
            }
            prefix[j++] = ' ';
            i--;
        }
        else if (reversedInfix[i] == '(')
        {
            pushOperator('(');
        }
        else if (reversedInfix[i] == ')')
        {
            while (top >= 0 && operatorStack[top] != '(')
            {
                prefix[j++] = popOp();
                prefix[j++] = ' ';
            }
            if (top >= 0 && operatorStack[top] == '(')
            {
                popOp();
            }
        }
        else
        {
            while (top >= 0 && precedence(operatorStack[top]) > precedence(reversedInfix[i]))
            {
                prefix[j++] = popOp();
                prefix[j++] = ' ';
            }
            pushOperator(reversedInfix[i]);
        }
    }
    while (top >= 0)
    {
        prefix[j++] = popOp();
        prefix[j++] = ' ';
    }
    prefix[j] = '\0';
    ReverseString(prefix);
}
double EvaluatePrefix(const char *prefix)
{
    double stack[MAX_STACK_SIZE];
    int top = -1;
    int i = strlen(prefix) - 1;
    while (i >= 0)
    {
        if (isdigit(prefix[i]) || (prefix[i] == '-' && isdigit(prefix[i - 1])))
        {
            char *endptr;
            double num = strtod(&prefix[i], &endptr);
            i = endptr - prefix - 1;
            stack[++top] = num;
        }
        else if (prefix[i] == ' ')
        {
        }
        else
        {
            double operand1 = stack[top--];
            double operand2 = stack[top--];
            switch (prefix[i])
            {
            case '+':
                stack[++top] = operand1 + operand2;
                break;
            case '-':
                stack[++top] = operand1 - operand2;
                break;
            case '*':
                stack[++top] = operand1 * operand2;
                break;
            case '/':
                stack[++top] = operand1 / operand2;
                break;

            default:
                break;
            }
        }
        i--;
    }
    return stack[0];
}
int main()
{
    char infix[50];
    char prefix[50];
    printf("Enter infix string : ");
    gets(infix);
    InfixtoPrefix(infix, prefix);
    printf("Prefix expression is %s\n", prefix);
    double result = EvaluatePrefix(prefix);
    printf("Result: %f\n", result);
}