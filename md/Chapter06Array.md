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
      - plain enums
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
      - enums class  
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
      - First way to fix
            ```C++
            (StudentNames::MAX_STUDENTS)]; // allocate 6 integers
            ```
      - Better one
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
            - `std::nullptr_t` can only hold one value: `nullptr`
            - This can be really useful sometimes
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
4. C-style string symbolic constants
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
5. Dynamic memory allocation with new and delete
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
6. Dynamically allocating arrays
    1. new and delete
        ```C++
        int *array = new int[length];
        delete[] array;
        ```
    2. Dynamic arrays are almost identical to fixed arrays
        - a pointer does not know its size
    3. dynamically initializing
        ```C++
        //way 1
        int *array = new int[5];
        array[0] = 9;
        array[1] = 7;
        array[2] = 5;
        array[3] = 3;
        array[4] = 1;
        //way 2
        nt *array = new int[5] { 9, 7, 5, 3, 1 }; // C++11
        ```
    4. not okay method
        ```C++
        char *array = new char[14] { "Hello, world!" }; // doesn't work in C++11
        int *dynamicArray1 = new int[] {1, 2, 3}; // not okay: implicit size for dynamic arrays
        ```
    5. Resizing arrays
        - C++ does not provide a built-in way to resize an array
        - how to
            - allocate a new array
            - copy elements
            - delete old array 
7. Pointers and const
    1. Pointer to a const value 
        - Pointer to a const value means the destination of pointer is of const type.
            ```C++
            const int value = 5;
            const int *ptr = & value;
            ```
    2. Const pointer
        - A const pointer is a pointer whose value can not be changed after initialization
            ```C++
            int value = 5;
            int *const ptr = &value; // ptr will always point to value
            *ptr = 6; // allowed, since ptr points to a non-const int
            ```
8. Reference variables
    1. Reference
        - A reference is a type of C++ variable that acts as an alias to another object or value.
    2. 3 types of reference
        - References to non-const values
        - References to const values
        - C++11 added r-value references
    3. References to non-const values
        ```C++
        int value = 5; // normal integer
        int &ref = value; // reference to variable value
        ```
    4. References must be initialized
        ```C++
        int x = 5;
        int &ref1 = x; // okay, x is an non-const l-value
        
        const int y = 7;
        int &ref2 = y; // not okay, y is a const l-value
        
        int &ref3 = 6; // not okay, 6 is an r-value
        ```
    5. References can not be reassigned
    6. References as function parameters
        ```C++
        void changeN(int &ref)
        {
            ref = 6;
        }
        ```
    7. Using references to pass C-style arrays to functions
        - if a **C-style array** is passed by reference, this decaying does not happen.
            ```C++
            #include <iostream>
            
            // Note: You need to specify the array size in the function declaration
            void printElements(int (&arr)[4])
            {
            int length{ sizeof(arr) / sizeof(arr[0]) }; // we can now do this since the array won't decay
            
            for (int i{ 0 }; i < length; ++i)
            {
                std::cout << arr[i] << std::endl;
            }
            }
            
            int main()
            {
                int arr[]{ 99, 20, 14, 80 };
                
                printElements(arr);
            
                return 0;
            }
            ```
    8. reference as shotcuts
        ```C++
        struct Something
        {
            int value1;
            float value2;
        };
        
        struct Other
        {
            Something something;
            int otherValue;
        };
        
        Other other;
        //-----------------shotcuts-----------------//
        int &ref = other.something.value1;
        ref = 5;
        ```
9. Reference and const
    1. references to const values can be initialized with non-const l-value, const l-values, and r-values.
        ```C++
        int x = 5;
        const int &ref1 = x; // non-const l-value
        const int y = 7;
        const int &ref2 = y; // const l-value
        const int &ref3 = 6; // r-value
        ```
    2. Const references as function parameters
        ```C++
        // ref is a const reference , not a copy
        void changeN(const int &ref)
        {
            //ref = 6; // not allowed, ref is const
        }
        ```
10. Member selection with pointers and references
    1. reference and var - member selection operator (`.`)
    2. pointer - member selection operator (`->`)
