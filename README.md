# C Katas

![](https://www.codewars.com/users/besterboris/badges/micro)

This repo contains my solutions for some C katas submitted in [Codewars](https://www.codewars.com).

## Setup

### Prerequisites

You need to install following tools/packages:

* gcc
* cmake
* clang
* meson/ninja

### Compile and install [Criterion](https://github.com/Snaipe/Criterion)

```bash
git submodule update --init --recursive

cd extern/Criterion # (from project root)
meson build
ninja -C build
ninja -C build install # (sudo permissions are required)
```

## Build

```bash
cd build # (from project root)
cmake ..
cmake --build .
```

## Run tests

```bash
cd build # (from project root)
./test/c_katas_test
```
