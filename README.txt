# README for Assignment 4
# 28 Apr 2018
# Tony Guo
# GXXHEN001

-----------------------------------
Files in this directory
-----------------------------------
sample_filters/ folder - contains filter samples to use for filter operation.

Filter.cpp - source file containing the body of method signatures in
Filter.h for generating a Filter object from a .fir file.

Filter.h - method headers for source file Filter.cpp.

Image.cpp - source file containing the body of method signatures in
Image.h for PGM Image Manipulation.

Image.h - method headers for source file Image.cpp along with its data.

main.cpp - driver source file for manipulating PNG Images and contains the
main() method.

Makefile - makefile to compile source files and get: imageops, main.o, Image.o,
and Filter.o

tests-main.cpp - main unit test file that define CATCH_CONFIG_MAIN for the rest
of the test files.

tests-image.cpp - unit test for Image containing tests for all
methods: Move and copy semantics, Iterator and its operators, Thresholding,
inverting and masking operator overloads, Addition and subtraction of images,
and the filtering operator, along with a qualitative test.

catch.hpp - library used in test classes for testing.

*.pgm - pgm image files used for testing and generating new images.

Tutorial_4.pdf - assignment instructions.

-----------------------------------
Running imageops
-----------------------------------
Open this directory in terminal.

Run the following commands:
make clean
make
make run

*make run will run the executable imageops 11 times:
1) Add operation:
  ./imageops -a Lenna_hat_mask.pgm Lenna_standard.pgm AddLenna1
  ./imageops -a Lenna_standard.pgm Lenna_hat_mask.pgm AddLenna2
2) Subtract operation:
  ./imageops -s Lenna_hat_mask.pgm Lenna_standard.pgm SubtractLenna1
  ./imageops -s Lenna_standard.pgm Lenna_hat_mask.pgm SubtractLenna2
3) Invert operation:
  ./imageops -i Lenna_standard.pgm InvertLenna
4) Mask operation:
  ./imageops -l Lenna_standard.pgm Lenna_hat_mask.pgm MaskLenna
5) Threshold operation:
  ./imageops -t Lenna_standard.pgm 100 Threshold100Lenna
6) Filter operation:
  ./imageops -f Lenna_standard.pgm sample_filters/blur.fir FilterBlurLenna
  ./imageops -f Lenna_standard.pgm sample_filters/motion_blur.fir FilterMotionBlurLenna
  ./imageops -f Lenna_standard.pgm sample_filters/all_dir_edge_detect.fir FilterAllDirEdgeDetectLenna
  ./imageops -f Lenna_standard.pgm sample_filters/unity.fir FilterUnityLenna
---The above values for the operation arguments were used for demo runs---

The following files will be created:
1) For Add operation:
  AddLenna1.pgm
  AddLenna2.pgm
2) For Subtract operation:
  SubtractLenna1
  SubtractLenna2
3) For Invert operation:
  InvertLenna.pgm
4) For Mask operation:
  MaskLenna.pgm
5) For Threshold operation:
  ThresholdLenna.pgm
6) For Filter operation:
  FilterBlurLenna.pgm
  FilterMotionBlurLenna.pgm
  FilterAllDirEdgeDetectLenna.pgm
  FilterUnityLenna.pgm

-----------------------------------
Checking outputted files
-----------------------------------
Open this directory in terminal.

Run the following command:
gimp <OutputImage_filename>

*<OutputImage_filename> is the filename of any of the newly generated images.

Or open this directory in GUI, and double click on any of the newly generated images.
This should open any of the images in Image Viewer.

-----------------------------------
Running unit tests
-----------------------------------
Open this directory in terminal.

After running the commands above in "Running imageops",
Run the following commands:
make test
make runtest

The file "tests" will be created, and make runtest runs this executable.
The results of the unit tests will be outputted to console.

-----------------------------------
Running imagesops with own arguments
-----------------------------------
Open terminal in this directory.

To run volimage with own arguments, type in a command in the following form:
./imageops <option> OutputImageName

*<option> can be any of the following options: (I1 and I2 represent pgm image filenames)
  -a I1 I2 (add I1 and I2)
  -s I1 I2 (subtract I2 from I1)
  -i I1 (invert I1)
  -l I1 I2 (mask I1 with I2)
  -t I1 f (threshold I1 with integer value f)
  -f I1 g (apply filter g on I1)

To run this command with available test data, run any of the commands with
I1, I2 with being any of the following pgm image filenames:
  donkey_mask.pgm
  shrek_rectangular.pgm
  Lenna_hat_mask.pgm
  Lenna_standard.pgm
