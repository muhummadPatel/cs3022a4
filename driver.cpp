#include <iostream>
#include <fstream>

#include "image.h"

using namespace ptlmuh006;

int main(int argc, char* argv[]){
    std::cout << "imageops running" << std::endl;
    Image i1;
    
    std::ifstream ifs("shrek_rectangular.pgm");
    ifs >> i1;
    
    std::ofstream ofs("croc1.pgm");
    ofs << i1;
    
    /*i1.load("shrek_rectangular.pgm");
    Image i2;
    i2.load("donkey_mask.pgm");
    
    Image sum = i1 + i2;
    sum.save("sum.pgm");
    
    Image diff = i1 - i2;
    diff.save("diff.pgm");
    
    Image inv = !i1;
    inv.save("inv.pgm");
    
    Image msk = i1 / i2;
    msk.save("msk.pgm");
    
    Image lenna;
    lenna.load("Lenna_standard.pgm");
    Image thr = lenna * 100;
    thr.save("thr.pgm");
    */
    return 1;
}
