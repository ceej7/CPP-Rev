# Part9. Overloading
## Introduction to operator overloading
1. Using function overloading to overload operators is called operator overloading.
2. What are the limitations on operator overloading?  
    1. First, almost any existing operator in C++ can be overloaded. The exceptions are: conditional (?:), sizeof, scope (::), member selector (.), and member pointer selector (.*).
    2. Second, you can only overload the operators that exist.
    3. Third, at least one of the operands in an overloaded operator must be a user-defined type. 
    4. Finally, all operators keep their default precedence and associativity
## Overloading the arithmetic operators using friend functions
1. Version 01
     ```C++
     class Cents
     {
     private:
         int m_cents;
     
     public:
         Cents(int cents) { m_cents = cents; }
     
         // add Cents + Cents using a friend function
         friend Cents operator+(const Cents &c1, const Cents &c2);
     
         int getCents() const { return m_cents; }
     };
     
     // note: this function is not a member function!
     Cents operator+(const Cents &c1, const Cents &c2)
     {
         // use the Cents constructor and operator+(int, int)
         // we can access m_cents directly because this is a friend function
         return Cents(c1.m_cents + c2.m_cents);
     }
     ```
2. Friend functions can be defined inside the class
    ```C++
    class Cents
    {
    private:
        int m_cents;
    
    public:
        Cents(int cents) { m_cents = cents; }
    
        // add Cents + Cents using a friend function
            // This function is not considered a member of the class, even though the definition is inside the class
        friend Cents operator+(const Cents &c1, const Cents &c2)
        {
            // use the Cents constructor and operator+(int, int)
            // we can access m_cents directly because this is a friend function
            return Cents(c1.m_cents + c2.m_cents);
        }
    
        int getCents() const { return m_cents; }
    };
    ```
3. Overloading operators for operands of different types
    ```C++
    // add Cents + int using a friend function
    friend Cents operator+(const Cents &c1, int value);

    // add int + Cents using a friend function
    friend Cents operator+(int value, const Cents &c1);
    ```
4. Implementing operators using other operators
   1. operator+(int, MinMax) by calling operator+(MinMax, int)
## Overloading operators using normal functions
1. Version 01
    ```C++
    Cents operator+(const Cents &c1, const Cents &c2)
    {
        // use the Cents constructor and operator+(int, int)
            // we don't need direct access to private members here
        return Cents(c1.getCents() + c2.getCents());
    }
    ```
2. the normal and friend functions work almost identically (they just have different levels of access to private members)
3. Rule: Prefer overloading operators as normal functions instead of friends if it’s possible to do so without adding additional functions.
## Overloading the I/O operators
1. Overloading operator<<
   1. If the operator is <<, what are the operands? The left operand is the std::cout object, and the right operand is your Point class object.
   2. Demo
        ```C++
        friend std::ostream& operator<< (std::ostream &out, const Point &point);
        std::ostream& operator<< (std::ostream &out, const Point &point)
        {
            out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ")";
            return out;
        }
        ```
2. Overloading operator>>
   1. This is done in a manner analogous to overloading the output operator.
   2. Demo
        ```C++
        std::ostream& operator<< (std::ostream &out, const Point &point)
        {
            out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ")";
            return out;
        }
        ```
##  Overloading operators using member functions
1. Overloading member function
   - The overloaded operator must be added as a member function of the left operand.
   - The left operand becomes the implicit *this object
   - All other operands become function parameters.
2. How
    ```C++
    Cents Cents::operator+(int value)
    {
        return Cents(m_cents + value);
    }
    ```
3. Not everything can be overloaded as a friend function  
   - The assignment (=), subscript ([]), function call (()), and member selection (->) operators must be overloaded as member functions, because the language requires them to be.
4. Not everything can be overloaded as a member function
   - for instance, `<<`
   - the left operand of `<<` is `std::ostream`
5. rules of thumb
   - If you’re overloading assignment (=), subscript ([]), function call (()), or member selection (->), do so as a member function.
   - If you’re overloading a unary operator, do so as a member function.
   - If you’re overloading a binary operator that modifies its left operand (e.g. operator+=), do so as a member function if you can.
   - If you’re overloading a binary operator that does not modify its left operand (e.g. operator+), do so as a normal function or friend function. 
