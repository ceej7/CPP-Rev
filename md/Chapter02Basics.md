## Part2. Basics
1. Variables
   - l-value and r-value  
      **l-value** has a persistent addr while opposite for **r-value**   
      ``` C++
      int y;      // define y as an integer variable
      y = 4;      // r-value 4 evaluates to 4, which is then assigned to l-value y
      int x;      // define x as an integer variable
      x = y;      // l-value y evaluates to 4 (from before), which is then assigned to l-value x.
      ```
2. Keywords and indentifier
   ![img](../img/Img04-Keywords.png)
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
   - First, header guard
      ```C++
      #ifndef ADD_H //any unique name
      #define ADD_H //if not define, define it to prevent multi-define
      //TODO:
      #endif
      ``` 
      - Note: the macro's scope is within the single file and preprocessed
      - Thus: it prevents multi defining in single file not in the whole proj
      - Alternative
        ```C++
        #pragma once
        ```
   - However, consider the another file `addB.cpp` with `add` function. 
   - Link Error: multiple `add` function.------->Solution : `namespace`
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
   - Why do we include `.h` instread of `.cpp`? [See reference](https://stackoverflow.com/questions/19547091/including-cpp-files)
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
    - `< >` or `" "`?
        - Use angled brackets `< >` to include header files that come with the compiler. 
        - Use double quotes `" "` to include any other header files.
