# SDL Library
## Project Description
This project is a layer for SDL. Its role is to make certain tasks with SDL easier and to be able to use more drawing primitives than the few provided
by SDL.

## Setup
### Dependencies
On a Debian system you can install the needed dependencies using:
```shell
sudo apt install g++ cmake make libsdl2-dev -y
```

### Clone Repository
```shell
git clone https://github.com/llikian/SDL-Library.git
cd SDL-Library
```

### Build
To build you can simply run the `build.sh` script at the root of the project using:
```shell
bash build.sh
```

You can also manually build it using:
```shell
cmake -B build && \
cmake --build build -j
```

Then you can run it using:
```shell
bin/SDL-Library
```

## Credits
The rendering is done using [SDL2](https://www.libsdl.org/).