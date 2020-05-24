#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>

int usage(const char* prog_name) {
  fprintf(stderr, "%s [--seed=SEED] [--nb=N]\n", prog_name);
  return 1;
}

int testutils_run(
    int argc, char* argv[], void(*seed_func)(uint64_t), uint64_t(*next)(void)
) {
  long nb_iterations = -1;
  uint64_t seed = 0xdd6d0e2e849e51ad;

  struct option long_options[] = {
    {"seed", optional_argument, NULL, 's'},
    {"nb", optional_argument, NULL, 'n'},
  };

  while (1) {
    int option_index = 0;
    int c = getopt_long(argc, argv, "", long_options, &option_index);
    char* endptr;
    if (c == -1) break;
    switch (c) {
      case 's':
        if (optarg == NULL) return usage(argv[0]);
        seed = strtoull(optarg, &endptr, 10);
        if (endptr == optarg || *endptr != '\0') return usage(argv[0]);
        break;
      case 'n':
        if (optarg == NULL) return usage(argv[0]);
        nb_iterations = strtol(optarg, &endptr, 10);
        if (endptr == optarg || *endptr != '\0') return usage(argv[0]);
        break;
      default:
        return usage(argv[0]);
    }
  }

  if (optind < argc) return usage(argv[0]);

  seed_func(seed);
  for (long i = 0; i != nb_iterations; i++) {
    printf("%lx\n", next());
  }

  return 0;
}

