FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        clang \
        clang-format \
        clang-tidy \
        clangd \
        cmake \
        gdb \
        git \
        ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Ubuntu 24.04 ships a non-root "ubuntu" user (uid 1000); we work as that user.
USER ubuntu
