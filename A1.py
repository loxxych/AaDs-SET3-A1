import subprocess
import numpy as np
import matplotlib.pyplot as plt

def run_cpp(N, rect_type):
    """
    Run Area calculation function (A1.cpp) with parameters:
    N - number of iterations
    rect_type - type of rectangle to generate points in (big - "b" or small - "s")
    """

    proc = subprocess.Popen(
        ["./a1", str(N), rect_type],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    # values of the circles (taken from task description)
    circles = """1 1 1
    1.5 2 1.11803399
    2 1.5 1.11803399
    """

    out, err = proc.communicate(circles)

    return float(out.strip())


# Area calculated using calculator and given formula (from the task description)
# (for relative error)
EXPECTED_AREA = 0.944517

# Parameters
Ns = np.array([i for i in range(100, 100000, 500)])
modes = ["s", "b"]

# Results
approx_area = {m: [] for m in modes}
rel_error = {m: [] for m in modes}


# Running program with different parameters
for mode in modes:
    for N in Ns:
        val = run_cpp(int(N), mode)

        # Adding approximate area to results
        approx_area[mode].append(val)

        # Calculating and adding the relative error to results
        rel_error[mode].append(100 * abs(val - EXPECTED_AREA) / EXPECTED_AREA)


# Plotting
plt.figure(figsize=(7, 5))
for mode in modes:
    if mode == "b":
        rect = "Широкий"
    else:
        rect = "Узкий"
    plt.plot(Ns, approx_area[mode], label=f"Прямоугольник - {rect}")

# Plot of type 1 - approximate area
plt.axhline(EXPECTED_AREA, color="green", linestyle="--", label="Точная площадь")
plt.xlabel("N")
plt.ylabel("Приближенное значение площади")
plt.title("Изменение приближенного значения площади")
plt.legend()
plt.tight_layout()
plt.show()

# Plot of type 2 - relative error
plt.figure(figsize=(7, 5))
for mode in modes:
    if mode == "b":
        rect = "Широкий"
    else:
        rect = "Узкий"
    plt.plot(Ns, rel_error[mode], label=f"Прямоугольник - {rect}")

plt.xlabel("N")
plt.ylabel("Относительное отклонение (%)")
plt.title("Зависимость относительного отклонения от N")
plt.legend()
plt.tight_layout()
plt.show()
