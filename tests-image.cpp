#include "Image.h"
#include "Filter.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("MOVE AND COPY SEMANTICS","[MoveandCopySemantics]"){
  Image I1(4,2,{0,1,2,3,4,5,6,7});
  Image I2(4,2,{255,254,253,252,251,250,249,248});
  Image I3(4,2,{16,17,18,19,20,10,11,12});
  Image moveI1=Image(4,2,{7,8,9,10,11,12,13,14});
  Image moveI2 = I1;
  moveI2 = Image(4,2,{16,17,18,19,20,10,11,12});
  Image copyI1(I1);
  Image copyI2;
  copyI2 = moveI1;

  SECTION("MOVE CONSTRUCTOR"){
    auto buf = moveI1.getBuffer();
    REQUIRE(buf[0]==7);
    REQUIRE(buf[1]==8);
    REQUIRE(buf[2]==9);
    REQUIRE(buf[3]==10);
    REQUIRE(buf[4]==11);
    REQUIRE(buf[5]==12);
    REQUIRE(buf[6]==13);
    REQUIRE(buf[7]==14);
  }

  SECTION("MOVE ASSIGNMENT OPERATOR"){
    auto buf = moveI2.getBuffer();
    REQUIRE(buf[0]==16);
    REQUIRE(buf[1]==17);
    REQUIRE(buf[2]==18);
    REQUIRE(buf[3]==19);
    REQUIRE(buf[4]==20);
    REQUIRE(buf[5]==10);
    REQUIRE(buf[6]==11);
    REQUIRE(buf[7]==12);
  }

  SECTION("COPY CONSTRUCTOR"){
    auto buf = copyI1.getBuffer();
    REQUIRE(buf[0]==0);
    REQUIRE(buf[1]==1);
    REQUIRE(buf[2]==2);
    REQUIRE(buf[3]==3);
    REQUIRE(buf[4]==4);
    REQUIRE(buf[5]==5);
    REQUIRE(buf[6]==6);
    REQUIRE(buf[7]==7);
  }

  SECTION("COPY ASSIGNMENT OPERATOR"){
    auto buf = copyI2.getBuffer();
    REQUIRE(buf[0]==7);
    REQUIRE(buf[1]==8);
    REQUIRE(buf[2]==9);
    REQUIRE(buf[3]==10);
    REQUIRE(buf[4]==11);
    REQUIRE(buf[5]==12);
    REQUIRE(buf[6]==13);
    REQUIRE(buf[7]==14);
  }

}


TEST_CASE("ITERATOR AND ITS OPERATORS","[IteratorandItsOperators]"){
  //can only construct iterators via begin and end methods
  Image I1(4,2,{24,11,15,107,16,4,78,78});
  Image::iterator I1Beg = I1.begin(), I1End = I1.end();

  SECTION("BEGIN AND END CONSTRUCTS AND OPERATOR ="){
    REQUIRE(int(*I1Beg)==24);
    int iCount = 0;
    while (I1Beg != I1End){
      ++iCount;
      ++I1Beg;
    }
    REQUIRE(iCount==8);
  }

  SECTION("COPY CONSTRUCT AND OPERATOR == AND !="){
    Image::iterator copyI1Beg(I1Beg);
    bool a = (I1Beg==copyI1Beg);
    bool b = (I1Beg!=I1End);
    REQUIRE(a==true);
    REQUIRE(b==true);
  }

  SECTION("OPERATORS *,++,--"){
    ++I1Beg;
    REQUIRE(*I1Beg==11);
    --I1End;
    REQUIRE(*I1End==78);
    ++I1Beg;
    ++I1Beg;
    --I1End;
    --I1End;
    --I1End;
    --I1End;
    REQUIRE(*I1Beg==*I1End);
  }

}

TEST_CASE("THRESHOLDING, INVERTING AND MASKING OPERATOR OVERLOADS","[ThresholdingInvertingandMaskingOperatorOverloads]"){
  Image I1(4,2,{5,89,78,4,3,26,45,74});
  Image I2(4,2,{5,4,2,100,101,123,141,151});
  Image ThreshI1 = I2*100;
  Image InverseI1 = !I1;
  Image MaskI1 = I1/ThreshI1;

  SECTION("THRESHOLDING OPERATOR *"){
    auto buf = ThreshI1.getBuffer();
    REQUIRE(buf[0]==0);
    REQUIRE(buf[1]==0);
    REQUIRE(buf[2]==0);
    REQUIRE(buf[3]==0);
    REQUIRE(buf[4]==255);
    REQUIRE(buf[5]==255);
    REQUIRE(buf[6]==255);
    REQUIRE(buf[7]==255);
  }

  SECTION("INVERTING OPERATOR !"){
    auto buf = InverseI1.getBuffer();
    REQUIRE(buf[0]==250);
    REQUIRE(buf[1]==166);
    REQUIRE(buf[2]==177);
    REQUIRE(buf[3]==251);
    REQUIRE(buf[4]==252);
    REQUIRE(buf[5]==229);
    REQUIRE(buf[6]==210);
    REQUIRE(buf[7]==181);
  }

  SECTION("MASKING OPERATOR /"){
    auto buf = MaskI1.getBuffer();
    REQUIRE(buf[0]==0);
    REQUIRE(buf[1]==0);
    REQUIRE(buf[2]==0);
    REQUIRE(buf[3]==0);
    REQUIRE(buf[4]==3);
    REQUIRE(buf[5]==26);
    REQUIRE(buf[6]==45);
    REQUIRE(buf[7]==74);
  }

}

