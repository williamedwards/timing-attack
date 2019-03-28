#!/usr/bin/python3
import subprocess
import time
import os
import random

iterations = 1000
command_a = ["./main", "alvishwordforfriend"]
command_b = ["./main", "elvishwordforfrienb"]

def main():
    FNULL = open(os.devnull, "w")
    times_a = []
    times_b = []
    for _ in range(iterations):
        if random.random() < 0.5:
            # Do command a
            start_time = time.time()
            subprocess.call(command_a, stdout=FNULL)
            elapsed = time.time() - start_time
            times_a.append(elapsed)
            # Do command b
            start_time = time.time()
            subprocess.call(command_b, stdout=FNULL)
            elapsed = time.time() - start_time
            times_b.append(elapsed)
    mean_a = sum(times_a) / len(times_a)
    mean_b = sum(times_b) / len(times_b)
    print(mean_b - mean_a)

if __name__ == "__main__":
    main()

