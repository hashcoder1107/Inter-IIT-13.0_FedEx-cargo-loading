from ortools.sat.python import cp_model

class BinPacking:
  def __init__(self, n, m, l, w, h, wt, K, cost, priority, L, W, H, C):
    # Initialize solver and model
    self.solver = cp_model.CpSolver()
    self.model = cp_model.CpModel()

    # Store parameters
    self.n = n  # Number of items
    self.m = m  # Number of bins
    self.l = l  # Item lengths
    self.w = w  # Item widths
    self.h = h  # Item heights
    self.wt = wt  # Item weights
    self.K = K  # Any additional constraints or groupings
    self.cost = cost  # Item costs
    self.priority = priority  # Item priorities
    self.L = L  # Bin lengths
    self.W = W  # Bin widths
    self.H = H  # Bin heights
    self.C = C  # Bin capacities (max weight)

  def set_solver(self, model, solver):
    self.solver = solver
    self.model = model

  def set_time_limit(self, time_limit_in_seconds):
    self.solver.parameters.max_time_in_seconds = time_limit_in_seconds

  def solve(self):
    # Create parameter variables
    variables = self.create_variables()

    # Add constraints
    self.add_constraints(variables)

    # Add objective function
    self.add_objective_function(variables)

    # solve
    return self.solve_mips(variables)

  def create_variables(self):
    n = self.n
    m = self.m

    p = [[self.model.NewBoolVar(name=f"p[{i}][{j}]") for j in range(m)] for i in range(n)]
    prio = [self.model.NewBoolVar(name=f"prio[{j}]") for j in range(m)]

    x = [self.model.NewIntVar(name=f"x[{i}]", lb = 0, ub = 1000) for i in range(n)]
    y = [self.model.NewIntVar(name=f"y[{i}]", lb = 0, ub = 1000) for i in range(n)]
    z = [self.model.NewIntVar(name=f"z[{i}]", lb = 0, ub = 1000) for i in range(n)]

    _x = [self.model.NewIntVar(name=f"_x[{i}]", lb = 0, ub = 1000) for i in range(n)]
    _y = [self.model.NewIntVar(name=f"_y[{i}]", lb = 0, ub = 1000) for i in range(n)]
    _z = [self.model.NewIntVar(name=f"_z[{i}]", lb = 0, ub = 1000) for i in range(n)]
    

    x_a = [[self.model.NewBoolVar(name=f"x_a[{i}][{j}]") for j in range(n)] for i in range(n)]
    x_b = [[self.model.NewBoolVar(name=f"x_b[{i}][{j}]") for j in range(n)] for i in range(n)]

    y_a = [[self.model.NewBoolVar(name=f"y_a[{i}][{j}]") for j in range(n)] for i in range(n)]
    y_b = [[self.model.NewBoolVar(name=f"y_b[{i}][{j}]") for j in range(n)] for i in range(n)]

    z_a = [[self.model.NewBoolVar(name=f"z_a[{i}][{j}]") for j in range(n)] for i in range(n)]
    z_b = [[self.model.NewBoolVar(name=f"z_b[{i}][{j}]") for j in range(n)] for i in range(n)]

    r = [[[self.model.NewBoolVar(name=f"r[{i}][{j}][{k}]") for k in range(3)] for j in range(3)] for i in range(n)]

    return p, prio, x, y, z, _x, _y, _z, x_a, x_b, y_a, y_b, z_a, z_b, r

  def add_constraints(self, variables): 
    model = self.model
    n = self.n
    m = self.m

    # Initialize or retrieve these variables
    l = self.l  # Lengths of items
    w = self.w  # Widths of items
    h = self.h  # Heights of items
    wt = self.wt  # Weights of items
    C = self.C  # Capacities of containers
    L = self.L  # Lengths of containers
    W = self.W  # Widths of containers
    H = self.H  # Heights of containers
    priority = self.priority  # Priority levels of items

    # Retrieve variables (Ensure `create_variables` is called before this method)
    p, prio, x, y, z, _x, _y, _z, x_a, x_b, y_a, y_b, z_a, z_b, r = variables

    for i in range(n):
      model.Add(sum(p[i][j] for j in range(m)) <= 1)

    for j in range(m):
      model.Add(sum(p[i][j] * wt[i] for i in range(n)) <= C[j])
      model.Add(sum(p[i][j] * priority[i] for i in range(n)) >= 1).OnlyEnforceIf(prio[j])
      model.Add(sum(p[i][j] * priority[i] for i in range(n)) == 0).OnlyEnforceIf(prio[j].Not())

    for i in range(n):
      model.Add(_x[i] - x[i] == r[i][0][0] * l[i] + r[i][0][1] * w[i] + r[i][0][2] * h[i])
      model.Add(_y[i] - y[i] == r[i][1][0] * l[i] + r[i][1][1] * w[i] + r[i][1][2] * h[i])
      model.Add(_z[i] - z[i] == r[i][2][0] * l[i] + r[i][2][1] * w[i] + r[i][2][2] * h[i])

      for j in range(3):
        model.Add(sum(r[i][j][k] for k in range(3)) == 1)
        model.Add(sum(r[i][k][j] for k in range(3)) == 1)

      for j in range(m):
        model.Add(_x[i] <= L[j]).OnlyEnforceIf(p[i][j]) 
        model.Add(_y[i] <= W[j]).OnlyEnforceIf(p[i][j])
        model.Add(_z[i] <= H[j]).OnlyEnforceIf(p[i][j])

    for j in range(m):
      for i in range(n):
        for k in range(n):
          if(i == k):
            continue
          model.Add(x[i] - _x[k] >= 0).OnlyEnforceIf(x_b[k][i], p[i][j], p[k][j])
          model.Add(x[k] - _x[i] >= 0).OnlyEnforceIf(x_a[k][i], p[i][j], p[k][j])

          model.Add(y[i] - _y[k] >= 0).OnlyEnforceIf(y_b[k][i], p[i][j], p[k][j])
          model.Add(y[k] - _y[i] >= 0).OnlyEnforceIf(y_a[k][i], p[i][j], p[k][j])

          model.Add(z[i] - _z[k] >= 0).OnlyEnforceIf(z_b[k][i], p[i][j], p[k][j])
          model.Add(z[k] - _z[i] >= 0).OnlyEnforceIf(z_a[k][i], p[i][j], p[k][j])

          model.AddBoolOr(x_a[k][i], x_b[k][i], y_a[k][i], y_b[k][i], z_a[k][i], z_b[k][i]).OnlyEnforceIf(p[i][j], p[k][j])

  def add_objective_function(self, variables):
    model = self.model
    n = self.n
    m = self.m
    cost = self.cost  # Cost associated with unassigned items
    K = self.K        # Penalty for unused containers

    # Retrieve variables
    p, prio = variables[0], variables[1]

    model.Minimize(
      sum((1 - sum(p[i][j] for j in range(m))) * cost[i]  for i in range(n))
      + sum(prio[i] for i in range(m)) * K
    )

  def solve_mips(self, variables):
    p, prio, x, y, z, _x, _y, _z, x_a, x_b, y_a, y_b, z_a, z_b, r = variables
    n, m = self.n, self.m
    solver, model = self.solver, self.model

    # Use solver with specified parameters
    status = solver.Solve(model)

    # Retrieve the objective value
    objective = solver.ObjectiveValue()

    # Extract the assignments for the decision variables
    p_assignment = [[solver.Value(p[i][j]) for j in range(m)] for i in range(n)]
    x_assignment = [solver.Value(x[i]) for i in range(n)]
    y_assignment = [solver.Value(y[i]) for i in range(n)]
    z_assignment = [solver.Value(z[i]) for i in range(n)]

    # Extract the values of the r array (3D assignment variable)
    r_assignment = [[[solver.Value(r[i][j][k]) for k in range(3)] for j in range(3)] for i in range(n)]

    # Return the status, objective value, and the variable assignments
    return status, objective, p_assignment, x_assignment, y_assignment, z_assignment, r_assignment


def bin_packing(n, m, l, w, h, wt, K, cost, priority, L, W, H, C):
  problem = BinPacking(n, m, l, w, h, wt, K, cost, priority, L, W, H, C)
  problem.set_time_limit = 10.0
  return problem.solve()

def main():
  n = 5
  m = 1

  l = [1] * (n-1) + [9]
  w = [1] * (n-1) + [9]
  h = [1] * (n-1) + [9]
  wt = [1, 1, 1, 1, 1]
  
  K = 100
  cost = [100, 100, 50, 50, 1e6]
  priority = [0, 0, 0, 0, 1]

  L = [10] * m
  W = [9] * m
  H = [9] * m
  C = [3] * m

  (status, 
  objective, 
  p_assignment, 
  x_assignment, 
  y_assignment, 
  z_assignment, 
  r_assignment) = bin_packing(n, m, l, w, h, wt, K, cost, priority, L, W, H, C)

  print("Status = ", status)
  print("Objective value =", objective)

  print("p:")
  for i in range(n):
    for j in range(m):
      print(p_assignment[i][j], end=' ')
    print()

  print("cord:")
  for i in range(n):
    print(i,":", x_assignment[i], y_assignment[i], z_assignment[i])

main()
