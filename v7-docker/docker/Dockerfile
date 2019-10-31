FROM frolvlad/alpine-gxx
WORKDIR /build
RUN apk update && apk upgrade && apk add git cmake make
RUN git clone --recursive https://github.com/jeffmm/take_two.git . &&\
    cd v6-continuous-integration &&\
    mkdir build &&\
    cd build &&\
    cmake -DTESTS=TRUE .. &&\
    make && make test && make install
RUN rm -rf /build && apk del git
WORKDIR /app
