/**
 * @file main.c
 * @author Meu Pai
 * @date 9 Sep 2012
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html	
 */

#include "main.h"

/**
 * @brief main, otherwise the index won't have a brief explanation.
 *
 * Detailed explanation.
 */
int main() {
  printf("Meu meninao\n.");

  printf("2+3=%d\n", adder(2, 3));

  return 0;
}