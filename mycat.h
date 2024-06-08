#ifndef _MYCAT_H
#define _MYCAT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_MEMORY -1      // Error of create buffer
#define ERR_READ -2        // Error of read file
#define ERR_WRITE -3       // Error of write
#define ERR_OPEN_FILE -4   // Error of open file
#define ERR_DELETE_FILE -5 // Error of delete file

#define PIPE_BUF 4096 // Size of pipe buffer

#define NUMBER_NONBLANK "--number-nonblank" // GUI -b
#define NUMBER "--number"                   // GUI -n
#define SQUEEZE_BLANK "--squeeze-blank"     // GUI -s
#define HELP "--help"                       // GUI --help

#define VALIDITY_FAILURE -1 // Not exist flag
#define VALIDITY_SUCCESS 0  // All flags exist or not define

// Struct of options for mycat
typedef struct {
  bool A;
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool h;
  int validity;
} flags;

// Struct of GUI options for mycat
typedef struct {
  char *num_nblnk;
  char *num;
  char *sqz_blnk;
  char *help;
} flags_GNU;

/* Analogue of the cat bash command
   argc_local: number of arguments passed from the command line
   argv_local: array of arguments passed from the command line */
int mycat(int argc_local, char *argv_local[]);

/* Parser of arguments of the mycat bash command
   argc_local: number of arguments passed from the command line
   argv_local: array of arguments passed from the command line */
flags mycat_parser(int argc_local, char *argv_local[]);

#endif