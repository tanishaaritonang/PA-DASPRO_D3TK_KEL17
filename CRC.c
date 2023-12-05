#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertToBinary(char decimalStr[], char binary[])
{
  // ubah tipe data dari string ke integer
  int n = atoi(decimalStr);

  // variable check jika bit sudah dimulai
  int significantBitsStarted = 0;

  // besar integer dalam bit
  int size = sizeof(n) * 8;
  //printf("SIZE %d\n", size);

  // Index binary array
  int index = 0;

  for (int i = size - 1; i >= 0; i--)
  {
    // Contoh nilai nim itu 179
    // >> shift right
    // Operasi >> pada bilangan biner adalah operasi shift-right, yang memindahkan semua bit dalam representasi biner ke kanan sejumlah posisi tertentu.
    // 179 >> 7 = 1
    // biner 179 = 00000000 00000000 00000000 10110011
    // >> shift right 7 posisi
    // 00000000 00000000 00000000 00000001

    if ((n >> i) & 1 || significantBitsStarted)
    {
      significantBitsStarted = 1;
      binary[index++] = ((n >> i) & 1) ? '1' : '0';
    }
  }

  // jika input sama dengan 0 maka binary = '0'
  if (index == 0)
  {
    binary[index++] = '0';
  }

  // Menambahkan null terminator ke dalam string biner
  binary[index] = '\0';
}

// Fungsi untuk menghitung CRC
void calculateCRC(char binary[], char divisor[], char crcResult[])
{
  int dataLength = strlen(binary);     // 10110011 // length = 8
  int divisorLength = strlen(divisor); // 5 // 10011

  // tempat sementara divisor
  char tempDivisor[64];
  strcpy(tempDivisor, divisor);
  // tempDivisor = 10011

  // tempat sementara binary agar tidak mengubah nilai aslinya
  char tempBinary[160];
  strcpy(tempBinary, binary);
  // tempBinary = 10110011
  // 1 0 1 1 0 0 1 1
  // 0 1 2 3 4 5 6 7

  // Append zeros to the binary data for division
  for (int i = 0; i < divisorLength - 1; i++)
  {
    tempBinary[dataLength + i] = '0';
    // tempBinary[8] = '0';
    // tempBinary[9] = '0';
    // tempBinary[10] = '0';
    // tempBinary[11] = '0';
  }

  // tempBinary = 101100110000
  // value = 1 0 1 1 0 0 1 1 0 0 0  0
  // index = 0 1 2 3 4 5 6 7 8 9 10 11

  // tempDivisor = 10011
  // value = 1 0 0 1 1
  // index = 0 1 2 3 4

  // dataLength = 8
  for (int i = 0; i < dataLength; i++)
  {
    if (tempBinary[i] == '1')
    {
      for (int j = 0; j < divisorLength; j++)
      {
        tempBinary[i + j] = (tempBinary[i + j] == tempDivisor[j]) ? '0' : '1';

        // i = 0
        // tempBinary[0] = (tempBinary[0] == tempDivisor[0]) ? '0' : '1'; => 0
        // tempBinary[1] = (tempBinary[1] == tempDivisor[1]) ? '0' : '1'; => 0
        // tempBinary[2] = (tempBinary[2] == tempDivisor[2]) ? '0' : '1'; => 1
        // tempBinary[3] = (tempBinary[3] == tempDivisor[3]) ? '0' : '1'; => 0
        // tempBinary[4] = (tempBinary[4] == tempDivisor[4]) ? '0' : '1'; => 1
      }
    }
  }

  // Copy the remainder (CRC) to the result array
  strcpy(crcResult, tempBinary + dataLength);

  // Null-terminate the result string
  crcResult[divisorLength - 1] = '\0';
}

void decimalToPolynomial(int n, char polynomial[])
{
  int degree = sizeof(int) * 8 - 1;
  int count = 0;
  int exponent[50];

  for (int i = degree; i >= 0; i--)
  {
    if ((n >> i) & 1)
    {
      exponent[count++] = i;
    }
  }

  int addedTerm = 0;
  for (int i = 0; i < count; i++)
  {
    int currentExponent = exponent[i];
    if (!addedTerm)
    {
      if (currentExponent == 1)
      {
        strcat(polynomial, "x^1");
      }
      else if (currentExponent == 0)
      {
        strcat(polynomial, "x^0");
      }
      else
      {
        char term[10];
        sprintf(term, "x^%d", currentExponent);
        strcat(polynomial, term);
      }
      addedTerm = 1;
    }
    else
    {
      if (currentExponent == 1)
      {
        strcat(polynomial, " + x^1");
      }
      else if (currentExponent == 0)
      {
        strcat(polynomial, " + x^0");
      }
      else
      {
        char term[10];
        sprintf(term, " + x^%d", currentExponent);
        strcat(polynomial, term);
      }
    }
  }
}

