FROM alpine:3.7 as builder

RUN apk update
RUN apk --no-cache add ca-certificates cmake g++ make linux-headers
RUN apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted
RUN apk add --no-cache wget

ADD . /opt/sources
WORKDIR /opt/sources
RUN wget https://chrberger.github.io/libcluon/headeronly/cluon-complete.hpp
RUN cluon-msc --cpp --out=messages.hpp opendlv.odvd
RUN mkdir /tmp/build
RUN cd /tmp/build
RUN cmake -D CMAKE_BUILD_TYPE=Release /opt/sources
RUN make
RUN cp opendlv-logic-imansh /tmp


# Deploy .
FROM alpine:3.7
RUN apk update
RUN apk --no-cache add libstdc++
RUN mkdir /opt
WORKDIR /opt
COPY --from=builder /tmp/opendlv-logic-imansh .
CMD ["/opt/opendlv-logic-imansh"]
