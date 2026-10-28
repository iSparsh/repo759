#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 8
#SBATCH -t 0-00:10:00
#SBATCH -J hw04-task3
#SBATCH -o hw04-task3-%j.out
#SBATCH -e hw04-task3-%j.err

set -euo pipefail

# OpenMP N-body run with 8 threads.
# Submit from the repo759 directory with: sbatch slurm/hw4/hw04_task3.sh
[[ -d HW04 ]] || { echo "Submit this script from the repo759 directory." >&2; exit 1; }
cd HW04
g++ task3.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

num_particles=200
end_time=100
num_threads=4

# task3.cpp uses schedule(runtime), so pick the policy explicitly
export OMP_SCHEDULE=static

echo "N=$num_particles tEnd=$end_time threads=$num_threads schedule=$OMP_SCHEDULE"
./task3 "$num_particles" "$end_time" "$num_threads"
