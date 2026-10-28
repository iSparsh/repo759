#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 8
#SBATCH -t 0-00:30:00
#SBATCH -J hw04-task4
#SBATCH -o hw04-task4-%j.out
#SBATCH -e hw04-task4-%j.err

set -euo pipefail

# Sweeps every scheduling policy x 1..8 threads in one job, so all three
# policies are timed on the same node.
# Submit from the repo759 directory with: sbatch slurm/hw4/hw04_task4.sh
[[ -d HW04 ]] || { echo "Submit this script from the repo759 directory." >&2; exit 1; }
cd HW04
g++ task3.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

num_particles=500
end_time=100
runs=3

# Pin one thread per allocated CPU for stable timings
export OMP_PROC_BIND=close
export OMP_PLACES=threads

echo "policy,threads,run,time_ms" > ../task4.csv
for policy in static dynamic guided; do
  # task3.cpp uses schedule(runtime), which reads the policy from OMP_SCHEDULE
  export OMP_SCHEDULE=$policy
  for threads in {1..8}; do
    for run in {1..$runs}; do
      time_ms=$(./task3 "$num_particles" "$end_time" "$threads" | sed -E 's/^time: ([0-9.]+)ms$/\1/')
      echo "$policy,$threads,$run,$time_ms" >> ../task4.csv
    done
  done
done

echo "N=$num_particles tEnd=$end_time runs=$runs"
echo "Wrote $SLURM_SUBMIT_DIR/task4.csv"
