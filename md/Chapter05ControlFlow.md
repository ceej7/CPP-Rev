## Part5. Control Flow
1. If statement
2. Switch
3. ~~GoTo~~(not recommended)
4. While
5. Do while
6. For
7. Break and continue
8. Random number generation(PRNG)
   1. Generate random number sequence
       ```C++
       #include <stdlib.h>//rand & srand
       #include <ctime>//std::time
       void RandGen::testRand()
       {
           srand(static_cast<unsigned int>(std::time(nullptr)));
           for (int count = 1; count <= 100; ++count)
           {
               std::cout << rand() << "\t";

               // If we've printed 5 numbers, start a new row
               if (count % 5 == 0)
                   std::cout << "\n";
           }
       }
       ```
   2.  Generate random number in range
       ```C++
       void  RandGen::setRoot()
       {
           if (!isInI)
               srand(static_cast<unsigned int>(std::time(nullptr)));
           isInI = true;
       }
       int  RandGen::getRand()
       {
           if (!isInI)
               setRoot();
           isInI = true;
           return rand();
       }
       int RandGen::getRand(int _min, int _max)
       {
           static const double fraction = 1.0 / (RAND_MAX + 1.0);
           //*srand belong to [0,1) inclusive - exclusive
           return _min + static_cast<int>(_max - _min + 1)*(std::rand()*fraction);
       }
        ```
    3. Limit
        - biased result
            > 0 + static_cast(7 * (0 * 0.1))) = 0 + static_cast(0) = 0  
            > 0 + static_cast(7 * (1 * 0.1))) = 0 + static_cast(0.7) = 0  
            > 0 + static_cast(7 * (2 * 0.1))) = 0 + static_cast(1.4) = 1  
            > 0 + static_cast(7 * (3 * 0.1))) = 0 + static_cast(2.1) = 2  
            > 0 + static_cast(7 * (4 * 0.1))) = 0 + static_cast(2.8) = 2  
            > 0 + static_cast(7 * (5 * 0.1))) = 0 + static_cast(3.5) = 3  
            > 0 + static_cast(7 * (6 * 0.1))) = 0 + static_cast(4.2) = 4  
            > 0 + static_cast(7 * (7 * 0.1))) = 0 + static_cast(4.9) = 4  
            > 0 + static_cast(7 * (8 * 0.1))) = 0 + static_cast(5.6) = 5  
            > 0 + static_cast(7 * (9 * 0.1))) = 0 + static_cast(6.3) = 6  
        -  Rand() is that RAND_MAX is usually set to 32767
           -  larger range is not supported
           -  floating point in (0,1) is not supported 
9. std::cin, buffers, and extraction
   1.  Extraction procedure - Buffer - `cin>>`
    >- Data already **in** the input buffer->used for extraction.  
    >- **No** data -> the user is asked to input data for extraction. When the user hits enter, a ‘\n’ character will be placed in the input buffer.  
    >- operator`>>` extracts **as much** data from the input buffer as it can into the variable (**ignoring any `leading` whitespace characters, such as spaces, tabs, or ‘\n’**).  
   2. Validate input
   3. Case 1. Extraction succeeds but input is meaningless
       ```C++
       //Enter a double value: 5
       //Enter one of the following: +, -, *, or /: k
       //Enter a double value: 7
       //Solution
       char getOperator()
       {
           while (true) // Loop until user enters a valid input
           {
               std::cout << "Enter one of the following: +, -, *, or /: ";
               char op;
               std::cin >> op;
       
               // Check whether the user entered meaningful input
               if (op == '+' || op == '-' || op == '*' || op == '/')    
                   return op; // return it to the caller
               else // otherwise tell the user what went wrong
                   std::cout << "Oops, that input is invalid.  Please try again.\n";
           } // and try again
       }
       ```
   4. Case 2. Extraction succeeds but with extraneous input
        ```C++
        //Enter a double value: 5*7
        //Enter one of the following: +, -, *, or /: Enter a double value: 5 * 7 is 35
        //Solution
        double getDouble()
        {
            std::cout << "Enter a double value: ";
            double x;
            std::cin >> x;
            std::cin.ignore(32767, '\n'); // clear (up to 32767) characters out of the buffer until a '\n' character is removed
            return x;
        }
        ```
   5.  Case 3. Extraction fails
        ```C++
        //Enter a double value: a
        //Solution
        double getDouble()
        {
            while (true) // Loop until user enters a valid input
            {
                std::cout << "Enter a double value: ";
                double x;
                std::cin >> x;
            
                if (std::cin.fail()) // has a previous extraction failed?
                {
                    // yep, so let's handle the failure
                    std::cin.clear(); // put us back in 'normal' operation mode
                    std::cin.ignore(32767,'\n'); // and remove the bad input
                }
                else // else our extraction succeeded
                {
                    std::cin.ignore(32767, '\n'); // clear (up to 32767) characters out of the buffer until a '\n' character is removed
                    return x; // so return the value we extracted
                }
            }
        }
        ```
   4. Case 4. Extraction succeeds but the user overflows a numeric value
        ```C++
        //Enter a number between -32768 and 32767: 40000
        //Solution
        std::int16_t x { 0 }; // x is 16 bits, holds from -32768 to 32767
            std::cout << "Enter a number between -32768 and 32767: ";
            std::cin >> x;
        ```