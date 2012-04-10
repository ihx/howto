#include "bitarray.h"
#include "classify.h"

int main(int argc, char *argv[])
{
  ih_bitarray_t bitarray;
  ih_bit_t classification;

  srandom(time(NULL));
  ih_bitarray_randomize(&bitarray);
  classification = ih_classify(bitarray, 30, ih_classify_style_majority);
  printf("%d\n", classification);

  return 0;
}
