ARG RELEASE=latest

FROM ubuntu:${RELEASE} as c-dev-environment

MAINTAINER borisskert <boris.skert@gmail.com>

ENV DEBIAN_FRONTEND     noninteractive

RUN apt update && \
    apt install -y git \
                       build-essential \
                       cmake \
                       clang \
                       meson \
                       pkg-config \
    && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

ENV SHELL /bin/bash


FROM c-dev-environment as build

COPY . /usr/local/src

WORKDIR /usr/local/src

RUN git submodule update --init --recursive && \
    cd extern/Criterion && \
    meson build && \
    ninja -C build && \
    ninja -C build install

RUN cd build && \
    cmake .. && \
    cmake --build .


FROM ubuntu:${RELEASE}

WORKDIR /opt

COPY --from=build /usr/local/lib/x86_64-linux-gnu/libcriterion.* /usr/local/lib/x86_64-linux-gnu/
COPY --from=build /usr/local/src/build/test/c_katas_test .

CMD ["./c_katas_test"]
