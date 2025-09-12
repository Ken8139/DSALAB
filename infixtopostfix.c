#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE 100

// STACK for CHARACTERS

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


// STACK for FLOATING-POINT NUMBERS

float floatStack[MAX_SIZE];
int floatTop = -1;

void floatPush(float value) {
    if (floatTop >= MAX_SIZE - 1) {
        printf("Float stack overflow\n");
        exit(1);
    }
    floatStack[++floatTop] = value;
}

float floatPop() {
    if (floatTop == -1) {
        printf("Float stack underflow\n");
        exit(1);
    }
    return floatStack[floatTop--];
}


int precedence(char symbol) {
    if (symbol == '^') return 3;
    else if (symbol == '*' || symbol == '/') return 2;
    else if (symbol == '+' || symbol == '-') return 1;
    else return 0;
}

float floatPower(float base, float exp) {
    float result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}


// INFIX → POSTFIX

void infixToPostfix(char infix[], char postfix[]) {
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char c = infix[i];

        if (isdigit(c)) { // read full number
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            continue;
        } 
        else if (isalpha(c)) { // variable (a,b,x,y…)
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
            if (!isCharStackEmpty()) charPop(); // pop '('
        } 
        else { // operator
            while (!isCharStackEmpty() && precedence(charPeek()) >= precedence(c)) {
                if (precedence(charPeek()) == precedence(c) && c == '^') break;
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


// POSTFIX EVALUATION (for floating-point numbers)

float evaluatePostfix(char postfix[]) {
    int i = 0;

    while (postfix[i] != '\0') {
        if (isdigit(postfix[i]) || postfix[i] == '.') {
            float num = 0;
            float decimalPlace = 1;

            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            if (postfix[i] == '.') {
                i++;
                while (isdigit(postfix[i])) {
                    num = num + (postfix[i] - '0') / (decimalPlace *= 10);
                    i++;
                }
            }
            floatPush(num);
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
            float val2 = floatPop();
            float val1 = floatPop();

            switch (postfix[i]) {
                case '+': floatPush(val1 + val2); break;
                case '-': floatPush(val1 - val2); break;
                case '*': floatPush(val1 * val2); break;
                case '/':
                    if (val2 == 0) {
                        printf("Division by zero error\n");
                        exit(1);
                    }
                    floatPush(val1 / val2);
                    break;
                case '^': floatPush(floatPower(val1, val2)); break;
            }
            i++;
        }
    }

    return floatPop();
}


// MAIN

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("Enter Infix Expression (numbers + variables allowed): ");
    scanf("%[^\n]", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix : %s\n", postfix);

    // Try evaluation only if there are no variables
    int hasVariable = 0;
    for (int k = 0; postfix[k] != '\0'; k++) {
        if (isalpha(postfix[k])) {
            hasVariable = 1;
            break;
        }
    }

    if (!hasVariable) {
        float result = evaluatePostfix(postfix);
        printf(" Result: %.2f\n", result);
    } else {
        printf("Expression contains variables → cannot evaluate .\n");
    }

    return 0;
}

      
