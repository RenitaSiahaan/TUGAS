#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};
typedef struct node node;

void tambahAwal(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void tambahData(node **head);
void tranverse(node *head);
int hitungPenjumlahan(node *head);
int hitungJumlah(node *head);
int cariData(node *head, int bil);

int main() {
    node *head = NULL;
    int pilih;

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
        scanf("%d", &pilih);

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
        if (*head == NULL) {
            pNew->next = pNew;
            pNew->prev = pNew;
        } else {
            pNew->next = *head;
            pNew->prev = (*head)->prev;
            (*head)->prev->next = pNew;
            (*head)->prev = pNew;
        }
        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

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
        if (*head == NULL) {
            pNew->next = pNew;
            pNew->prev = pNew;
            *head = pNew;
        } else {
            pCur = (*head)->prev;
            pNew->next = *head;
            pNew->prev = pCur;
            pCur->next = pNew;
            (*head)->prev = pNew;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

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
    while (pCur->next != *head && pCur->data != pos) {
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
        pNew->prev = pCur;
        pCur->next->prev = pNew;
        pCur->next = pNew;
    }
}

void hapusAwal(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada data yang dihapus.\n");
        getch();
        return;
    }

    node *temp = *head;
    if (temp->next == *head) {
        free(temp);
        *head = NULL;
    } else {
        node *pCur = *head;
        while (pCur->next != *head) {
            pCur = pCur->next;
        }
        pCur->next = temp->next;
        temp->next->prev = pCur;
        free(temp);
        *head = temp->next;
    }
}

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
    while (pCur->next != *head && pCur->data != pos) {
        pCur = pCur->next;
    }

    if (pCur == NULL || pCur->next == *head) {
        printf("Data tidak ditemukan atau tidak ada data setelahnya.\n");
        getch();
        return;
    }

    node *temp = pCur->next;
    pCur->next = temp->next;
    temp->next->prev = pCur;
    free(temp);
}

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada data yang dihapus.\n");
        getch();
        return;
    }

    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
    } else {
        node *pCur = *head;
        while (pCur->next->next != *head) {
            pCur = pCur->next;
        }
        free(pCur->next);
        pCur->next = *head;
        (*head)->prev = pCur;
    }
}

void tranverse(node *head) {
    system("cls");
    node *pWalker = head;
    do {
        printf("%d\t", pWalker->data);
        pWalker = pWalker->next;
        printf(" -> ");
    } while (pWalker != head);
    printf("NULL\n");
}

int hitungPenjumlahan(node *head) {
    int total = 0;
    node *pWalker = head;
    do {
        total += pWalker->data;
        pWalker = pWalker->next;
    } while (pWalker != head);
    return total;
}

int hitungJumlah(node *head) {
    int count = 0;
    node *pWalker = head;
    do {
        count++;
        pWalker = pWalker->next;
    } while (pWalker != head);
    return count;
}

int cariData(node *head, int bil) {
    node *pWalker = head;
    do {
        if (pWalker->data == bil) {
            return 1;
        }
        pWalker = pWalker->next;
    } while (pWalker != head);
    return 0;
}
