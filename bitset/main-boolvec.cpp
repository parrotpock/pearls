//
//  main-boolvec.cpp
//  programmingpearls
//
//  Created by Rob on 31/05/2020.
//  Copyright © 2020 Rob. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, const char * argv[]) {
    const int vectorSize = 10000000;
    std::vector<bool> bits(10000000);
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
