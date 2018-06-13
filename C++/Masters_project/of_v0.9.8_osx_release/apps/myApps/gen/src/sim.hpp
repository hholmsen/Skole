//
//  sim.hpp
//  gen
//
//  Created by Henrik Holmsen on 4/21/18.
//

#ifndef sim_hpp
#define sim_hpp

#include <stdio.h>
#include <iostream>
#include "Vertex.hpp"
#include "Vertex_Object.hpp"
#include <vector>
#include <array>
#include <cmath>
#include <memory>

class Sim: public Vertex_Object
{
private:
    float force_vector_x;
    float force_vector_y;
    float force_vector_z;
    std::vector<float> force_begin_x;
    std::vector<float> force_begin_y;
    std::vector<float> force_begin_z;
    Vertex_Object v0;
public:
    Sim()=default;
    Sim(float fx, float fy, float fz, std::vector<float> bx,std::vector<float> by, std::vector<float> bz, Vertex_Object v0);
    void calculate_update(void);
    std::array<float, 3> vector_product_3d(float vec_1_x,float vec_1_y,float vec_1_z,float vec_2_x,float vec_2_y,float vec_2_z);
    std::array<float,3> translate_into_coordinates(std::array<float,3>& vec,std::array<float,3>& co);
    Vertex_Object _v0_return(void);
    
    
};

#endif /* sim_hpp */
