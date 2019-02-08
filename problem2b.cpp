std::vector<int> sizes = {16, 32, 64, 128, 256, 512, 1024, 2048};
std::vector<int> nthreads = {1, 2, 3, 4};

cout << "n" << '\t' << "T" << '\t' << "w" << '\n';
for (auto&& n : sizes) {
  for (auto&& t : nthreads) {
    Grid grid(n, n);

    Timer timer;

    for (int x = 0; x < (n < 512 ? 500 : 250); x++)
      grid = evolve(grid, t);

    cout << n << '\t' << t << '\t' << timer.elapsed()/100 << '\n';

  }
}



