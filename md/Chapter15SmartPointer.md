## Part15. Smart Pointer
1. Intro to smart pointers and move semantics
   1. First Draft
        ```C++
        template<class T>
        class Auto_ptr1
        {
            T* m_ptr;
        public:
            // Pass in a pointer to "own" via the constructor
            Auto_ptr1(T* ptr=nullptr)
                :m_ptr(ptr)
            {
            }
            // The destructor will make sure it gets deallocated
            ~Auto_ptr1()
            {
                delete m_ptr;
            }
            // Overload dereference and operator-> so we can use Auto_ptr1 like m_ptr.
            T& operator*() const { return *m_ptr; }
            T* operator->() const { return m_ptr; }
        };
        ```
   2. A critical flaw
        ```C++
        Auto_ptr1<Resource> res1(new Resource);
        Auto_ptr1<Resource> res2(res1);
        ```
        - resource is deleted twice
   3. Two critical flaw
        ```C++
        ??? generateResource()
        {
            Resource *r = new Resource;
            return Auto_ptr1(r);//copy and crushed
        }
        ```
   4. Move semantics
        ```C++
        //Auto_ptr2, compared with Auto_ptr1
        // override copy and assign owner
        Auto_ptr2(Auto_ptr2& a) // note: not const
        {
            m_ptr = a.m_ptr; 
            a.m_ptr = nullptr; 
        }
        Auto_ptr2& operator=(Auto_ptr2& a) // note: not const
        {
            if (&a == this)
                return *this;
            delete m_ptr; 
            m_ptr = a.m_ptr; 
            a.m_ptr = nullptr;
            return *this;
        }
        ```
   5. `std::auto_ptr()`, and why to avoid it
      - First, because std::auto_ptr implements move semantics through the copy constructor and assignment operator, passing a std::auto_ptr by value to a function will cause your resource to get moved to the function parameter 
      - Second, std::auto_ptr always deletes its contents using non-array delete.
      - Finally, auto_ptr doesn’t play nice with a lot of the other classes in the standard library, including most of the containers and algorithms.
2. R-value references
   1. L-values and r-values
      - It’s simplest to think of an l-value (also called a locator value) as a function or an object. All l-values have assigned memory addresses.
      - It’s simplest to think of an r-value as “everything that is not an l-value”. This notably includes literals (e.g. 5), temporary values (e.g. x+1), and anonymous objects (e.g. Fraction(5, 2)).
   2. L-value references
        |L-value reference|	Can be initialized with	|Can modify|
        |-|-|-|
        |Modifiable l-values	|Yes	|Yes|
        |Non-modifiable l-values|	No|	No|
        |R-values|	No|	No|

        |L-value reference to const|	Can be initialized with	|Can modify|
        |-|-|-|
        |Modifiable l-values	|Yes|	No|
        |Non-modifiable l-values	|Yes	|No|
        |R-values	|Yes	|No|
   3. R-value references
        |R-value reference|	Can be initialized with	|Can modify|
        |-|-|-|
        |Modifiable l-values	|No|	No|
        |Non-modifiable l-values	|No	|No|
        |R-values	|Yes	|Yes|

        |R-value reference to const|	Can be initialized with	|Can modify|
        |-|-|-|
        |Modifiable l-values	|No|	No|
        |Non-modifiable l-values	|No	|No|
        |R-values	|Yes	|No|
    4. R-value references have two properties that are useful.
        ```C++
        int &&rref = 5; // because we're initializing an r-value reference with a literal, a temporary with value 5 is created here
        rref = 10;
        std::cout << rref;
        ```
    5. R-value references as function parameters
        ```C++
        void fun(const int &lref) // l-value arguments will select this function
        {
            std::cout << "l-value reference to const\n";
        }
        
        void fun(int &&rref) // r-value arguments will select this function
        {
            std::cout << "r-value reference\n";
        }
        
        int main()
        {
            int x = 5;
            fun(x); // l-value argument calls l-value version of function
            fun(5); // r-value argument calls r-value version of function
        
            return 0;
        }
        ```
        - useful when you want to have different behavior for l-value and r-value arguments
        ```C++
        int &&ref = 5;
        fun(ref);
        //it calls void fun(const int &lref) 
        //in that ref itself is a l-value
        ```
    6. Returning an r-value reference
       - You should almost never return an r-value reference
