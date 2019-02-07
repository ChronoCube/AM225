#include <iostream>
#include <random>

double casino(std::default_random_engine &engine,
              std::uniform_real_distribution<> &unif) {
  double winnings = 0.0;
  double n = 0.0;

  while (winnings < 1.0) {
    winnings += unif(engine);
    n++;
  }

  return n;
}

int main(int argc, char **argv) {
  double sum = 0.0;
  const double NTIMES = 1000000000;

  #pragma omp parallel num_threads(4)
  {
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_real_distribution<> unif(0.0, 1.0);

    #pragma omp for reduction(+:sum)
    for(int i = 0; i < (int) NTIMES; ++i) {
      sum += casino(engine, unif);
    }
  }

  std::cout << (100 * sum) / NTIMES - 250 << std::endl;
  return 0;
}