## Overloading unary operators +, -, and !
1. typically unary operator overloads are implemented as member functions.
2. Demo
    ```C++
    class Cents
    {
    private:
        int m_cents;
    
    public:
        Cents(int cents) { m_cents = cents; }
    
        // Overload -Cents as a member function
        Cents operator-() const;
    
        int getCents() const { return m_cents; }
    };
    
    // note: this function is a member function!
    Cents Cents::operator-() const
    {
        return Cents(-m_cents);
    }
    ```
## Overloading the comparison operators
1. Implement by frined function
    1. `==`, `!=`, `<`...
2. Demo 
    ```C++
    class Car
    {
    private:
        std::string m_make;
        std::string m_model;
    
    public:
        Car(std::string make, std::string model)
            : m_make(make), m_model(model)
        {
        }
    
        friend bool operator== (const Car &c1, const Car &c2);
        friend bool operator!= (const Car &c1, const Car &c2);
    };
    
    bool operator== (const Car &c1, const Car &c2)
    {
        return (c1.m_make== c2.m_make &&
                c1.m_model== c2.m_model);
    }
    
    bool operator!= (const Car &c1, const Car &c2)
    {
        return !(c1== c2);
    }
    ```
## Overloading the increment and decrement operators
1. Overloading the increment (++) and decrement (--) operators are pretty straightforward, with one small exception. 
   - a prefix increment and decrement (e.g. ++x; --y;)
   - a postfix increment and decrement (e.g. x++; y--;).
2. Overloading prefix increment and decrement
```C++
Digit& Digit::operator++()
{
    // If our number is already at 9, wrap around to 0
    if (m_digit == 9)
        m_digit = 0;
    // otherwise just increment to next number
    else
        ++m_digit;
 
    return *this;
}
 
Digit& Digit::operator--()
{
    // If our number is already at 0, wrap around to 9
    if (m_digit == 0)
        m_digit = 9;
    // otherwise just decrement to next number
    else
        --m_digit;
 
    return *this;
}
```
3. Overloading postfix increment and decrement
   1. Dummy parameter
   2. return by value -  do inc/dec then return origin
   3. How
        ```C++
        Digit Digit::operator++(int)
        {
            // Create a temporary variable with our current digit
            Digit temp(m_digit);
        
            // Use prefix operator to increment this digit
            ++(*this); // apply operator
        
            // return temporary result
            return temp; // return saved state
        }
        
        Digit Digit::operator--(int)
        {
            // Create a temporary variable with our current digit
            Digit temp(m_digit);
        
            // Use prefix operator to decrement this digit
            --(*this); // apply operator
        
            // return temporary result
            return temp; // return saved state
        }

        ```
## Overloading the subscript operator
1. overload the subscript operator ([]) to allow access to the elements of m_list
2. Demo
```C++
class IntList
{
private:
    int m_list[10];
 
public:
    int& operator[] (const int index);
};
 
int& IntList::operator[] (const int index)
{
    return m_list[index];
}
```
3. Why operator[] returns a reference
    1. Because operator[] is returning a reference, it returns the actual list.m_list[2] array element.
4. Dealing with const objects
   1. we can define a non-const and a const version of operator[] separately
   2. Demo 
        ```C++
        class IntList
        {
        private:
            int m_list[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // give this class some initial state for this example
        
        public:
            int& operator[] (const int index);
            const int& operator[] (const int index) const;
        };
        
        int& IntList::operator[] (const int index) // for non-const objects: can be used for assignment
        {
            return m_list[index];
        }
        
        const int& IntList::operator[] (const int index) const // for const objects: can only be used for access
        {
            return m_list[index];
        }
        
        int main()
        {
            IntList list;
            list[2] = 3; // okay: calls non-const version of operator[]
            std::cout << list[2];
        
            const IntList clist;
            clist[2] = 3; // compile error: calls const version of operator[], which returns a const reference.  Cannot assign to this.
            std::cout << clist[2];
        
            return 0;
        }
        ```
   3. Error checking
        ```C++
        int& IntList::operator[] (const int index)
        {
            assert(index >= 0 && index < 10);
        
            return m_list[index];
        }
        ```
   4. The function parameter does not need to be an integer
        ```C++
        void Stupid::operator[] (std::string index)
        {
            std::cout << index;
        } 
        ```
