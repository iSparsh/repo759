#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 1
#SBATCH -t 0-00:10:00
#SBATCH -J hw04-task2
#SBATCH -o hw04-task2-%j.out
#SBATCH -e hw04-task2-%j.err

set -euo pipefail

# Serial N-body baseline (single-threaded, so only 1 core is requested).
# Submit from the repo759 directory with: sbatch slurm/hw4/hw04_task2.sh
[[ -d HW04 ]] || { echo "Submit this script from the repo759 directory." >&2; exit 1; }
cd HW04
g++ task2.cpp -Wall -O3 -std=c++17 -o task2

num_particles=200
end_time=100

echo "N=$num_particles tEnd=$end_time"
./task2 "$num_particles" "$end_time"
