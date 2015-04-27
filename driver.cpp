#include <iostream>
#include <string>

#include "image.h"

void printUsage(){
    using namespace std;
    
    cout << "imageops Usage:__________" << endl;
    cout << "imageops <option> outputImageName.pgm" << endl;
    cout << "\tOptions:___" << endl;
    cout << "\t-a i1 i2\t(add i1 and i2)" << endl;
    cout << "\t-s i1 i2\t(subtract i2 from i1)" << endl;
    cout << "\t-i i1\t\t(invert i1)" << endl;
    cout << "\t-l i1 i2\t(mask i1 with i2)" << endl;
    cout << "\t-t i1 f\t\t(threshold i1 with integer value f)" << endl;
}

int main(int argc, char* argv[]){
    using namespace ptlmuh006;
    
    if(argc == 5){
        //we need to do one of the binary operations
        if(argv[1] == "-a"){
            //add
            std::string infile1 = argv[2];
            std::string infile2 = argv[3];
            std::string outfilename = argv[4];
            
            Image i1; i1.load(infile1);
            Image i2; i2.load(infile2);
            Image out = i1 + i2;
            out.save(outfilename);
            
            std::cout << infile1 << " added to " << infile2 << "." << std::endl;
            std::cout << "Result saved to " << outfilename << "." << std::endl;
        }else if(argv[1] == "-s"){
            //subtract
            std::string infile1 = argv[2];
            std::string infile2 = argv[3];
            std::string outfilename = argv[4];
            
            Image i1; i1.load(infile1);
            Image i2; i2.load(infile2);
            Image out = i1 - i2;
            out.save(outfilename);
            
            std::cout << infile2 << " subtracted from " << infile1 << "." << std::endl;
            std::cout << "Result saved to " << outfilename << "." << std::endl;
        }else if(argv[1] == "-l"){
            //mask
            std::string infile1 = argv[2];
            std::string infile2 = argv[3];
            std::string outfilename = argv[4];
            
            Image i1; i1.load(infile1);
            Image i2; i2.load(infile2);
            Image out = i1 / i2;
            out.save(outfilename);
            
            std::cout << infile1 << " masked with " << infile2 << "." << std::endl;
            std::cout << "Result saved to " << outfilename << "." << std::endl;
        }else if(argv[1] == "-t"){
            //threshold
            std::string infilename = argv[2];
            int threshold = std::stoi(argv[3]);
            std::string outfilename = argv[4];
            
            Image src; src.load(infilename);
            Image out = src * threshold;
            out.save(outfilename);
            
            std::cout << "Thresholded " << infilename << " with " << threshold << "." << std::endl;
            std::cout << "Result saved to " << outfilename << "." << std::endl;
        }else{
            //incorrect usage
            printUsage();
        }
        
    }else if(argc == 4){
        if(argv[1] == "-i"){
            //we need to invert the given image
            std::string infilename = argv[2];
            std::string outfilename = argv[3];
            
            Image src; src.load(infilename);
            Image out = !src;
            out.save(outfilename);
            
            std::cout << "Inverted " << infilename << "." << std::endl;
            std::cout << "Result saved to " << outfilename << "." << std::endl;
        }else{
            //incorrect usage
            printUsage();
        }
    }else{
        //missing argument/s
        printUsage();
    }
    
    return 0;
}
