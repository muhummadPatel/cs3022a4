/*
 * Image class header file. This file defines the Image class and a few related 
 * helper functions. The image class is used to read in, store, manipulate, and
 * save pgm images. It defines a number of operations that can be performed 
 * on/between image objects including: addition, subtraction, masking, 
 * inversion, and thresholding. The image class also contains a nested iterator
 * class that allows for easy access to the individual pixels in the represented
 * image. The iterator is fully functional.
 *
 * Muhummad Patel
 * 28-Apr-2015
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>

namespace ptlmuh006{
    
    typedef unsigned char uchar;
    
    //Image class to read, manipulate, and save binary pgm images.
    class Image{
    
        //friended functions to allow for stream operator overloading
        friend std::ostream& operator<<(std::ostream& os,const Image& img);
        friend std::istream& operator>>(std::istream& is, Image& img);
    
        private:
            std::string imageName; //name of the image being stored
            std::string header; //image header
            int width, height; //dimensions of the image
            std::unique_ptr<uchar[]> data; //the pixel data of the image
        
        public:
            Image();                            //default constructor
            Image(const Image& other);          //copy constructor
            Image(Image&& other);               //move constructor
            ~Image();                           //destructor
            Image& operator= (const Image& rhs);//copy assignment
            Image& operator= (Image&& rhs);     //move assignment
            
            void load(std::string filename); //load image with the given filename
            void save(std::string outfilename); //save image data to file with given name
            
            Image operator+(const Image& rhs) const; //add two images
            Image operator-(const Image& rhs) const; //subtract images
            Image operator!() const; //invert an image
            Image operator/(const Image& rhs) const; //mask an image with another
            Image operator*(const int threshold) const; //threshold an image by given int
            
        
        public:
            //nested iterator class to allow easy access to image pixel data
            class iterator{
                //friend the image class to allow for access to private members
                friend class Image;
                
                private:
                    uchar* ptr; //actual pointer to the current pixel
                    iterator(u_char *p) : ptr(p) {} //constructor (only called by Image::begin())
                    
                public:
                    //copy construct is public
                    iterator( const iterator & rhs) : ptr(rhs.ptr) {}
                    
                    //overloaded operators
                    iterator& operator=(const iterator& rhs); //copy assignment
                    iterator& operator=(iterator&& rhs); //move assignment
                    uchar& operator*();             //dereference
                    const iterator& operator++();   //prefix ++
                    const iterator& operator--();   //prefix --
                    bool operator==(const iterator& rhs); //equality
                    bool operator!=(const iterator& rhs); //inequality
            };
            
            iterator begin(void) const; //iterator to start of pixel data
            iterator end() const; //one past the last valid position
    };
    
    int clamp(int num); //clamps the number to range [0, 255]
    
    //overloaded stream operators
    std::ostream& operator<<(std::ostream& os, const Image& img);
    std::istream& operator>>(std::istream& is, Image& img);
}

#endif
