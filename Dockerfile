FROM ubuntu:20.04
RUN apt update
RUN apt install -y gcc g++ cmake

# Building
COPY ./banking/ ./
WORKDIR ./

RUN cmake -S ./ -B ./build/
RUN cmake --build build

# Running
RUN groupadd -r sample && useradd -r -g sample sample
USER sample

WORKDIR ./
ENTRYPOINT ["./build/banking_lib_test"]
