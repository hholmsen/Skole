//
//  GA.hpp
//  Generative_design_sim_ga
//
//  Created by Henrik Holmsen on 5/25/18.
//

#ifndef GA_hpp
#define GA_hpp

#include <stdio.h>
#include <vector>
#include <array>
#include <cmath>
#include "Obj.hpp"


class GA{
private:
//    needs to save initial specimens, not the ones borken by sim.
//    
    std::vector<Obj> specimens;
    std::vector<Obj> initial_specimens;
    std::vector<std::array<double,2>> fitness;
public:
    GA() = default;
    GA(int num_specimens, int num_iterations);
    void init_specimens(int num_specimens, double set_random,int size, double radius);
    void criterions(void);
    void calculate_fitness(double size, int num_iterations, double height);
    void compare_specimens(void);
    void mate_specimens(int size);
    void run_one_gen(void);
    std::vector<Obj>& get_specimens(void);
    void print_fitness(void);
    
};
#endif /* GA_hpp */
