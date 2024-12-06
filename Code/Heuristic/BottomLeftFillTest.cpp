#include <vector>
#include <thread>
#include "BottomLeftFillSolution.h"
#include "../uld.h"
#include "../package.h"
#include "../output.h"
#include "../parser.h"
#include "../validator.h"

using namespace std;

const double alpha_min = 3500;
const double alpha_max = 7500;
const double alpha_step = 800;

const double beta_min = 5975.6536;
const double beta_max = 5975.6536;
const double beta_step = 1000;

const int num_threads = 7;

vector<vector<int>> res;

int k;
vector<PACKAGE> packages;
vector<ULD> ulds;

void run(vector<double> alphas, vector<double> betas)
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

  vector<double> alphas;
  for (int i = alpha_min; i <= alpha_max; i += alpha_step)
  {
    alphas.push_back(i);
  }

  vector<double> betas;
  for (int i = beta_min; i <= beta_max; i += beta_step)
  {
    betas.push_back(i);
  }

  int n_alpha = alphas.size(), n_beta = betas.size();

  res.assign(n_alpha, vector<int>(n_beta));

  vector<thread> threads;

  vector<vector<double>> alphaSplit = {{}};
  int m = n_alpha % num_threads;
  int t = 1;
  cout << m << endl;
  for (auto x : alphas)
  {
    cout << m << ' ' << t << endl;
    if (alphaSplit.back().size() < (n_alpha) / num_threads + t)
    {
      alphaSplit.back().push_back(x);
    }
    else
    {
      m--;
      alphaSplit.push_back({x});
    }
    if(m == 0) t = 0;
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

  cout << threads.size() << endl;

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