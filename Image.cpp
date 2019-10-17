//
// Created by Tony Guo on 4/17/2018.
//

#include "Image.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

//helper methods
int Image::rowcolToArray(int row, int col) const{
    return row*width+col;
}

//construct only via Image class (begin/end)
Image::iterator::iterator(unsigned char *p): ptr(p) {

}

//copy constructor
Image::iterator::iterator(const Image::iterator& rhs): ptr(rhs.ptr){

}

//overloaded ops: *,++,--,=
unsigned char& Image::iterator::operator*() {
    return *ptr;
}

void Image::iterator::operator++() {
    ++ptr;
}

void Image::iterator::operator--() {
    --ptr;
}

Image::iterator& Image::iterator::operator=(const Image::iterator &rhs) {
    ptr = rhs.ptr;
    return *this;
}

bool Image::iterator::operator!=(const Image::iterator &rhs) const {
    if (ptr!=rhs.ptr)
        return true;
    else
        return false;

}

bool Image::iterator::operator==(const Image::iterator &rhs) const {
    if (ptr==rhs.ptr)
        return true;
    else
        return false;
}

//constructor
Image::Image():width(0), height(0) {

}

//parameterised constructor
Image::Image(const int &w, const int &h): width(w), height(h) {
    data=unique_ptr<unsigned char[]>(new unsigned char[width*height]);
}

//test constructor
Image::Image(const int &w, const int &h, std::initializer_list<unsigned char> lst):width(w), height(h) {
    data=unique_ptr<unsigned char[]>(new unsigned char[width*height]);
    //copy(lst.begin(), lst.end(), this->begin());
    auto onImage = lst.begin();
    for(int i=0;i<width*height;++i){
        data[i]= *onImage;
        ++onImage;
    }
}

//destructor
Image::~Image() {

}

//copy constructor
Image::Image(const Image &rhs):width(rhs.width), height(rhs.height) {
    data=unique_ptr<unsigned char[]>(new unsigned char[width*height]);

    iterator thisBeg = this->begin(), thisEnd = this->end();
    iterator rhsBeg = rhs.begin();//, rhsEnd = rhs.end();

    while(thisBeg!=thisEnd){
        *thisBeg = *rhsBeg;
        ++rhsBeg;
        ++thisBeg;
    }
}

//move constructor
Image::Image(Image &&rhs):width(rhs.width), height(rhs.height), data(move(rhs.data)) {

}

//copy assignment operator
Image& Image::operator=(const Image &rhs) {
    width = rhs.width;
    height = rhs.height;

    data.reset(new unsigned char[width*height]);

    iterator thisBeg = this->begin(), thisEnd = this->end();
    iterator rhsBeg = rhs.begin();//, rhsEnd = rhs.end();

    while(thisBeg!=thisEnd){
        *thisBeg = *rhsBeg;
        ++thisBeg;
        ++rhsBeg;
    }

    return *this;
}

//move assignment operator
Image& Image::operator=(Image &&rhs) {
    width = rhs.width;
    height = rhs.height;

    data.reset();
    data = move(rhs.data);
    return *this;
}

/*void Image::copy(const Image &rhs) {
    width = rhs.width;
    height = rhs.height;

    iterator beg = this->begin(), end = this->end();
    iterator inStart = rhs.begin();//, inEnd = rhs.end();

    while(beg!=end){
        *beg = *inStart;
        ++beg;
        ++end;
    }
}*/

//image operations should be expressed in terms of iterators
//Add I1+I2: add pixel values of I1 to I2
Image Image::operator+(const Image &rhs) const {
    Image result(*this);
    //result.copy(*this);
    /*for (int i=0;i<width*height;++i){
        result.data[i] += rhs.data[i];
    }*/
    iterator resBeg = result.begin(), resEnd = result.end();
    iterator rhsBeg = rhs.begin(); //rhsEnd = rhs.end();
    while(resBeg!=resEnd){
        if (*resBeg+*rhsBeg<=255)
            *resBeg += *rhsBeg;
        else
            *resBeg = 255;
        ++resBeg;
        ++rhsBeg;
    }
    return result;
}

//Subtract I1-I2: subtract pixel values of I2 from I1
Image Image::operator-(const Image &rhs) const {
    Image result(*this);
    //result.copy(*this);

    iterator resBeg = result.begin(), resEnd = result.end();
    iterator rhsBeg = rhs.begin(); //rhsEnd = rhs.end();

    while(resBeg!=resEnd){
        if (*resBeg-*rhsBeg>=0)
            *resBeg -= *rhsBeg;
        else
            *resBeg = 0;
        ++resBeg;
        ++rhsBeg;
    }

    return result;
}

//Invert !I1: replace each pixel value p with (255-p)
Image Image::operator!() const {
    Image result(width, height);
    //result.copy(*this);

    iterator resBeg = result.begin(), resEnd = result.end();
    iterator thisBeg = this->begin();//thisEnd = this->end();

    while(resBeg!=resEnd){
        *resBeg = 255-*thisBeg;
        ++resBeg;
        ++thisBeg;
    }

    return result;
}

