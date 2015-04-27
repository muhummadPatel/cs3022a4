#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "image.h"

using namespace ptlmuh006;

typedef unsigned char uchar;

TEST_CASE("Test image class operators", "[operators]"){
    uchar* buffer1 = new uchar[9];
    buffer1[0] = (uchar)255;
    buffer1[1] = (uchar)255;
    buffer1[2] = (uchar)0;
    buffer1[3] = (uchar)255;
    buffer1[4] = (uchar)255;
    buffer1[5] = (uchar)0;
    buffer1[6] = (uchar)0;
    buffer1[7] = (uchar)0;
    buffer1[8] = (uchar)0;
    Image img1(3, 3, &buffer1);
    
    uchar* buffer2 = new uchar[9];
    buffer2[0] = (uchar)0;
    buffer2[1] = (uchar)0;
    buffer2[2] = (uchar)0;
    buffer2[3] = (uchar)0;
    buffer2[4] = (uchar)255;
    buffer2[5] = (uchar)255;
    buffer2[6] = (uchar)0;
    buffer2[7] = (uchar)255;
    buffer2[8] = (uchar)255;
    Image img2(3, 3, &buffer2);
    
    SECTION("Test addition and clamping"){        
        int expected[] = {255, 255, 0, 255, 255, 255, 0, 255, 255};
        
        Image ans = img1 + img2;
        int i = 0;
        for(Image::iterator it = ans.begin(); it != ans.end(); ++it, i++){
            REQUIRE( (int)(*it) == expected[i] );
        }
    }
    
    SECTION("Test subtraction and clamping"){
       int expected[] = {255, 255, 0, 255, 0, 0, 0, 0, 0};
        
        Image ans = img1 - img2;
        int i = 0;
        for(Image::iterator it = ans.begin(); it != ans.end(); ++it, i++){
            REQUIRE( (int)(*it) == expected[i] );
        } 
    }
    
    SECTION("Test Inversion"){
       int expected[] = {0, 0, 255, 0, 0, 255, 255, 255, 255};
        
        Image ans = !img1;
        int i = 0;
        for(Image::iterator it = ans.begin(); it != ans.end(); ++it, i++){
            REQUIRE( (int)(*it) == expected[i] );
        } 
    }
    
    SECTION("Test Masking"){
       int expected[] = {0, 0, 0, 0, 255, 0, 0, 0, 0};
        
        Image ans = img1 / img2;
        int i = 0;
        for(Image::iterator it = ans.begin(); it != ans.end(); ++it, i++){
            REQUIRE( (int)(*it) == expected[i] );
        } 
    }
    
    SECTION("Test Thresholding"){
       int expected[] = {255, 255, 0, 255, 255, 0, 0, 0, 0};
        
        Image ans = img1 * 100;
        int i = 0;
        for(Image::iterator it = ans.begin(); it != ans.end(); ++it, i++){
            REQUIRE( (int)(*it) == expected[i] );
        } 
    }   
}

TEST_CASE("Test image class move/copy semantics", "[operators]"){
    uchar* buffer1 = new uchar[9];
    buffer1[0] = (uchar)255;
    buffer1[1] = (uchar)255;
    buffer1[2] = (uchar)0;
    buffer1[3] = (uchar)255;
    buffer1[4] = (uchar)255;
    buffer1[5] = (uchar)0;
    buffer1[6] = (uchar)0;
    buffer1[7] = (uchar)0;
    buffer1[8] = (uchar)0;
    Image img1(3, 3, &buffer1);
    
    SECTION("Test Move Construction"){
        //so we know img1 is valid
        REQUIRE( img1.getWidth() == 3 );
        REQUIRE( img1.getHeight() == 3 );
        
        //now move construct img2 using img1
        Image img2(std::move(img1));
        
        //img2 should now be valid
        REQUIRE( img2.getWidth() == 3 );
        REQUIRE( img2.getHeight() == 3 );
        
        //and img1 should be empty and cleaned up
        REQUIRE( img1.getWidth() == 0 );
        REQUIRE( img1.getHeight() == 0 );
    }
    
     SECTION("Test Copy Construction"){
        //check that img1 is valid
        REQUIRE( img1.getWidth() == 3 );
        REQUIRE( img1.getHeight() == 3 );
        
        //now copy construct img2 using img1
        Image img2(img1);
        
        //img2 should now be valid
        REQUIRE( img2.getWidth() == 3 );
        REQUIRE( img2.getHeight() == 3 );
        
        //and img1 should also still be valid
        REQUIRE( img1.getWidth() == 3 );
        REQUIRE( img1.getHeight() == 3 );
    }
    
    SECTION("Test Move Assignment"){
        //check that img1 is valid
        REQUIRE( img1.getWidth() == 3 );
        REQUIRE( img1.getHeight() == 3 );
        
        //now construct img2 and move assign img1 into img2
        Image img2;
        img2 = std::move(img1);
        
        //img2 should now be valid
        REQUIRE( img2.getWidth() == 3 );
        REQUIRE( img2.getHeight() == 3 );
        
        //and img1 should be empty and cleaned up
        REQUIRE( img1.getWidth() == 0 );
        REQUIRE( img1.getHeight() == 0 );
    }
    
    SECTION("Test Copy Assignment"){
        //check that img1 is valid
        REQUIRE( img1.getWidth() == 3 );
        REQUIRE( img1.getHeight() == 3 );
        
        //now construct img2 and copy assign img1 into img2
        Image img2;
        img2 = img1;
        
        //img2 should now be valid
        REQUIRE( img2.getWidth() == 3 );
        REQUIRE( img2.getHeight() == 3 );
        
        //and img1 should also still be valid
        REQUIRE( img1.getWidth() == 3 );
        REQUIRE( img1.getHeight() == 3 );
    }
}
