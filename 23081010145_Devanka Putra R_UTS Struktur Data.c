#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char nama[50];
    char gender;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    int size;
} CircularList;

int main() {
    CircularList lingkaran = { NULL, 0 };
    int choice;
    char nama[50], gender;

    while (1) {
        system("cls");
        printf("1. Tambah mahasiswa kelingkaran \n");
        printf("2. Mahasiswa yang keluar lingkaran\n");
        printf("3. Tampilkan Lingkaran\n");
        printf("Masukkan Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nama: ");
                scanf("%s", nama);
                printf("Jenis kelamin (l/p): ");
                scanf(" %c", &gender);
                tambahmhs(&lingkaran, nama, gender);
                break;
            case 2:
                printf("Nama yang dihapus: ");
                scanf("%s", nama);
                hapusmhs(&lingkaran, nama);
                break;
            case 3:
                displayCircle(&lingkaran);
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
        printf("Tekan enter untuk lanjut...");
        getchar(); getchar();
    }

    return 0;
}

Node* createNode(char* nama, char gender) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->nama, nama);
    newNode->gender = gender;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

void tambahmhs(CircularList* list, char* nama, char gender) {
    Node* newNode = createNode(nama, gender);
    if (!list->head) {
        list->head = newNode;
    } else {
        Node* tail = list->head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = list->head;
        list->head->prev = newNode;
    }
    list->size++;
    printf("%s masuk lingkaran\n", nama);
}

void hapusmhs(CircularList* list, char* nama) {
    if (!list->head) {
        printf("Lingkaran kosong.\n");
        return;
    }
    Node* temp = list->head;
    while (2) {
        if (strcmp(temp->nama, nama) == 0) {
            if (temp->next == temp) {
                list->head = NULL; 
            } else {
                if (temp == list->head) list->head = temp->next; 
                temp->prev->next = temp->next; 
                temp->next->prev = temp->prev; 
            }
            return;
        }
        temp = temp->next;
        if (temp == list->head) break; 
    }

    printf("%s tidak ada di lingkarang\n", nama);
}

void displayCircle(CircularList* list) {
    if (!list->head) {
        printf("Lingkaran kosong.\n");
        return;
    }

    Node* temp = list->head;
    do {
        printf("%s (%c) -> ", temp->nama, temp->gender);
        temp = temp->next;
    } while (temp != list->head);
    printf("(NULL)\n");
}
