#include "classify.h"
#include "vclass.h"

#define CLASSIFY_STYLE ih_classify_style_majority
#define CXBITARRAYS_SIZE 16
#undef DEBUG_PRINT
#define REQUIRED_FITNESS 0.75
#define TEST_BATCH_COUNT 8

void set_bitarrays(ih_cxbitarray_t cxbitarrays[])
{
  unsigned long i;
  unsigned char value_a;
  unsigned char value_b;
  unsigned char value_c;
  unsigned char value_d;
  ih_bitarray_t *bitarray;

  for (i = 0; i < CXBITARRAYS_SIZE; i++) {
    bitarray = &cxbitarrays[i].bitarray;
    if (0 == (random() % 2)) {
      cxbitarrays[i].classification = 1;
      value_a = random() % 256;
      value_b = value_a;
      value_c = value_a;
      value_d = value_a;
      ih_bitarray_set_uchar(bitarray, 0, value_a);
      ih_bitarray_set_uchar(bitarray, 8, value_b);
      ih_bitarray_set_uchar(bitarray, 16, value_c);
      ih_bitarray_set_uchar(bitarray, 24, value_d);
    } else {
      cxbitarrays[i].classification = 0;
      ih_bitarray_randomize(bitarray);
    }
  }
}

int main(int argc, char *argv[])
{
  ih_cxbitarray_t cxbitarrays[CXBITARRAYS_SIZE];
  unsigned long rules[4];
  ih_bit_t classification;
  unsigned long total_correct;
  unsigned short j;
  double total_percentage_correct = 0.0;
  unsigned long i;

  set_bitarrays(cxbitarrays);
  ih_vclass_evolve(cxbitarrays, CXBITARRAYS_SIZE, REQUIRED_FITNESS,
      CLASSIFY_STYLE, rules);
  printf("%lu %lu %lu %lu\n", rules[0], rules[1], rules[2], rules[3]);

#ifdef DEBUG_PRINT
  printf("fz\n");
#endif

  for (j = 0; j < TEST_BATCH_COUNT; j++) {
    total_correct = 0;
    set_bitarrays(cxbitarrays);
    for (i = 0; i < CXBITARRAYS_SIZE; i++) {
      classification = ih_classify(cxbitarrays[i].bitarray, CLASSIFY_STYLE, 4,
          rules[0], rules[1], rules[2], rules[3]);
#ifdef DEBUG_PRINT
      printf("\n");
#endif
      if (classification == cxbitarrays[i].classification) {
        total_correct++;
      }
    }
    printf("%f%%\n", ((double) total_correct) / CXBITARRAYS_SIZE);
    total_percentage_correct += ((double) total_correct) / CXBITARRAYS_SIZE;
  }
  printf("= %f%%\n", total_percentage_correct / TEST_BATCH_COUNT);

  return 0;
}