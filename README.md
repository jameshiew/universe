# universe [![pipeline status](https://gitlab.com/jameshiew/universe/badges/master/pipeline.svg)](https://gitlab.com/jameshiew/universe/commits/master)

![Screenshot](screenshot.png "Screenshot")

Learning C++ and OpenGL by experimenting with simple procedural generation.

## Getting Started

### Prerequisites

* C/C++ compiler
* Make
* CMake
* [Conan](https://conan.io/) package manager

### Dependencies

Some dependencies are vendored as Git submodules under `vendor/`, if you clone the repository recursively these will be cloned as well.

```shell script
git clone --recursive https://github.com/jameshiew/universe.git
```

Others are recorded in `conanfile.txt` and can be pulled in using Conan.

### Building and running

```shell script
./build.sh
cd bin/
./universe
```

## Controls

WASD to move about, mouse to look around, space/lctrl to go up/down.

Hold shift to go faster.

Q for wireframe mode.
