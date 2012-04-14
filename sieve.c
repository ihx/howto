#include "classify.h"
#include "sieve.h"

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
  unsigned char value_e;
  unsigned char value_f;
  unsigned char value_g;
  unsigned char value_h;
  ih_bitarray_t *bitarray;

  for (i = 0; i < CXBITARRAYS_SIZE; i++) {
    bitarray = &cxbitarrays[i].bitarray;
    if (0 == (random() % 2)) {
      cxbitarrays[i].classification = 1;
      value_a = random() % 256;
      value_b = value_a;
      value_c = value_a;
      value_d = value_a;
      value_e = value_a;
      value_f = value_a;
      value_g = value_a;
      value_h = value_a;
      ih_bitarray_set_uint8(bitarray, 0, value_a);
      ih_bitarray_set_uint8(bitarray, 8, value_b);
      ih_bitarray_set_uint8(bitarray, 16, value_c);
      ih_bitarray_set_uint8(bitarray, 24, value_d);
      ih_bitarray_set_uint8(bitarray, 32, value_e);
      ih_bitarray_set_uint8(bitarray, 40, value_f);
      ih_bitarray_set_uint8(bitarray, 48, value_g);
      ih_bitarray_set_uint8(bitarray, 56, value_h);
    } else {
      cxbitarrays[i].classification = 0;
      ih_bitarray_randomize(bitarray);
    }
  }
}

int main(int argc, char *argv[])
{
  ih_cxbitarray_t cxbitarrays[CXBITARRAYS_SIZE];
  unsigned char rules[8];
  ih_bit_t classification;
  unsigned long total_correct;
  unsigned short j;
  double total_percentage_correct = 0.0;
  unsigned long i;

  set_bitarrays(cxbitarrays);
  ih_sieve_evolve(cxbitarrays, CXBITARRAYS_SIZE, REQUIRED_FITNESS,
      CLASSIFY_STYLE, rules);
  printf("%d %d %d %d %d %d %d %d\n", rules[0], rules[1], rules[2], rules[3],
      rules[4], rules[5], rules[6], rules[7]);

#ifdef DEBUG_PRINT
  printf("fz\n");
#endif

  for (j = 0; j < TEST_BATCH_COUNT; j++) {
    total_correct = 0;
    set_bitarrays(cxbitarrays);
    for (i = 0; i < CXBITARRAYS_SIZE; i++) {
      classification = ih_sieve_classify(cxbitarrays[i].bitarray,
          CLASSIFY_STYLE, rules[0], rules[1], rules[2], rules[3], rules[4],
          rules[5], rules[6], rules[7]);
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
