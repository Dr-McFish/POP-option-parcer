# POP Option Parser

<!-- insert cool logo -->
***hell yeah***

## About

POP is a C library for creating your own custom command line options.

If you ever used the command line you have encountered an option, for example take this:

```
 $ git clone --depth 1 --progress https://github.com/Dr-McFish/POP-option-parcer.git
   ~~~~~~~~~ ~~~~~~~~~ ~~~~~~~~~~ ~~~~~~~~~~~~~~~~~  
   COMMAND   OPTION 1  OPTION 2	  ARGUMENT 1
```

`--depth 1` and `--progress` are options for the git clone program. Likewise, POP enables you to create your own option for your own program in C.

Learn more about how this is done in the documentation(Coming soon).

## Demo

If the library is compiled correctly for your OS(the `build` folder contains the pre-compiled library for Windows ready to go), then you can try the demo, and look at the code in `POP_example_usage.c`.

To run the demo type this command in the root directory of this repo:

	make demo

It compiles a small demo program that creates and prints a your profile based on the options. Once you have done this, you can try it personalize this profile to gauge how these options work, type:

	./demo --help



## Compiling

If you are not on Windows, you will need to compile this library yourself. This is not hard.

### 1. Prerequisites

You will need to install:
 1. The gcc compiler
 2. Make.

### 2. Get code

Clone this repository:
```
$ git clone --depth 1 https://github.com/Dr-McFish/POP-option-parcer.git
```
Navigate to the correct directory:
```
$ cd POP-option-parser/dev
```

### 3. Compile

Run this command to compile:

	$ make release.

The all the necessary library files will be outputted to `POP-option-parser/build/`.
Done!
