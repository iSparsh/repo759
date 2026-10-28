#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 20
#SBATCH -t 0-00:10:00
#SBATCH -J hw03-task1
#SBATCH -o hw03-task1-%j.out
#SBATCH -e hw03-task1-%j.err

set -euo pipefail

# Submit from the repo759 directory with: sbatch slurm/hw3/hw03_task1.sh
[[ -d HW03 ]] || { echo "Submit this script from the repo759 directory." >&2; exit 1; }
cd HW03
g++ task1.cpp matmul.cpp -Wall -O3 -std=c++17 -o task1 -fopenmp

echo "threads,time_ms" > ../task1.csv
for threads in {1..20}; do
  time_ms=$(./task1 1024 "$threads" | tail -n 1)
  echo "$threads,$time_ms" >> ../task1.csv
done

echo "Wrote $SLURM_SUBMIT_DIR/task1.csv"
