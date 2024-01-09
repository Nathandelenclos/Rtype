#! /bin/bash

image_name="jenkins/$1"

if [[ -f Dockerfile ]]; then
    docker build . -t "$image_name"
    docker push "$image_name"
fi

if [[ -f deploy.sh ]]; then
    ./deploy.sh
fi