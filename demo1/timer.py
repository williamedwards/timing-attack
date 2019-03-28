#!/usr/bin/python3
import subprocess
import time
import os
import random

iterations = 100
command = ["./main"]
pass_a = b"alvishwordforfriend"
pass_b = b"elvishwordforfrienb"

def main():
    FNULL = open(os.devnull, "w")
    times_a = []
    times_b = []
    with subprocess.Popen(command, stdout=subprocess.PIPE, stdin=subprocess.PIPE) as p:
        for _ in range(iterations):
            if random.random() < 0.5:
                password = pass_a
                times = times_a
            else:
                password = pass_b
                times = times_b
            start_time = time.time()
            p.stdin.write(pass_a + b"\n")
            p.stdin.flush()
            response = p.stdout.readline()
            elapsed = time.time() - start_time
            times.append(elapsed)
    mean_a = sum(times_a) / len(times_a)
    mean_b = sum(times_b) / len(times_b)
    print(mean_b - mean_a)

if __name__ == "__main__":
    main()

