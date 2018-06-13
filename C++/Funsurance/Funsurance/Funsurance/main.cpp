//
//  main.cpp
//  Funsurance
//
//  A desentralized insurance solution implemented in C++
//
//
//  Created by Henrik Holmsen on 12/30/17.
//  Copyright © 2017 Henrik Holmsen. All rights reserved.
//
#include "Case_Chain.hpp"
#include "Case_Chain.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    Case_Chain chain = Case_Chain();
    chain.add_to_chain(Case(1,"hei"));
    chain.add_to_chain(Case(2,"heilåå"));
    std::cout<< "height "<< chain.get_chain_height()<<"\n";
    std::cout<< "text2 " << chain.get_Case_sub(1).get_case_text()<<"\n";
    return 0;
}
