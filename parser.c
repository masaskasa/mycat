#include "mycat.h"

flags mycat_parser(int argc_local, char *argv_local[]) {

  flags cat_flags = {0};

  flags_GNU cat_flags_GNU = {NUMBER_NONBLANK, NUMBER, SQUEEZE_BLANK, HELP};

  for (int n = 1; n <= argc_local - 1; n++) {
    if (argv_local[n][0] == '-' && argv_local[n][1] != '-') {
      for (int m = 1; argv_local[n][m] != '\0'; m++) {
        switch (argv_local[n][m]) {
        case 'A':
          cat_flags.A = true;
          break;

        case 'b':
          cat_flags.b = true;
          break;

        case 'E':
          cat_flags.e = true;
          break;
        case 'e':
          cat_flags.e = true;
          break;

        case 'n':
          cat_flags.n = true;
          break;

        case 's':
          cat_flags.s = true;
          break;

        case 'T':
          cat_flags.t = true;
          break;
        case 't':
          cat_flags.t = true;
          break;

        default:
          fprintf(stderr, "mycat: invalid option -- '%c'\n\
          Try:\n\
          \t-A: \tPrints out all characters, including non-printing characters\n\
          \t-b: \tNumber non-blank output lines\n\
          \t-E or -e: \tDisplay a '$' at the end of each line\n\
          \t-n: \tNumber all output lines\n\
          \t-s: \tSqueeze multiple blank lines into one\n\
          \t-T or -t: \tDisplay a '^I' at the TAB\n\
          \n\
          or mycat --help",
                  argv_local[n][m]);
          cat_flags.validity = VALIDITY_FAILURE;
          return cat_flags;
        }
      }
    } else if (argv_local[n][0] == '-' && argv_local[n][1] != '-')
      return cat_flags;
  }

  for (int i = 1; i <= argc_local - 1; i++) {
    if (argv_local[i][0] == '-' && argv_local[i][1] == '-' &&
        argv_local[i][2] != '\0') {

      if ((strcmp(argv_local[i], cat_flags_GNU.num_nblnk)) == 0) {
        cat_flags.b = true;

      } else if ((strcmp(argv_local[i], cat_flags_GNU.num)) == 0) {
        cat_flags.n = true;

      } else if ((strcmp(argv_local[i], cat_flags_GNU.sqz_blnk)) == 0) {
        cat_flags.s = true;

      } else if ((strcmp(argv_local[i], cat_flags_GNU.help)) == 0) {
        cat_flags.h = true;

      } else {
        fprintf(stderr, "mycat: unrecognized option '%s'\n\
          Try:\n\
          \t--number-nonblank: \tNumber non-blank output lines\n\
          \t--number: \t\tNumber all output lines\n\
          \t--squeeze-blank: \tSqueeze multiple blank lines into one\n\
          \n\
          or mycat --help",
                argv_local[i]);
        cat_flags.validity = VALIDITY_FAILURE;
        return cat_flags;
      }
    }
  }
  return cat_flags;
}