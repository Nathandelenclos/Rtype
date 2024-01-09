docker rm -f "$1"
docker run --rm -d -p 4242:4242/udp "$1" --name "$1"
