#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE 150  

char charStack[MAX_SIZE];
int charTop = -1;

void charPush(char c) {
    if (charTop >= MAX_SIZE - 1) {
        printf("Character stack overflow\n");
        exit(1);
    }
    charStack[++charTop] = c;
}

char charPop() {
    if (charTop == -1) {
        printf("Character stack underflow\n");
        exit(1);
    }
    return charStack[charTop--];
}

char charPeek() {
    if (charTop == -1) return '\0';
    return charStack[charTop];
}

int isCharStackEmpty() {
    return charTop == -1;
}


int intStack[MAX_SIZE];
int intTop = -1;

void intPush(int value) {
    if (intTop >= MAX_SIZE - 1) {
        printf("Integer stack overflow\n");
        exit(1);
    }
    intStack[++intTop] = value;
}

int intPop() {
    if (intTop == -1) {
        printf("Integer stack underflow\n");
        exit(1);
    }
    return intStack[intTop--];
}


int precedence(char symbol) {
    if (symbol == '^') return 3;
    else if (symbol == '*' || symbol == '/') return 2;
    else if (symbol == '+' || symbol == '-') return 1;
    else return 0;
}

int intPower(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}


void infixToPostfix(char infix[], char postfix[]) {
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char c = infix[i];

       
        if (isdigit(c)) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            continue;
        }
        
        else if (isalpha(c)) {
            postfix[j++] = c;
            postfix[j++] = ' ';
        }
       
        else if (c == '(') {
            charPush(c);
        }
        
        else if (c == ')') {
            while (!isCharStackEmpty() && charPeek() != '(') {
                postfix[j++] = charPop();
                postfix[j++] = ' ';
            }
            if (!isCharStackEmpty()) charPop(); 
        }
       
        else {
            while (!isCharStackEmpty() && precedence(charPeek()) >= precedence(c)) {
    
                if (precedence(charPeek()) == precedence(c) && c == '^')
                    break;
                postfix[j++] = charPop();
                postfix[j++] = ' ';
            }
            charPush(c);
        }
        i++;
    }

    
    while (!isCharStackEmpty()) {
        postfix[j++] = charPop();
        postfix[j++] = ' ';
    }

    postfix[j] = '\0'; 
}


int evaluatePostfix(char postfix[]) {
    int i = 0;

    while (postfix[i] != '\0') {
        
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            intPush(num);
        }
      
        else if (postfix[i] == ' ') {
            i++;
            continue;
        }
       
        else if (isalpha(postfix[i])) {
            printf("Variable '%c' found → cannot evaluate without value.\n", postfix[i]);
            exit(1);
        }
        
        else {
            int val2 = intPop();
            int val1 = intPop();

            switch (postfix[i]) {
                case '+': intPush(val1 + val2); break;
                case '-': intPush(val1 - val2); break;
                case '*': intPush(val1 * val2); break;
                case '/':
                    if (val2 == 0) {
                        printf("Division by zero error\n");
                        exit(1);
                    }
                    intPush(val1 / val2);
                    break;
                case '^': intPush(intPower(val1, val2)); break;
            }
            i++;
        }
    }

    return intPop();
}


int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("Enter Infix Expression (numbers + variables allowed): ");
    scanf("%[^\n]", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

  
    int hasVariable = 0;
    for (int k = 0; postfix[k] != '\0'; k++) {
        if (isalpha(postfix[k])) {
            hasVariable = 1;
            break;
        }
    }

 
    if (!hasVariable) {
        int result = evaluatePostfix(postfix);
        printf("Result: %d\n", result);
    } else {
        printf("Expression contains variables → cannot evaluate .\n");
    }

    return 0;
}

      
