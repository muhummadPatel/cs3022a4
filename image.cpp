/*
 * Image class implementation. This file implemnts the classes and functions 
 * that were defined in the Image.h header file.
 *
 * Muhummad Patel
 * 28-Apr-2015
 */

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#include "image.h"

namespace ptlmuh006{
    
    using namespace std;

    //default constructor for image class
    Image::Image():imageName(""), header(""), width(0), height(0), data(nullptr){
    }
    
    //copy constructor for image class
    Image::Image(const Image& other){
        imageName = other.imageName;
        header = other.header;
        width = other.width;
        height = other.height;
        
        //copy over the data
        data = unique_ptr<uchar[]>(new uchar[other.width * other.height]);
        for(Image::iterator othI = other.begin(), thiI = begin(); othI != other.end(); ++othI, ++thiI){
            *thiI = *othI;
        }
    }
    
    //move constructor for image class
    Image::Image(Image&& other){
        imageName = other.imageName;
        header = other.header;
        width = other.width;
        height = other.height;
        
        //move over the data
        data = unique_ptr<uchar[]>(new uchar[other.width * other.height]);
        for(Image::iterator othI = other.begin(), thiI = begin(); othI != other.end(); ++othI, ++thiI){
            *thiI = *othI;
        }
        
        other.imageName = "";
        other.header = "";
        other.width = 0;
        other.height = 0;
        other.data = nullptr;
    }
    
    //destructor
    Image::~Image(){
    }
    
    //copy assignment for image class
    Image& Image::operator=(const Image& other){
        imageName = other.imageName;
        header = other.header;
        width = other.width;
        height = other.height;
        
        //copy over the data;
        data = unique_ptr<uchar[]>(new uchar[other.width * other.height]);
        for(Image::iterator othI = other.begin(), thiI = begin(); othI != other.end(); ++othI, ++thiI){
            *thiI = *othI;
        }
    }
    
    //move assignment for image class
    Image& Image::operator=(Image&& other){
        imageName = other.imageName;
        header = other.header;
        width = other.width;
        height = other.height;
        
        //move over the data
        data = unique_ptr<uchar[]>(new uchar[other.width * other.height]);
        for(Image::iterator othI = other.begin(), thiI = begin(); othI != other.end(); ++othI, ++thiI){
            *thiI = *othI;
        }
        
        other.imageName = "";
        other.header = "";
        other.width = 0;
        other.height = 0;
        other.data = nullptr;
    }
    
    //Function to load in the pgm image with the given file name
    void Image::load(string filename){
        //open the file
        ifstream infile(filename, ios::in|ios::binary);
        
        imageName = filename;
        
        //read in the header
        string line;
        getline(infile, line);
        cout << imageName << endl;
        header += line + "\n";
        
        getline(infile, line);
        while(line[0] == '#'){
            cout << line << endl;
            
            header += line + "\n";
            
            getline(infile, line);
        }
        
        //read in the dimensions
        istringstream dimensions(line);
        dimensions >> width;
        dimensions >> height;
        cout << "height " << height << endl;
        cout << "width " << width << endl;
        
        //read in and discard the 255
        int range;
        infile >> range >> ws;
        
        //read in the pixel data
        data = unique_ptr<uchar[]>(new uchar[width * height]);
        infile.read((char*)data.get(), width * height);
        
        //close the original file
        infile.close();
    }
    
    //function to save the pixel data stored in this object to a pgm image file
    void Image::save(string outfilename){
        //open output file
        ofstream outfile(outfilename, ios::out|ios::binary);
        
        //write header data
        outfile << header;
        outfile << width << " " << height << endl;
        outfile << 255 << endl;
        
        //write pixel data
        outfile.write((char*)data.get(), width * height);
        
        //flush and close output file
        outfile.close();
    }
    
    //Add operator to add two image objects together
    Image Image::operator+(const Image& rhs) const{
        //only allow the operation if they have the same dimensions
        if(width == rhs.width && height == rhs.height){
        
            //add two images pixel by pixel and return new image with the answer
            Image ans(*this);
            for(Image::iterator aI = ans.begin(), rI = rhs.begin(); rI != rhs.end(); ++aI, ++rI){
                *aI = (uchar)clamp((int)(*aI) + (int)(*rI));
            }
            
            return ans;
        }else{
            //if wrong dimensions, exit the program with error status
            exit(1);
        }
    }
    
