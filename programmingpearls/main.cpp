//
//  main.cpp
//  programmingpearls
//
//  Created by Rob on 31/05/2020.
//  Copyright © 2020 Rob. All rights reserved.
//

#include <bitset>
#include <fstream>
#include <iostream>


int main(int argc, const char * argv[]) {
    const int vectorSize = 10000000;
    std::bitset<vectorSize> bits;
/*
    if(argc < 2) {
        std::cout << "Usage: prog <inputs>" << std::endl << std::endl;
        std::cout << "inputs is a file containing ascii-encoded numeric strings" << std::endl;
        return 1;
    }
    std::fstream myfile(argv[1], std::ios_base::in);
*/
    std::fstream myfile("/Users/rob/data.txt", std::ios_base::in);
    int32_t i;
    while(myfile >> i) {
        bits[i] = 1;
    }
    
    for(int i = 0; i < vectorSize; i++) {
        if(bits[i] == 1) {
            std::cout << i << std::endl;
        }
    }
    return 0;
}