## Overloading the parenthesis operator
1. The parenthesis operator (operator()) is a particularly interesting operator in that it allows you to vary both the **type** AND **number** of parameters it takes.
2. Two things
   1. implement as a member function
   2. operator() is just a normal operator
3. An example
    ```C++
    class Matrix
    {
    private:
        double data[4][4];
    public:
        Matrix()
        {
            // Set all elements of the matrix to 0.0
            for (int row=0; row < 4; ++row)
                for (int col=0; col < 4; ++col)
                    data[row][col] = 0.0;
        }
    
        double& operator()(int row, int col);
        const double& operator()(int row, int col) const; // for const objects
    };
    
    double& Matrix::operator()(int row, int col)
    {
        assert(col >= 0 && col < 4);
        assert(row >= 0 && row < 4);
    
        return data[row][col];
    }
    
    const double& Matrix::operator()(int row, int col) const
    {
        assert(col >= 0 && col < 4);
        assert(row >= 0 && row < 4);
    
        return data[row][col];
    }
    ```
## Overloading typecasts
1. Overloading the typecast operators allows us to convert our class into another data type. Take a look at the following class:
2. Example
```C++
// Overloaded int cast
operator int() { return m_cents; }
```
3. two things to note
    - there is a space between the word operator and the type we are casting to
    - Casting operators do not have a return type.
4. Overload user-defined cast
## The copy constructor
1. types of initialization that C++ supports: 
   - direct initialization
   - uniform initialization
   - copy initialization
