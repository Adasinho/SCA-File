# SCA-File Implementation

### Build process
Go to build direction
```shell script
cd build
```

Next compile command
```shell script
cmake -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=make -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
```

Build tests command
```shell script
cmake --build ./ --target radmor_test
```

Run tests
```shell script
./radmor_test
```