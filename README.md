# pipenetwork

course assignment: solves the fluxes in a pipe network from a text description of nodes and tubes. C++11, CMake, Catch for tests.

## build and run

```sh
cmake -B build && cmake --build build
./build/main
```

`main` reads `input.txt` from the working directory and writes the fluxes to `pipedata.txt`. run the tests with `./build/pipenetwork_testrunner`.
