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
  printf("SIZE %d\n", size);

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

int main()
{
  // Input data NIM
  char nim[20][10];
  printf("Input 20 NIM:\n");
  for (int i = 0; i < 20; i++)
  {
    printf("NIM %d: ", i + 1);
    scanf("%s", nim[i]);
  }

  // Output program dalam .txt
  FILE *outputFile;
  outputFile = fopen("output.txt", "w");

  for (int i = 0; i < 20; i++)
  {
    char binary[160]; // Panjang biner, 20 NIM * 8 bit
    char crcResult[64];

    // 1. Konversi NIM menjadi biner
    convertToBinary(nim[i], binary);
    fprintf(outputFile, "a. NIM %d: %s\n", i + 1, nim[i]);
    printf("Binary representation: %s\n", binary);

    fprintf(outputFile, "b. Biner: %s\n", binary);

    // 2. Hitung CRC
    char divisor[64] = "10011"; // 100 // Contoh primitive polynomial
    calculateCRC(binary, divisor, crcResult);

    // 3. Output hasil
    fprintf(outputFile, "c. Hasil CRC: %s\n", crcResult);
    fprintf(outputFile, "d. Primitive Polynomial: %s\n", divisor);
    fprintf(outputFile, "e. Primitive Polynomial (Biner): %s\n", divisor);
    fprintf(outputFile, "f. Hasil Transmisi CRC: %s\n", crcResult);

    // binary = 1011
    // crcRes = 0110
    strcat(binary, crcResult);
    // binary = 10110110
    // crcRes = 0110

    fprintf(outputFile, "c. Concat CRC: %s\n", binary);

    // kalkulasi crc lagi antara divisor dengan binary dengan crcResult
    calculateCRC(binary, divisor, crcResult);
    fprintf(outputFile, "g. Pembuktian CRC: %s\n\n", strcmp(crcResult, "0000") == 0 ? "Valid" : "Tidak Valid");
  }

  fclose(outputFile);

  printf("Program selesai. Hasil disimpan dalam output.txt\n");

 return 0;
}