# Inheritance
## Introduction to inheritance
1. Hierarchies
   - A hierarchy is a diagram that shows how various objects are related.
   - inheritance involves creating new objects by directly acquiring the attributes and behaviors of other objects and then extending or specializing them.
## Basic inheritance in C++
1. In an inheritance (is-a) relationship
   - the class being inherited from is called the parent class, base class, or superclass
   - the class doing the inheriting is called the child class, derived class, or subclass
2. a derived class
    ```C++
    class BaseballPlayer : public Person
    ```
3. Inheritance chains
    ```C++
    class Employee: public Person
    class Supervisor: public Employee
    ```
## Order of construction of derived classes
1. To illustrate
    ```C++
    class Base
    {
    public:
        int m_id;
    
        Base(int id=0)
            : m_id(id)
        {
        }
    
        int getId() const { return m_id; }
    };
    
    class Derived: public Base
    {
    public:
        double m_cost;
    
        Derived(double cost=0.0)
            : m_cost(cost)
        {
        }
    
        double getCost() const { return m_cost; }
    };
    ```
2. First, the most-base class is constructed first. Then each child class is constructed in order, until the most-child class is constructed last.
## Constructors and initialization of derived classes
1. Initial derived
    ```C++
    Derived derived(1.3);
    ```
2. Sequence
   - Memory for derived is set aside (enough for both the Base and Derived portions)
   - The appropriate Derived constructor is called
   - **The Base object is constructed first using the appropriate Base constructor. If no base constructor is specified, the default constructor will be used.**
   - The initialization list initializes variables
   - The body of the constructor executes
   - Control is returned to the caller
3. Initializing base class members
   1. C++ prevents classes from initializing inherited member variables in the initialization list of a constructor.
   2. Const variables - after base class has been initialed, they cannot be changed by the initialization list of derived class
   3. Proper one
        ```C++
        Derived(double cost=0.0, int id=0)
            : Base(id), // Call Base(int) constructor with value id!
                m_cost(cost)
        {
        }
        ```
    4. Now we can make our `m_id` members private
4. Inheritance chains
5. Destructors
   1. When a derived class is destroyed, each destructor is called in the reverse order of construction.
## Inheritance and access specifiers
1. public and private members
   1. public members can be accessed by anybody
   2. private members can only be accessed by member functions of the same class or friends
2. The protected access specifier
   1. can access protected base members from derived class
   2. can not access protected members from outside class
3. Different kinds of inheritance
    |access specifier|public|protected|private|
    |---------|-------|---|---|
    |public   |public   |protected|x|
    |protected|Protected|Protected|x|
    |private  |private  |private  |x|
## Adding new functionality to a derived class
## Calling inherited functions and overriding behavior
1. Calling a base class function
   - When a member function is called with a derived class object, the compiler first looks to see if that member exists in the derived class. If not, it begins walking up the inheritance chain and checking whether the member has been defined in any of the parent classes. It uses the first one it finds.
2. Redefining behaviors
   - access specifier will also be redefined
3. Adding to existing functionality
    ```C++
    class Derived: public Base
    {
    public:
        Derived(int value)
            : Base(value)
        {
        }
    
        int GetValue() { return m_value; }
    
        void identify()
        {
            Base::identify(); // call Base::identify() first
            std::cout << "I am a Derived\n"; // then identify ourselves
        }
    };
    ```
## Hiding inherited functionality
1. Changing an inherited member’s access level - `using`
    ```C++
    class Base
    {
    private:
        int m_value;
    
    public:
        Base(int value)
            : m_value(value)
        {
        }
    
    protected:
        void printValue() { std::cout << m_value; }
    };
    class Derived: public Base
    {
    public:
        Derived(int value)
            : Base(value)
        {
        }
    
        // Base::printValue was inherited as protected, so the public has no access
        // But we're changing it to public via a using declaration
        using Base::printValue; // note: no parenthesis here
    };
    ```
2. hide functionality
    ```C++
    class Base
    {
    public:
        int m_value;
    };
    
    class Derived : public Base
    {
    private:
        using Base::m_value;
    }
    ```
## Multiple inheritance
1. Multiple inheritance enables a derived class to inherit members from more than one parent.
    ```C++
    class Teacher: public Person, public Employee
    ```
2. Problems with multiple inheritance
   1. solved by explicitly specify it
   2. diamond problem
    ```C++
    class PoweredDevice
    {
    };
    
    class Scanner: public PoweredDevice
    {
    };
    
    class Printer: public PoweredDevice
    {
    };
    
    class Copier: public Scanner, public Printer
    {
    };
    ```