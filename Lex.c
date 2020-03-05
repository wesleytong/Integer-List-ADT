/****************************************************************************************
*  Wesley Tong
*  PA1
*  wtong5
*  Lex.c
*  Code for the Lex aspect of PA1
*  Based off of File.IO provided by Professor Tantalo
*****************************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "List.h"
#define MAX_LEN 160

extern int strcmp(const char*, const char*);
extern char *strtok(char*, const char*);
extern char* strcpy (char* destination, const char* source);
extern size_t strlen(const char *str);

int main(int argc, char * argv[]){
  int i = 0, count = 0;
  FILE *in, *out;
  char line[MAX_LEN];
  char* word;

  //checks command line for correct number of arguments
  if(argc != 3){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  // open files for reading and writing
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  if( in==NULL ){
     printf("Unable to open file %s for reading\n", argv[1]);
     exit(1);
  }
  if( out==NULL ){
     printf("Unable to open file %s for writing\n", argv[2]);
     exit(1);
  }

  //counts number of lines
  int c = 0;
  while((c=fgetc(in)) != EOF){
    if(c == '\n'){
      count++;
    }
  }

  //holds all of the lines of file
  char* Words[count];

  //goes back to the top of file (originally rewind but close/open is better)
  fclose(in);
  in = fopen(argv[1], "r");

  //copies inputs of file into Word array
  while(fgets(line, MAX_LEN, in) != NULL){
    word = strtok(line, "\n");
    if(word!=NULL){
      Words[i] = malloc(sizeof(char)*(strlen(word)+1));
      strcpy(Words[i], line);                             //automatically adds null terminator using +1 from 56
      i++;
    }
  }

  fclose(in);

  List L = newList();

  if(Words[0] != NULL){
    append(L, 0);
  }

  //moves cursor to the front before sorting
  moveFront(L);

  //follows a roughly similar pattern as insertion sort
  for(i = 1; i < count; i++){
    int j = i-1;
    while(j >= 0 && strcmp(Words[i],Words[get(L)]) <= 0){
      movePrev(L);
      j = j-1;
    }
    if(index(L)>=0){
      insertAfter(L, i);
    }
    else{
       prepend(L, i);
    }
    moveBack(L);
  }

  //prints out the values of list in alphabetical order.
  moveFront(L);
  int k = 0;
  while(k<count){
    fprintf(out, "%s \n", Words[get(L)]);
    moveNext(L);
    k++;
  }
  //printList(out, L);

  fclose(out);
  freeList(&L);

  for(i = 0; i < count; i++){
    free(Words[i]);
  }
  return 0;
}
