#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    int top;
    char items[MAX];
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char value) {
    if (!isFull(s)) {
        s->items[++(s->top)] = value;
    }
}

char pop(Stack *s) {
    return isEmpty(s) ? '\0' : s->items[(s->top)--];
}

char peek(Stack *s) {
    return isEmpty(s) ? '\0' : s->items[s->top];
}

int isMatchingBalanced(char *expr) {
    Stack s;
    initStack(&s);
    for (int i = 0; i < strlen(expr); i++) {
        if (expr[i] == '(') {
            push(&s, '(');
        } else if (expr[i] == ')') {
            if (isEmpty(&s)) {
                return 0;
            }
            pop(&s);
        }
    }
    return isEmpty(&s);
}

int precedence(char op) {
    return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : 0;
}

void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    initStack(&s);
    int k = 0;
    for (int i = 0; i < strlen(infix); i++) {
        if (isdigit(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            push(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            pop(&s);
        } else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(infix[i])) {
                postfix[k++] = pop(&s);
            }
            push(&s, infix[i]);
        }
    }
    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }
    postfix[k] = '\0';
}

int main() {
    int choice;
    char expr[MAX], postfix[MAX];

    do {
        printf("Menu:\n");
        printf("1. Matching balancing parenthesis\n");
        printf("2. Convert infix to postfix\n");
        printf("3. Exit\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan ekspresi: ");
                scanf("%s", expr);
                if (isMatchingBalanced(expr)) {
                    printf("Ekspresi memiliki tanda kurung yang seimbang.\n");
                } else {
                    printf("Ekspresi tidak seimbang.\n");
                }
                break;
            case 2:
                printf("Masukkan ekspresi infix: ");
                scanf("%s", expr);
                infixToPostfix(expr, postfix);
                printf("Ekspresi postfix: %s\n", postfix);
                break;
            case 3:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
