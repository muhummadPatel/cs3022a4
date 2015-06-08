##Assignment 4 - _Operator Overloading and Iterators: Image Manipulation_

**Author** : Muhummad Yunus Patel  
**Student#** : PTLMUH006  
**Date** : 28-Apr-2015

###Usage:
Please have the neccessary files in the same directory when running.

./imageops <option>  
**Options:**

* -a i1 i2 \(add i1 and i2\)
* -s i1 i2 \(subtract i2 from i1\)
* -i i1	\(invert i1\)
* -l i1 i2 \(mask i1 with i2\)
* -t i1 f \(threshold i1 with integer value f\)

**Compiling:**

* To compile the executable, simply type _make_.
* To run, _./imageops <option>_.
* To clean up, type _make clean_.

To compile and run the tests, type _make test_.

Should you require any further clarification regarding this submission, please
feel free to contact me at muhummad.patel@gmail.com. Thank you. :\)

###Description:
A description of what each file does and how it fits into the program follows:

1. **image.h:**  
    This header file define the Image class and some related helper functions.
    The Image::iterator class is also defined here. All member functions of these
    classes \(including the overloaded operators\) are defined in this header file.
    This header file also defines some helper functions viz. clamp \(clamps the 
    given int to range \[0, 255\]\), and the overloaded stream operators for the 
    Image class.  
    
2. **image.cpp:**  
    This is the implementation file for the Image and Image::iterator classes
    defined in image.h. All constructors, operators, and associated functions
    are implemented here. All requested operations have been overloaded \(viz.
    add, subtract, invert, mask, and threshold\). Note, filtering has not been
    implemented. Mote also that the requested overloaded stream operators >> and
    << *have* been implemented. All of the operations have been defined, as 
    requested, using the Image::iterator class.  
    
3. **driver.cpp:**  
    This is the driver file. It contains the main method that is run when the 
    program is executed. Handles user input and executes the appropriate option.  
    
4. **test.cpp:**  
    This file contains the implementation of the unit-tests that were requested
    as part of this assignment specification. All operators, and the move/copy
    semantics were thoroughly tested. Note that because, the iterator class was
    used to define the add, subtract, invert, mask, and threshold operators, they
    too are being tested implicitly in the tests for those operators.