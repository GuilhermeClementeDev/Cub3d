FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    valgrind \
    libc6-dev \
    libx11-dev \
    libxext-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libbsd-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN make

CMD ["./tests/run_tests.sh"]
