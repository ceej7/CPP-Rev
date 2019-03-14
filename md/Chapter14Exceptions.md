# Exceptions
## The need for exceptions
1. When return codes fail - return with error code
2. Exceptions
   1. Exception handling provides a mechanism to decouple handling of errors or other exceptional circumstances from the typical control flow of your code.
## Basic exception handling
1. three keywords 
   1. `throw`
   2. `try`
   3. `catch`
2. Throwing exceptions
   1. Sample
        ```C++
        throw ENUM_INVALID_INDEX;
        throw "Can not take square root of negative number";
        throw dX;
        throw MyException("Fatal Error");
        ```
3. Looking for exceptions
   1. try block
        ```C++
        try
        {
            // Statements that may throw exceptions you want to handle go here
            throw -1; // here's a trivial throw statement
        }
        ```
   2. Handling exceptions
        ```C++
        catch (int x)
        {
            // Handle an exception of type int here
            std::cerr << "We caught an int exception with value" << x << '\n';
        }
        ```
4. Recapping exception handling
   1. When an exception is raised (using throw), execution of the program immediately jumps to the nearest enclosing try block
   2. If no appropriate catch handlers exist, execution of the program propagates to the next enclosing try block.
   3. Note that the compiler **will not perform implicit conversions or promotions** when matching exceptions with catch blocks
5. Exceptions are handled immediately
6. What catch blocks typically do
   1. catch blocks may print an error
   2. catch blocks may return a value or error code back to the caller
   3. a catch block may throw another exception
## Exceptions, functions, and stack unwinding
1. Throwing exceptions outside of a try block
   1. throw outside the try block
        ```C++
        double mySqrt(double x)
        {
            // If the user entered a negative number, this is an error condition
            if (x < 0.0)
                throw "Can not take sqrt of negative number"; // throw exception of type const char*
        
            return sqrt(x);
        }
        ```
   2. unwinding the stack
        - Each function is terminated in sequence until a handler for the exception is found, or until main() is terminated without the exception being handled.
## Uncaught exceptions, catch-all handlers, and exception specifiers
1. Uncaught exceptions
    ```C++
    double mySqrt(double x)
    {
        // If the user entered a negative number, this is an error condition
        if (x < 0.0)
            throw "Can not take sqrt of negative number"; // throw exception of type const char*
    
        return sqrt(x);
    }
    
    int main()
    {
        std::cout << "Enter a number: ";
        double x;
        std::cin >> x;
    
        // Look ma, no exception handler!
        std::cout << "The sqrt of " << x << " is " << mySqrt(x) << '\n';
    
        return 0;
    }
    ```
2. Catch-all handlers
    ```C++
    catch(...) {}
    ```
## Exceptions, classes, and inheritance
1. member function
    ```C++
    int& IntArray::operator[](const int index)
    {
        if (index < 0 || index >= getLength())
            throw index;
    
        return m_data[index];
    }
    ```
2. When constructors fail
   1. the object’s construction is aborted, and all class members are destructed as per usual
3. Exception classes
   1. An exception class is just a normal class that is designed specifically to be thrown as an exception. 
   2. Sample
        ```C++
        class ArrayException
        {
        private:
            std::string m_error;
        
        public:
            ArrayException(std::string error)
                : m_error(error)
            {
            }
        
            const char* getError() { return m_error.c_str(); }
        };
        ```
4. Exceptions and inheritance: 
    ```C++
    //output: caught Base
    try
    {
        throw Derived();
    }
    catch (Base &base)
    {
        cerr << "caught Base";
    }
    catch (Derived &derived)
    {
        cerr << "caught Derived";
    }
    ```
   - Rule: Handlers for derived exception classes should be listed before those for base classes.
5. `std::exception`
   1. when an exception is thrown by the standard library, we can set up an exception handler to catch exceptions of type std::exception.
   2. Sample
        ```C++
        try
        {

            std::string s;
            s.resize(-1); 
        }
        catch (std::exception &exception)
        {
            std::cerr << "Standard exception: " << exception.what() << '\n';
        }
        ```
6. Deriving your own classes from std::exception
   1. Sample
        ```C++
        class ArrayException: public std::exception
        {
        private:
            std::string m_error;
        
        public:
            ArrayException(std::string error)
                : m_error(error)
            {
            }
        
            // return the std::string as a const C-style string
        //	const char* what() const { return m_error.c_str(); } // pre-C++11 version
            const char* what() const noexcept { return m_error.c_str(); } // C++11 version
        };
        ```
## Rethrowing exceptions
1. you want to catch an exception, but not want to fully handle it at the point where you catch it
2. **Wrong rethrow**
    ```C++
    int getIntValueFromDatabase(Database *d, std::string table, std::string key)
    {
        assert(d);
    
        try
        {
            return d->getIntValue(table, key); // throws Derived exception on failure
        }
        catch (Base &exception)
        {
            // Write an error to some global logfile
            g_log.logError("doSomethingImportant failed");
    
            throw exception; // Danger: this throws a Base object, not a Derived object
        }
    }
    ```
    - exception copied
    - exception maybe sliced(Base vs. Derived)
3. **Rethrowing an exception (the right way)**
   1. C++ provides a way to rethrow the exact same exception as the one that was just caught. To do so, **simply use the throw keyword** from within the catch block
   ```C++
    try
    {
        try
        {
            throw Derived();
        }
        catch (Base& b)
        {
            std::cout << "Caught Base b, which is actually a ";
            b.print();
            std::cout << "\n";
            throw; // note: We're now rethrowing the object here
        }
    }
    catch (Base& b)
    {
        std::cout << "Caught Base b, which is actually a ";
        b.print();
        std::cout << "\n";
    }
    ```
## Function try blocks
1. Function try blocks
   - Function try blocks are designed to allow you to establish an exception handler around the body of an entire function, rather than around a block of code.
        ```C++
        class A
        {
        private:
            int m_x;
        public:
            A(int x) : m_x(x)
            {
                if (x <= 0)
                    throw 1;
            }
        };
        
        class B : public A
        {
        public:
            B(int x) try : A(x) // note addition of try keyword here
            {
            }
            catch (...) // note this is at same level of indentation as the function itself
            {
                        // Exceptions from member initializer list or constructor body are caught here
        
                        std::cerr << "Construction of A failed\n";
        
                        // If an exception isn't explicitly thrown here, the current exception will be implicitly rethrown
            }
        };
        
        int main()
        {
            try
            {
                B b(0);
            }
            catch (int)
            {
                std::cout << "Oops\n";
            }
        }
        ```
   - note: after function try block, you must throw an exception in catch
## Exception dangers and downsides
1. Cleaning up resources
    ```C++
    Person *john = NULL;
    try
    {
        john = new Person("John", 18, PERSON_MALE);
        processPerson(john);
        delete john;
    }
    catch (PersonException &exception)
    {
        delete john;
        cerr << "Failed to process person: " << exception.what() << '\n';
    }
    ```
   - or by `std::unique_ptr` - a template class that holds a pointer, and deallocates it when it goes out of scope.
2. Exceptions and destructors
   1. exceptions should never be thrown in destructors
3. Performance concerns
4. When should I use exceptions?
   1. Exception handling is best used when all of the following are true:
      1. The error being handled is likely to occur only infrequently.
      2. The error is serious and execution could not continue otherwise.
      3. The error cannot be handled at the place where it occurs.
      4. There isn’t a good alternative way to return an error code back to the caller.