    //Subtracg operator to subtract one image from another
    Image Image::operator-(const Image& rhs) const{
        //only allow this operation if the images have the same dimensions
        if(width == rhs.width && height == rhs.height){
            //subtract pixel by pixel and return new image object with the answer
            Image ans(*this);
            for(Image::iterator aI = ans.begin(), rI = rhs.begin(); rI != rhs.end(); ++aI, ++rI){
                *aI = (uchar)clamp((int)(*aI) - (int)(*rI));
            }
            
            return ans;
        }else{
            //exit with error because of non-matching dimensions
            exit(1);
        }
    }
    
    //Invert operator to invert a single image
    Image Image::operator!() const{
        //return a new image where each pixel is 255 - original pixel value
        Image ans(*this);
        for(Image::iterator thiI = begin(), aI = ans.begin(); thiI != end(); ++thiI, ++aI){
            *aI = (uchar)clamp(255 - (int)(*thiI));
        }
        
        return ans;
    }
    
    //Mask one image with another
    Image Image::operator/(const Image& rhs) const{
        //only allow for images with equal dimensions
        if(width == rhs.width && height == rhs.height){
            
            //copy over the pixels where the mask is white and return this new image
            Image ans(rhs);
            for(Image::iterator aI = ans.begin(), thiI = begin(); thiI != end(); ++aI, ++thiI){
                if((int)(*aI) == 255){
                    *aI = (uchar)clamp((int)(*thiI));
                }
            }
            
            return ans;
        }else{
            exit(1);
        }
    }
    
    //Threshold operator that operates on an image
    Image Image::operator*(const int threshold) const{
        //return new image with either black or white pixel based on threshold value
        Image ans(*this);
        for(Image::iterator thiI = begin(), aI = ans.begin(); thiI != end(); ++thiI, ++aI){
            if((int)(*aI) > threshold){
                *aI = (uchar)255;
            }else{
                *aI = (uchar)0;
            }
        }
        
        return ans;
    }
    
    //overloaded ostream operator. Allows us to push the pgm into ostream objects
    ostream& operator<<(ostream& os,const Image& img){
        os << img.header;
        os << img.width << " " << img.height << endl;
        os << 255 << endl;
        os.write((char*)img.data.get(), img.width * img.height);
        
        return os;
    }
    
    //overloaded istream operator. Allows us to pull in an image from an istream
    istream& operator>>(istream& is, Image& img){
        string line;
        getline(is, line);
        img.header += line + "\n";
        
        getline(is, line);
        while(line[0] == '#'){            
            img.header += line + "\n";
            
            getline(is, line);
        }
        
        istringstream dimensions(line);
        dimensions >> img.width;
        dimensions >> img.height;
        
        int range;
        is >> range >> ws;
        
        img.data = unique_ptr<uchar[]>(new uchar[img.width * img.height]);
        is.read((char*)img.data.get(), img.width * img.height);
        
        return is;
    }
    
    //returns an Image::iterator object ponting to the first pixel
    Image::iterator Image::begin(void) const{
        return iterator(data.get());
    }
    
    //returns an Image::iterator object pointing to one past the last valid pixel
    Image::iterator Image::end() const{
        return iterator(&data[width * height]);
    }
    
    
    //ITERATOR-----------------------------------------------------------------
    
    //copy assignment for iterator class
    Image::iterator& Image::iterator::operator=(const Image::iterator& rhs){
       ptr = rhs.ptr;
    }
    
    //move assignment for iterator class
    Image::iterator& Image::iterator::operator=(Image::iterator&& rhs){
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
    }
    
    //dereference operator for iterator class
    uchar& Image::iterator::operator*(){
        return *ptr;
    }
    
    //prefix ++
    const Image::iterator& Image::iterator::operator++(){
        ptr += 1;
        return *this;
    }
    
    //prefix --
    const Image::iterator& Image::iterator::operator--(){
        ptr -= 1;
        return *this;
    }
    
    //equality operator
    bool Image::iterator::operator==(const Image::iterator& rhs){
        return (ptr == rhs.ptr);
    }
    
    //inequality operator
    bool Image::iterator::operator!=(const Image::iterator& rhs){
        return (ptr != rhs.ptr);
    }
    
    //returns num clamped to the range [0, 255]
    int clamp(int num){
        if(num < 0){
            num = 0;
        }else if(num > 255){
            num = 255;
        }
        
        return num;
    }
}
