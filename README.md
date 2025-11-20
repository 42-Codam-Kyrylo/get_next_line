# 📜 get_next_line

A project from the **Codam / 42 Network** curriculum focusing on low-level file I/O, static state, and dynamic memory management in C.

The goal is to implement a function that returns one line at a time from a file descriptor, working with both regular files and standard input. A bonus part adds support for handling multiple file descriptors concurrently.

---

## 🧩 Objective

Mandatory function:

```c
char	*get_next_line(int fd);
```

- Reads from `fd` until a newline `'\n'` or EOF.
- Returns the line including the trailing `'\n'` if present.
- Preserves state between calls using static storage.
- Supports arbitrary `BUFFER_SIZE` (set at compile time).

Bonus: independent reading state per file descriptor (multi-fd support).

---

## 🗂️ Project structure

```
get_next_line/
├── get_next_line.c                 # Core logic (mandatory)
├── get_next_line_utils.c           # Helpers (mandatory)
├── get_next_line.h                 # Header (mandatory)
├── get_next_line_bonus.c           # Bonus logic (multi-fd)
├── get_next_line_utils_bonus.c     # Bonus helpers
├── get_next_line_bonus.h           # Bonus header
├── main.c                          # Example: read from file or stdin
├── main_bonus.c                    # Example: interleaved read from 2 fds
├── Makefile                        # Build and run helpers
├── README.md
└── tests/                          # Criterion tests + test files
		├── Makefile
		├── get_next_line.test.c
		├── edge_cases.test.c
		├── bonus/
		│   └── get_next_line_bonus.test.c
		├── single_line.txt
		├── only_newlines.txt
		├── no_newline.txt
		├── empty.txt
		└── file1.txt
```

---

## ⚙️ Build and run

The root Makefile builds two small example binaries: mandatory and bonus.

- Build everything (both binaries):

```bash
make
```

- Set buffer size (default `BUFFER_SIZE=42`):

```bash
make BUFFER_SIZE=1
```

- Build and run the mandatory example with a file (override `FILE`):

```bash
make run FILE=tests/single_line.txt
```

- Build and run the bonus example:

```bash
make run-bonus FILE=tests/file1.txt
```

Resulting binaries:

- `./gnl_main` — reads from a file or stdin. Examples:
	- `./gnl_main tests/file1.txt`
	- `./gnl_main -` (read from stdin), or simply run with no arguments

- `./gnl_main_bonus` — reads interleaved from two sources:
	- `./gnl_main_bonus tests/file1.txt tests/single_line.txt`
	- `./gnl_main_bonus - tests/file1.txt` (stdin + file)

---

## 🔬 Tests (Criterion)

A dedicated Makefile in `tests/` drives the Criterion-based tests.

- Run all mandatory tests:

```bash
make -C tests test
```

- Run bonus tests:

```bash
make -C tests test-bonus
```

- Change buffer size for tests:

```bash
make -C tests test BUFFER_SIZE=1
```

- Run tests for multiple buffer sizes:

```bash
make -C tests test-all SIZES="1 5 42 1000"
```

- List available tests:

```bash
make -C tests test-list
make -C tests test-list-bonus
```

- Valgrind leak checks:

```bash
make -C tests valgrind
make -C tests valgrind-bonus
```

### Criterion on Linux

The test `Makefile` expects Criterion at `~/criterion-2.4.3-linux-x86_64/criterion-2.4.3`.
Either unpack the release there or adjust `CRIT_DIR` in `tests/Makefile` to your local path.

---

## 📘 Notes

- `BUFFER_SIZE` is set at build time via `-D BUFFER_SIZE=...` (already wired in the Makefiles).
- The function returns `NULL` on error or when EOF is reached and no data remains.
- Returned lines include `'\n'` when it was read.
- In the bonus, state is kept per `fd` to allow concurrent reads.

---

## 🔧 Tech

- C (C99)
- Makefile
- Criterion, Valgrind, GDB
- Linux / macOS

---

### 🪄 Author

👤 **Kyrylo**
[GitHub](https://github.com/42-Codam-Kyrylo) · [LinkedIn](https://www.linkedin.com/link)