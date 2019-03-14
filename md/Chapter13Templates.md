# Templates
## The need for function templates
1. What is a function template?
   1. In C++, function templates are functions that serve as a pattern for creating other similar functions.
2. Creating function templates in C++
    ```C++
    template <typename T> 
    T max(T x, T y)
    {
        return (x > y) ? x : y;
    }
    ```
3. multiple template type parameter
   ```C++
   template <typename T1, typename T2>
    // template function here
    ```
## Function template instances
1. The function with actual types is called a function template instance.
2. Operators, function calls, and function templates
   1. In a normal function, any operators or function calls that you use with your types must be defined, or you will get a compiler error. 
   2. sample
        ```C++
        template <typename T> // this is the template parameter declaration
        const T& max(const T& x, const T& y)
        {
            return (x > y) ? x : y;
        }
        
        class Cents
        {
        private:
            int m_cents;
        public:
            Cents(int cents)
                : m_cents(cents)
            {
            }
            friend bool operator>(const Cents &c1, const Cents &c2)
            {
                return (c1.m_cents > c2.m_cents);
            }
        };
        
        int main()
        {
            Cents nickle(5);
            Cents dime(10);
        
            Cents bigger = max(nickle, dime);
        
            return 0;
        }
        ```
## Template classes
1. Templates and container classes
    ```C++
    template <class T> 
    class Array
    {
    private:
        int m_length;
        T *m_data;
    ```
2. Template classes in the standard library
   1. such as `std::vector<int>`
3. Splitting up template classes
   1. In order for the compiler to use a template, it must see both the template definition (not just a declaration) and the template type used to instantiate the template. Also remember that C++ compiles files individually. When the Array.h header is #included in main, the template class definition is copied into main.cpp. When the compiler sees that we need two template instances, Array<int>, and Array<double>, it will instantiate these, and compile them as part of main.cpp. However, when it gets around to compiling Array.cpp separately, it will have forgotten that we need an Array<int> and Array<double>, so that template function is never instantiated. Thus, we get a linker error, because the compiler can’t find a definition for Array<int>::getLength() or Array<double>::getLength().
4. Solution:
   1.  simply put all of your template class code in the header file
   2.  an alternative is to rename Array.cpp to Array.inl (.inl stands for inline), and then include Array.inl from the bottom of the Array.h header.
## Template non-type parameters
1. Non-type parameters
   - A value that has an integral type or enumeration
   - A pointer or reference to a class object
   - A pointer or reference to a function
   - A pointer or reference to a class member function
   - std::nullptr_t
2. Sample
    ```C++
    template <class T, int size> // size is the non-type parameter
    class StaticArray
    {
    private:
        // The non-type parameter controls the size of the array
        T m_array[size];
    
    public:
        T* getArray();
        
        T& operator[](int index)
        {
            return m_array[index];
        }
    };
    
    // Showing how a function for a class with a non-type parameter is defined outside of the class
    template <class T, int size>
    T* StaticArray<T, size>::getArray()
    {
        return m_array;
    }
    ```
## Function template specialization
1. occasionally there are cases where it is useful to implement a templated function slightly different for a specific data type.
2. function template soecialization sample 
    ```C++
    template <>
    void Storage<double>::print()
    {
        std::cout << std::scientific << m_value << '\n';
    }
    ```
## Class template specialization
1. Class template specialization sample
    ```C++
    template <>
    class Storage8<bool> // we're specializing Storage8 for bool
    {
    // implementation details
    }
    ```
## Partial template specialization
1. Partial template specialization
   1. Partial template specialization allows us to specialize classes (but not individual functions!) where some, but not all, of the template parameters have been explicitly defined.
        ```C++
        template <class T, int size> // size is the expression parameter
        class StaticArray
        {
        private:
            // The expression parameter controls the size of the array
            T m_array[size];
        
        public:
            T* getArray() { return m_array; }
        
            T& operator[](int index)
            {
                return m_array[index];
            }
        };
        
        template <typename T, int size>
        void print(StaticArray<T, size> &array)
        {
            for (int count = 0; count < size; ++count)
                std::cout << array[count] << ' ';
        }
        
        // overload of print() function for partially specialized StaticArray<char, size>
        template <int size>
        void print(StaticArray<char, size> &array)
        {
            for (int count = 0; count < size; ++count)
                std::cout << array[count];
        }
        ```
2. Partial template specialization for member functions - by create a base class without member function
    ```C++
    #include<iostream>
    
    template <class T, int size> // size is the expression parameter
    class StaticArray_Base
    {
    protected:
        // The expression parameter controls the size of the array
        T m_array[size];
    
    public:
        T* getArray() { return m_array; }
    
        T& operator[](int index)
        {
            return m_array[index];
        }
        virtual void print()
        {
            for (int i = 0; i < size; i++)
                std::cout << m_array[i];
            std::cout << "\n";
        }
    };
    
    template <class T, int size> // size is the expression parameter
    class StaticArray: public StaticArray_Base<T, size>
    {
    public:
        StaticArray()
        {
    
        }
    };
    
    template <int size> // size is the expression parameter
    class StaticArray<double, size>: public StaticArray_Base<double, size>
    {
    public:
    
        virtual void print() override
        {
            for (int i = 0; i < size; i++)
                std::cout << std::scientific << this->m_array[i] << " ";
    // note: The this-> prefix in the above line is needed.  See https://stackoverflow.com/a/6592617 for more info on why.
            std::cout << "\n";
        }
    };
    ```
## Partial template specialization for pointers
1. Sample - what if int *
    ```C++
    template <>
    Storage<char*>::Storage(char* value)
    {
        // Figure out how long the string in value is
        int length=0;
        while (value[length] != '\0')
            ++length;
        ++length; // +1 to account for null terminator
    
        // Allocate memory to hold the value string
        m_value = new char[length];
    
        // Copy the actual value string into the m_value memory we just allocated
        for (int count=0; count < length; ++count)
            m_value[count] = value[count];
    }
    ```
2. pointer partially specialized
    ```C++
    template <typename T>
    class Storage<T*> // this is a partial-specialization of Storage that works with pointer types
    {
    private:
        T* m_value;
    public:
        Storage(T* value) // for pointer type T
        {
            // For pointers, we'll do a deep copy
            m_value = new T(*value); // this copies a single value, not an array
        }
    
        ~Storage()
        {
            delete m_value; // so we use scalar delete here, not array delete
        }
    
        void print()
        {
            std::cout << *m_value << '\n';
        }
    };
    ```