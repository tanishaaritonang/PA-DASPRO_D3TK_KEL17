#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi untuk mengkonversi NIM menjadi biner
void convertToBinary(char nim[], char binary[]) {
    // Implementasi konversi dari NIM ke biner di sini
    // ...

    // Contoh implementasi sederhana (asumsi NIM adalah bilangan)
    int decimalNIM = atoi(nim);
    itoa(decimalNIM, binary, 2);
}

// Fungsi untuk menghitung CRC
void calculateCRC(char data[], char divisor[], char crcResult[]) {
    // Implementasi perhitungan CRC di sini
    // ...

    // Contoh implementasi sederhana (asumsi XOR sebagai operasi pembagian)
    strcpy(crcResult, data);
    // Operasi XOR antara data dan divisor
    for (int i = 0; i < strlen(data) - strlen(divisor) + 1; i++) {
        if (crcResult[i] == '1') {
            for (int j = 0; j < strlen(divisor); j++) {
                crcResult[i + j] = crcResult[i + j] == divisor[j] ? '0' : '1';
            }
        }
    }
}

int main() {
    // Input data NIM
    char nim[20][10];
    printf("Input 20 NIM:\n");
    for (int i = 0; i < 20; i++) {
        printf("NIM %d: ", i + 1);
        scanf("%s", nim[i]);
    }

    // Output program dalam .txt
    FILE *outputFile;
    outputFile = fopen("output.txt", "w");

    for (int i = 0; i < 20; i++) {
        char binary[64];
        char crcResult[64];

        // 1. Konversi NIM menjadi biner
        convertToBinary(nim[i], binary);
        fprintf(outputFile, "a. NIM %d: %s\n", i + 1, nim[i]);
        fprintf(outputFile, "b. Biner: %s\n", binary);

        // 2. Hitung CRC
        char divisor[64] = "10011";  // Contoh primitive polynomial
        calculateCRC(binary, divisor, crcResult);

        // 3. Output hasil
        fprintf(outputFile, "c. Hasil CRC: %s\n", crcResult);
        fprintf(outputFile, "d. Primitive Polynomial: %s\n", divisor);
        fprintf(outputFile, "e. Primitive Polynomial (Biner): %s\n", divisor);
        fprintf(outputFile, "f. Hasil Transmisi CRC: %s\n", crcResult);
        fprintf(outputFile, "g. Pembuktian CRC: %s\n\n", strcmp(crcResult, "0000") == 0 ? "Valid" : "Tidak Valid");
    }

    fclose(outputFile);

    printf("Program selesai. Hasil disimpan dalam output.txt\n");

    return 0;
}
