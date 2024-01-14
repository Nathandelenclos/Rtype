./clean.sh
mkdir ./build/ && cd ./build/
cmake .. && make
mv r-type_server ../ && mv r-type_client ../
cd ../