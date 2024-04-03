FROM mcr.microsoft.com/devcontainers/base:jammy

RUN sudo apt update && sudo apt install -y wget

RUN wget https://github.com/bazelbuild/bazelisk/releases/download/v1.19.0/bazelisk-linux-amd64 && \
    sudo mv bazelisk-linux-amd64 /usr/local/bin/bazel && \
    sudo chmod 777 /usr/local/bin/bazel && \
    bazel --version

RUN wget https://github.com/bazelbuild/buildtools/releases/download/v7.1.0/buildifier-linux-amd64 && \
    sudo mv buildifier-linux-amd64 /usr/local/bin/buildifier && \
    sudo chmod 777 /usr/local/bin/buildifier