//Mask I1/I2: copy across values of I1 where I2 has a value of 255, all other values are set to 0
Image Image::operator/(const Image &rhs) const {
    Image result(*this);
    //result.copy(*this);

    iterator resBeg = result.begin(), resEnd = result.end();
    iterator rhsBeg = rhs.begin(); //rhsEnd = rhs.end();

    while(resBeg!=resEnd){
        if (*rhsBeg != 255)
            *resBeg = 0;
        ++resBeg;
        ++rhsBeg;
    }

    return result;
}

//Threshold I1*f: if I1>f, set to 255, else set to 0 - create mask
Image Image::operator*(const int &rhs) const {
    Image result(width, height);
    //result.copy(*this);

    iterator resBeg = result.begin(), resEnd = result.end();
    iterator thisBeg = this->begin();//thisEnd = this->end();

    while(resBeg!=resEnd){
        if (*thisBeg>rhs)
            *resBeg = 255;
        else
            *resBeg = 0;
        ++resBeg;
        ++thisBeg;
    }

    return result;
}

//Filter I1 % g: filtered version of the input
Image Image::operator%(const Filter &rhs) const {
    Image result(width, height);

    int filterSize = rhs.getFilterSize();

    for (int i=0;i<width*height;++i){
        //data[i] in focus

        //get centre
        int iCentre = (filterSize/2)+1;

        //row and coloumn of i
        int focusCol = i%width;
        int focusRow = i/width;

        int onCol = focusCol-(filterSize/2);
        int onRow = focusRow-(filterSize/2);

        //int iRowCounter=1;
        int iColCounter=1;
        //compute nxn weighted sum
        float fTotal=0;
        for (int j=0;j<filterSize*filterSize;++j){
            //make sure row and col is valid - boundary cases
            int rowToUse, colToUse;
            if (onRow<0){
                rowToUse = -onRow-1;
            } else if (onRow>=height){
                rowToUse = 2*height-onRow-1;
            } else {
                rowToUse = onRow;
            }

            if (onCol<0){
                colToUse = -onCol-1;
            } else if (onCol>=width){
                colToUse = 2*width-onCol-1;
            } else {
                colToUse = onCol;
            }
            float fAdd = data[rowcolToArray(rowToUse, colToUse)]*rhs.getWeight(j);
            fTotal += fAdd;

            ++iColCounter;
            if (iColCounter>filterSize){
                iColCounter=1;
                ++onRow;
                onCol = onCol-(filterSize-1);
            } else{
                ++onCol;
            }
        }

        //have fTotal write to new Image
        result.data[i] = fTotal;

    }

    return result;
}

void Image::load(std::string FileToOpen) {
    ifstream ifsLoad(FileToOpen, ios::binary);

    if (!ifsLoad){
        //cerr << "Opening " << headerFilename << " failed :(" << endl;
        cout << "Opening " << FileToOpen << " failed :(" << endl;
        return;
    }
    //P5
    //# comment lines
    //Nrows Ncols
    //255
    //binary_data_block

    string line;
    getline(ifsLoad, line);
    getline(ifsLoad, line);
    while (line[0] == '#') {
        getline(ifsLoad, line);
    }

    istringstream issRowCol(line);
    issRowCol >> height >> width;
    ifsLoad >> line >> ws;

    data = unique_ptr<unsigned char[]>(new unsigned char[width * height]);
    ifsLoad.read((char *) (data.get()), width * height);
    ifsLoad.close();
}

void Image::save(std::string FileToWriteTo) {
    ofstream ofsExtra(FileToWriteTo,ios::binary);
    //P5
    //# comment lines
    //Nrows Ncols
    //255
    //binary_data_block
    ofsExtra<<"P5" << endl;
    ofsExtra<<"#Creator: Tony Guo" << endl;
    ofsExtra<<height<<" "<<width<<endl;
    ofsExtra<<255<<endl;
    ofsExtra.write((char *) (data.get()), width * height);
    ofsExtra.flush();

    ofsExtra.close();

}

Image::iterator Image::begin(void) const{
    return iterator(data.get());
}

Image::iterator Image::end() const {
    return iterator(data.get()+(width*height));
}

unsigned char* Image::getBuffer(){
    unsigned char* result = new unsigned char[width*height];

    for (int i=0;i<width*height;++i){
        result[i] = data[i];
    }
    return result;
}

std::unique_ptr<unsigned char[]>& Image::getData() {
    return data;
}

ostream &operator <<(ostream & os, const Image & rhs){
    os<<"Width: "<<rhs.width << " Height: " << rhs.height;
    for (int i=0;i<rhs.width*rhs.height;++i){
        if (i==rhs.width*rhs.height-1)
            os<<rhs.data[i];
        else
            os<<rhs.data[i] << " ";
    }
    return os;
}

istream &operator >>(istream & is, Image & rhs){
    //Nrows Ncols [binary data]
    is>>rhs.height >> rhs.width;
    rhs.data = unique_ptr<unsigned char[]>(new unsigned char[rhs.height*rhs.width]);
    int iCounter = 0;

    while (!is.eof()){
        is >> rhs.data[iCounter];
        ++iCounter;
    }

    return is;
}

bool isImageSameSize(const Image& Image1, const Image& Image2){
  if ((Image1.width == Image2.width) &&(Image1.height==Image2.height))
    return true;
  else
    return false;
}
