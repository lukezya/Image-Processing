//
// Created by Tony Guo on 4/17/2018.
//

#ifndef ASSIGNMENT4_IMAGE_H
#define ASSIGNMENT4_IMAGE_H


#include <memory>
#include <string>
#include "Filter.h"

class Image {
//friend class iterator;
    friend std::ostream &operator <<(std::ostream & os, const Image & rhs);
    friend std::istream &operator >>(std::istream & is, Image & rhs);
    friend bool isImageSameSize(const Image& Image1, const Image& Image2);
private:
    int width, height;
    std::unique_ptr<unsigned char[]> data;

    //helper methods
    int rowcolToArray(int row, int col) const;
public:
    class iterator {
    friend class Image;
    private:
        unsigned char *ptr;

        //construct only via Image class (begin/end)
        iterator (unsigned char *p);

    public:
        //copy construct is public
        iterator(const iterator & rhs);

        //define overloaded ops: *, ++, --, =
        unsigned char& operator*(void);
        void operator++(void);
        void operator--(void);
        iterator& operator=(const iterator &rhs);

        //other methods for iterator
        bool operator!=(const iterator& rhs)const;
        bool operator==(const iterator& rhs)const;
    };

    //default constructor
    Image();
    //parameterised constructor
    Image(const int& w, const int& h);
    //test constructor
    Image(const int& w, const int& h, std::initializer_list<unsigned char> lst);
    //destructor
    ~Image();

    //copy/move semantics
    //copy constructor
    Image(const Image&rhs);
    //move constructor
    Image(Image&& rhs);
    //copy assignment operator
    Image& operator=(const Image& rhs);
    //move assignment operator
    Image& operator=(Image && rhs);
    //void copy(const Image& rhs);

    //functions for image operations: +,-,!,/,*
    //Add I1+I2: add pixel values of I1 to I2
    Image operator+(const Image& rhs) const;
    //Subtract I1-I2: subtract pixel values of I2 from I1
    Image operator-(const Image& rhs) const;
    //Invert !I1: replace each pixel value p with (255-p)
    Image operator!(void) const;
    //Mask I1/I2: copy across values of I1 where I2 has a value of 255, all other values are set to 0
    Image operator/(const Image& rhs) const;
    //Threshold I1*f: if I1>f, set to 255, else set to 0 - create mask
    Image operator*(const int& rhs) const ;
    //Filter I1 % g: filtered version of the input
    Image operator%(const Filter& rhs) const;

    //load/save methods
    void load(std::string FileToOpen);
    void save(std::string FileToWriteTo);

    //define begin()/end() to get iterator to start and "one-past" end
    iterator begin(void) const;
    iterator end(void) const;

    //test method
    unsigned char* getBuffer();
    std::unique_ptr<unsigned char[]>& getData();

};

//I/O operators for Image
std::ostream &operator <<(std::ostream & os, const Image & rhs);
std::istream &operator >>(std::istream & is, Image & rhs);

//checking for samesize
bool isImageSameSize(const Image& Image1, const Image& Image2);

#endif //ASSIGNMENT4_IMAGE_H
