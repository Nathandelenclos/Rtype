docker rm -f "$1"
docker run --name "$1" --rm -d -p 4242:4242/udp "$2/$1"
