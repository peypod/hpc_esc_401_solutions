#!/bin/bash -l
#SBATCH --job-name="cpi-cuda"
#SBATCH --time=00:10:00
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --gres=gpu:1
#SBATCH --account=uzh8
#SBATCH -e cuda-%j.err
#SBATCH -o cuda-%j.out

declare -a BLOCKS=(60 120 180 240 300 360 420 600)
declare -a THREADS=(16 32 48 64 80 96 112 128 144 160)

echo "Running CUDA PI benchmark"

for B in "${BLOCKS[@]}"; do
    for T in "${THREADS[@]}"; do
        echo ">>> Blocks: $B, Threads: $T"
        srun ./cpi_cuda $B $T
        echo ""
    done
done

