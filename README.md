# CPP-Rev
Advanced C++ and C++11 new feature review/training. Reviewing C++ with the intention of penetrating into CG. Thus basic function will not be involved in this review.
## Part1. Intro
- Compile and link
   - Procedure   
     ![img](./img/Img01-Procedure.png)
   - Compile  
     ![img](./img/Img02-Complie.png)  
     - Compiler checks the code whether it follows the rules of the C++ language.  
     - Then translate the C++ source code into a machine language (.o)
   - Link  
     ![img](./img/Img03-Link.png)  
     - Combine generated obj files into an executable one.
     - Add on a library file <- C++ STL
## Part2. Basics
1. Variables
   - l-value and r-value  
      **l-value** has a persistent addr while opposite for **r-value**   
      ``` C++
      int y;      // define y as an integer variable
      y = 4;      // r-value 4 evaluates to 4, which is then assigned to l-value y
      y = 2 + 5;  // r-value 2 + r-value 5 evaluates to r-value 7, which is then assigned to l-value y
      
      int x;      // define x as an integer variable
      x = y;      // l-value y evaluates to 7 (from before), which is then assigned to l-value x.
      x = x;      // l-value x evaluates to 7, which is then assigned to l-value x (useless!)
      x = x + 1;  // l-value x + r-value 1 evaluate to r-value 8, which is then assigned to l-value x.
      ```
2. Keywords and indentifier
   ![img](./img/Img04-Keywords.png)
   - `*` for C++98
   - `**` for C++11
3. MutiFiles
   - It will work.
     - `main.cpp`
        ```C++
        #include <iostream>
        int add(int x, int y); //need in main.cpp
        int main()
        {
          std::cout << "The sum of 3 and 4 is: " << add(3, 4) << std::endl;
          return 0;
        }
        ```
     - `add.cpp`
        ```C++
        int add(int x, int y)
        {
          return x + y;
        }
        ```
4. Headfiles
   1. First, header guard
      ```C++
      #ifndef ADD_H //any unique name
      #define ADD_H //if not define, define it to prevent multi-define
      //TODO:
      #endif
      ``` 
   2. However, consider the another file `addB.cpp` with `add` function. 
   3. Link Error: multiple `add` function.------->Solution : `namespace`
      - `main.cpp`
        ```C++
        #include <iostream>
        #include "addA.h"
        #include "addB.h"
        int main()
        {
          std::cout << "The sum of 3 and 4 is: " << A::add(3, 4) << std::endl;
          std::cout << "The sum of 3 and 4 is: " << B::add(3, 4) << std::endl;
          system("pause");
          return 0;
        }
        ```
      - `addA.h`
        ```C++
        namespace A
        {
          int add(int x, int y);
        }
        ```
      - `addA.cpp`
        ```C++
        #include "addA.h"

        int A::add(int x, int y)
        {
          return 0;
        }
        ```
      - `addB.h`
        ```C++
        namespace B
        {
          int add(int x, int y);
        }
        ```
      - `addB.cpp`
        ```C++
        #include "addB.h"
        int B::add(int x, int y)
        {
          return x + y;
        }
        ```
   4. Why do we include `.h` instread of `.cpp`? [See reference](https://stackoverflow.com/questions/19547091/including-cpp-files)
        - What `include` does is copying all the contents from the file included.
        - Example:
           ```C++
           int foo(int a){ // from include "foop.cpp"
           return ++a;
           }
           int main(int argc, char *argv[])
           {
             int x=42;
             std::cout << x <<std::endl;
             std::cout << foo(x) << std::endl;
             return 0;
           }
           ```
         - Thus, `foo` function exists in both main.cpp and foop.cpp, duplicated.
    5. `< >` or `" "`?
        - Use angled brackets `< >` to include header files that come with the compiler. 
        - Use double quotes `" "` to include any other header files.

   




## Reference
Learning within online course is not recommended(basically time-consuming). It's better to read reference material if you have a programming foundation. As for the material, here you go.
* [LearnCPP.com](https://www.learncpp.com/cpp-tutorial/introduction-to-cplusplus/)
   