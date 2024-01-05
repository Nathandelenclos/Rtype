FROM alpine:3.12

RUN apk update && apk upgrade
RUN apk add build-base cmake git make

COPY . /rtype

RUN mkdir /rtype/build

WORKDIR /rtype/build

RUN cmake .. && make

EXPOSE 4242

CMD ["./rtype_server"]
