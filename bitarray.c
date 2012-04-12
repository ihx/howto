#include "bitarray.h"

int main(int argc, char *argv[])
{
  ih_bitarray_t bitarray;
  unsigned char value;

  ih_bitarray_set_uchar(&bitarray, 0, 117);
  value = ih_bitarray_get_uchar(&bitarray, 0);

  printf("%d\n", value);

  return 0;
}
