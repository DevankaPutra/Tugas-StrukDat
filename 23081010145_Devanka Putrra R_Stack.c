#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK 10

typedef struct node {
    char item[50];
    struct node* next;
} Node;

typedef struct stack {
    int size;
    Node* head;
} Stack;

void initializeStack(Stack* s) {
    s->size = 0;
    s->head = NULL;
}

int isEmpty(Stack* s) {
    return s->head == NULL;
}

int isFull(Stack* s) {
    return s->size == MAX_STACK;
}

int pushStack(Stack* s, const char* newData) {
    if (isFull(s)) {
        printf("Stack sudah penuh! Maksimal %d elemen.\n", MAX_STACK);
        return 0;
    }
    
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Alokasi memori gagal.\n");
        return 0;
    }
    
    strcpy(newNode->item, newData);
    newNode->next = s->head;
    s->head = newNode;
    s->size++;
    printf("'%s' berhasil ditambahkan.\n", newData);
    return 1;
}

int popStack(Stack* s, char* removedData) {
    if (isEmpty(s)) {
        printf("Stack kosong, tidak ada elemen yang bisa dihapus.\n");
        return 0;
    }
    
    Node* temp = s->head;
    strcpy(removedData, temp->item);
    s->head = temp->next;
    free(temp);
    s->size--;
    printf("'%s' berhasil dihapus.\n", removedData);
    return 1;
}

int peekStack(Stack* s, char* topData) {
    if (isEmpty(s)) {
        printf("Stack kosong, tidak ada elemen di bagian atas.\n");
        return 0;
    }
    
    strcpy(topData, s->head->item);
    printf("Elemen teratas adalah '%s'\n", topData);
    return 1;
}

void clearStack(Stack* s) {
    while (!isEmpty(s)) {
        Node* temp = s->head;
        s->head = temp->next;
        free(temp);
    }
    s->size = 0;
    printf("Semua elemen dalam stack telah dihapus.\n");
}

int main() {
    Stack s;
    int choice;
    char buffer[50];
    
    initializeStack(&s);
    
    do {
        printf("Menu Stack:\n");
        printf("1. Tambah Elemen (Push)\n");
        printf("2. Hapus Elemen (Pop)\n");
        printf("3. Lihat Elemen Teratas (Peek)\n");
        printf("4. Cek Apakah Stack Kosong\n");
        printf("5. Kosongkan Stack\n");
        printf("6. Keluar\n");
        printf("Pilih operasi: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("Masukkan kata yang akan ditambah: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                pushStack(&s, buffer);
                system("pause");
                system("cls");
                break;
                
            case 2:
                popStack(&s, buffer);
                system("pause");
                system("cls");
                break;
                
            case 3:
                peekStack(&s, buffer);
                system("pause");
                system("cls");
                break;
                
            case 4:
                if (isEmpty(&s)) {
                    printf("Stack kosong.\n");
                } else {
                    printf("Stack tidak kosong.\n");
                }
                system("pause");
                system("cls");
                break;
                
            case 5:
                clearStack(&s);
                system("pause");
                system("cls");
                break;
                
            case 6:
                printf("Keluar dari program.\n");
                system("pause");
                system("cls");
                break;
                
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                system("pause");
                system("cls");
        }
    } while (choice != 6);
    
    return 0;
}
