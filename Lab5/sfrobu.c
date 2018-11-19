#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>


#include <stdio.h>
//Global to check whether or not the f flag has been passed
int isF = 0;


//comparison function between frobnicated char arrays
int frobcmp(char const * a, char const * b)
{
  char a2, b2;
  while (*a != ' ' && *b != ' ')
  {
    a2 = *a^42;
    b2 = *b^42;

    if (isF == 1)
      {
	a2 = toupper((unsigned char)(a2));
	b2 = toupper((unsigned char)(b2));
      }
    
    if (a2 < b2)
      return -1;
    else if (a2 > b2)
      return 1;
    else
      {
	a++;
	b++;
	if (*a == ' ' && *b != ' ')
	  return -1;
	else if (*b == ' ' && *a != ' ')
	  return 1;
      }
  }
  return 0;
}

// Wrapper for the frobcmp function, so it can be used in qsort
int frobcmpWrapper(const void* a, const void* b)
{
  return frobcmp((*(const char**) a), (*(const char**) b));

}

// Print out the contents of a char string
void writeCharArray(const char* str)
{
  int size = 0;
  char curr = str[0];
  while (curr != ' ')
    {
      size++;
      curr = *(str + size);
    }
  
    write(1, str, size);
    if (size > 0)
      write(1, " ", 1);
}



int main(int argc, const char* argv[])
{
  // Initialize "string" variable, index pointer, and size
  char *readChar, *inputString;
  char **arrayToSortEQ, **arrayToSort;
  long size = 0, arrSize = 0;
  int inputSize, readStatus, prevCharSpace = 0;
  long i = 0;

  if (argc > 1 && strcmp("-f", argv[1]) == 0)
      isF = 1;


  struct stat fileStat;
  
  //check error status of stdin
  if (fstat(0, &fileStat) < 0)
    {
      write(2, "fstat error!\n", 14);
      exit(1);
    }

  // check if stdin contains a regular file
  if (S_ISREG(fileStat.st_mode) != 0)
    {
      if (fileStat.st_size > 0)
	{
	  // Allocate memory based on size of file
	  inputString = malloc(fileStat.st_size);
	  inputSize = fileStat.st_size;
	  size = inputSize;
	  readStatus = read(0, inputString, inputSize);
	}
      else
	{
	  inputString = malloc (100);
	  inputSize = 100;
	}
    }
  else
    {
      // Allocate an arbitrary amount of memory
      inputString = malloc(100);
      inputSize = 100;
    }

  

  // Traverse through stdin input and collect all chars into an array
  // including EXT characters
  readChar = inputString + size;
  readStatus = read(0, readChar, 1);
  if (size > 0)
   {
      if (readStatus > 0)
     	  inputSize++;	
   }else if (S_ISREG(fileStat.st_mode) == 0)
    {
      if (readStatus == -1)
	{
	  free(inputString);
	  write(2, "Input Error 1\n", 15);
	  exit(1);
	}

    }
      
  while (readStatus > 0)
    {
      size++;
      if (size % inputSize == 0)
      {
	  inputString = realloc(inputString, size + inputSize);
          if (inputString == NULL)
            {
              free(inputString);
              write(2, "Memory Allocation Error!\n", 26);
	      exit(1);
            }

	  inputSize = 100;
      }
      
      readChar = inputString + size;
      readStatus = read(0, readChar, 1);

      if (readStatus == -1)
	{
	  write(2, "Input error 2!\n", 16);
	  exit(1);
	}
      
    }

  
  // If stdin was not empty and the last character is not a space, add a space
  if (size > 0)
    if (inputString[size-1] != ' ')
      {
      	inputString = realloc(inputString, size+1);
        if (inputString == NULL)
            {
              free(inputString);
	      write(2, "Memory Allocation Error!\n", 26);
	      exit(1);
            }
      	inputString[size] = ' ';
      	size++;
      }


  // add the individual arrays for sorting
  arrayToSort = malloc(100 * sizeof(char*));
  i = 0;
  while (*(inputString + i) == ' ')
    i++;
  
  if (i < size)
    {
      arrayToSort[0] = inputString + i;
      arrSize++;
    }
  i++;

  while (i < size -1)
    {
      if (*(inputString + i) == ' ')
	{
	  while (*(inputString + i  + 1) == ' ' && i < size - 1)
	    i++;
	  arrayToSort[arrSize] = inputString + i  + 1;	  
	  arrSize++;
	  if (arrSize % 100 == 0)
	    {
	      arrayToSort = realloc(arrayToSort, arrSize * sizeof(char*) + 100 * sizeof(char*));
	      if (arrayToSort == NULL)
		{
		  free(inputString);
		  free(arrayToSort);
		  write(2, "Memory Allocation Error!\n", 26);
		  exit(1);
		}
	    }
	  
	}
      i++;
    }












  
  // sort the array
  qsort(arrayToSort, arrSize, sizeof(char*), frobcmpWrapper);

  
  // print the output to standard output
  i = 0;
  while (i < arrSize)
     {
       writeCharArray(arrayToSort[i]);
       i++;
     }


  
   //free array variables
   //free(arrayToSort);
   free(inputString);

}
