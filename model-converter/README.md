Katana Model-Converter
======

**Model-Converter** is used to convert 3D models in different formats to that supported by Katana game engine.


# Building

You will first need to install the dependencies to build the converter.

### GLM

GLM is OpenGL Mathematics library containing header only implementation based on GLSL specifications. You can download the headers directly from its [github page](https://github.com/g-truc/glm/releases).

```
# For Debian systems, you may install it with apt-get
sudo apt-get install libglm-dev
```

### Assimp
[Assimp](http://assimp.sourceforge.net/main_downloads.html) is a 3D model loading library.

```
# For Debian systems, you may install it with apt-get
sudo apt-get install libassimp-dev
```


### Building Model-Converter

Simply execute `make` to build the binaries, which are built into the *bin* directory. If error is encountered, try to clean up the previous build outputs using `make clean`.

```
make clean
make
```
