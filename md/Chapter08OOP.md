## Part8. Basic object-oriented programming
1. Classes and class members
   1. Classes
   2. Member Functions
2. Public vs private access specifiers
   1. Access specifiers
      - public/protected/private
   2. Mixing access specifiers
      - member variables are usually made private, and member functions are usually made public.
   3. Structs vs classes revisited
      - A class defaults its members to private. A struct defaults its members to public.
      - Structs inherit from other classes publicly and classes inherit privately. 
3. Access functions and encapsulation
   1. Encapsulation
   2. encapsulated classes are easier to use and reduce the complexity of your programs
   3. encapsulated classes help protect your data and prevent misuse
   4. encapsulated classes are easier to debug
4. Constructors
   1. Default constructors
        ```C++
        class Fraction
        {
            Fraction();
            Fraction(int numerator, int denominator=1);
        }
        ```
   2. Direct and uniform initialization
        ```C++
        int x(5);
        Fraction fiveThirds(5, 3);
        ```
   3. Copy initialization using equals with classes
      ```C++
      Fraction six = Fraction(6);
      ```
   4. An implicitly generated default constructor
   5. Classes containing classes
      ```C++
      #include <iostream>
      
      class A
      {
      public:
         A() { std::cout << "A\n"; }
      };
      
      class B
      {
      private:
         A m_a; // B contains A as a member variable
      
      public:
         B() { std::cout << "B\n"; }
      };
      
      int main()
      {
         B b;
         return 0;
      }
      ```
5. Constructor member initializer lists
   1. C++ provides a method for ***initializing class member variables*** (rather than assigning values to them after they are created)
   2. member initializer list 
      ```C++
      class Something
      {
      private:
         int m_value1;
         double m_value2;
         char m_value3;

      public:
         // directly initialize, not assignment
         Something() : m_value1(1), m_value2(2.2), m_value3('c') 
         {
         }
      }
      ```
   3. passing in initialization values
      ```C++
      Something(int value1, double value2, char value3='c')
            : m_value1(value1), m_value2(value2), m_value3(value3)
      {
      }
      ``` 
   4. Uniform initialization in C++11   
      ```c++
      Something(): m_value { 5 }
      {
      } 
      ```    
   5. C++11, initial a member array
      ```C++
      class Something
      {
      private:
         const int m_array[5];
      public:
         Something(): m_array { 1, 2, 3, 4, 5 }
         {
         }
      
      };
      ```
6. Non-static member initialization
   1. give normal class member variables a default initialization value directly
   2. Non-static member initialization (also called in-class member initializers) provides default values for your member variables that your constructors will use **if the constructors do not provide initialization values** for the members themselves (**via the member initialization list**)
7. Overlapping and delegating constructors
   1. Overlapping error
      ```C++
      class Foo
      {
      public:
         Foo()
         {
            // code to do A
         }
      
         Foo(int value)
         {
            Foo(); // use the above constructor to do A (doesn't work)
            // code to do B
         }
      };
      ```
   2. Solution: Using a separate function
   3. Delegating constructors in C++11
      1. Example 01
         ```C++
         class Foo
         {
         private:
         
         public:
            Foo()
            {
            }
            Foo(int value): Foo() // delegate: use Foo() default constructor to do A
            {
            }
         
         };
         ```
      2. Example 02
         ```C++
         class Employee
         {
         private:
            int m_id;
            std::string m_name;
         
         public:
            Employee(int id=0, const std::string &name=""):
               m_id(id), m_name(name)
            {
               std::cout << "Employee " << m_name << " created.\n";
            }
         
            // Use a delegating constructors to minimize redundant code
            Employee(const std::string &name) : Employee(0, name) { }
         }
         ```
      3. Note
         1. your constructors can delegate or initialize, but not both.
         2. it’s possible for one constructor to delegate to another constructor, which delegates back to the first constructor
8. Destructors
   1. destructors are designed to help clean up
   2. Destructor naming
      1. The destructor must have the same name as the class, preceded by a tilde (~).
      2. The destructor can not take arguments.
      3. The destructor has no return type.
   3. RAII (Resource Acquisition Is Initialization)
      1. resource use is tied to the lifetime of objects with automatic duration 
      2. RAII is implemented via classes with constructors and destructors.
      3. Under the RAII paradigm, objects holding resources should not be dynamically allocated.
9. The hidden “this” pointer
   1. C++ utilizes a hidden pointer named “this”!
   2. Explicityly
      ```C++
      class Something
      {
      private:
         int data;

      public:
         Something(int data)
         {
            this->data = data;
         }
      };
      ```
   3. Chain
      ```C++
      class Calc
      {
      private:
         int m_value;
      
      public:
         Calc() { m_value = 0; }
      
         Calc& add(int value) { m_value += value; return *this; }
         Calc& sub(int value) { m_value -= value; return *this; }
         Calc& mult(int value) { m_value *= value; return *this; }
      
         int getValue() { return m_value; }
      };
      //Calc calc;
      //calc.add(5).sub(3).mult(4);
      ```
11. Class code and header files
    1. Defining member functions outside the class definition
    2. Default parameters
         - Default parameters for member functions should be declared in the class definition (in the header file), where they can be seen by whomever #includes the header.
12. Const class objects and member functions
    1. Const classes
       - no attempting to change a member variable directly
       - no calling a member function that attempts to change a member variable
    2. const member function
       - guarantees it will not modify the object or call any non-const member functions (as they may modify the object)
       - eg
            ```C++
            class Something
            {
            public:
               int m_value ;
               void resetValue() const { m_value = 0; } 
            };
            ```
    3. Const references
       - const reference and only call const member function
    4. Overloading const and non-const function
         ```C++
         #include <string>
         
         class Something
         {
         private:
            std::string m_value;
         
         public:
            Something(const std::string &value="") { m_value= value; }
         
            const std::string& getValue() const { return m_value; } // getValue() for const objects
            std::string& getValue() { return m_value; } // getValue() for non-const objects
         };
         ```
13.