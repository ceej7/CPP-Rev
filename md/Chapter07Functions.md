## Part7. Functions
1. Function parameters and arguments
   1. A function parameter is a variable declared in the function declaration
   2. An argument is the value that is passed to the function by the caller
2. Passing arguments by value
   1. By default, non-pointer arguments in C++ are passed by value. When an argument is passed by value, the argument’s value is copied into the value of the corresponding function parameter
3. Passing arguments by reference
   1. To pass a variable by reference, we simply declare the function parameters as references rather than as normal variables
   2. Pass by const reference
        ```C++
        void foo(const int &x)
        ```
    3. reference and C-style string
        ```C++
        void printElements(int (&arr)[4])
        {
            int length{ sizeof(arr) / sizeof(arr[0]) }; 
            // we can now do this since the array won't decay
            
            for (int i{ 0 }; i < length; ++i)
            {
                std::cout << arr[i] << std::endl;
            }
        }
        void printElements(int arr[4])
        the parameter arr will decay to int* so sizeof(arr)=8(64-bit machine)
        ```
        this fixed-length can be extended to any length by C++ template.
4. Passing arguments by address
   1. Passing an argument by address involves passing the address of the argument variable rather than the argument variable itself
5. Returning values by value, reference, and address
   1. return by value
      - the variables are evaluated before the function returns, and **a copy of the value** is returned to the caller
        ```C++
        //a copy of the value try
        class ConstTest
        {
        public:
            ConstTest(const ConstTest& c)
            {
                std::cout << static_cast<void*>(this) << " copied" << std::endl;
            }
            ConstTest* operator=(const ConstTest& c)
            {
                std::cout << static_cast<void*>(this) << " assigned from"<< (void*)(&c) << std::endl;
                return this;
            }
            ConstTest()
            {
                std::cout << static_cast<void*>(this) << " created" << std::endl;
            }
            ~ConstTest()
            {
                std::cout << static_cast<void*>(this) << " released" << std::endl;
            }
        };
        ConstTest c;
        c = returnbyVal();
        ```
    2. return by address
       - return by address just copies an address from the function to the caller
    3. return by reference
       - a reference to the variable is passed back to the caller
    4. a common mistake
        ```c++
        const int& returnByReference()
        {
            return 5;
        }
        
        int main()
        {
            const int &ref = returnByReference(); // runtime error
        }
        ```
        - returned reference points to 5
        - 5 is released first
        - ref is refering to returned reference, a dangling reference
        - the life of 5 is not extended
    5. std::tuple and std::tie
        ```C++
        std::tuple<int, double> returnTuple()
        {
            return std::make_tuple(5, 6.7);
        }
        
        int main()
        {
            std::tuple<int, double> s = returnTuple();
            std::cout << std::get<0>(s) << ' ' <<       std::get<1>(s) << '\n'; // use std::get<n> to get the nth element of the tuple
            //std::tie
            int a;
	        double b;
	        std::tie(a, b) = returnTuple();
        }
        ```
6. Inline functions
    1. Demo
        ```C++
        inline int min(int x, int y)
        {
            return x > y ? y : x;
        }
        ```
    2. exempt from the one-definition per program rule
       - inline functions do not actually result in a real function being compiled -- therefore, there’s no conflict when the linker goes to link multiple files together.
7. Function overloading
    1. multiple functions with the same name
    2. **different parameters**
