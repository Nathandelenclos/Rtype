FROM alpine:latest

RUN apk update && apk upgrade
RUN apk add build-base git make cmake wget libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev mesa-dev eudev-dev openal-soft-dev freetype-dev sfml-dev

COPY . /rtype

RUN mkdir /rtype/build

WORKDIR /rtype/build

RUN cmake .. && make

EXPOSE 4242

CMD ["./r-type_server"]