int binaryToPolynomial(char binary[], char polynomial[], int exponent[], int *count)
{
  int degree = strlen(binary) - 1;
  int maxExponent = -1;

  *count = 0;
  for (int i = 0; i < strlen(binary); i++)
  {
    if (binary[i] == '1')
    {
      int currentExponent = degree - i;
      exponent[*count] = currentExponent;
      (*count)++;
      if (currentExponent > maxExponent)
      {
        maxExponent = currentExponent;
      }
    }
  }

  int addedTerm = 0;
  for (int i = 0; i < strlen(binary); i++)
  {
    if (binary[i] == '1')
    {
      int currentExponent = degree - i;
      if (!addedTerm)
      {
        if (currentExponent == 1)
        {
          strcat(polynomial, "x^1");
        }
        else if (currentExponent == 0)
        {
          strcat(polynomial, "x^0");
        }
        else
        {
          char term[10];
          sprintf(term, "x^%d", currentExponent);
          strcat(polynomial, term);
        }
        addedTerm = 1;
      }
      else
      {
        if (currentExponent == 1)
        {
          strcat(polynomial, " + x^1");
        }
        else if (currentExponent == 0)
        {
          strcat(polynomial, " + x^0");
        }
        else
        {
          char term[10];
          sprintf(term, " + x^%d", currentExponent);
          strcat(polynomial, term);
        }
      }
    }
  }

  return maxExponent;
}

int main()
{

    printf("=========================================\n");
    printf("         SELAMAT DATANG                \n");
    printf("=========================================\n");
    printf("       SIMULASI CRC NIM D3TK       \n");
    printf("=========================================\n");
    printf("       Silakan Pilih Menu   \n");
    printf("=========================================\n");

    int choice;
    do{
    printf("Menu:\n");
    printf("1. Masukkan NIM\n");
    printf("2. Lakukan CRC\n");
    printf("3. Keluar\n");

    printf("Pilih: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1: {
    FILE *fp;
    fp = fopen("nim_data.txt", "w");
    if (fp == NULL) {
        printf("Gagal membuka file.\n");
        return 1;
    }

    char nim[20][10];
    printf("Input 20 NIM:\n");
    for (int i = 0; i < 20; i++) {
        printf("NIM %d: ", i + 1);
        scanf("%s", nim[i]);
        fprintf(fp, "%s\n", nim[i]); // Menulis NIM ke file
    }

    fclose(fp);
    break;
}


 case 2: {
    FILE *outputFile;
    outputFile = fopen("output.txt", "w");
    FILE *nimFile = fopen("nim_data.txt", "r");

    if (nimFile == NULL || outputFile == NULL) {
        printf("Gagal membuka file.\n");
        return 1;
    }

    char nim[20][10];

    // Membaca NIM dari file
    int i = 0;
    while (fscanf(nimFile, "%s", nim[i]) != EOF && i < 20) {
        char binary[160]; // Panjang biner, 20 NIM * 8 bit
        char crcResult[64];
        char polynomial[160];
        int exponent[100];
        int count;

        // 1. Konversi NIM menjadi biner
        convertToBinary(nim[i], binary);
        fprintf(outputFile, "a. NIM %d: %s\n", i + 1, nim[i]);

        fprintf(outputFile, "b. Biner: %s\n", binary);
        int maxExponent = binaryToPolynomial(binary, polynomial, exponent, &count);
        fprintf(outputFile, "b.1. Biner menjadi polinomial: %s\n", polynomial);
        fprintf(outputFile, "Nilai k adalah : %d\n", maxExponent);

        // 2. Hitung CRC
        char divisor[64] = "10011"; // 100 // Contoh primitive polynomial
        calculateCRC(binary, divisor, crcResult);

        memset(polynomial, 0, sizeof(polynomial));
        int divisorPolinomial = binaryToPolynomial("10011", polynomial, exponent, &count);
        // 3. Output hasil
   
        fprintf(outputFile, "c. Primitive Polynomial: %s\n", polynomial);
        fprintf(outputFile, "d. Primitive Polynomial (Biner): %s\n", divisor);
        fprintf(outputFile, "e. Hasil Transmisi CRC: %s\n", crcResult);

        // binary = 1011
        // crcRes = 0110
        strcat(binary, crcResult);
        // binary = 10110110
        // crcRes = 0110

        fprintf(outputFile, "f. Concat CRC: %s\n", binary);

        // kalkulasi crc lagi antara divisor dengan binary dengan crcResult
        calculateCRC(binary, divisor, crcResult);
        fprintf(outputFile, "g. Pembuktian CRC yang diterima telah sesuai: %s\n", crcResult);
        fprintf(outputFile, "h. Pembuktian CRC: %s\n\n", strcmp(crcResult, "0000") == 0 ? "Valid" : "Tidak Valid");

        memset(polynomial, 0, sizeof(polynomial));

        i++;
    }

    fclose(nimFile);
    fclose(outputFile);

    printf("Program selesai. Hasil disimpan dalam output.txt\n");
    break;
}
  case 3: {
                printf("Program selesai.\n");
                break;
            }
            default: {
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
                break;
            }
        }
    } while (choice != 3);

  return 0;
}