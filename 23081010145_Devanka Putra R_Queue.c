#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int npm;
    char nama[50];
    char prodi[20];
    float ipk;
} Mahasiswa;

typedef struct Node {
    Mahasiswa data;
    struct Node* next;
} Node;

typedef struct {
    Node* depan;
    Node* belakang;
    int ukuran;
} Antrian;

Antrian* buatAntrian() {
    Antrian* antrian = (Antrian*)malloc(sizeof(Antrian));
    antrian->depan = antrian->belakang = NULL;
    antrian->ukuran = 0;
    return antrian;
}

int antrianKosong(Antrian* antrian) {
    return antrian->ukuran == 0;
}

void tambahAntrian(Antrian* antrian, Mahasiswa data) {
    Node* nodeBaru = (Node*)malloc(sizeof(Node));
    nodeBaru->data = data;
    nodeBaru->next = NULL;

    if (antrianKosong(antrian)) {
        antrian->depan = antrian->belakang = nodeBaru;
    } else {
        antrian->belakang->next = nodeBaru;
        antrian->belakang = nodeBaru;
    }
    antrian->ukuran++;
}

Mahasiswa hapusAntrian(Antrian* antrian) {
    if (antrianKosong(antrian)) {
        printf("Antrian kosong!\n");
        Mahasiswa kosong = {0, "", "", 0.0};
        return kosong;
    }

    Node* sementara = antrian->depan;
    Mahasiswa data = sementara->data;
    antrian->depan = antrian->depan->next;

    if (antrian->depan == NULL) {
        antrian->belakang = NULL;
    }

    free(sementara);
    antrian->ukuran--;
    return data;
}

void tampilkanAntrian(Antrian* antrian) {
    if (antrianKosong(antrian)) {
        printf("Antrian kosong.\n");
        return;
    }

    printf("NPM         Nama             Prodi              IPK\n");
    Node* sementara = antrian->depan;
    while (sementara) {
        Mahasiswa mhs = sementara->data;
        printf("%-10d %-17s %-18s %.2f\n", mhs.npm, mhs.nama, mhs.prodi, mhs.ipk);
        sementara = sementara->next;
    }
}

void masukkanMahasiswa(Antrian* antrian) {
    Mahasiswa mhs;
    printf("Masukkan NPM: ");
    scanf("%d", &mhs.npm);
    getchar();
    printf("Masukkan Nama: ");
    fgets(mhs.nama, 50, stdin);
    mhs.nama[strcspn(mhs.nama, "\n")] = 0;
    printf("Masukkan Prodi: ");
    fgets(mhs.prodi, 20, stdin);
    mhs.prodi[strcspn(mhs.prodi, "\n")] = 0;
    printf("Masukkan IPK: ");
    scanf("%f", &mhs.ipk);

    tambahAntrian(antrian, mhs);
    printf("Mahasiswa berhasil ditambahkan ke antrian.\n");
}

int main() {
    Antrian* antrian = buatAntrian();
    int pilihan;

    do {
        system("cls");
        printf("Menu:\n");
        printf("1. Tambahkan Mahasiswa ke Antrian\n");
        printf("2. Hapus Mahasiswa dari Antrian\n");
        printf("3. Tampilkan Antrian\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                system("cls");
                masukkanMahasiswa(antrian);
                system("pause");
                break;
            case 2:
                system("cls");
                if (!antrianKosong(antrian)) {
                    Mahasiswa mhs = hapusAntrian(antrian);
                    printf("Mahasiswa yang dihapus dari antrian:\n");
                    printf("NPM: %d, Nama: %s, Prodi: %s, IPK: %.2f\n", 
                           mhs.npm, mhs.nama, mhs.prodi, mhs.ipk);
                } else {
                    printf("Antrian kosong.\n");
                }
                system("pause");
                break;
            case 3:
                system("cls");
                printf("Data Mahasiswa dalam Antrian:\n");
                tampilkanAntrian(antrian);
                system("pause");
                break;
            case 4:
                system("cls");
                printf("Keluar dari program.\n");
                break;
            default:
                system("cls");
                printf("Pilihan tidak valid.\n");
                system("pause");
                break;
        }
    } while (pilihan != 4);

    return 0;
}
