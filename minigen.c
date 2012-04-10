#include "boole.h"
#include "minigen.h"
#include "standard.h"
#include "tools.h"

#define GOAL_TOTAL 256

unsigned short numbers[IH_GENOME_SIZE_BITS] = {
  23, 123, 456, 235, 567, 123, 11, 89,
  213, 1, 76, 57, 78, 131, 411, 859,
  44, 45, 56, 315, 15, 126, 101, 889,
  243, 423, 356, 87, 192, 348, 45, 54
};

double calculate_fitness(ih_genome_t genome, void *context)
{
  double fitness;
  unsigned long total = 0;
  unsigned short i;
  unsigned short *numbers = context;
  unsigned short total_numbers = 0;

  for (i = 0; i < IH_GENOME_SIZE_BITS; i++) {
    if (ih_tools_get_bit(genome, i)) {
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
  ih_minigen_t *minigen;
  ih_genome_t fittest_genome;
  unsigned short i;
  unsigned long total = 0;
  ih_boole_t first_number = ih_boole_true;

  /*  minigen = ih_minigen_create(calculate_fitness, 0.8, numbers);  */
  minigen = ih_minigen_create(calculate_fitness, 0.1, numbers);
  if (!minigen) {
    ih_tools_trace_exit("ih_minigen_create");
  }

  fittest_genome = ih_minigen_generate(minigen);
  for (i = 0; i < IH_GENOME_SIZE_BITS; i++) {
    if (ih_tools_get_bit(fittest_genome, i)) {
      if (!first_number) {
        printf(" + ");
      }
      total += *(numbers + i);
      printf("%d", *(numbers + i));
      first_number = ih_boole_false;
    }
  }
  printf(" = %lu\n", total);

  ih_minigen_destroy(minigen);

  return 0;
}
