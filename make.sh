protoc --proto_path=../proto --cpp_out=../proto ../proto/*.proto
if [[ $1 == "MinGW" ]]; then
   cmake .. -G "MinGW Makefiles"
else
   cmake ..
fi
make -j32