2. Example
    ```C++
    class Fraction
    {
    private:
        int m_numerator;
        int m_denominator;
    
    public:
        // Default constructor
        Fraction(int numerator=0, int denominator=1) :
            m_numerator(numerator), m_denominator(denominator)
        {
            assert(denominator != 0);
        }
    
        friend std::ostream& operator<<(std::ostream& out, const Fraction &f1);
    };
3. a direct initialization:
    ```C++
    int x(5);
    Fraction fiveThirds(5, 3);
    ```
4. a uniform initialization:
    ```C++
    int x { 5 };
    Fraction fiveThirds {5, 3};
    ```
5. a copy initialization:
    ```C++
    int x = 6; 
    Fraction six = Fraction(6); 
    Fraction seven = 7;
    ```
6. default copy constructor
    - Memberwise initialization: each member of the copy is initialized directly from the member of the class being copied.
7. explicitly define a default constructor
    ```C++
    raction(const Fraction &fraction) :
            m_numerator(fraction.m_numerator), m_denominator(fraction.m_denominator)
    ```
8. Preventing copies
    - by making the copy constructor private
9. The copy constructor may be elided
    ```C++
    \\So although you wrote:
        Fraction fiveThirds(Fraction(5, 3));
    \\The compiler may change this to:
        Fraction fiveThirds(5, 3);
    ```
## copy initialization
1. Other places copy initialization is used
    - When you pass or return a class by value, that process uses copy initialization.
## Converting constructors, explicit, and delete
1. Consider the following case
    ```C++
    class Fraction
    {
    private:
        int m_numerator;
        int m_denominator;
    
    public:
        // Default constructor
        Fraction(int numerator=0, int denominator=1) :
            m_numerator(numerator), m_denominator(denominator)
        {
            assert(denominator != 0);
        }
    
            // Copy constructor
        Fraction(const Fraction &copy) :
            m_numerator(copy.m_numerator), m_denominator(copy.m_denominator)
        {
            // no need to check for a denominator of 0 here since copy must already be a valid Fraction
            std::cout << "Copy constructor called\n"; // just to prove it works
        }
    
        friend std::ostream& operator<<(std::ostream& out, const Fraction &f1);
            int getNumerator() { return m_numerator; }
            void setNumerator(int numerator) { m_numerator = numerator; }
    };
    
    std::ostream& operator<<(std::ostream& out, const Fraction &f1)
    {
        out << f1.m_numerator << "/" << f1.m_denominator;
        return out;
    }
    
    Fraction makeNegative(Fraction f)
    {
        f.setNumerator(-f.getNumerator());
        return f;
    }
    
    int main()
    {
        std::cout << makeNegative(6); // note the integer here
    
        return 0;
    }
    ```
    - Fraction has a constructor willing to take a single integer
    - compiler will implicitly convert the literal 6 into a Fraction object
    - in C++11 constructors taking multiple parameters can now be converting constructors with unifotm initialization
2. The explicit keyword
    1. Example
        ```C++
        private:
            std::string m_string;
        public:
            MyString(int x) // allocate string of size x
            {
                m_string.resize(x);
            }
        
            MyString(const char *string) // allocate string to hold string value
            {
                m_string = string;
            }
        //MyString mine = 'x'
        ```
        - this will call the first constructor
    2. Solution - `explicit` keyword
        ```C++
        explicit MyString(int x) // allocate string of size x
        {
            m_string.resize(x);
        }
        ```
    3. Explicit conversions (via casting) are still allowed
        ```C++
        static_cast<MyString>(5)
        ```
    4. Direct or uniform initialization will also still convert parameters to match
        ```C++
        MyString str('x');
        ```
3. The delete keyword
    - When a function has been deleted, any use of that function is considered a compile error.
        ```C++
        MyString(char) = delete;
        ```
## Overloading the assignment operator
1. Assignment vs Copy constructor  
    - the copy constructor initializes new objects, whereas the assignment operator replaces the contents of existing objects.
2. Overloading the assignment operator
    ```C++
    Fraction& Fraction::operator= (const Fraction &fraction)
    {
        // do the copy
        m_numerator = fraction.m_numerator;
        m_denominator = fraction.m_denominator;
    
        // return the existing object so we can chain this operator
        return *this;
    }
    ```
3. Issues due to self-assignment
    ```C++
    Fraction f1(5,3);
    f1 = f1; // self assignment
    ```
4. Detecting and handling self-assignment
    ```C++
    Fraction& Fraction::operator= (const Fraction &fraction)
    {
        // self-assignment guard
        if (this == &fraction)
            return *this;
    
        // do the copy
        m_numerator = fraction.m_numerator;
        m_denominator = fraction.m_denominator;
    
        // return the existing object so we can chain this operator
        return *this;
    }
    ```
5. Default assignment operator
    - Tthe compiler will provide a default public assignment operator
    - This assignment operator does memberwise assignment 
##  Shallow vs. deep copying
1. Shallow copying = memberwise copying
2. deep copying
    - when designing classes that handle dynamically allocated memory
    - shallow copies of a pointer just copy the address of the pointer 
    ```C++
    // Copy constructor
    MyString::MyString(const MyString& source)
    {
        // because m_length is not a pointer, we can shallow copy it
        m_length = source.m_length;
    
        // m_data is a pointer, so we need to deep copy it if it is non-null
        if (source.m_data)
        {
            // allocate memory for our copy
            m_data = new char[m_length];
    
            // do the copy
            for (int i=0; i < m_length; ++i)
                m_data[i] = source.m_data[i];
        }
        else
            m_data = 0;
    }
    ```
    ```C++
    // Assignment operator
    MyString& MyString::operator=(const MyString & source)
    {
        // check for self-assignment
        if (this == &source)
            return *this;
    
        // first we need to deallocate any value that this string is holding!
        delete[] m_data;
    
        // because m_length is not a pointer, we can shallow copy it
        m_length = source.m_length;
    
        // m_data is a pointer, so we need to deep copy it if it is non-null
        if (source.m_data)
        {
            // allocate memory for our copy
            m_data = new char[m_length];
    
            // do the copy
            for (int i=0; i < m_length; ++i)
                m_data[i] = source.m_data[i];
        }
        else
            m_data = 0;
    
        return *this;
    }
    ```   