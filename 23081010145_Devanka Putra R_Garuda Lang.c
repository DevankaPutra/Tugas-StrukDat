#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void cleanCode(char *input, char *output) {
    int j = 0;
    int inString = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '"' || input[i] == '\'') {
            inString = !inString;
            output[j++] = input[i];
            continue;
        }

        if (inString) {
            output[j++] = input[i];
            continue;
        }

        if (input[i] == '/' && input[i + 1] == '/') {
            while (input[i] != '\n' && input[i] != '\0') i++;
            continue;
        }

        if (input[i] == '(' || input[i] == ')' ||
            input[i] == '{' || input[i] == '}' ||
            input[i] == '[' || input[i] == ']' ||
            input[i] == '<' || input[i] == '>') {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

typedef struct {
    char data[MAX];
    int top;
} Stack;

void init(Stack* s) { s->top = -1; }
int isEmpty(Stack* s) { return s->top == -1; }
void push(Stack* s, char c) { if (s->top < MAX - 1) s->data[++(s->top)] = c; }
char pop(Stack* s) { return isEmpty(s) ? '\0' : s->data[(s->top)--]; }
int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']') ||
           (open == '<' && close == '>');
}

int validateBrackets(const char* code) {
    Stack stack;
    init(&stack);
    for (int i = 0; code[i] != '\0'; i++) {
        if (code[i] == '(' || code[i] == '{' || code[i] == '[' || code[i] == '<') {
            push(&stack, code[i]);
        } else if (code[i] == ')' || code[i] == '}' || code[i] == ']' || code[i] == '>') {
            if (isEmpty(&stack) || !isMatchingPair(pop(&stack), code[i])) {
                return 0;
            }
        }
    }
    return isEmpty(&stack);
}

int main() {
    char inputCode[MAX];
    char cleanedCode[MAX];

    printf("Masukkan kode untuk diuji (akhiri dengan 'END'):\n");

    inputCode[0] = '\0';
    char line[MAX];
    while (fgets(line, sizeof(line), stdin)) {
        if (strncmp(line, "END", 3) == 0) break;
        strcat(inputCode, line);
    }

    cleanCode(inputCode, cleanedCode);

    if (validateBrackets(cleanedCode)) {
        printf("\nKode valid: Semua bracket sesuai.\n");
    } else {
        printf("\nKode tidak valid: Terdapat ketidaksesuaian pada bracket.\n");
    }

    return 0;
}
