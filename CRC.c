#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void convertToBinary(char nim[], char binary[]) {
    int n = atoi(nim);
    int size = sizeof(n) * 8;
    int index = 0;
    for (int i = size - 1; i >= 0; i--) {
        if ((n >> i) & 1)
            binary[index++] = '1';
        else
            binary[index++] = '0';
    }
    binary[index] = '\0';
}

void calculateCRC(char data[], char divisor[], char crcResult[]) {
    // Implementasi perhitungan CRC di sini
    // ...

    // Kode perhitungan CRC yang sesuai
    // ...

    strcpy(crcResult, "0000"); // Contoh nilai CRC kosong untuk sekarang
}

void binerKePolinomial(int bilangan, FILE *outputFile) {
    if (bilangan == 0) {
        fprintf(outputFile, "CRC: 0\n");
        printf("Polinomial: 0\n");
        return;
    }

    int panjang = log2(bilangan) + 1;
    fprintf(outputFile, "CRC: ");
    printf("Polinomial: ");
    for (int i = panjang - 1; i >= 0; i--) {
        if ((bilangan >> i) & 1) {
            if (i == 1) {
                fprintf(outputFile, " + x");
                printf(" + x");
            } else if (i == 0) {
                fprintf(outputFile, " + x^0");
                printf(" + x^0");
            } else {
                if (i == panjang - 1) {
                    fprintf(outputFile, "x^%d", i);
                    printf("x^%d", i);
                } else {
                    fprintf(outputFile, " + x^%d", i);
                    printf(" + x^%d ", i);
                }
            }
        }
    }
    fprintf(outputFile, "\n");
    printf("\n");
}

int main() {
    char nim[20][10];
    printf("Input 20 NIM:\n");
    for (int i = 0; i < 20; i++) {
        printf("NIM %d: ", i + 1);
        scanf("%s", nim[i]);
    }

    FILE *outputFile;
    outputFile = fopen("output.txt", "w");

    for (int i = 0; i < 20; i++) {
        char binary[160];
        char crcResult[64];

        convertToBinary(nim[i], binary);
        fprintf(outputFile, "a. NIM %d: %s\n", i + 1, nim[i]);
        fprintf(outputFile, "b. Biner: %s\n", binary);

        char divisor[64] = "10011";
        calculateCRC(binary, divisor, crcResult);

        fprintf(outputFile, "c. Hasil CRC: %s\n", crcResult);
        fprintf(outputFile, "d. Primitive Polynomial: %s\n", divisor);
        fprintf(outputFile, "e. Primitive Polynomial (Biner): %s\n", divisor);
        fprintf(outputFile, "f. Hasil Transmisi CRC: %s\n", crcResult);
        fprintf(outputFile, "g. Pembuktian CRC: %s\n\n", strcmp(crcResult, "0000") == 0 ? "Valid" : "Tidak Valid");

        int bilangan = atoi(crcResult);
        binerKePolinomial(bilangan, outputFile);
    }

    fclose(outputFile);

    printf("Program selesai. Hasil disimpan dalam output.txt\n");

    return 0;
}
