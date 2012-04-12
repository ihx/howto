#include "bit.h"
#include "boole.h"
#include "minigen.h"
#include "standard.h"
#include "trace.h"

#define GOAL_TOTAL 1024

unsigned short numbers[IH_GENOME_SIZE_BITS] = {
  23, 123, 456, 235, 567, 123, 11, 89,
  213, 1, 76, 57, 78, 131, 411, 859,
  44, 45, 56, 315, 15, 126, 101, 889,
  243, 423, 9356, 987, 192, 348, 45, 54,
  123, 2123, 3456, 4235, 55676, 1723, 118, 809,
  1213, 21, 763, 574, 785, 1316, 4711, 8589,
  144, 245, 563, 3154, 515, 1266, 1701, 8889,
  1243, 2423, 39356, 49875, 6192, 3478, 485, 954
};

double calculate_fitness(ih_genome_t genome, void *context)
{
  double fitness;
  unsigned long total = 0;
  unsigned short i;
  unsigned short *numbers = context;
  unsigned short total_numbers = 0;

  for (i = 0; i < IH_GENOME_SIZE_BITS; i++) {
    if (ih_bit_get(genome, i)) {
      total += *(numbers + i);
      total_numbers++;
    }
  }

  /*  fitness = 1 / (1 + fabs(GOAL_TOTAL - total));  */
  fitness = (1 / (1 + fabs(GOAL_TOTAL - total))) / (1 + total_numbers);

  return fitness;
}

int main(int argc, char *argv[])
{
  ih_genome_t fittest_genome;
  unsigned short i;
  unsigned long total = 0;
  ih_boole_t first_number = ih_boole_true;

  /*  fittest_genome = ih_minigen_evolve(calculate_fitness, 0.8, numbers);  */
  fittest_genome = ih_minigen_evolve(calculate_fitness, 0.1, numbers);

  for (i = 0; i < IH_GENOME_SIZE_BITS; i++) {
    if (ih_bit_get(fittest_genome, i)) {
      if (!first_number) {
        printf(" + ");
      }
      total += *(numbers + i);
      printf("%d", *(numbers + i));
      first_number = ih_boole_false;
    }
  }
  printf(" = %lu\n", total);

  return 0;
}
