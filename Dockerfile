# Base image
FROM ubuntu:22.04

# Set the working directory
WORKDIR /app

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    binutils \
    binutils-multiarch-dev \
    libcapstone-dev

# Copy the files into the container
COPY src /app/src
COPY Makefile /app/Makefile

# Build the project using the Makefile
RUN make setup
RUN make
