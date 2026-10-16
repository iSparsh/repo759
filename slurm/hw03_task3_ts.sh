#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 20
#SBATCH -t 0-00:20:00
#SBATCH -J hw03-task3-ts
#SBATCH -o hw03-task3-ts.out
#SBATCH -e hw03-task3-ts.err

set -euo pipefail

# Submit from the repo759 directory with: sbatch slurm/hw03_task3_ts.sh
cd HW03
g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

echo "threshold,time_ms" > ../task3_ts.csv
for threshold in 2 4 8 16 32 64 128 256 512 1024; do
  time_ms=$(./task3 1000000 8 "$threshold" | tail -n 1)
  echo "$threshold,$time_ms" >> ../task3_ts.csv
done

