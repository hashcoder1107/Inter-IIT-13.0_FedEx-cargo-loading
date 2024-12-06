#include <vector>
#include <thread>
#include "BottomLeftFillSolution.h"
#include "../uld.h"
#include "../package.h"
#include "../output.h"
#include "../parser.h"
#include "../validator.h"

using namespace std;

const int alpha_min = 5000;
const int alpha_max = 6000;
const int alpha_step = 500;

const int beta_min = 6000;
const int beta_max = 6000;
const int beta_step = 1000;

const int num_threads = 3;

vector<vector<int>> res;

int k;
vector<PACKAGE> packages;
vector<ULD> ulds;

void run(vector<int> alphas, vector<int> betas)
{
  for (auto alpha : alphas)
  {
    for (auto beta : betas)
    {
      int cost = delayCost(alpha, beta, k, packages, ulds);
      res[alpha][beta] = cost;
    }
  }
}

int main(int argc, char *argv[])
{
  // if(argc < 8) {
  //   cout << "Insufficient Arguments" << endl;
  //   return -1;
  // }
  parseInput(k, packages, ulds);
  // return 0;

  vector<int> alphas;
  for (int i = alpha_min; i <= alpha_max; i += alpha_step)
  {
    alphas.push_back(i);
  }

  vector<int> betas;
  for (int i = beta_min; i <= beta_max; i += beta_step)
  {
    betas.push_back(i);
  }

  int n_alpha = alphas.size(), n_beta = betas.size();

  res.assign(n_alpha, vector<int>(n_beta));

  vector<thread> threads;

  vector<vector<int>> alphaSplit = {{}};
  for (auto x : alphas)
  {
    if (alphaSplit.back().size() < (n_alpha + num_threads - 1) / num_threads)
    {
      alphaSplit.back().push_back(x);
    }
    else
    {
      alphaSplit.push_back({x});
    }
  }

  for (auto &p_alphas : alphaSplit)
  {
    for (auto x : p_alphas)
    {
      cout << x << ' ';
    }
    cout << endl;
    threads.emplace_back([&p_alphas, &betas](){
      run(p_alphas, betas);
    });
  }

  for (int i = 0; i < num_threads; i++)
  {
    threads[i].join();
  }

  for(auto x: res) {
    for(auto y: x) {
      cout << y << ' ';
    }
    cout << endl;
  }

  return 0;
}