# Part4. Variable Scope and More Types
## Global scope operator (`::`)
``` C++
#include <iostream>
int value(5); // global variable
 
int main()
{
    int value = 7; // hides the global variable value
    value++; // increments local value, not global value
    ::value--; // decrements global value, not local value
 
    std::cout << "global value: " << ::value << "\n";
    std::cout << "local value: " << value << "\n";
    return 0;
} // local value is destroyed
```
## Internal and external linkage via the static and extern keywords
- **Internal variable**(or static variable) -  can be used anywhere within the file
    ```C++
    static int g_x; //static, and can only be used within this file
    int main()
    {
        return 0;
    }
    ```
- **External variable**(or static variable) -  can be used anywhere within all files
    ```C++
    extern double g_y(9.8); 
    // g_y is external
    // Note: those other files will need to use a forward declaration
    ```
- **non-const variables** declared outside of a function are assumed to be **external**
- **const variables** declared outside of a function are assumed to be **internal**
## Forward declarations
- `extern` keyword without initialization
    ```C++
    extern int g_y;
    ```
## Global symbolic constants
- A bad version - duplicated when included by multi-files
    ```C++
    #ifndef CONSTANTS_H
    #define CONSTANTS_H
    // define your own namespace to hold constants
    namespace Constants
    {
        const double pi(3.14159);
        const double avogadro(6.0221413e23);
        const double my_gravity(9.2);
    }
    #endif
    ```
- Good Version - external linkage
    ```C++
    //constant.h
    namespace Constants
    {
        // actual global variables
        extern const double pi;
        extern const double avogadro;
        extern const double my_gravity; 
    }
    ```
    ```C++
    //constant.cpp
    #include "constants.h"
    extern const double Constants::pi(3.14159);
    extern const double Constants::avogadro(6.0221413e23);
    extern const double Constants::my_gravity(9.2); 
    ```
## Namespace
- Normal
    ```C++
    namespace Foo
    {
        int doSomething(int x, int y)
        {
            return x + y;
        }
    }
    ```
- Nested
    ```C++
    namespace Foo
    {
        namespace
        {
            const int g_x = 5;
        }
    }
    ```
- Aliases
    ```C++
    namespace Boo = Foo::Goo;
    ``` 
## `std::string`
- Init
  ```C++
  #include <string>
  std::string myName("Alex");
  myName = "John";
  ```
- I/O
- Combine `std::cin` and `std::getline`
  ```C++
  #include <string>
  #include <iostream>
  
  int main()
  {
      std::cout << "Pick 1 or 2: ";
      int choice { 0 };
      std::cin >> choice;
      //std::cin.ignore(32767, '\n'); // ignore up to 32767 characters until a \n is removed

      std::cout << "Now enter your name: ";
      std::string name;
      std::getline(std::cin, name);
  
      std::cout << "Hello, " << name << ", you picked " << choice << '\n';
  
      return 0;
  }
  ```
- With out `std::cin.ignore(32767,'\n');`, the `std::cin` will catch the `\n` but instead of being captured in the `choice`, it is stuck in the input stream. When the `std::getline` is called, it is extracted.
- As a result, here is the i/o pair
  > Input:  
  > 1  
  > Joy  
  > Output:  
  > 1  
  > `\n`
- Technically right one
  ```C++
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore unlimited characters until a \n is removed
  ```
## Enumerator values
-  Special cases
    ```C++
    enum Animal
    {
        ANIMAL_CAT = -3,
        ANIMAL_DOG, // assigned -2
        ANIMAL_PIG, // assigned -1
        ANIMAL_HORSE = 5,
        ANIMAL_GIRAFFE = 5, // shares same value as ANIMAL_HORSE
        ANIMAL_CHICKEN // assigned 6
    }
    ```
- Enum class - **Strong Type**
    ```C++
    enum class Color
    {
        RED,BLUE
    }
    std::cout << Color::RED<<std::endl;
    ```
## Typedefs and type alias
- typedef
    ```C++
    typedef double distance_t;
    ```
- type alias
    ```C++
    using distance_t = double;
    ```
## Struct
- Type
    ```C++
    struct Employee
    {
        short id;
        int age;
        double wage;
    };
    ```
- Initializing structs
    ```C++
    Employee joe = { 1, 32, 60000.0 }; // joe.id = 1, joe.age = 32, joe.wage = 60000.0
    Employee frank = { 2, 28 }; // frank.wage = 0.0 (default initialization)
    ```
- Non static member initialization
- incompatible with the initializer list (C++11)
    ```C++
    struct Rectangle
    {
        double length = 1.0;
        double width = 1.0;
    };

    int main()
    {
        Rectangle x; // length = 1.0, width = 1.0

        // uniform initialization 
        // not allowed with non-static initialization
        //Rectangle x{ 2.0, 2.0 }; 
        
        x.length = 2.0; // you can assign other values like normal

        return 0;
    }
    ```
- Struct size and data alignment
    ```C++
    struct Employee
    {
        short id; // size 2
        int age;  // size 4
        double wage;// size 8
    };//size 16!=2+4+8
    ```
##  The auto keyword (C++11)
- `auto`
    ```C++
    auto d = 5.0; 
    auto i = 1 + 2;
    ```
- Trailing return type syntax in C++11
    ```C++
    //int add(int x, int y);
    auto add(int x, int y) -> int;
    ```
  

