# An introduction to object relationships
## Object relationships
1. Relationships between objects
   - a square “is-a” shape
   - A car “has-a” steering wheel
   - A computer programmer “uses-a” keyboard
   - A flower “depends-on” a bee for pollination
   - A student is a “member-of” a class
   - And your brain exists as “part-of” you
## Composition
1. object composition models a “has-a” relationship between two objects.
   - it allows us to create complex classes by combining simpler, more easily manageable parts.
2. relationship
   - The part (member) is part of the object (class)
   - The part (member) can only belong to one object (class) at a time
   - The part (member) has its existence managed by the object (class)
   - The part (member) does not know about the existence of the object (class)
## Aggregation
1. relationship
- The part (member) is part of the object (class)
- The part (member) can belong to more than one object (class) at a time
- The part (member) does not have its existence managed by the object (class)
- The part (member) does not know about the existence of the object (class)
2. Implementation
    ```C++
    class Teacher
    {
    private:
        std::string m_name;
    
    public:
        Teacher(std::string name)
            : m_name(name)
        {
        }
    
        std::string getName() { return m_name; }
    };
    
    class Department
    {
    private:
        Teacher *m_teacher; // This dept holds only one teacher for simplicity, but it could hold many teachers
    
    public:
        Department(Teacher *teacher = nullptr)
            : m_teacher(teacher)
        {
        }
    };
    ```
## Association 
1. relationship - "use-a"
   - The associated object (member) is otherwise unrelated to the object (class)
   - The associated object (member) can belong to more than one object (class) at a time
   - The associated object (member) does not have its existence managed by the object (class)
   - The associated object (member) may or may not know about the existence of the object (class)
2. Reflexive association
    ```C++
    class Course
    {
    private:
        std::string m_name;
        Course *m_prerequisite;
    
    public:
        Course(std::string &name, Course *prerequisite=nullptr):
            m_name(name), m_prerequisite(prerequisite)
        {
        }
    
    };
    ```
3. Associations can be indirect
## Dependencies
1. A dependency occurs when one object invokes another object’s functionality in order to accomplish some specific task.
2. Dependencies vs Association in C++
   1. In C++, associations are a relationship between two classes at the class level.
   2. Dependencies typically are not represented at the class level
## Container classes
1. Container classes is a class designed to hold and organize multiple instances of another type
2. Types of containers
   1. Value containers 
   2. Reference containers 
## std::initializer_list
1. fixed array
    ```C++
    int *array = new int[5] { 5, 4, 3, 2, 1 }; // initializer list
    ```
2. class with initializer_list
    ```C++
    class IntArray
    {
    private:
        int m_length;
        int *m_data;
        IntArray(const std::initializer_list<int> &list): // allow IntArray to be initialized via list initialization
            IntArray(list.size()) // use delegating constructor to set up initial array
        {
            // Now initialize our array from the list
            int count = 0;
            for (auto &element : list)
            {
                m_data[count] = element;
                ++count;
            }
        }
    }
    ```
3. Class assignment using std::initializer_list
   1. if you implement a constructor that takes a std::initializer_list, you should ensure you do at least one of the following
      - Provide an overloaded list assignment operator
      - Provide a proper deep-copying copy assignment operator
      - Make the constructor explicit, so it can’t be used for implicit conversions
   2. Why?
      - consider the above class
        ```C++
        array = { 1, 3, 5, 7, 9, 11 };
        ```
   3.  If you provide list construction, it’s a good idea to provide list assignment as well.