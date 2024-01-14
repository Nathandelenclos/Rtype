docker rm -f "$1"
docker run --name "$1" --rm -d -p 4242:4245/udp "$2/$1"
