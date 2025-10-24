# LabProg Exercizes

This folder contains all the exercises for the "Advanced Programming for Astrophysics" course.

---

### How to Compile

To keep the directory clean, compile your programs as follows:

```bash
mkdir -p build
gcc filename.c -o build/output_name [-lm]
```
> **Note:** Most programs require `-lm` to link the math library.

Some exercises require special compilation flags:

- `03_newt_bisec.c`

    By default, this program solves a transcendental equation $(x^x - e^{-x} - 1 = 0)$ using the bisection method.

    - Use `-DTEST` to run a test with a parabolic function $(x^2 - 1 = 0)$ whose solutions are known ($\pm1$).
    - Use `-DNEWTON` to use the Newton method instead of bisection.

- `09_sparse_vec.c`
    If you want to check the program’s behavior in detail, there’s an optional debug print feature.
    - Compile with `-DDEBUG` to print the internal representation of the vectors along with the final results.
---

### How to Run

To execute a compiled program:

```bash
# Run while inside the project directory
build/output_name [arguments]
```

If a program expects arguments, running it without any will usually print an error message and usage instructions.

---

### Where to Find Outputs

To keep the folder tidy, all output files are saved in the `artifacts` folder, which is automatically generated.

---