#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>

namespace ptlmuh006{
    
    typedef unsigned char uchar;
    
    class Image{
    
        friend std::ostream& operator<<(std::ostream& os,const Image& img);
        friend std::istream& operator>>(std::istream& is, Image& img);
    
        private:
            std::string imageName;
            std::string header;
            int width, height;
            std::unique_ptr<uchar[]> data;
        
        public:
            Image();                            //default constructor
            Image(const Image& other);          //copy constructor
            Image(Image&& other);               //move constructor
            ~Image();                           //destructor
            Image& operator= (const Image& rhs);//copy assignment
            Image& operator= (Image&& rhs);     //move assignment
            
            void load(std::string filename);
            void save(std::string outfilename);
            
            Image operator+(const Image& rhs) const;
            Image operator-(const Image& rhs) const;
            Image operator!() const;
            Image operator/(const Image& rhs) const;
            Image operator*(const int threshold) const;
            
        
        public:
            class iterator{
                friend class Image;
                
                private:
                    uchar* ptr;
                    iterator(u_char *p) : ptr(p) {}
                    
                public:
                    //copy construct is public
                    iterator( const iterator & rhs) : ptr(rhs.ptr) {}
                    
                    // define overloaded ops: *, ++, --, =
                    iterator& operator=(const iterator& rhs);
                    iterator& operator=(iterator&& rhs);
                    uchar& operator*();             //dereference
                    const iterator& operator++();   //prefix ++
                    const iterator& operator--();   //prefix --
                    bool operator==(const iterator& rhs);
                    bool operator!=(const iterator& rhs);
                    
                    // other methods for iterator
            };
            iterator begin(void) const;
            iterator end() const;
    };
    
    int clamp(int num);
    std::ostream& operator<<(std::ostream& os, const Image& img);
    std::istream& operator>>(std::istream& is, Image& img);
}

#endif
