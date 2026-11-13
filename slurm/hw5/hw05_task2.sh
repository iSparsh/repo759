#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH --gpus-per-task=1
#SBATCH -c 1
#SBATCH -t 0-00:05:00
#SBATCH -J hw05-task2
#SBATCH -o hw05-task2-%j.out
#SBATCH -e hw05-task2-%j.err

set -euo pipefail

# a*x + y over 2 blocks of 8 threads, with a random `a` each run.
# Submit from the repo759 directory with: sbatch slurm/hw5/hw05_task2.sh
[[ -d HW05 ]] || { echo "Submit this script from the repo759 directory." >&2; exit 1; }
module load nvidia/cuda

bin=$(mktemp -d)
trap 'rm -rf "$bin"' EXIT

cd HW05
nvcc task2.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o "$bin/task2"

"$bin/task2"
