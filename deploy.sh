docker rm -f "$1"
docker run --name "$1" --rm -d -p 4244:4242/udp "$2/$1"
