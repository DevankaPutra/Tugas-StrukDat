#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================
struct node {
    int data;
    struct node *next;
};
typedef struct node node; 

//========================================================

void tambahAwal(node **head);   
void tambahData(node **head);   
void tranverse(node *head);     
void tambahAkhir(node **head);         
void hapusAwal(node **head);           
void hapusTengah(node **head, int target); 
void hapusAkhir(node **head);          
void searchNode(node *head, int target);
int countNodes(node *head);            
int sumNodes(node *head);              
void createCircularList(node **head);  
void tranverseCircular(node *head);     

//========================================================

int main() {
    node *head;      
    char pilih;       
    int target;       
    head = NULL;  
    
    do {
        system("cls");  
        printf("Masukkan pilihan:\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah list\n");
        printf("3. Tambah data di akhir\n");
        printf("4. Hapus data di awal\n");
        printf("5. Hapus data di tengah list\n");
        printf("6. Hapus data di akhir\n");
        printf("7. Cetak isi list\n");
        printf("8. Cari data\n");
        printf("9. Jumlahkan semua data\n");
        printf("10. Tampilkan jumlah data\n");
        printf("11. Buat Circular Linked List\n");  
        printf("12. Cetak isi Circular Linked List\n"); 

        printf("MASUKKAN PILIHAN (tekan q untuk keluar): ");
        fflush(stdin);  
        scanf("%c", &pilih); 

        switch (pilih) {
            case '1':
                tambahAwal(&head); 
                break;
            case '2':
                tambahData(&head);  
                break;
            case '3':
                tambahAkhir(&head);  
                break;
            case '4':
                hapusAwal(&head);   
                break;
            case '5':
                printf("Masukkan nilai node yang ingin dihapus: ");
                fflush(stdin);
                scanf("%d", &target);
                hapusTengah(&head, target);  
                break;
            case '6':
                hapusAkhir(&head);  
                break;
            case '7':
                tranverse(head); 
                getch();
                break;
            case '8':
                printf("Masukkan data yang ingin dicari: ");
                fflush(stdin);
                scanf("%d", &target);
                searchNode(head, target);  
                getch();
                break;
            case '9':
                printf("Hasil penjumlahan semua data: %d\n", sumNodes(head));  
                getch();
                break;
            case '10':
                printf("Jumlah node di dalam linked list: %d\n", countNodes(head)); 
                getch();
                break;
            case '11':
                createCircularList(&head); 
                break;
            case '12':
                tranverseCircular(head);  
                getch();
                break;
        }
    } while (pilih != 'q');  
    return 0;
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node)); 

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head); 
    printf("\nPosisi penyisipan setelah data bernilai: ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nBilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));
    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
        getch();
    } else if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
    }
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;
        if (*head == NULL) {
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void hapusAwal(node **head) {
    node *pTemp;

    system("cls");
    if (*head != NULL) {
        pTemp = *head;
        *head = (*head)->next;
        free(pTemp);
        printf("Data awal berhasil dihapus.\n");
    } else {
        printf("List kosong.\n");
    }
    getch();
}

//========================================================

void hapusTengah(node **head, int target) {
    node *pCur, *pPrev;

    system("cls");
    if (*head == NULL) {
        printf("List kosong.\n");
        getch();
        return;
    }

    pCur = *head;
    pPrev = NULL;
    while (pCur != NULL && pCur->data != target) {
        pPrev = pCur;
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("Data tidak ditemukan.\n");
    } else {
        if (pPrev != NULL) {
            pPrev->next = pCur->next;
        } else {
            *head = pCur->next;
        }
        free(pCur);
        printf("Data berhasil dihapus.\n");
    }
    getch();
}

//========================================================

void hapusAkhir(node **head) {
    node *pCur, *pPrev;

    system("cls");
    if (*head == NULL) {
        printf("List kosong.\n");
        getch();
        return;
    }

    pCur = *head;
    pPrev = NULL;
    while (pCur->next != NULL) {
        pPrev = pCur;
        pCur = pCur->next;
    }

    if (pPrev != NULL) {
        pPrev->next = NULL;
    } else {
        *head = NULL;
    }
    free(pCur);
    printf("Data akhir berhasil dihapus.\n");
    getch();
}

//========================================================

void tranverse(node *head) {
    node *pWalker;

    system("cls");
    pWalker = head;
    while (pWalker != NULL) {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    }
    printf("NULL\n");
}

//========================================================

int countNodes(node *head) {
    int count = 0;
    node *pWalker = head;

    while (pWalker != NULL) {
        count++;
        pWalker = pWalker->next;
    }
    return count;
}

//========================================================

int sumNodes(node *head) {
    int sum = 0;
    node *pWalker = head;

    while (pWalker != NULL) {
        sum += pWalker->data;
        pWalker = pWalker->next;
    }
    return sum;
}

//========================================================

void searchNode(node *head, int target) {
    node *pWalker = head;

    while (pWalker != NULL) {
        if (pWalker->data == target) {
            printf("Data ditemukan: %d\n", pWalker->data);
            return;
        }
        pWalker = pWalker->next;
    }
    printf("Data tidak ditemukan.\n");
}

//========================================================

void createCircularList(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak dapat membuat circular linked list.\n");
        return;
    }
    node *pCur = *head;

    while (pCur->next != NULL) {
        pCur = pCur->next;
    }
    pCur->next = *head;  
    printf("Circular Linked List berhasil dibuat.\n");
}

//========================================================

void tranverseCircular(node *head) {
    node *pWalker;

    system("cls");
    if (head == NULL) {
        printf("List kosong.\n");
        return;
    }
    pWalker = head;
    do {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    } while (pWalker != head);
    printf("(kembali ke head)\n");
}