8. Default parameters
    1. Demo
        ```C++
        void printValues(int x, int y=10)
        {
            std::cout << "x: " << x << '\n';
            std::cout << "y: " << y << '\n';
        }
        ```
    2. Default parameters can only be declared once
        ```C++
        void printValues(int x, int y=10);
        void printValues(int x, int y=10)
        {
            std::cout << "x: " << x << '\n';
            std::cout << "y: " << y << '\n';
        }
        ```
    3. function overloading
        ```C++
        void printValues(int x);
        void printValues(int x, int y=20);
        ```
 9. Function Pointer
    1.  Demo
        ```C++
        int foo() // code starts at memory address 0x002717f0
        {
            return 5;
        }
        //std::cout<<foo;
        ```
    2. Assigning a function to a function pointer
        ```C++
        int foo()
        {
            return 5;
        }
        //int (*fcnPtr)();
        //fcnPtr=foo;
        //(*fcnPtr)();
        ```
    3. One interesting note: **Default parameters** won’t work for functions called through function pointers. Default parameters are resolved at compile-time (that is, if you don’t supply an argument for a defaulted parameter, the compiler substitutes one in for you when the code is compiled). However, function pointers are resolved at run-time. Consequently, default parameters can not be resolved when making a function call with a function pointer. You’ll explicitly have to pass in values for any defaulted parameters in this case.
    4. Passing function as arguments to other functions
        ```C++
        void selectionSort(int *array, int size, bool (*comparisonFcn)(int, int))
        {
            for (int startIndex = 0; startIndex < size; ++startIndex)
            {
                int bestIndex = startIndex;
                for (int currentIndex = startIndex + 1; currentIndex < size; ++currentIndex)
                {
                    //also can be explicit called
                    //(*ccomparisonFcn(...))
                    if (comparisonFcn(array[bestIndex], array[currentIndex])) 
                        bestIndex = currentIndex;
                }
                std::swap(array[startIndex], array[bestIndex]);
            }
        }
        
        bool ascending(int x, int y)
        {
            return x > y; 
        }
        
        bool descending(int x, int y)
        {
            return x < y; 
        }

        void printArray(int *array, int size)
        {
            for (int index=0; index < size; ++index)
                std::cout << array[index] << " ";
            std::cout << '\n';
        }
        
        int main()
        {
            int array[9] = { 3, 7, 9, 5, 6, 1, 8, 2, 4 };
        
            // Sort the array in descending order using the descending() function
            selectionSort(array, 9, descending);
            printArray(array, 9);
        
            // Sort the array in ascending order using the ascending() function
            selectionSort(array, 9, ascending);
            printArray(array, 9);
        
            return 0;
        }
        ```
    5. typedef or type aliases
        ```C++
        typedef bool (*validateFcn)(int, int);
        //or
        using validateFcn = bool(*)(int, int); 

        //call
        bool validate(int x, int y, validateFcn pfcn) // clean
        ```
    6.  `std::function` in C++11
        ```C++
        bool validate(int x, int y, std::function<bool(int, int)> fcn); 
        ```
10. stack and heap
    1.  The heap segment
    2.  The call stack
11. std::vector capacity and stack behavior
    1.  Length vs capacity
        ```C++
        //length = capacity = 5
        std::vector<int> array { 0, 1, 2 };
        array.resize(5); 
        std::cout << "The length is: " << array.size() << '\n';
        ```
    2.  More length vs capacity
        ```C++
        std::vector<int> array;
        array = { 0, 1, 2, 3, 4 }; //length = 5 capacity = 5
        
        array = { 9, 8, 7 }; // length = 3 capacity = 5
        ```
    3. Stack behavior with std::vector
12. Recursive
    1.  recursive function
        -  every function call causes data to be placed on the call stack
    2.  Recursive vs iterative
        -  recursive version is often much simpler to write 
        -  Iterative functions are almost always more efficient 
13. Handling errors, cerr and exit
    1.  Syntax errors
    2.  Semantic errors
        - logic error
        - violated assumption 
    3.  `exit(1)` in `cstdlib` to return error code
14. Assert and static_assert
    1.  An assert statement is a preprocessor macro    that evaluates a conditional expression at runtime.
        ```C++
        #include <cassert> // for assert()
        int getArrayValue(const std::array<int, 10> &array, int index)
        {
            // we're asserting that index is between 0 and 9
            assert(index >= 0 && index <= 9); 
            return array[index];
        }
        ```
    2.  NDEBUG 
        - asserts are only active in debug builds.
        ```C++
        #define NDEBUG
        ```
    3.  Static_assert
        - static_assert is designed to operate at compile time
        - For instance
            ```C++
            static_assert(sizeof(long) == 8, "long must be 8 bytes");
            static_assert(sizeof(int) == 4, "int must be 4 bytes");
            ```
15. Command line arguments
    1.  int main(int argc, char** argv)
    2.  argc - argument count
    3.  argv - argument vectors
    4.  For instance
        ```C++
        int main(int argc, char *argv[])
        {
            std::cout << "There are " << argc << " arguments:\n";
        
            // Loop through each argument and print its number and value
            for (int count=0; count < argc; ++count)
                std::cout << count << " " << argv[count] << '\n';
        
            return 0;
        }
        ```
16. Ellipsis 
    1.  ellipsis are rarely used, potentially dangerous
        ```C++
        double findAverage(int count, ...)
        {
            double sum = 0;

            // We access the ellipsis through a va_list, so let's declare one
            va_list list;

            // We initialize the va_list using va_start.  The first parameter is
            // the list to initialize.  The second parameter is the last non-ellipsis
            // parameter.
            va_start(list, count);

            // Loop through all the ellipsis arguments
            for (int a = 0; a < count; ++a)
                // We use va_arg to get parameters out of our ellipsis
                // The first parameter is the va_list we're using
                // The second parameter is the type of the parameter
                sum += va_arg(list, int);

            // Cleanup the va_list when we're done.
            va_end(list);

            return sum / count;
        }
        ```
    2. Danger 1: Type checking is suspended
    3. Danger 2: ellipsis don’t know how many parameters were passed
       1. Use a sentinel value
       2. Use a decoder string