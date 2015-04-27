#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#include "image.h"

namespace ptlmuh006{
    
    using namespace std;

    Image::Image():imageName(""), header(""), width(0), height(0), data(nullptr){
    }
    
    //copy constructor
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
    
    //move constructor
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
        //nothing to do really right?
    }
    
    //copy assignment
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
    
    //move assignment
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
    
    void Image::load(string filename){
        ifstream infile(filename, ios::in|ios::binary);
        
        imageName = filename;
        
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
        
        istringstream dimensions(line);
        dimensions >> width;
        dimensions >> height;
        cout << "height " << height << endl;
        cout << "width " << width << endl;
        
        int range;
        infile >> range >> ws;
        
        data = unique_ptr<uchar[]>(new uchar[width * height]);
        infile.read((char*)data.get(), width * height);
        
        infile.close();
    }
    
    void Image::save(string outfilename){
        ofstream outfile(outfilename, ios::out|ios::binary);
        
        outfile << header;
        outfile << width << " " << height << endl;
        outfile << 255 << endl;
        outfile.write((char*)data.get(), width * height);
        
        outfile.close();
    }
    
    Image Image::operator+(const Image& rhs) const{
        if(width == rhs.width && height == rhs.height){
            Image ans(*this);
            for(Image::iterator aI = ans.begin(), rI = rhs.begin(); rI != rhs.end(); ++aI, ++rI){
                *aI = (uchar)clamp((int)(*aI) + (int)(*rI));
            }
            
            return ans;
        }else{
            exit(1);
        }
    }
    
    Image Image::operator-(const Image& rhs) const{
        if(width == rhs.width && height == rhs.height){
            Image ans(*this);
            for(Image::iterator aI = ans.begin(), rI = rhs.begin(); rI != rhs.end(); ++aI, ++rI){
                *aI = (uchar)clamp((int)(*aI) - (int)(*rI));
            }
            
            return ans;
        }else{
            exit(1);
        }
    }
    
    Image Image::operator!() const{
        Image ans(*this);
        for(Image::iterator thiI = begin(), aI = ans.begin(); thiI != end(); ++thiI, ++aI){
            *aI = (uchar)clamp(255 - (int)(*thiI));
        }
        
        return ans;
    }
    
    Image Image::operator/(const Image& rhs) const{
        if(width == rhs.width && height == rhs.height){
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
    
    Image Image::operator*(const int threshold) const{
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
    
    ostream& operator<<(ostream& os,const Image& img){
        os << img.header;
        os << img.width << " " << img.height << endl;
        os << 255 << endl;
        os.write((char*)img.data.get(), img.width * img.height);
        
        return os;
    }
        
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
    
    
    
    
    
    
    
    Image::iterator Image::begin(void) const{
        return iterator(data.get());
    }
    
    Image::iterator Image::end() const{
        return iterator(&data[width * height]);
    }
    
    //copy assignment
    Image::iterator& Image::iterator::operator=(const Image::iterator& rhs){
       ptr = rhs.ptr;
    }
    
    //move assignment
    Image::iterator& Image::iterator::operator=(Image::iterator&& rhs){
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
    }
    
    //dereference operator
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
    
    int clamp(int num){
        if(num < 0){
            num = 0;
        }else if(num > 255){
            num = 255;
        }
        
        return num;
    }
}
