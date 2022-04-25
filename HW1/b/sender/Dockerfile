FROM ubuntu:16.04 as builder

RUN apt-get update -y && \
        apt-get install -y build-essential cmake software-properties-common

RUN add-apt-repository -y ppa:chrberger/libcluon && \
        apt-get update && \
        apt-get install libcluon

ADD . /opt/sources
WORKDIR /opt/sources

RUN mkdir /tmp/build && \
        cd /tmp/build && \
        cmake -D CMAKE_BUILD_TYPE=Release /opt/sources && \
        make && cp sender /tmp

# Deploy .
FROM ubuntu:16.04
RUN apt-get update -y && \
        apt-get install -y build-essential cmake software-properties-common 

WORKDIR /opt
COPY --from=builder /tmp/sender .
CMD ["/opt/sender"]
