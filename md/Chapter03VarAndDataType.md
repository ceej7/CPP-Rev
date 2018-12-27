## Part3. Variables and Fundamental Data Types
1. Variable initialization
   - Copy initialization
     ```C++
     int nValue = 5;
     ```
   - Direct initialization
     ```C++
     int nValue(5);
     ```
   - Performance  
     Generally, the **direct initialization** out-performes for some *data types* and come with some benefits among *classes*
2. Uniform initialization in C++11
   - Because C++ grew organically, the copy initialization and direct initialization forms only work for some types of variables (for example, you can’t use either of these forms to initialize a list of values).
   - In an attempt to provide a single initialization mechanism that will work with all data types, C++11 adds a new form of initialization called uniform initialization (also called brace initialization):
      ```C++
      int value{5}; // uniform initialization
      ```
   - Initializing a variable with an empty brace indicates default initialization. Default initialization initializes the variable to zero (or empty, if that’s more appropriate for a given type).
      ```C++
      int value{}; // default initialization to 0
      ```
   - Uniform initialization has the added benefit of **disallowing “narrowing” type conversions**. This means that if you try to use uniform initialization to initialize a variable with a value it can not safely hold, the compiler will throw an warning or error. For example:
      ``` C++
      int value{4.5}; // error: an integer variable can not hold a non-integer value
      ```
      > Rule: If you’re using a C++11 compatible compiler, favor uniform initialization
3. `size_t`
   ```C++
   size_t sz_t=sizeof(int) //usually 32-bit unsigned integral value.
   ```
4. The fixed-width integers (`cstdint` in `C++11`)

     |Type     |Length       |
     |---------|------|
     |int8_t	  |1 byte signed|
     |uint8_t	|1 byte unsigned|
     |int16_t	|2 byte signed|
     |uint16_t	|2 byte unsigned|
     |int32_t	|4 byte signed	|
     |uint32_t	|4 byte unsigned|
     |int64_t	|8 byte signed|
     |uint64_t|8 byte unsigned|
5. Floating point number

    |Size|Range|Precision|
    |--|--|--|
    |4 bytes	|±1.18 x 10-38 to ±3.4 x 1038	|6-9 significant digits, typically 7|
    |8 bytes	|±2.23 x 10-308 to ±1.80 x 10308	|15-18 significant digits, typically 16|
    |80-bits (12 bytes)	|±3.36 x 10-4932 to ±1.18 x 104932	|18-21 significant digits|
    |16 bytes	|±3.36 x 10-4932 to ±1.18 x 104932	|33-36 significant digits|
   - TODO: 
     - [ ] **the IEEE 754 binary format**
   - Rounding errors
     - For instance, in binary, 0.1 is represented in the infinite sequence 0.0001100110011....When assigned to a floating point.
        ```C++
        double d(0.1);
        std::cout << d << std::endl; // use default cout precision of 6
        std::cout << std::setprecision(17);
        std::cout << d << std::endl;
        return 0;
        ```
     - The OPT is 
        > 0.1  
        > 0.10000000000000001 //not precise here
     - Consequence, please consider the situation adding up ten `0.1`
        ```C++
        double d2(0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1); // should equal 1.0
        std::cout << d2 << std::endl;
        ``` 
      - The OPT is
        > 0.99999999999999989 //which is not equal to 1.0, out of expectation.
6. char and type casting
   - For instance
      ```C++
      char ch(97);
      std::cout << ch << std::endl;
      std::cout << static_cast<int>(ch) << std::endl;
      std::cout << ch << std::endl;
      ```
    - TODO:
      - [x] `static_cast<type>()`
        -  same as cast in C `(type)var`
      - [ ] `dynamic_cast<type>()`
      - [ ] `const_cast<type>()`
      - [ ] `reinterpret_cast<type>()`
    - `std::endl` v.s. `\n`
      - `std::cout` is used for output, adn the output may be buffered
      - `std::endl` makes sure your output is output at once, flush the buffer
      - `\n` vice versa
7. const
     - compile constant and runtime constant
     - `constexpr` ensures a compile-time constant `C++11`
8. Relational operator - floating point
    ```C++
    // return true if the difference between a and b is less than absEpsilon
    // or within relEpsilon percent of the larger of a and b
    bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
    {
        // Check if the numbers are really close -- needed when comparing numbers near zero.
        double diff = fabs(a - b);
        if (diff <= absEpsilon)
            return true;
    
        // Otherwise fall back to Knuth's algorithm
        return diff <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
    }
    ``` 
9. Two complements
    - The first bit is a sign bit, `0->+/1->-`
    - Positive signed numbers are stored just like positive unsigned numbers (with the sign bit set to 0).
    - Negative signed numbers are stored as the inverse of the positive number, plus 1.
    - Converting binary two’s complement to integers 
      - If the sign bit is 1, then we invert the bits, add 1, then convert to decimal, then make that decimal number negative (because the sign bit was originally negative).
10. `std::bitset` 
     - Demo 1 and 2 is enough for understanding
     - Demo 1
        ```C++
        // Define 8 separate bit flags (these can represent whatever you want)
        const unsigned char option0 = 1 << 0; // 0000 0001 
        const unsigned char option1 = 1 << 1; // 0000 0010
        const unsigned char option2 = 1 << 2; // 0000 0100
        const unsigned char option3 = 1 << 3; // 0000 1000
        const unsigned char option4 = 1 << 4; // 0001 0000
        const unsigned char option5 = 1 << 5; // 0010 0000
        const unsigned char option6 = 1 << 6; // 0100 0000
        const unsigned char option7 = 1 << 7; // 1000 0000

        std::bitset<8> bits(option1 | option2); // start with option 1 and 2 turned on
        std::bitset<8> morebits(0x3); // start with bit pattern 0000 0011
        std::cout << bits << std::endl;
        std::cout << morebits << std::endl;
        ```
     - Demo 2
        ```C++
        const int option0 = 0;
        const int option1 = 1;
        const int option2 = 2;
        const int option3 = 3;
        const int option4 = 4;
        const int option5 = 5;
        const int option6 = 6;
        const int option7 = 7;

        std::bitset<8> bits(0x2); // we need 8 bits, start with bit pattern 0000 0010
        bits.set(option4); // set bit 4 to 1 (now we have 0001 0010)
        bits.flip(option5); // flip bit 5 (now we have 0011 0010) 0-1 and vice versa
        bits.reset(option5); // set bit 5 back to 0 (now we have 0001 0010)

        std::cout << "Bit 4 has value: " << bits.test(option4) << '\n';
        std::cout << "Bit 5 has value: " << bits.test(option5) << '\n';
        std::cout << "All the bits: " << bits << '\n';
        ```