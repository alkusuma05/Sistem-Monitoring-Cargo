#include <stdio.h>
#include <string.h>

#define MAX_BARANG 5
#define MAX_NAMA   50
#define BAR_LEN    20

//ANSI Color
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"

//FUNGSI

void tentukanStatus(int stok, int batas, char status[]) {
    if (stok < batas)
        strcpy(status, "KRITIS");
    else if (stok < batas + 5)
        strcpy(status, "WASPADA");
    else
        strcpy(status, "AMAN");
}

void tentukanPrioritas(int stok, int batas, char prioritas[]) {
    if (stok < batas)
        strcpy(prioritas, "TINGGI");
    else if (stok < batas + 5)
        strcpy(prioritas, "SEDANG");
    else
        strcpy(prioritas, "RENDAH");
}

void tampilBar(int stok, int batas) {
    int persen, isi, i;

    persen = (stok * 100) / (batas + 10);
    if (persen > 100) persen = 100;

    isi = (persen * BAR_LEN) / 100;

    printf("[");
    for (i = 0; i < BAR_LEN; i++) {
        printf(i < isi ? "#" : "-");
    }
    printf("] %3d%%", persen);
}

int hitungSkor(int kritis, int waspada) {
    int skor = 100;
    skor -= kritis * 20;
    skor -= waspada * 10;
    if (skor < 0) skor = 0;
    return skor;
}

//MAIN 

int main() {
    char nama[MAX_BARANG][MAX_NAMA];
    int stok[MAX_BARANG], batas[MAX_BARANG];
    char status[MAX_BARANG][10];
    char prioritas[MAX_BARANG][10];

    int i, menu;
    int kritis, waspada, skor;

    //INPUT DATA
    printf(CYAN);
    printf("====================================================\n");
    printf("          INPUT DATA BARANG - KABUTO CARGO           \n");
    printf("====================================================\n");
    printf(RESET);

    for (i = 0; i < MAX_BARANG; i++) {
        printf("\nBarang ke-%d\n", i + 1);

        printf("Nama Barang        : ");
        fgets(nama[i], MAX_NAMA, stdin);
        nama[i][strcspn(nama[i], "\n")] = '\0';

        do {
            printf("Stok Saat Ini      : ");
            scanf("%d", &stok[i]);
        } while (stok[i] < 0);

        do {
            printf("Batas Minimum Aman : ");
            scanf("%d", &batas[i]);
        } while (batas[i] < 0);

        getchar();
    }

    //MENU 
    do {
        kritis = 0;
        waspada = 0;

        for (i = 0; i < MAX_BARANG; i++) {
            tentukanStatus(stok[i], batas[i], status[i]);
            tentukanPrioritas(stok[i], batas[i], prioritas[i]);

            if (strcmp(status[i], "KRITIS") == 0) kritis++;
            else if (strcmp(status[i], "WASPADA") == 0) waspada++;
        }

        skor = hitungSkor(kritis, waspada);

        printf("\n====================================================\n");
        printf("               SMART WAREHOUSE MENU                  \n");
        printf("====================================================\n");
        printf("1. Laporan Stok Barang\n");
        printf("2. Rekomendasi Restock\n");
        printf("3. Ringkasan Kesehatan Gudang\n");
        printf("0. Keluar\n");
        printf("Pilih menu : ");
        scanf("%d", &menu);

        //MENU 1 
        if (menu == 1) {
            printf("\n============================================================\n");
            printf("                        LAPORAN STOK                            \n");
            printf("============================================================\n");
            printf("| %-2s | %-20s | %-6s | %-6s | %-10s |\n",
                   "No", "Nama Barang", "Stok", "Min", "Status");
            printf("------------------------------------------------------------\n");

            for (i = 0; i < MAX_BARANG; i++) {
                printf("| %-2d | %-20s | %-6d | %-6d | %-10s |\n",
                       i + 1, nama[i], stok[i], batas[i], status[i]);
            }

            printf("============================================================\n");

            printf("\nVISUAL STOK:\n");
            for (i = 0; i < MAX_BARANG; i++) {
                printf("%-20s ", nama[i]);
                tampilBar(stok[i], batas[i]);
                printf("\n");
            }
        }

        //MENU 2
        else if (menu == 2) {
            printf("\n=====================================================\n");
            printf("                    REKOMENDASI RESTOCK                          \n");
            printf("=====================================================\n");
            printf("| %-20s | %-9s | %-14s |\n",
                   "Nama Barang", "Prioritas", "Jumlah Pesan");
            printf("-----------------------------------------------------\n");

            for (i = 0; i < MAX_BARANG; i++) {
                if (strcmp(prioritas[i], "RENDAH") != 0) {
                    int pesan = batas[i] + 5 - stok[i];
                    if (pesan < 0) pesan = 0;

                    printf("| %-20s | %-9s | %-14d |\n",
                           nama[i], prioritas[i], pesan);
                }
            }

            printf("=====================================================\n");
        }

        //MENU 3 
        else if (menu == 3) {
            printf("\n====================================================\n");
            printf("              RINGKASAN KESEHATAN GUDANG             \n");
            printf("====================================================\n");
            printf("Skor Gudang : %d / 100\n", skor);

            if (skor >= 80)
                printf(GREEN "Status : SEHAT\n" RESET);
            else if (skor >= 50)
                printf(YELLOW "Status : PERLU PERHATIAN\n" RESET);
            else
                printf(RED "Status : DARURAT LOGISTIK\n" RESET);
        }

    } while (menu != 0);

    printf(CYAN "\nProgram selesai. Kabuto Cargo siap beroperasi.\n" RESET);
    return 0;
}
