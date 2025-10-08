#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char **argv)
{
  FILE *Fin = (argc > 1) ? fopen(argv[1], "r") : stdin;
  if (Fin == NULL) return -1;

  int line_counter = 0;
  int word_counter = 0;
  int char_counter = 0;

  int result = 0;
  bool in_word = false;
  int ch;
  do {
    ch = fgetc(Fin);

    if (ch == EOF || ch == '\x04') break; // end of transmission

    if (ch < 0) // unknown char
    {
      result = -2;
      break;
    }

    ++char_counter;

    if (ch == '\n') ++line_counter; // end line

    if (isspace(ch) && in_word) // space char
    {
      ++word_counter;
      in_word = false;
      continue;
    }

    in_word = true;
  }
  while (1);

  if (in_word) ++word_counter;

  if (Fin != NULL) fclose(Fin);

  printf("%d\n%d\n%d\n", line_counter, word_counter, char_counter);

  return result;
}
