# Makefile for Assignemnt 4
# 26 Apr 2018
# Tony Guo
# GXXHEN001

imageops: main.o
	g++ -o imageops main.o Image.o Filter.o -std=c++11

main.o: main.cpp Image.o
	g++ -c -o main.o main.cpp -std=c++11

Image.o: Image.cpp Image.h Filter.o
	g++ -c -o Image.o Image.cpp -std=c++11

Filter.o: Filter.cpp Filter.h
	g++ -c -o Filter.o Filter.cpp -std=c++11

run:
	./imageops -a Lenna_hat_mask.pgm Lenna_standard.pgm AddLenna1
	./imageops -a Lenna_standard.pgm Lenna_hat_mask.pgm AddLenna2
	./imageops -s Lenna_hat_mask.pgm Lenna_standard.pgm SubtractLenna1
	./imageops -s Lenna_standard.pgm Lenna_hat_mask.pgm SubtractLenna2
	./imageops -i Lenna_standard.pgm InvertLenna
	./imageops -l Lenna_standard.pgm Lenna_hat_mask.pgm MaskLenna
	./imageops -t Lenna_standard.pgm 100 Threshold100Lenna
	./imageops -f Lenna_standard.pgm sample_filters/blur.fir FilterBlurLenna
	./imageops -f Lenna_standard.pgm sample_filters/motion_blur.fir FilterMotionBlurLenna
	./imageops -f Lenna_standard.pgm sample_filters/all_dir_edge_detect.fir FilterAllDirEdgeDetectLenna
	./imageops -f Lenna_standard.pgm sample_filters/unity.fir FilterUnityLenna

test:
	g++ -c -o tests-main.o tests-main.cpp -std=c++11
	g++ -o tests tests-main.o tests-image.cpp Image.o Filter.o -std=c++11

runtest:
	./tests

clean:
	@rm -f *.o imageops tests
	@rm -f AddLenna1.pgm AddLenna2.pgm SubtractLenna1.pgm SubtractLenna2.pgm InvertLenna.pgm MaskLenna.pgm Threshold100Lenna.pgm
	@rm -f FilterBlurLenna.pgm FilterMotionBlurLenna.pgm FilterAllDirEdgeDetectLenna.pgm FilterUnityLenna.pgm
