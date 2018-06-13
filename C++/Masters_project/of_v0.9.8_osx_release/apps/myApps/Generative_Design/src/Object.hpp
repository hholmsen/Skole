//
//  Object.hpp
//  Generative_Design
//
//  Created by Henrik Holmsen on 5/1/18.
//

#ifndef Object_hpp
#define Object_hpp
#define PI 3.141592

#include <stdio.h>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include "Vertex.hpp"
#include "Quad.hpp"

class Object
{
private:
    std::vector<Quad> obj;
    int sim_count;
    int circumference_resolution;
    int vertex_resolution;

    
    //    TODO: keep an array of all of the previos length, and update this every new run.
public:
    Object() = default;
    Object(int num_height, int num_points, double radius);
    std::vector<Quad>& get_quads(void);
    std::array<double, 3> vector_product_3d(double vec_1_x, double vec_1_y, double vec_1_z, double vec_2_x, double vec_2_y, double vec_2_z, float sgn);
    void set_vertex(std::array<double, 3>& pos, int indexobj, int indexquad);
    //    TODO: make something that updates all the springs in quads in order to reflect all the adjacent spring forces as well, then update all the verteces when this is calculated(as in x1.beregnBoy), when a new vertex is set the Quads class wil calculate the difference in spring force from the previous.
    void sim_routine(void);
    void calc_boi(std::array<double,3> p1,std::array<double,3> pX,std::array<double,3> p2, int i, int is_h);
    void mod(void);
    int get_c_res();
};

#endif /* Object_hpp */
