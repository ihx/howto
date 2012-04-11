#include "classify.h"
#include "vclass.h"

#define CLASSIFY_STYLE ih_classify_style_majority
#define CXBITARRAYS_SIZE 16

int main(int argc, char *argv[])
{
  ih_cxbitarray_t cxbitarrays[CXBITARRAYS_SIZE];
  unsigned long rules[4];
  unsigned long i;
  ih_bit_t classification;
  unsigned long total_correct = 0;

  for (i = 0; i < CXBITARRAYS_SIZE; i++) {
    if (0 == (random() % 2)) {
      cxbitarrays[i].classification = 1;
      ih_bitarray_seed_center(&cxbitarrays[i].bitarray);
    } else {
      cxbitarrays[i].classification = 0;
      ih_bitarray_randomize(&cxbitarrays[i].bitarray);
    }
  }

  ih_vclass_evolve(cxbitarrays, CXBITARRAYS_SIZE, CLASSIFY_STYLE, rules);
  printf("%lu %lu %lu %lu\n", rules[0], rules[1], rules[2], rules[3]);

  for (i = 0; i < CXBITARRAYS_SIZE; i++) {
    classification = ih_classify(cxbitarrays[i].bitarray, CLASSIFY_STYLE, 4,
        rules[0], rules[1], rules[2], rules[3]);
    if (classification == cxbitarrays[i].classification) {
      total_correct++;
    }
  }
  printf("%f%%\n", ((double) total_correct) / CXBITARRAYS_SIZE);

  return 0;
}
