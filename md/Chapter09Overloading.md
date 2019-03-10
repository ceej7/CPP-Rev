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
##
