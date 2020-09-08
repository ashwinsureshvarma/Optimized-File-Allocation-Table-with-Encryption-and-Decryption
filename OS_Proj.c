#include <stdio.h>

#include <stdio.h>

#include <stdlib.h>

#include<conio.h>

#include <string.h>

char * buffer = NULL;
int s_b[10][2], empty[10]; //Stores size and number of blocks
int mem = 500; //keeps track of free memory
char * block[10]; //store address of the blocks
int * address[10] = { 0,0,0,0,0,0,0,0,0,0}; //stores address of files
char name[10][30]; //stores name of the file


void create() //to create a file
{
  char fname[30], c;
  int size = 1, i;
  printf("Enter .txt file name\n");
  scanf("%s", fname);;
  FILE * inputf;
  inputf = fopen(fname, "r");
  if (inputf == NULL) {
    printf("\nFile unable to open ");
    exit(0);
  }
  rewind(inputf);
  c = fgetc(inputf);
  while (c != EOF) {
    c = fgetc(inputf);
    size = size + 1;
  }
  printf("The size of given file is : %d\n", size);
  if (mem >= size) {
    int n = 1, parts = 0, m = 1;
    while (address[n] != 0)
      n++;
    strcpy(name[n], fname);
    s_b[n][1] = size;
    int bnum = size / 50;
    if (size % 50 != 0)
      bnum = bnum + 1;
    s_b[n][2] = bnum;
    mem = mem - (bnum * 50);
    int * bfile = (int * ) malloc(bnum * (sizeof(int)));
    address[n] = bfile;
    printf("Number of blocks required: %d\n", bnum);
    rewind(inputf);
    c = fgetc(inputf);
    while (parts != bnum && c != EOF) {
      int k = 0;
      if (empty[m] == 0) {
        char * temp = block[m];
        while (k != 50) {
          * temp = c;
          c = fgetc(inputf);
          temp++;
          k = k + 1;
        }
        *(bfile + parts) = m;
        parts = parts + 1;
        empty[m] = 1;
      } else
        m = m + 1;
    }
    printf("File created\n");
    printf("\n");
    fclose(inputf);
  } else
    printf("Not enough memory\n");
}
int filenum(char fname[30]) {
  int i = 1, fnum = 0;
  while (name[i]) {
    if (strcmp(name[i], fname) == 0) {
      fnum = i;
      break;
    }
    i++;
  }
  return fnum;
}


void blocks() {
  int i;
  printf(" Block address empty/free\n");
  for (i = 1; i <= 10; i++)
    printf("%d. %s - %d\n", i, block[i], empty[i]);
  printf("\n");
}


void file() {
  int i = 1;
  printf("File name size block number\n");
  for (i = 1; i <= 10; i++) {
    if (address[i] != 0)
      printf("%s %d %d\n", name[i], s_b[i][1], * address[i]);
  }
  printf("\n");
}


void print() {
  char fname[30];
  int i = 1, j, k, fnum = 0;
  printf("Enter the file name: ");
  scanf("%s", fname);
  fnum = filenum(fname);
  if (fnum != 0 && address[fnum] != 0) {
    int * temp;
    temp = address[fnum];
    printf("Content of the file %s is:\n", name[fnum]);
    int b = (s_b[fnum][2]);
    for (j = 0; j < b; j++) {
      int s = * (temp + j);
      char * prt = block[s];
      for (k = 0; k < 50; k++) {
        printf("%c", * prt);
        prt++;
      }
    }
    printf("\n");
    printf("\n");
  } else
    printf("File not available:/n");
}


void remover() {
  char fname[30];
  int i = 1, j, k, fnum = 0;
  printf("Enter the file name: ");
  scanf("%s", fname);
  fnum = filenum(fname);
  if (fnum == 0)
    printf("File not available:/n");
  else {
    int * temp = address[fnum];
    int b = (s_b[fnum][2]);
    mem = mem + b * 50;
    for (j = 0; j < b; j++) {
      int s = * (temp + j);
      empty[s] = 0;
    }
    address[fnum] = 0;
  }
  printf("\n");
}


void encrypt() {
  char fname[20], ch;
  FILE * fpts, * fptt;
  printf("\n\n Encrypt a text file :\n");
  printf("--------------------------\n");
  printf(" Input the name of file to encrypt : ");
  scanf("%s", fname);
  fpts = fopen(fname, "r");
  if (fpts == NULL) {
    printf(" File does not exists or error in opening..!!");
    exit(1);
  }
  fptt = fopen("temp.txt", "w");
  if (fptt == NULL) {
    printf(" Error in creation of file temp.txt ..!!");
    fclose(fpts);
    exit(2);
  }
  while (1) {
    ch = fgetc(fpts);
    if (ch == EOF) {
      break;
    } else {
      ch = ch + 100;
      fputc(ch, fptt);
    }
  }
  fclose(fpts);
  fclose(fptt);
  fpts = fopen(fname, "w");
  if (fpts == NULL) {
    printf(" File does not exists or error in opening..!!");
    exit(3);
  }
  fptt = fopen("temp.txt", "r");
  if (fptt == NULL) {
    printf(" File does not exists or error in opening..!!");
    fclose(fpts);
    exit(4);
  }
  while (1) {
    ch = fgetc(fptt);
    if (ch == EOF) {
      break;
    } else {
      fputc(ch, fpts);
    }
  }
  printf(" File %s successfully encrypted ..!!\n\n", fname);
  fclose(fpts);
  fclose(fptt);
}


void decrypt() {
  char ch, fname[20];
  FILE * fpts, * fptt;
  printf("\n\n Decrypt a text file :\n");
  printf("--------------------------\n");
  printf(" Input the name of file to decrypt : ");
  scanf("%s", fname);
  fpts = fopen(fname, "w");
  if (fpts == NULL) {
    printf(" File does not exists or error in opening..!!");
    exit(7);
  }
  fptt = fopen("temp.txt", "r");
  if (fptt == NULL) {
    printf(" File does not exists or error in opening..!!");
    fclose(fpts);
    exit(9);
  }
  while (1) {
    ch = fgetc(fptt);
    if (ch == EOF) {
      break;
    } else {
      ch = ch - 100;
      fputc(ch, fpts);
    }
  }
  printf(" The file %s decrypted successfully..!!\n\n", fname);
  fclose(fpts);
  fclose(fptt);
}


int main() {
  char * buffer = (char * ) malloc(500); //Memory created-500 bytes
  int choice, i;
  char * temp;
  if (buffer == NULL) {
    fputs("Memory error", stderr);
    exit(2);
  }
  temp = buffer;
  block[1] = buffer;
  empty[1] = 0;
  for (i = 2; i <= 10; i++) {
    block[i] = block[i - 1] + 50;
    empty[i] = 0;
  }
  while (1) {
    printf("1.Create a new file\n");
    printf("2.Delete a file\n");
    printf("3.Print a file \n");
    printf("4.Display FAT table\n");
    printf("5.Display Block Details\n");
    printf("6.Encrypt a txt file\n");
    printf("7.Decrypt a txt file\n");
    printf("8.Exit.\n");
    printf("Enter your choice: ");
    scanf("%d", & choice);
    switch (choice) {
    case 1:
      create();
      break;
    case 2:
      remover();
      break;
    case 3:
      print();
      break;
    case 4:
      file();
      break;
    case 5:
      blocks();
      break;
    case 6:
      encrypt();
      break;
    case 7:
      decrypt();
      break;
    case 8:
      exit(1);
    }
  }
  return 0;
}