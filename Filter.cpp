//
// Created by Tony Guo on 4/23/2018.
//

#include <fstream>
#include <iostream>
#include "Filter.h"

using namespace std;

//constructor
Filter::Filter(string textFile) {
    ifstream ifsFilter(textFile);
    if (!ifsFilter){
        //cerr << "Opening " << textFile << " failed :(" << endl;
        cout << "Opening " << textFile << " failed :(" << endl;
        return;
    }
    ifsFilter>>filterSize;
    vals = new float[filterSize*filterSize];

    for(int i=0;i<filterSize*filterSize;++i){
        ifsFilter>>vals[i];
    }

    ifsFilter.close();
}

//test constructor
Filter::Filter(const int &fs, std::initializer_list<float> lst):filterSize(fs) {
    vals = new float[filterSize*filterSize];
    auto onFloat = lst.begin();
    for(int i=0;i<filterSize*filterSize;++i){
        vals[i]= *onFloat;
        ++onFloat;
    }
}

//destructor
Filter::~Filter() {
    delete [] vals;
}

//get value of float at iPos
float Filter::getWeight(int iPos) const{
    return vals[iPos];
}

//get filter size
int Filter::getFilterSize() const{
    return filterSize;
}

