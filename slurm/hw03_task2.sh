#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 20
#SBATCH -t 0-00:10:00
#SBATCH -J hw03-task2
#SBATCH -o hw03-task2-%j.out
#SBATCH -e hw03-task2-%j.err

set -euo pipefail

# Submit from the repo759 directory with: sbatch slurm/hw03_task2.sh
[[ -d HW03 ]] || { echo "Submit this script from the repo759 directory." >&2; exit 1; }
cd HW03
g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp

echo "threads,time_ms" > ../task2.csv
for threads in {1..20}; do
  time_ms=$(./task2 1024 "$threads" | tail -n 1)
  echo "$threads,$time_ms" >> ../task2.csv
done

echo "Wrote $SLURM_SUBMIT_DIR/task2.csv"
