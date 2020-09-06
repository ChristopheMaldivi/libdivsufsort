#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>

#include <divsufsort.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("usage: sa INPUT_FILE\n");
    return -1;
  }

  char *filePath = argv[1];
  FILE *inputFilePtr = fopen(filePath, "rb");
  if (inputFilePtr == NULL)
  {
    printf("[ERROR] failed to open file '%s': %s\n", filePath, strerror(errno));
    return -2;
  }

  char *outputFilePath = "sa.out";
  FILE *outputFilePtr = fopen(outputFilePath, "w");
  if (outputFilePtr == NULL)
  {
    printf("[ERROR] failed to open file '%s': %s\n", filePath, strerror(errno));
    return -2;
  }


  fseek(inputFilePtr, 0, SEEK_END);
  long filelen = ftell(inputFilePtr);
  rewind(inputFilePtr);

  int n = filelen * 2;
  char *buffer = (char *)malloc(n * sizeof(char));
  fread(buffer, filelen, 1, inputFilePtr);
  memcpy(buffer + filelen, buffer, filelen);
  fclose(inputFilePtr);

  // intput data
  char *Text = buffer;

  // allocate
  int *SA = (int *)malloc(n * sizeof(int));

  // sort
  divsufsort((unsigned char *)Text, SA, n);

  // output
  /*
  for (i = 0; i < n; ++i)
  {
    printf("SA[%2d] = %2d: ", i, SA[i]);
    for (j = SA[i]; j < n; ++j)
    {
      printf("%c", Text[j]);
    }
    printf("\n");
  }
  */

  for (int i = 0; i < n; ++i)
  {
    int saIndex = SA[i];
    if (saIndex < (n / 2))
    {
      fprintf(outputFilePtr, "%d ", saIndex);
    }
  }
  fprintf(outputFilePtr, "\n");
  fclose(outputFilePtr);

  // deallocate
  free(SA);
  free(buffer);

  return 0;
}