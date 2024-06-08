#include "mycat.h"
#include <stdio.h>
#include <stdlib.h>

// implementation of mycat with no files
int mycat_no_file(int argc_local);

// Implementation of mycat in the absence of options
int mycat_no_flags(int argc_local, char *argv_local[]);

// Implementation of mycat with options
int mycat_with_flags(int argc_local, char *argv_local[], flags flags);

// Implementation of function of flags
int flag_functions(char *argv_local, flags flags);

// implementation of copying a file at a specified fpath into a out_stream
int copy_file(char *fpath, FILE *out_stream);

// Implementation of error output and clean up
void perror_and_clean(char *error_message, FILE *file, char *buff);

int mycat(int argc_local, char *argv_local[]) {
  flags mycat_flags = mycat_parser(argc_local, argv_local);
  if (mycat_flags.validity == VALIDITY_FAILURE)
    return EXIT_FAILURE;

  if (mycat_flags.h) {
    argv_local[1] = "README.md";
    mycat_no_flags(argc_local, argv_local);
    return EXIT_SUCCESS;
  }

  mycat_no_file(argc_local);

  if (mycat_flags.A == false && mycat_flags.b == false &&
      mycat_flags.e == false && mycat_flags.n == false &&
      mycat_flags.s == false && mycat_flags.t == false) {
    mycat_no_flags(argc_local, argv_local);
  } else {
    mycat_with_flags(argc_local, argv_local, mycat_flags);
  }

  return EXIT_SUCCESS;
}

int mycat_no_file(int argc_local) {
  if (argc_local == 1) {
    char *buff_stdin = calloc(PIPE_BUF, sizeof(char));
    if (buff_stdin == NULL) {
      perror("Buffer was not created");
      return ERR_MEMORY;
    }

    while (!feof(stdin)) {
      if ((fgets(buff_stdin, PIPE_BUF * sizeof(char), stdin)) == NULL) {
        if (!feof(stdin)) {
          perror("Stdin was not read");
          return ERR_READ;
        }
      }

      if (feof(stdin)) // Terminates the program if EOF after reading
        break;

      if (printf("%s", buff_stdin) < 0) {
        perror("Error of write in stdout");
        return ERR_WRITE;
      }
    }

    free(buff_stdin);
  }
  return EXIT_SUCCESS;
}

int mycat_no_flags(int argc_local, char *argv_local[]) {
  for (int i = 1; i <= argc_local - 1; i++) {
    if (argv_local[i][0] != '-' && argv_local[i][1] != '-') {
      copy_file(argv_local[i], stdout);
    }
  }
  return EXIT_SUCCESS;
}

int mycat_with_flags(int argc_local, char *argv_local[], flags flags) {
  if (flags.validity == VALIDITY_SUCCESS) {
    for (int i = 1; i <= argc_local - 1; i++) {
      if (argv_local[i][0] != '-' && argv_local[i][1] != '-') {
        flag_functions(argv_local[i], flags);
      }
    }
  } else if (flags.validity == VALIDITY_FAILURE)
    exit(EXIT_FAILURE);

  return EXIT_SUCCESS;
}

int copy_file(char *fpath, FILE *out_stream) {
  FILE *file = NULL;

  char *buff = calloc(BUFSIZ, sizeof(char));
  if (buff == NULL) {
    perror_and_clean("Buffer was not created", file, buff);
    return ERR_MEMORY;
  }

  if ((file = fopen(fpath, "r")) == NULL) {
    perror(fpath);
  } else {
    unsigned long int read_bytes = 0;

    do {
      if ((read_bytes = fread(buff, sizeof(char), BUFSIZ * sizeof(char),
                              file)) < BUFSIZ) {
        if (!feof(file)) {
          perror_and_clean("File was not read", file, buff);
          return ERR_READ;
        }
      }

      if (fwrite(buff, sizeof(char), read_bytes, out_stream) < read_bytes) {
        perror_and_clean("File was not output in stdout", file, buff);
        return ERR_WRITE;
      }
    } while (read_bytes == BUFSIZ);

    fclose(file);
  }
  free(buff);
  return EXIT_SUCCESS;
}

void perror_and_clean(char *error_message, FILE *file, char *buff) {
  if (file != NULL)
    fclose(file);

  if (buff != NULL)
    free(buff);

  perror(error_message);
}

int flag_functions(char *argv_local, flags flags) {
  FILE *file = NULL;

  char *buff = calloc(BUFSIZ, sizeof(char));
  if (buff == NULL) {
    perror_and_clean("Buffer was not created", file, buff);
    return ERR_MEMORY;
  }

  if ((file = fopen(argv_local, "r")) == NULL) {
    perror(argv_local);
  } else {
    unsigned long int copy_bytes = 0;
    int count_number = 1;

    if ((flags.n == true) || (flags.b == true)) {
      printf("%6d\t", count_number);
      count_number++;
    }

    int symbol_is_print = 0;

    do {
      if ((copy_bytes = fread(buff, sizeof(char), BUFSIZ * sizeof(char),
                              file)) < BUFSIZ) {
        if (!feof(file)) {
          perror_and_clean("File was not read", file, buff);
          return ERR_READ;
        }
      }

      for (unsigned long int i = 0; i < copy_bytes; i++) {

        if (buff[i] == '\t' && (flags.t == true || flags.A == true)) {
          if (printf("%s", "^I"))
            symbol_is_print++;
        }

        else if (buff[i] == '\n' && (flags.e == true || flags.A == true)) {
          printf("%c", '$');
          if (printf("%c", buff[i]))
            symbol_is_print++;
        }

        if ((buff[i] == '\n') && (buff[i + 1] == '\n') && (flags.s == true)) {
          int n = 2;
          while (buff[i + n] == '\n') {
            buff[i + n] = '\0';
            n++;
          }
        }

        if ((buff[i] == '\n' || buff[i] == '\0') && (flags.n == true) &&
            (flags.b == false)) {
          if (flags.e == false && flags.A == false)
            if (printf("%c", buff[i]))
              symbol_is_print++;
          if (copy_bytes != BUFSIZ && buff[i + 1] != '\0') {
            printf("%6d\t", count_number);
            count_number++;
          }
        }

        if ((buff[i] == '\n' || buff[i] == '\0') && (buff[i + 1] != '\n') &&
            (flags.b == true)) {
          if (flags.e == false && flags.A == false)
            if (printf("%c", buff[i]))
              symbol_is_print++;
          if (copy_bytes != BUFSIZ && buff[i + 1] != '\0') {
            printf("%6d\t", count_number);
            count_number++;
          }
        }

        if (!symbol_is_print && buff[i] != '\0')
          printf("%c", buff[i]);
        else
          symbol_is_print = 0;
      }
    } while (copy_bytes == BUFSIZ);
  }

  free(buff);
  fclose(file);

  return EXIT_SUCCESS;
}