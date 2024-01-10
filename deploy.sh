docker rm -f "$1"
docker run --name "$1" --rm -d -p 4243:4242/udp "$2/$1"
