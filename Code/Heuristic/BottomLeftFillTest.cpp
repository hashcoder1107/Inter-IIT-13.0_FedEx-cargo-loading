#include <vector>
#include <thread>
#include "BottomLeftFillSolution.h"

using namespace std;

vector<vector<int>> res;

void run(vector<int> alphas, vector<int> betas) {
  for(auto alpha: alphas) {
    for(auto beta: betas) {
      int cost = delayCost(alpha, beta);
      res[alpha][beta] = cost;
    }
  }
}

int main(int argc, char *argv[]) {

  if(argc < 8) {
    cout << "Insufficient Arguments" << endl;
    return -1;
  }

  int alpha_min = stoi(argv[1]);
  int alpha_max = stoi(argv[2]);
  int alpha_step = stoi(argv[3]);

  int beta_min = stoi(argv[4]);
  int beta_max = stoi(argv[5]);
  int beta_step = stoi(argv[6]);

  int num_threads = stoi(argv[7]);

  vector<int> alphas;
  for(int i = alpha_min; i <= alpha_max; i += alpha_step) {
    alphas.push_back(i);
  }

  vector<int> betas;
  for(int i = beta_min; i <= beta_max; i += beta_step) {
    betas.push_back(i);
  }

  int n_alpha = alphas.size(), n_beta = betas.size();

  res.assign(n_alpha, vector<int>(n_beta));


  vector<thread> threads;

  vector<vector<int>> alphaSplit = {{}};
  for(auto x: alphas) {
    if(alphaSplit.back().size() < (n_alpha + num_threads - 1) / num_threads) {
      alphaSplit.back().push_back(x);
    }else {
      alphaSplit.push_back({x});
    }
  }

  for(auto &p_alphas: alphaSplit) {
    threads.emplace_back([&p_alphas, &betas](){
      run(p_alphas, betas);
    });
  }

  for(int i = 0; i < num_threads; i++) {
    threads[i].join();
  }

  return 0;
}