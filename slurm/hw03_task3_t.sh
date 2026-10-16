#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 20
#SBATCH -t 0-00:20:00
#SBATCH -J hw03-task3-t
#SBATCH -o hw03-task3-t.out
#SBATCH -e hw03-task3-t.err

set -euo pipefail

if [[ $# -ne 1 ]]; then
  echo "Usage: sbatch slurm/hw03_task3_t.sh BEST_THRESHOLD" >&2
  exit 1
fi

best_threshold=$1

# Submit after examining task3_ts.csv, for example:
#   sbatch slurm/hw03_task3_t.sh 128
cd HW03
g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

echo "threads,time_ms" > ../task3_t.csv
for threads in {1..20}; do
  time_ms=$(./task3 1000000 "$threads" "$best_threshold" | tail -n 1)
  echo "$threads,$time_ms" >> ../task3_t.csv
done
