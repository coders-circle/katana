Katana
======

**Katana** is a free and open source game engine based on the Entity-Component-System (ECS) architecture. It is cross-platform, built and tested currently in C++ for desktop environment.


# Building

You will first need to install the dependencies to build the engine.

### GLFW

GLFW is used to create windows with OpenGL contexts and manage windows and inputs.

Download the source code from the [GLFW download page](http://www.glfw.org/download.html). For windows, you may directly download the library binaries. For linux systems, you can compile from the source code.

```
# Install GLFW dependencies
# For Debian systems, you can install them with apt-get
sudo apt-get install cmake xorg-dev libgl1-mesa-dev

# Install GLFW from its directory
cmake .
make
sudo make install
```

### GLM

GLM is OpenGL Mathematics library containing header only implementation based on GLSL specifications. You can download the headers directly from its [github page](https://github.com/g-truc/glm/releases).

```
# For Debian systems, you may install it with apt-get
sudo apt-get install libglm-dev
```

### GLEW

[GLEW](http://glew.sourceforge.net/index.html) provides efficient extension loading library for OpenGL applications.

```
# For Debian systems, you may install it with apt-get
sudo apt-get install libglew-dev
```


### SOIL
[SOIL](http://www.lonesock.net/soil.html) provides tiny library for uploading textures into OpenGL.

```
# For Debian systems, you may install it with apt-get
sudo apt-get install libsoil-dev
```


### Building Katana

Simply execute `make` to build the binaries, which are built into the *bin* directory. If error is encountered, try to clean up the previous build outputs using `make clean`.

```
make clean
make
```
