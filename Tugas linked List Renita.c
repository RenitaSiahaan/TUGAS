#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

/*Tugas struktur data F
Renita Enjel Siahaan
Npm : 23081010147
*/

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

// Prototipe fungsi
void tambahAwal(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void tambahData(node **head);
void tranverse(node *head);
int hitungPenjumlahan(node *head);
int hitungJumlah(node *head); //
int cariData(node *head, int bil);

//

int main()
{
    node *head;
    int pilih; // Ubah tipe data dari char ke int

    head = NULL;
    do {
        system("cls");
        printf("masukkan pilihan\n");
        printf("1. tambah data di awal\n");
        printf("2. tambah data di akhir\n");
        printf("3. tambah data di tengah list\n");
        printf("4. hapus data di awal\n");
        printf("5. hapus data di tengah\n");
        printf("6. hapus data di akhir\n");
        printf("7. cari data\n");
        printf("8. cetak isi list\n");
        printf("9. tampilkan hasil penjumlahan semua data\n");
        printf("10. tampilkan jumlah data\n");
        printf("MASUKKAN PILIHAN (tekan 0 untuk keluar) : ");
        fflush(stdin);
        scanf("%d", &pilih); // Menggunakan %d untuk membaca integer

        if (pilih == 1) {
            tambahAwal(&head);
        } else if (pilih == 2) {
            tambahAkhir(&head);
        } else if (pilih == 3) {
            tambahData(&head);
        } else if (pilih == 4) {
            hapusAwal(&head);
        } else if (pilih == 5) {
            hapusTengah(&head);
        } else if (pilih == 6) {
            hapusAkhir(&head);
        } else if (pilih == 7) {
            int bil;
            printf("\nMasukkan data yang dicari: ");
            scanf("%d", &bil);
            if (cariData(head, bil)) {
                printf("Data %d ditemukan.\n", bil);
            } else {
                printf("Data %d tidak ditemukan.\n", bil);
            }
            getch();
        } else if (pilih == 8) {
            tranverse(head);
            getch();
        } else if (pilih == 9) {
            int total = hitungPenjumlahan(head);
            printf("\nHasil penjumlahan semua data di linked list: %d\n", total);
            getch();
        } else if (pilih == 10) {
            int jumlah = hitungJumlah(head);
            printf("\nJumlah data di linked list: %d\n", jumlah);
            getch();
        }
    } while (pilih != 0);

    return 0;
}

//Menambahkan data di awal

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head; // Menambahkan di awal
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//Menambahkan data di akhir

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) {
            // Jika list kosong, tambahkan di awal
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next; // Mencari akhir list
            }
            pCur->next = pNew; // Menambahkan di akhir
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//

void hapusAwal(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada data yang dihapus.\n");
        getch();
        return;
    }

    node *temp = *head;
    *head = (*head)->next; // Menghapus node pertama
    free(temp);
}

//

void hapusTengah(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada data yang dihapus.\n");
        getch();
        return;
    }

    int pos;
    printf("Masukkan data setelah mana yang ingin dihapus: ");
    scanf("%d", &pos);

    node *pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    if (pCur == NULL || pCur->next == NULL) {
        printf("Data tidak ditemukan atau tidak ada data setelahnya.\n");
        getch();
        return;
    }

    node *temp = pCur->next;
    pCur->next = temp->next; // Menghapus node tengah
    free(temp);
}

//

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada data yang dihapus.\n");
        getch();
        return;
    }

    if ((*head)->next == NULL) {
        // Jika hanya ada satu node
        free(*head);
        *head = NULL;
        return;
    }

    node *pCur = *head;
    while (pCur->next->next != NULL) {
        pCur = pCur->next; // Mencari node sebelum akhir
    }

    free(pCur->next); // Menghapus node akhir
    pCur->next = NULL;
}

//

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nnode tidak ditemukan");
        getch();
    } else if (pNew == NULL) {
        printf("\nalokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pCur->next = pNew;
    }
}

//
void tranverse(node *head) {
    // Traverse a linked list
    node *pWalker;

    system("cls");
    pWalker = head;
    while (pWalker != NULL) {
        printf("%d\t", pWalker->data);
        pWalker = pWalker->next;
        printf(" -> ");
    }
    printf("NULL\n");
}

//

int hitungPenjumlahan(node *head) {
    int total = 0;
    node *pWalker = head;

    while (pWalker != NULL) {
        total += pWalker->data;
        pWalker = pWalker->next;
    }
    return total;
}

//

int hitungJumlah(node *head) {
    int count = 0;
    node *pWalker = head;

    while (pWalker != NULL) {
        count++; // Untuk enghitung jumlah node
        pWalker = pWalker->next;
    }
    return count; // Untuk mengembalikan jumlah node
}

//

int cariData(node *head, int bil) {
    node *pWalker = head;

    while (pWalker != NULL) {
        if (pWalker->data == bil) {
            return 1; // Apabila data ditemukan
        }
        pWalker = pWalker->next;
    }
    return 0; // Apabila data tidak ditemukan
}

