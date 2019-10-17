//
// Created by Tony Guo on 4/23/2018.
//

#ifndef ASSIGNMENT4_FILTER_H
#define ASSIGNMENT4_FILTER_H

#include <string>

class Filter {
private:
    int filterSize;
    float * vals;
public:
    //constructor
    Filter(std::string textFile);
    //test constructor
    Filter(const int& fs, std::initializer_list<float> lst);
    //destructor
    ~Filter();

    //get value of float at iPos
    float getWeight(int iPos) const;
    //get filter size
    int getFilterSize() const;


};


#endif //ASSIGNMENT4_FILTER_H
