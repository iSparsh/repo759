#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH --ntasks=1
#SBATCH --gpus-per-task=1
#SBATCH -c 1
#SBATCH -t 0-00:05:00
#SBATCH -J hw05-task1
#SBATCH -o hw05-task1-%j.out
#SBATCH -e hw05-task1-%j.err

set -euo pipefail

# Factorials of 1..8, one block of 8 threads.
# Submit from the repo759 directory with: sbatch slurm/hw5/hw05_task1.sh
[[ -d HW05 ]] || { echo "Submit this script from the repo759 directory." >&2; exit 1; }
module load nvidia/cuda

bin=$(mktemp -d)
trap 'rm -rf "$bin"' EXIT

cd HW05
nvcc task1.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o "$bin/task1"

"$bin/task1"
