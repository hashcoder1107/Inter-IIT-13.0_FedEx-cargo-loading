from ortools.sat.python import cp_model
import csv
import pandas as pd
import time
from BinPacking import BinPacking

def bin_packing(n, m, l, w, h, wt, K, cost, priority, L, W, H, C, time_limit_in_seconds):
  problem = BinPacking(n, m, l, w, h, wt, K, cost, priority, L, W, H, C)
  problem.set_time_limit(time_limit_in_seconds)
  return problem.solve()

def main():
  start_time = time.time()
  # Open the input CSV file
  inputPath = "Input/input.csv"

  with open(inputPath, "r") as file:
      lines = file.readlines()

  # Read the first line which contains K
  K = int(lines[0].strip())

  # Prepare lists for ULD and Package data
  uld_data = []
  package_data = []

  # Read the rest of the lines
  for line in lines[1:]:
      # Strip any leading/trailing whitespace and split by commas
      parts = line.strip().split(',')
      
      # Check if the line starts with "U" (ULD data)
      if parts[0].startswith("U"):
          uld_data.append(parts)
      # Check if the line starts with "P" (Package data)
      elif parts[0].startswith("P"):
          package_data.append(parts)

  # Convert ULD data into DataFrame with the appropriate column names
  uld_data_df = pd.DataFrame(uld_data, columns=["ULDID", "Length", "Width", "Height", "Weight Limit"])

  # Convert Package data into DataFrame with the appropriate column names
  package_data_df = pd.DataFrame(package_data, columns=["PackageID", "Length", "Width", "Height", "Weight", "Priority/Economy", "Cost of Delay"])

  # Convert the data to numeric arrays
  L = pd.to_numeric(uld_data_df['Length'], errors='coerce').to_numpy()  # Convert to NumPy array
  W = pd.to_numeric(uld_data_df['Width'], errors='coerce').to_numpy()
  H = pd.to_numeric(uld_data_df['Height'], errors='coerce').to_numpy()
  C = pd.to_numeric(uld_data_df['Weight Limit'], errors='coerce').to_numpy()

  l = pd.to_numeric(package_data_df['Length'], errors='coerce').to_numpy()
  w = pd.to_numeric(package_data_df['Width'], errors='coerce').to_numpy()
  h = pd.to_numeric(package_data_df['Height'], errors='coerce').to_numpy()
  wt = pd.to_numeric(package_data_df['Weight'], errors='coerce').to_numpy()
  cost = pd.to_numeric(package_data_df['Cost of Delay'].replace({'-': int(1e8)}), errors='coerce').to_numpy()
  priority = pd.to_numeric(package_data_df['Priority/Economy'].replace({'Priority': 1, 'Economy': 0}), errors='coerce').to_numpy()

  n=len(l)
  m=len(L)


  (status, 
  objective, 
  p_assignment, 
  x_assignment, 
  y_assignment, 
  z_assignment, 
  r_assignment) = bin_packing(n, m, l, w, h, wt, K, cost, priority, L, W, H, C, 30)

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

  # Record end time
  end_time = time.time()

  # Calculate elapsed time
  elapsed_time = end_time - start_time

  print(f"Elapsed time: {elapsed_time} seconds")

main()
