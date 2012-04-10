#include "bit.h"
#include "ca.h"
#include "standard.h"
#include "wrap.h"

#define CA_RULE 30
#define TIME_STEPS 32

int main(int argc, char *argv[])
{
  uint32_t history[TIME_STEPS];
  unsigned char i;
  unsigned char j;
  ih_bit_t cell_value;
  unsigned short neighborhood;
  ih_bit_t a;
  ih_bit_t b;
  ih_bit_t c;

  for (i = 0; i < TIME_STEPS; i++) {
    for (j = 0; j < 32; j++) {
      ih_bit_set(&history[i], j, 0);
    }
  }

  ih_bit_set(&history[0], 16, 1);

  for (i = 1; i < TIME_STEPS; i++) {
    for (j = 0; j < 32; j++) {
      a = ih_bit_get(history[i - 1], ih_wrap(j - 1, 32));
      b = ih_bit_get(history[i - 1], ih_wrap(j, 32));
      c = ih_bit_get(history[i - 1], ih_wrap(j + 1, 32));
      neighborhood = (4 * a) + (2 * b) + c;
      cell_value = ih_ca_calculate(CA_RULE, neighborhood);
      ih_bit_set(&history[i], j, cell_value);
    }
  }

  for (i = 0; i < TIME_STEPS; i++) {
    for (j = 0; j < 32; j++) {
      cell_value = ih_bit_get(history[i], j);
      printf("%i", cell_value);
    }
    printf("\n");
  }

  return 0;
}