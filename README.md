> ![Icon](data/icons/hyper_ico.png)

# HyperPad
A fast, simple and open-source text editor using Qt5

## Getting Started
### Prerequisites
* qt5 >= 5.12
* cmake >= 3.5
* C++ compiler (like GCC or Clang)

Clone the project with git clone command

```
$ git clone https://github.com/ecsuarez/hyperpad.git
```

### Build
Create a directory and configure cmake.
You can use other **PREFIX_PATH** instead of "/usr".

```
$ cd hyperpad
$ mkdir build && cd build
$ cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..
$ cmake --build .
```

### Install
If you want install hyperpad on your system, use

```
$ cmake --install .
```

## Contributing
All pull requests will be revised, do one!

## License
This project is licensed under the GPL v3 License - see the [LICENSE](LICENSE)
file for details.

## Author
Ernest C. Suarez <ernestcsuarez@gmail.com>