TEST_CASE("ADDITION AND SUBTRACTION OF IMAGES","[AdditionandSubtractionofImages]"){
  Image I1(4,2,{4,78,150,223,245,6,66,181});
  Image I2(4,2,{86,67,152,144,122,210,5,30});
  Image AddI1 = I1+I2;
  Image SubI1 = I1-I2;

  SECTION("ADDITION OPERATOR +"){
    auto buf = AddI1.getBuffer();
    REQUIRE(buf[0]==90);
    REQUIRE(buf[1]==145);
    REQUIRE(buf[2]==255);
    REQUIRE(buf[3]==255);
    REQUIRE(buf[4]==255);
    REQUIRE(buf[5]==216);
    REQUIRE(buf[6]==71);
    REQUIRE(buf[7]==211);
  }

  SECTION("SUBTRACTION OPERATOR -"){
    auto buf = SubI1.getBuffer();
    REQUIRE(buf[0]==0);
    REQUIRE(buf[1]==11);
    REQUIRE(buf[2]==0);
    REQUIRE(buf[3]==79);
    REQUIRE(buf[4]==123);
    REQUIRE(buf[5]==0);
    REQUIRE(buf[6]==61);
    REQUIRE(buf[7]==151);
  }
}

TEST_CASE("THE FILTERING OPERATOR","[TheFilteringOperator]"){
  Image I1(4,2,{243,210,52,160,7,85,222,142});
  Filter g(3,{0,0,0.05,0,0,0.05,0,0,0.05});
  Image FilterI1 = I1%g;

  auto buf = FilterI1.getBuffer();
  REQUIRE(buf[0]==25);
  REQUIRE(buf[1]==16);
  REQUIRE(buf[2]==23);
  REQUIRE(buf[3]==23);
  REQUIRE(buf[4]==19);
  REQUIRE(buf[5]==24);
  REQUIRE(buf[6]==22);
  REQUIRE(buf[7]==22);
}

TEST_CASE("QUALITATIVE TEST","[QualitativeTest]"){
  Image I1(4,2,{5,4,2,100,101,123,141,151});
  Image I2(4,2,{4,78,150,223,245,6,66,181});
  Image I3(4,2,{86,67,152,144,122,210,5,30});
  Image ThresholdI1 = I1*100;
  Image InvertI1 = !ThresholdI1;
  Image MaskI1 = I2/ThresholdI1;
  Image MaskI2 = I3/InvertI1;
  Image AddI1 = MaskI1 + MaskI2;

  SECTION("IMAGE MASK VIA THRESHOLDING"){
    auto buf = ThresholdI1.getBuffer();
    REQUIRE(buf[0]==0);
    REQUIRE(buf[1]==0);
    REQUIRE(buf[2]==0);
    REQUIRE(buf[3]==0);
    REQUIRE(buf[4]==255);
    REQUIRE(buf[5]==255);
    REQUIRE(buf[6]==255);
    REQUIRE(buf[7]==255);
  }

  SECTION("INVERTED MASK"){
    auto buf = InvertI1.getBuffer();
    REQUIRE(buf[0]==255);
    REQUIRE(buf[1]==255);
    REQUIRE(buf[2]==255);
    REQUIRE(buf[3]==255);
    REQUIRE(buf[4]==0);
    REQUIRE(buf[5]==0);
    REQUIRE(buf[6]==0);
    REQUIRE(buf[7]==0);
  }

  SECTION("MASKED IMAGE"){
    auto buf = MaskI1.getBuffer();
    REQUIRE(buf[0]==0);
    REQUIRE(buf[1]==0);
    REQUIRE(buf[2]==0);
    REQUIRE(buf[3]==0);
    REQUIRE(buf[4]==245);
    REQUIRE(buf[5]==6);
    REQUIRE(buf[6]==66);
    REQUIRE(buf[7]==181);
  }

  SECTION("SECOND MASKED IMAGE"){
    auto buf = MaskI2.getBuffer();
    REQUIRE(buf[0]==86);
    REQUIRE(buf[1]==67);
    REQUIRE(buf[2]==152);
    REQUIRE(buf[3]==144);
    REQUIRE(buf[4]==0);
    REQUIRE(buf[5]==0);
    REQUIRE(buf[6]==0);
    REQUIRE(buf[7]==0);
  }

  SECTION("ADDITION OF MASKED IMAGES"){
    auto buf = AddI1.getBuffer();
    REQUIRE(buf[0]==86);
    REQUIRE(buf[1]==67);
    REQUIRE(buf[2]==152);
    REQUIRE(buf[3]==144);
    REQUIRE(buf[4]==245);
    REQUIRE(buf[5]==6);
    REQUIRE(buf[6]==66);
    REQUIRE(buf[7]==181);
  }

}
