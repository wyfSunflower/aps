protoc --cpp_out=../protos --proto_path=../protos/ ../protos/graph.proto
protoc --cpp_out=../protos --proto_path=../protos/ ../protos/global.proto
if [[ $1 == "MinGW" ]]; then
   cmake .. -G "MinGW Makefiles"
else
   cmake ..
fi
make -j32
