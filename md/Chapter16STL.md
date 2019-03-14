# The Standard Template Library
## The Standard Library
1. The Standard Library - a collection of classes that provide templated containers, algorithms, and iterators
## STL containers overview
1. Sequence Containers
   1. std::vector  
        - a dynamic array capable of growing as needed to contain its elements. The vector class allows random access to its elements via operator[], and inserting and removing elements from the end of the vector is generally fast.
   2. std::deque - a double-ended queue class
   3. std::array - encapsulates fixed size arrays
   4. std::list 
        - list is a special type of sequence container called a doubly linked list where each element in the container contains pointers that point at the next and previous elements in the list
   6. std::forward_list - foward linked list
   7. std::basic_string - vector of char
2. Associative Containers
   1. set - a container that stores unique elements, with duplicate elements disallowed
   2. multiset - a set where duplicate elements are allowed
   3. map - each element is a pair, called a key/value pair (red-black tree)
   4. multimap - a map that allows duplicate keys
3. Container Adapters
   1. stack -LIFO
   2. queue - FIFO
   3. priority queue - where the elements are kept sorted
      1. by binary heap
## STL iterators overview
1. An Iterator is an object that can traverse (iterate over) a container class
   1. Operator* -- Dereferencing the iterator
   2. Operator++
   3. Operator== and Operator!=
   4. Operator=
   5. begin() - cbegin() - const
   6. end() - cend() - const
   7. container::iterator - container::const_iterator
2. Iterating through a vector
    ```C++
    std::vector<int> vect;
    for (int count=0; count < 6; ++count)
        vect.push_back(count);

    std::vector<int>::const_iterator it; // declare a read-only iterator
    it = vect.begin(); // assign it to the start of the vector
    while (it != vect.end()) // while it hasn't reach the end
        {
        std::cout << *it << " "; // print the value of the element it points to
        ++it; // and iterate to the next element
        }

    std::cout << '\n';
    ```
3. Iterating through a map
    ```C++
    std::map<int, string> mymap;
    mymap.insert(make_pair(4, "apple"));
    mymap.insert(make_pair(2, "orange"));
    mymap.insert(make_pair(1, "banana"));
    mymap.insert(make_pair(3, "grapes"));
    mymap.insert(make_pair(6, "mango"));
    mymap.insert(make_pair(5, "peach"));

    std::map<int, string>::const_iterator it; // declare an iterator
    it = mymap.begin(); // assign it to the start of the vector
    while (it != mymap.end()) // while it hasn't reach the end
    {
        std::cout << it->first << "=" << it->second << " "; // print the value of the element it points to
        ++it; // and iterate to the next element
    }

    std::cout << '\n';
    ```
## STL algorithms overview
1. min_element and max_element
    ```C++
    std::list<int>::const_iterator it; // declare an iterator
    it = min_element(li.begin(), li.end());
        std::cout << *it << ' ';
    it = max_element(li.begin(), li.end());
        std::cout << *it << ' ';
    ```
2. find (and list::insert)
    ```C++
    std::list<int> li;
    for (int nCount=0; nCount < 6; ++nCount)
        li.push_back(nCount);

    std::list<int>::iterator it; // declare an iterator
    it = find(li.begin(), li.end(), 3); // find the value 3 in the list
    li.insert(it, 8); // use list::insert to insert the value 8 before it

    for (it = li.begin(); it != li.end(); ++it) // for loop with iterators
        std::cout << *it << ' ';
    ```
3. sort and reverse
   ```C++
    std::sort(vect.begin(), vect.end()); // sort the list
 
    std::vector<int>::const_iterator it; // declare an iterator
    for (it = vect.begin(); it != vect.end(); ++it) // for loop with iterators
        cout << *it << ' ';
 
    std::cout << '\n';
 
    std::reverse(vect.begin(), vect.end()); // reverse the list
 
    for (it = vect.begin(); it != vect.end(); ++it) // for loop with iterators
        std::cout << *it << ' ';
    ```