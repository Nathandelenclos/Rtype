docker rm -f "$1"
docker run --name "$1" --rm -d -p 4245:4242/udp "$2/$1"
