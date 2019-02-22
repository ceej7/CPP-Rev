## Part6. Arrays, Strings, Pointers, and References
1. Array
   1. Declaration
        ```C++
        int testScore[30]
        //name + brackets + arraylength
        ```
   2. Fixed length array declarations
       ```C++
       // using a literal constant
       int array[5]; // Ok
       
       // using a symbolic constant
       const int arrayLength = 5;
       int array[arrayLength]; // Ok
       
       // using an enumerator
       enum ArrayElements
       {
           MAX_ARRAY_LENGTH = 5
       };
       int array[MAX_ARRAY_LENGTH]; // Ok
       ```
   3. Array and enums
      1. plain enums
            ```C++
            enum StudentNames
            {
                KENNY, // 0
                KYLE, // 1
                STAN, // 2
                BUTTERS, // 3
                CARTMAN, // 4
                MAX_STUDENTS // 5
            };
            
            int main()
            {
                int testScores[MAX_STUDENTS]; // allocate 5 integers
                testScores[STAN] = 76;
            
                return 0;
            }
            ```
      2. enums class  
            Enum classes don’t have an implicit conversion to integer
            ```C++
            enum class StudentNames
            {
                KENNY, // 0
                KYLE, // 1
                STAN, // 2
                BUTTERS, // 3
                CARTMAN, // 4
                WENDY, // 5
                MAX_STUDENTS // 6
            };
            
            int main()
            {
                int testScores[StudentNames::MAX_STUDENTS]; // compile error!!
                testScores[StudentNames::STAN] = 76;
            
                return 0;
            }
            ```
      3. First way to fix
            ```C++
            (StudentNames::MAX_STUDENTS)]; // allocate 6 integers
            ```
      4. Better one
            ```C++
            namespace StudentNames
            {
                enum StudentNames
                {
                    KENNY, // 0
                    KYLE, // 1
                    STAN, // 2
                    BUTTERS, // 3
                    CARTMAN, // 4
                    WENDY, // 5
                    MAX_STUDENTS // 6
                };
            }
            
            int main()
            {
                int testScores[StudentNames::MAX_STUDENTS]; // allocate 6 integers
                testScores[StudentNames::STAN] = 76;
            
                return 0;
            }
            ```
    4. Sizeof and arrays
        ```C++
        void printSize(int array[])
        {
            std::cout << sizeof(array) << '\n'; // prints the size of a pointer, not the size of the array!
        }
        
        int main()
        {
            int array[] = { 1, 1, 2, 3, 5, 8, 13, 21 };
            std::cout << sizeof(array) << '\n'; // will print the size of the array
            printSize(array);
        
            return 0;
        }
        ```
        - When array is passed into a function, `sizeof` will give the length of a pointer
    5. Multidimensional arrays
       - `int mAry[5][5]`
2. C-style strings
    - null-terminated (`\0`) string
    - Manipulating C-style strings
      - strcpy(dest, source); //overflow
      - strncpy(dest, source,n);//not null-terminated
3. Pointers
   1. Intro to pointer
      1. The address-of operator (&)
      2. The dereference operator (*)
      3. Assigning a value to a pointer
            ```C++
            int value = 5;
            int *ptr = &value;
            ```
   2. Null pointer
      1. Initial
            ```C++
            float *ptr1 {0};
            float *ptr2 = 0;
            ```
      2. `NULL` macro
         1. the value of NULL is implementation defined, but is usually defined as the integer constant 0.(note: in C++11, NULL can be defined as nullptr instead)
      3. `nullptr` in C++11
         1. `nullptr` is a keyword and also an integer pointer, which is the type of `true` or `false`
         2. **C++ will implicitly convert nullptr to any pointer type**
         3. example:
            ```C++
            void print(int x)
            {
                std::cout << "print(int): " << x << '\n';
            }
            
            void print(int *x)
            {
                if (!x)
                    std::cout << "print(int*): null\n";
                else
                    std::cout << "print(int*): " << *x << '\n';
            }
            
            int main()
            {
                int *x { nullptr };
                print(x); // calls print(int*)
            
                print(nullptr); // calls print(int*) as desired
                print(NULL);    // calls print(int) 
                return 0;
            }
        4. `std::nullptr_t` in C++11 
            1. `std::nullptr_t` can only hold one value: `nullptr`
            2. This can be really useful sometimes
                ```C++
                #include <iostream>
                #include <cstddef> // for std::nullptr_t
                
                void doSomething(std::nullptr_t ptr)
                {
                    std::cout << "in doSomething()\n";
                }
                
                int main()
                {
                    doSomething(nullptr); // call doSomething with an argument of type std::nullptr_t
                
                    return 0;
                }
                ```
    3. Pointer and arrays
    4. Pointer arithmetic and array indexing
        1. scaling  
            When calculating the result of a pointer arithmetic expression, the compiler always multiplies the integer operand by the size of the object being pointed to.
        2. Arrays are laid out sequentially in memory
        3. link BTW poinetr pointer arithmetic and indexing
            ```C++
                std::cout << &array[1] << '\n'; // print memory address of array element 1
                std::cout << array+1 << '\n'; // print memory address of array pointer + 1 
            
                std::cout << array[1] << '\n'; // prints 7
                std::cout << *(array+1) << '\n'; // prints 7 (note the parenthesis required here)
            ```
    5. C-style string symbolic constants
        1. example
            ```C++
            char myName[] = "Alex"; // fixed array
            const char *myName = "Alex"; // pointer to symbolic constant
            ```
        2. Difference in memory allocation
            - fixed array case  
                allocates memory for a fixed array of length 5
            - symbolic constant case  
                places the string “Alex\0” into **read-only** memory somewhere, and then sets the pointer to point to it
            - multiple string consolidated into a single value
                ```C++
                const char *name1 = "Alex";
                const char *name2 = "Alex";
                ```
                Note that "Alex" may both have static and const property
            - Other case of C-style string
                ```C++
                const char* getName()
                {
                    return "Alex";
                }
                ```
                if the "Alex" is not refered by other const pointer, getName will get a dangling pointer(dangerous)
    6. Dynamic memory allocation with new and delete
        1. Static memory allocation
            - static and global variables
            - stack
        2. Automatic memory allocation
            - function parameters and local variables
            - stack
        3. Dynamic memory allocation
            - request memory from the operating system
            - heap
        4. Initial a dynamically allocated var
            ```C++
            int *ptr1 = new int (5); // use direct initialization
            int *ptr2 = new int { 6 }; // use uniform initialization
            ```
        5. Deleting single variables
            ```C++
            delete ptr; 
            ptr = 0;
            ```
        6. Operator new can fail
            - use `std::nothrow` not to throw an exception
                ```C++
                int *value = new (std::nothrow) int; // ask for an integer's worth of memory
                if (!value) // handle case where new returned null
                {
                    // Do error handling here
                    std::cout << "Could not allocate memory";
                }
                ```
        7. Memory leaks
            - program loses the address of some bit of dynamically allocated memory before give back to the OS
            - Example 1
                ```C++
                void doSomething()
                {
                    int *ptr = new int;
                }
                ```
            - Example 2
                ```C++
                int value = 5;
                int *ptr = new int; // allocate memory
                ptr = &value; // old address lost, memory leak results
                ```