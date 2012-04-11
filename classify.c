#include "bitarray.h"
#include "classify.h"

int main(int argc, char *argv[])
{
  ih_bitarray_t bitarray;
  ih_bit_t classification;

  srandom(time(NULL));
  ih_bitarray_randomize(&bitarray);
  classification = ih_classify(bitarray, ih_classify_style_majority, 2,
      30, 80);
  printf("%d\n", classification);

  return 0;
}
