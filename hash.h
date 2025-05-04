#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T w[5] = {0,0,0,0,0};

        // initialize the string to hold info
        std::string myStr = "";
        // loop thru input string, all lowercase
        for (unsigned int i = 0; i < k.size(); ++i) {
          char characterr = k[i];
          if (std::isalpha(characterr)) {
            myStr += std::tolower(characterr);
          }
          else {
            myStr += characterr;
          }
        }

        //std:: cout<<"here is the string: "<< myStr<<std::endl;

        int length = myStr.size();
        // six chars process per iteration
        int x = ((6-(length%6))%6);
        if (x != 0) {
          myStr = std::string(x,'a')+myStr;
        }
        //std:: cout<<"here is the padded string: "<< myStr<<std::endl;
        

        //int lenggg = myStr.size();
        int grpnum=(myStr.size())/6;
        int startgrp=5-grpnum;
        //if (grpss>5) {grpss=5;}
        for (int i=0; i < grpnum; ++i) {
          HASH_INDEX_T value=0;
          //int s =(i>=6)?(i-6):0;
          for (int j=0; j<6;++j) {
            value=value*36+letterDigitToNumber(myStr[i*6+j]);

          }
          //w[i]=value;
          w[startgrp+i]=value;
          //grpnum++;
        }

        HASH_INDEX_T h=0;
        for (int i=0; i < 5; ++i) {
          h+=rValues[i]*w[i];
        }
        return h;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (std::isdigit(letter)) {
          return letter-'0'+26;
        }
        else if (std::isalpha(letter)) {
          return std::tolower(letter)-'a';
        }
        return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