11. `For-each` loops - C++11
    1. loops structure
        ```C++
        for (element_declaration : array)
        statement;
        ```
    2. For each loops and the auto keyword
        - perfect situation for `auto` key
        ```C++
            int fibonacci[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
            for (auto number : fibonacci) // type is auto
                std::cout << number << ' ';
        ```
    3. For-each loops and references(preferred)
        ```C++
        int array[5] = { 9, 7, 5, 3, 1 };
        for (auto &element: array) // a reference, preventing a copy
                std::cout << element << ' ';
        ```
        - `const auto &` is much safer
    4. For-each doesn’t work with pointers to an array
12. Void pointers
    1. A void pointer is declared like a normal pointer
        ```C++
        int value = 5;
        void *voidPtr = &value;
        //cout << *voidPtr << endl; // illegal:
        int *intPtr = static_cast<int*>(voidPtr); //static cast
        cout << *intPtr << endl; 
        ```
    2. `void` pointer and `enum`
        ```C++
        enum Type
        {
            INT,
            FLOAT,
            CSTRING
        };
        
        void printValue(void *ptr, Type type)
        {
            switch (type)
            {
                case INT:
                    std::cout << *static_cast<int*>(ptr) << '\n';
                    break;
                case FLOAT:
                    std::cout << *static_cast<float*>(ptr) << '\n'; 
                    break;
                case CSTRING:
                    std::cout << static_cast<char*>(ptr) << '\n'; // cast to char pointer (no dereference)
                    break;
            }
        }
        ```
13. **Pointers to pointers and dynamic multidimensional arrays**
    1. Pointers to pointers
        ```C++
        int **ptrptr;
        ``` 
    2. Arrays of pointers
        ```C++
        int **array = new int*[10]; // allocate an array of 10 int pointers
        ```
    3. Two-dimensional dynamically allocated arrays
        - two dimensional fixed array
            ```C++
            int array[10][5];
            ```
        - dynamically, if right-most array dimension is a compile-time constant - `int[] *var`
            ```C++
            int (*array)[5] = new int[10][5];
            ```
        - dynamically, if right-most array dimension isn't a compile-time constant `int **var`
            ```C++
            int **array = new int*[10]; // allocate an array of 10 int pointers — these are our rows
            for (int count = 0; count < 10; ++count)
                array[count] = new int[5];
            //------------deallocate-----------//
            for (int count = 0; count < 10; ++count)
                delete[] array[count];
            delete[] array; // this needs to be done last
            ```
        - substitution - flaten a 2-dim array
            ```C++
            // Instead of this:
            int **array = new int*[10]; 
            for (int count = 0; count < 10; ++count)
                array[count] = new int[5]; 
            
            // Do this
            int *array = new int[50];
            ```
14. An introduction to std::array C++11
    1. structure
        ```C++
        #include <array>
        std::array<int, 3> myArray; 
        ```
    2. elements access
        ```C++
        myArray.at(1) = 6;
        ```
    3. Size `.size()` and sorting `std::sort()`
    4. Manually indexing std::array via size_type
        - wrong version - i signed  and index size_type(unsigned)
            ```C++
            std::array<int, 5> myArray { 7, 3, 1, 9, 5 };

            for (int i{ 0 }; i < myArray.size(); ++i)
                std::cout << myArray[i] << ' ';
            ```
        - right version with help of type alias
            ```C++
            std::array<int, 5> myArray { 7, 3, 1, 9, 5 };
            
            using index_t = std::array<int, 5>::size_type;
            for (index_t i{ 0 }; i < myArray.size(); ++i)
                std::cout << myArray[i] << ' ';
            ```
15. An introduction to std::vector
    1. Declaration
        ```C++
        #include <vector>
        
        std::vector<int> array; 
        std::vector<int> array2 = { 9, 7, 5, 3, 1 };
        std::vector<int> array3 { 9, 7, 5, 3, 1 };
        ```
    2. size - `.size()` - `.resize(5)`
    3. Auto deallocated as soon as array goes out of scope