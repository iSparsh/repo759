#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH --gpus-per-task=1
#SBATCH -c 1
#SBATCH --mem=8G
#SBATCH -t 0-00:30:00
#SBATCH -J hw05-task3
#SBATCH -o hw05-task3-%j.out
#SBATCH -e hw05-task3-%j.err

set -euo pipefail

# Scaling sweep for vscale: n = 2^10 .. 2^29, with 512 and 16 threads per
# block, all on the same GPU node in one job. Each (tpb, n) is run `runs`
# times; average them (or take the min) when plotting.
# Submit from the repo759 directory with: sbatch slurm/hw5/hw05_task3.sh
[[ -d HW05 ]] || { echo "Submit this script from the repo759 directory." >&2; exit 1; }
module load nvidia/cuda

# Load all kernels at context creation so the first launch doesn't pay a
# lazy-loading cost (~1 ms) that would swamp the small-n timings.
export CUDA_MODULE_LOADING=EAGER

bin=$(mktemp -d)
trap 'rm -rf "$bin"' EXIT

cd HW05
flags=(-Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17)
# The submitted task3.cu uses 512; THREADS_PER_BLOCK overrides it for the
# second curve.
nvcc task3.cu vscale.cu "${flags[@]}" -o "$bin/task3_512"
nvcc task3.cu vscale.cu "${flags[@]}" -DTHREADS_PER_BLOCK=16 -o "$bin/task3_16"

runs=3

echo "threads_per_block,exponent,n,run,time_ms" > ../task3.csv
for tpb in 512 16; do
  for exponent in {10..29}; do
    n=$(( 2 ** exponent ))
    for run in {1..$runs}; do
      # first line of the program's output is the kernel time in ms
      time_ms=$("$bin/task3_$tpb" "$n" | head -n 1)
      echo "$tpb,$exponent,$n,$run,$time_ms" >> ../task3.csv
    done
  done
done

echo "runs=$runs"
echo "Wrote $SLURM_SUBMIT_DIR/task3.csv"
