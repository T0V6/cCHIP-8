# cCHIP-8
A CHIP-8 emulator built in C

CHIP-8 is a simple interpreted programming language developed in the mid-1970s for early 8-bit computers. It was designed specifically for video game development and features a limited instruction set, running on a virtual machine and enabling cross-platform compatibility through emulators.

## Installation

1. Clone the repository
```bash
    git clone https://github.com/TV08/cCHIP-8.git
```

2. Build source code
```bash
    make
```

3. Delete build
```bash
    make clean
```

## Usage
* From project's folder
```bash
    ./bin/chip8 <rom file>
```
* The key assignments depend on the chosen ROM!

## Documentation
The source code contains numerous development comments created during the emulator's development, explaining its functionality. This currently serves as the project's sole documentation.

## Contributing

Bugs, proposals, or feature pull requests are welcome :D

## License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/). See the [LICENSE](LICENSE) file for details.