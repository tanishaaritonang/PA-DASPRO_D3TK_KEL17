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



int binaryToPolynomial(char binary[], char polynomial[]) {
    int degree = strlen(binary) - 1;
    int foundFirstTerm = 0;
    int maxExponent = -1;

    for (int i = 0; i < strlen(binary); i++) {
        if (binary[i] == '1') {
            int currentExponent = degree - i;
            if (currentExponent > maxExponent) {
                maxExponent = currentExponent;
            }
        }
    }

    int addedTerm = 0;
    for (int i = 0; i < strlen(binary); i++) {
        if (binary[i] == '1') {
            int currentExponent = degree - i;
            if (!addedTerm) {
                if (currentExponent == 1) {
                    strcat(polynomial, "x^1");
                } else if (currentExponent == 0) {
                    strcat(polynomial, "x^0");
                } else {
                    char term[10];
                    sprintf(term, "x^%d", currentExponent);
                    strcat(polynomial, term);
                }
                addedTerm = 1;
            } else {
                if (currentExponent == 1) {
                    strcat(polynomial, " + x^1");
                } else if (currentExponent == 0) {
                    strcat(polynomial, " + x^0");
                } else {
                    char term[10];
                    sprintf(term, " + x^%d", currentExponent);
                    strcat(polynomial, term);
                }
            }
        }
    }

    return maxExponent;
}

void primitivePolynomial(int maxExponent, char primitivePoly[]) {
    int nilaiN = maxExponent - 1;// Nilai n ialah 22 maka sesuai ketentuan degree n ialai "x^22 + x + 1"
    strcpy(primitivePoly, "x^22 + x + 1");
    printf("Nilai K ialah: %d\n", maxExponent);
    printf("Nilai N ialah: %d\n", nilaiN);
    printf("Primitive Polynomial: %s\n", primitivePoly);
}
void primitivePolyToBiner(char primitivePoly[]){

}
void calculateCRC(char data[], char divisor[], char crcResult[]) {
    int n = strlen(divisor) - 1; // Nilai n yang telah ditentukan sebelumnya (22)
    int dataLength = strlen(data);

    // Menambahkan n digit angka 0 pada data yang ditransmisikan
    char newData[160];
    strcpy(newData, data);
    for (int i = 0; i < n; i++) {
        strcat(newData, "0");
    }

    // Melakukan operasi pembagian
    for (int i = 0; i <= dataLength - n; i++) {
        if (newData[i] == '1') {
            for (int j = 0; j <= n; j++) {
                newData[i + j] = (newData[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    // Menyimpan hasil sisa operasi XOR sebagai CRC
    strcpy(crcResult, newData + dataLength);
}

int main() {

      printf("=========================================\n");
  printf("         SELAMAT DATANG                \n");
  printf("=========================================\n");
  printf("       di SIMULASI CRC NIM D3TK       \n");
  printf("=========================================\n");
  printf("    Silakan Pilih Menu   \n");
  printf("=========================================\n");
    char nim[20][10];
    printf("Input 20 NIM:\n");
    for (int i = 0; i < 20; i++) {
        printf("NIM %d: ", i + 1);
        scanf("%s", nim[i]);
    }
    char binary[160];
char crcResult[64];

    FILE *outputFile;
    outputFile = fopen("output.txt", "w");

    for (int i = 0; i < 20; i++) {
        char binary[160];
        char crcResult[64];

        convertToBinary(nim[i], binary);
        fprintf(outputFile, "a. NIM %d: %s\n", i + 1, nim[i]);  
        printf( "a. NIM %d: %s\n", i + 1, nim[i]);  

        fprintf(outputFile, "b. Biner: %s\n", binary);
        printf( "b. Biner: %s\n", binary);


        char polynomial[100] = "";
        int maxExponent = binaryToPolynomial(binary, polynomial);
        printf(" c.Polinomial: %s\n", polynomial);

        char divisor[64] = "10110"; // primitve polynomial yang digunakan dalam biner dari "x^22 + x + 1"
        calculateCRC(binary, divisor, crcResult);

        char primitivePoly[100];
        primitivePolynomial(maxExponent, primitivePoly);
        fprintf(outputFile, "c.Polinomial: %s\n", polynomial);
        fprintf(outputFile, "d. Primitive Polynomial: %s\n", primitivePoly);
        printf( "d. Primitive Polynomial: %s\n", primitivePoly);
        fprintf(outputFile, "e. Primitive Polynomial (Biner): %s\n", divisor);
        printf( "e. Primitive Polynomial (Biner): %s\n", divisor);
        fprintf(outputFile, "f. Hasil Transmisi CRC: %s\n", crcResult);
        printf( "f. Hasil Transmisi CRC: %s\n", crcResult);
        fprintf(outputFile, "g. Pembuktian CRC: %s\n\n", strcmp(crcResult, "0000") == 0 ? "Valid" : "Tidak Valid");
        printf( "g. Pembuktian CRC: %s\n\n", strcmp(crcResult, "0000") == 0 ? "Valid" : "Tidak Valid");

    }

    fclose(outputFile);

    printf("Program selesai. Hasil disimpan dalam output.txt\n");

    return 0;
}
