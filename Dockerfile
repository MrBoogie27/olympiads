FROM ubuntu:24.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        gcc \
        g++ \
        gdb \
        clang-format \
        clangd \
        cmake \
        make \
        git \
        valgrind \
        vim \
        htop \
        python3 \
        python3-pip \
        openssh-client \
        && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Create SSH directory with proper permissions
RUN mkdir -p /root/.ssh && chmod 700 /root/.ssh

# Configure SSH to accept host keys automatically
RUN echo "Host github.com\n    StrictHostKeyChecking accept-new" >> /root/.ssh/config && \
    chmod 600 /root/.ssh/config

# Set working directory
WORKDIR /workspace

# Default command
CMD ["/bin/bash"]