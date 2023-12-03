#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void convertToBinary(char nim[], char binary[]) {
    int n = atoi(nim);
    int size = sizeof(n) * 8;
    int index = 0;
    for (int i = size - 1; i >= 0; i--) {
        binary[index++] = ((n >> i) & 1) ? '1' : '0';
    }
    binary[index] = '\0';
}

int binaryToPolynomial(char binary[], char polynomial[], int exponents[], int *count) {
    int degree = strlen(binary) - 1;
    int maxExponent = -1;

    *count = 0; // Initialize count of exponents

    for (int i = 0; i < strlen(binary); i++) {
        if (binary[i] == '1') {
            int currentExponent = degree - i;
            exponents[*count] = currentExponent; // Store the exponent in the array
            (*count)++; // Increment the count
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
                sprintf(polynomial, "%s%s%d", polynomial, (currentExponent == 0) ? "" : " + x^", currentExponent);
                addedTerm = 1;
            } else {
                sprintf(polynomial + strlen(polynomial), "%s%d", (currentExponent == 0) ? " + x^0" : " + x^", currentExponent);
            }
        }
    }

    return maxExponent;
}

int getRandomExponent(int exponents[], int count) {
    // Generate a random index within the count of exponents
    int randomIndex = rand() % count;
    return exponents[randomIndex];
}

int main() {
    char binary[] = "1011"; // Contoh string biner
    char polynomial[100] = ""; // String untuk menyimpan polinomial
    int exponents[100]; // Array untuk menyimpan eksponen
    int count;

    srand(time(NULL)); // Inisialisasi seed untuk random number

    int maxExponent = binaryToPolynomial(binary, polynomial, exponents, &count);

    printf("Polynomial: %s\n", polynomial);
    printf("Max Exponent: %d\n", maxExponent);

    if (count > 0) {
        int randomExponent = getRandomExponent(exponents, count);
        printf("Random Exponent: %d\n", randomExponent);
    } else {
        printf("No exponents found.\n");
    }

    return 0;
}
