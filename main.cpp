#include <iostream>
#include <string>
#include "Image.h"
#include "Filter.h"

using namespace std;

int main(int argc, char * argv[]) {
    // imageops <option> outputimagename
    string sOperation = string(argv[1]);

    if (sOperation=="-a"){
        //Add: -a I1 I2
        string image1 = string(argv[2]);
        string image2 = string(argv[3]);
        cout << "Add operation: adding "<<image1<< " and " << image2 << "..." << endl;
        string sOutputName = string(argv[4]);
        string sSaveName = sOutputName+".pgm";

        Image I1, I2;
        cout << "Loading "<< image1 << "..."<< endl;
        I1.load(image1);
        cout << "Loading "<< image2 << "..."<< endl;
        I2.load(image2);
        cout << "Checking image dimensions..." << endl;
        if (!isImageSameSize(I1, I2)){
            cout << "Images are not of the same size, cannot process binary operation." << endl;
            return 0;
        }
        cout << "Creating new image..." << endl;
        Image IOut = I1+I2;
        IOut.save(sSaveName);
        cout << "Image "<<sSaveName << " created." << endl;
    } else if (sOperation=="-s"){
        //Subtract: -s I1 I2
        string image1 = string(argv[2]);
        string image2 = string(argv[3]);
        cout << "Subtract operation: subtracting "<<image2<< " from " << image1 << "..." << endl;
        string sOutputName = string(argv[4]);
        string sSaveName = sOutputName+".pgm";

        Image I1, I2;
        cout << "Loading "<< image1 << "..."<< endl;
        I1.load(image1);
        cout << "Loading "<< image2 << "..."<< endl;
        I2.load(image2);
        if (!isImageSameSize(I1, I2)){
            cout << "Images are not of the same size, cannot process binary operation." << endl;
            return 0;
        }
        cout << "Creating new image..." << endl;
        Image IOut = I1-I2;
        IOut.save(sSaveName);
        cout << "Image "<<sSaveName << " created." << endl;

    } else if (sOperation=="-i"){
        //Invert: -i I1
        string image1 = string(argv[2]);
        cout << "Invert operation: inverting "<<image1 << "..." << endl;
        string sOutputName = string(argv[3]);
        string sSaveName = sOutputName+".pgm";

        Image I1;
        cout << "Loading "<< image1 << "..."<< endl;
        I1.load(image1);
        cout << "Creating new image..." << endl;
        Image IOut = !I1;
        IOut.save(sSaveName);
        cout << "Image "<<sSaveName << " created." << endl;

    } else if (sOperation=="-l"){
        //Mask: -l I1 I2
        string image1 = string(argv[2]);
        string image2 = string(argv[3]);
        cout << "Mask operation: masking "<<image1 <<" with " << image2 << "..." << endl;
        string sOutputName = string(argv[4]);
        string sSaveName = sOutputName+".pgm";

        Image I1, I2;
        cout << "Loading "<< image1 << "..."<< endl;
        I1.load(image1);
        cout << "Loading "<< image2 << "..."<< endl;
        I2.load(image2);
        if (!isImageSameSize(I1, I2)){
            cout << "Images are not of the same size, cannot process binary operation." << endl;
            return 0;
        }
        cout << "Creating new image..." << endl;
        Image IOut = I1/I2;
        IOut.save(sSaveName);
        cout << "Image "<<sSaveName << " created." << endl;

    } else if (sOperation=="-t") {
        //Threshold: -t I1 f
        string image1 = string(argv[2]);
        int f = atoi(argv[3]);
        cout << "Threshold operation: creating a mask using "<<image1 <<" with threshold value " << f << "..." << endl;
        string sOutputName = string(argv[4]);
        string sSaveName = sOutputName+".pgm";

        Image I1;
        cout << "Loading "<< image1 << "..."<< endl;
        I1.load(image1);
        cout << "Creating new image..." << endl;
        Image IOut = I1*f;
        IOut.save(sSaveName);
        cout << "Image "<<sSaveName << " created." << endl;

    } else if (sOperation=="-f"){
        //Filter: -f I1 g
        string image1 = string(argv[2]);
        string sFilter = string(argv[3]);
        cout << "Filter operation: applying "<<sFilter<< " on " << image1 << "..." << endl;
        string sOutputName = string(argv[4]);
        string sSaveName = sOutputName+".pgm";

        Image I1;
        cout << "Loading "<< image1 << "..."<< endl;
        I1.load(image1);
        cout << "Processing "<< sFilter << "..."<< endl;
        Filter g(sFilter);
        cout << "Creating new image..." << endl;
        Image IOut = I1%g;
        IOut.save(sSaveName);
        cout << "Image "<<sSaveName << " created." << endl;

    } else {
        cout << "Your command construct for program imageops was incorrect." << endl;
    }

    return 0;
}