3. Move constructors and move assignment
   1. Copy constructors and copy assignment
   2. Move constructors and move assignment
        ```C++
        template<class T>
        class Auto_ptr4
        {
            T* m_ptr;
        public:
            Auto_ptr4(T* ptr = nullptr)
                :m_ptr(ptr)
            {
            }
        
            ~Auto_ptr4()
            {
                delete m_ptr;
            }
        
            // Copy constructor
            // Do deep copy of a.m_ptr to m_ptr
            Auto_ptr4(const Auto_ptr4& a)
            {
                m_ptr = new T;
                *m_ptr = *a.m_ptr;
            }
        
            // Move constructor
            // Transfer ownership of a.m_ptr to m_ptr
            Auto_ptr4(Auto_ptr4&& a)
                : m_ptr(a.m_ptr)
            {
                a.m_ptr = nullptr; // we'll talk more about this line below
            }
        
            // Copy assignment
            // Do deep copy of a.m_ptr to m_ptr
            Auto_ptr4& operator=(const Auto_ptr4& a)
            {
                // Self-assignment detection
                if (&a == this)
                    return *this;
        
                // Release any resource we're holding
                delete m_ptr;
        
                // Copy the resource
                m_ptr = new T;
                *m_ptr = *a.m_ptr;
        
                return *this;
            }
        
            // Move assignment
            // Transfer ownership of a.m_ptr to m_ptr
            Auto_ptr4& operator=(Auto_ptr4&& a)
            {
                // Self-assignment detection
                if (&a == this)
                    return *this;
        
                // Release any resource we're holding
                delete m_ptr;
        
                // Transfer ownership of a.m_ptr to m_ptr
                m_ptr = a.m_ptr;
                a.m_ptr = nullptr; // we'll talk more about this line below
        
                return *this;
            }
        
            T& operator*() const { return *m_ptr; }
            T* operator->() const { return m_ptr; }
            bool isNull() const { return m_ptr == nullptr; }
        };
        class Resource
        {
        public:
            Resource() { std::cout << "Resource acquired\n"; }
            ~Resource() { std::cout << "Resource destroyed\n"; }
        };
        
        Auto_ptr4<Resource> generateResource()
        {
            Auto_ptr4<Resource> res(new Resource);
            return res; // this return value will invoke the move constructor
        }
        
        int main()
        {
            Auto_ptr4<Resource> mainres;
            mainres = generateResource(); // this assignment will invoke the move assignment
        
            return 0;
        }
        ```
   3. Output
        >Resource acquired  
        >Resource destroyed
   4. what happened?
      1. Inside generateResource(), local variable res is created and initialized with a dynamically allocated Resource, which causes the first “Resource acquired”.
      2. **Res is returned back to main() by value. Res is move constructed into a temporary object, transferring the dynamically created object stored in res to the temporary object. We’ll talk about why this happens below.**
      3. Res goes out of scope. Because res no longer manages a pointer (it was moved to the temporary), nothing interesting happens here.
      4. The temporary object is move assigned to mainres. This transfers the dynamically created object stored in the temporary to mainres.
      5. The assignment expression ends, and the temporary object goes out of expression scope and is destroyed. However, because the temporary no longer manages a pointer (it was moved to mainres), nothing interesting happens here either.
      6.  At the end of main(), mainres goes out of scope, and our final “Resource destroyed” is displayed. 
   5. When are the move constructor and move assignment called?
      1. The move constructor and move assignment are called when those functions have been defined, and the argument for construction or assignment is an r-value. Most typically, this **r-value will be a literal or temporary value**.
   6. Automatic l-values returned by value may be moved instead of copied
      1. In the generateResource() function of the Auto_ptr4 example above, when variable res is returned by value, it is moved instead of copied, even though res is an l-value.
   7. Disabling copying
        ```C++
        //Auto_ptr5 delete copy
        Auto_ptr5(const Auto_ptr5& a) = delete;
        Auto_ptr5& operator=(const Auto_ptr5& a) = delete;
        ```
        - If you were to try to pass an Auto_ptr5 l-value to a function by value, the compiler would complain that the copy constructor required to initialize the copy constructor argument has been deleted. 
4. 