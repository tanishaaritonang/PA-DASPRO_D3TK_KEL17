#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void binerKePolinomial(int bilangan, FILE *outputFile) {
    if (bilangan == 0) {
        fprintf(outputFile, "CRC: 0\n");
        printf("Polinomial: 0\n");
        return;
    }

    int panjang = log2(bilangan) + 1;
    int nilaiPangkatTertinggi = -1; // Inisialisasi dengan nilai yang tidak mungkin
    fprintf(outputFile, "CRC: ");
    printf("Polinomial: ");
    for (int i = panjang - 1; i >= 0; i--) {
        if ((bilangan >> i) & 1) {
            if (i == 1) {
                fprintf(outputFile, "x + ");
                printf("x + ");
            } else if (i == 0) {
                fprintf(outputFile, "1");
                printf("1");
            } else {
                fprintf(outputFile, "x^%d + ", i);
                printf("x^%d + ", i);
                // Memperbarui nilai pangkat tertinggi
                if (i > nilaiPangkatTertinggi) {
                    nilaiPangkatTertinggi = i;
                }
            }
        }
    }
    fprintf(outputFile,"\nNilai pangkat tertinggi: %d|\n", nilaiPangkatTertinggi);
    printf("\nNilai pangkat tertinggi: %d|\n", nilaiPangkatTertinggi);

}

int main() {
    printf("=========================================\n");
    printf("         SELAMAT DATANG                \n");
    printf("=========================================\n");
    printf("       di SIMULASI CRC NIM D3TK       \n");
    printf("=========================================\n");
    printf("    Silakan Pilih Menu   \n");
    printf("=========================================\n");


    int choice;

    do {
        printf("Menu:\n");
        printf("1. Masukkan 20 NIM\n");
        printf("2. Melakukan CRC Pada NIM\n");
        printf("3. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Masukkan 20 NIM\n");
                int i;
                FILE *fp;
                fp = fopen("nim_data.txt", "w");
                for (int j = 1; j <= 20; j++) {
                    printf("Masukkan Nim Mahasiswa %d : ", j);
                    scanf("%d", &i);
                    fprintf(fp, "%d|\n", i); // Menulis NIM ke file
                }
                fclose(fp);
                break;
            }
            case 2: {
                printf("Program CRC : \n");
                FILE *fptr;
                if ((fptr = fopen("nim_data.txt", "r")) == NULL) {
                    printf("Error: File tidak ada!");
                    exit(1);
                }
                FILE *outputFile;
                outputFile = fopen("crc.txt", "w");
                if (outputFile == NULL) {
                    printf("Error: File tidak dapat dibuat!");
                    exit(1);
                }

                char buff[255];
                while (fgets(buff, sizeof(buff), fptr)) {
                    int num;
                    sscanf(buff, "%d", &num); // Mengambil bilangan dari string
                    int binary[32];
                    int q = 0;
                    // Konversi bilangan bulat menjadi biner
                    while (num > 0) {
                        binary[q] = num % 2;
                        num = num / 2;
                        q++;
                    }
                    
                    // Menuliskan NIM ke file 'crc.txt'
                    fprintf(outputFile, "NIM: %s | Representasi Biner: ", buff);
                    for (int r = q - 1; r >= 0; r--) {
                        fprintf(outputFile, "%d", binary[r]);
                    }
                    fprintf(outputFile, " | ");
                    
                    // Mengonversi bilangan biner menjadi polinomial
                    int bilanganBiner = atoi(buff);
                    
                    
                    // Menampilkan hasil di cmd
                    printf("NIM: %s | Representasi Biner: ", buff);
                    for (int r = q - 1; r >= 0; r--) {
                        printf("%d", binary[r]);
                    }
                    printf(" | ");
                    
                 
                    //menampilkan polinomial di crc.txt
                    binerKePolinomial(bilanganBiner, outputFile);


                }
                fclose(fptr);
                fclose(outputFile);
                printf("Data NIM dan representasi biner serta polinomial telah disimpan dalam file 'crc.txt'\n");
                break;
            }
            
            case 3:
                printf("Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
        }
    } while (choice != 3);

    return 0;
}
