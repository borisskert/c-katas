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

## Run tests in docker environment

```bash
docker-compose up --build
```
