import subprocess
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

import math
S_exact = 0.25 * math.pi + 1.25 * math.asin(0.8) - 1

def run_cpp(N):
    proc = subprocess.Popen(
        ["./mc", str(N)],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    circles = """1 1 1
1.5 2 1.11803399
2 1.5 1.11803399
"""

    out, err = proc.communicate(circles)
    N_val, S_small, S_big = out.strip().split(",")

    return int(N_val), float(S_small), float(S_big)


Ns = list(range(100, 100001, 500))

rows = []
for N in Ns:
    N_val, S_s, S_b = run_cpp(N)
    rows.append([N_val, S_s, S_b])

df = pd.DataFrame(rows, columns=["N", "area_small", "area_big"])
df.to_csv("results_mc.csv", index=False)


# Plotting
# Type 1
plt.figure(figsize=(10,6))
plt.title("Изменение приближенного значения площади")
plt.plot(df["N"], df["area_small"], label="Узкий прямоугольник")
plt.plot(df["N"], df["area_big"], label="Широкий прямоугольник")
plt.axhline(S_exact, color="black", linestyle="--", label="Точная площадь")
plt.xlabel("N")
plt.ylabel("Оценка площади")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("plot_area.png")

# type 2
df["rel_small"] = abs(df["area_small"] - S_exact) / S_exact
df["rel_big"]   = abs(df["area_big"] - S_exact) / S_exact

plt.figure(figsize=(10,6))
plt.title("Зависимость относительного отклонения от N")
plt.plot(df["N"], df["rel_small"], label="Узкий прямоугольник")
plt.plot(df["N"], df["rel_big"],   label="Широкий прямоугольник")
plt.xlabel("N")
plt.ylabel("Относительное отклонение")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("plot_relative_error.png")
