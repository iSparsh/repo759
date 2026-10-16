#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 20
#SBATCH -t 0-00:10:00
#SBATCH -J hw03-task1
#SBATCH -o hw03-task1.out
#SBATCH -e hw03-task1.err

set -euo pipefail

# Submit from the repo759 directory with: sbatch slurm/hw03_task1.sh
cd HW03
g++ task1.cpp matmul.cpp -Wall -O3 -std=c++17 -o task1 -fopenmp

echo "threads,time_ms" > ../task1.csv
for threads in {1..20}; do
  time_ms=$(./task1 1024 "$threads" | tail -n 1)
  echo "$threads,$time_ms" >> ../task1.csv
done

