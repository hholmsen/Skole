//
//  Obj.hpp
//  Generative_design_sim_ga
//
//  Created by Henrik Holmsen on 5/22/18.
//

#ifndef Obj_hpp
#define Obj_hpp

#include <stdio.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <random>
#include "ctime"
#include "Vertex.hpp"

#define PI 3.141592



// make a list of verteces
// use the indeces in this list to make edges, edge_lens and
//


class Obj{
private:
    std::vector<Vertex> verteces;
    std::vector<std::array<int, 2>> horizontal_edges;
    std::vector<std::array<int, 2>> vertical_edges;
    std::vector<std::array<int, 2>> cross_edges;
    std::vector<double> horizontal_lengths;
    std::vector<double> vertical_lengths;
    std::vector<double> cross_lengths;
    std::vector<double> horizontal_angles;
    std::vector<double> vertical_angles;
    int n_p;
    bool ext =false;
public:
    Obj()=default;
    Obj(std::vector<std::array<double, 3>>,int np);
    Obj(int num_height, int num_points, double radius, double randomness);
    std::vector<Vertex>& get_verteces(void);
    bool update_angles(int num_heights, int num_points);
    double update_lenghts(std::array<double, 3> v1, std::array<double, 3> v2);
    bool add_vector_force(void);
    std::vector<std::array<double, 3>> run_one_sim(void);
    bool bouyancy_routine(int,int,int,int);
    std::vector<std::array<int, 2>> get_horizontal_edges(void);
    std::vector<std::array<int, 2>> get_vertical_edges(void);
    std::vector<std::array<int, 2>> get_cross_edges(void);
    void external_forces(void);
    void set_bb(void);
    
};
#endif /* Obj_hpp */
