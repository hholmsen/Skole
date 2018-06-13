//
//  Quad.hpp
//  Generative_Design
//
//  Created by Henrik Holmsen on 5/1/18.
//

#ifndef Quad_hpp
#define Quad_hpp

#include <stdio.h>
#include<iostream>
#include <array>
#include "Vertex.hpp"
#include <cmath>


class Quad
{
private:
    std::array<Vertex, 4> qu;
    std::array<std::array<double, 3>,3> springs;
    std::array<double, 3> curr_lenghts;
    std::array<double, 3> prev_lenghts;
    std::array<double, 2> curr_angles;
    std::array<double, 2> prev_angles;
    int index;
public:
    Quad() = default;
    Quad(std::array<Vertex, 4>);
    Quad(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
    Quad(std::array<double, 3> v1,std::array<double, 3> v2,std::array<double, 3> v3,std::array<double, 3> v4);
    void set_h_angles(float hangle);
    void set_v_angles(float vangle);
    float get_h_angle(void);
    float get_v_angle(void);
    void set_spring(std::array<std::array<double, 3>,3>& s);
    double extracted(double constant);
    void add_to_springs(int is_h, int x_y_z, double value);
    void update_spring(double constant);
    double calculate_len(std::array<double, 3>& point1, std::array<double,3>& point2);
    std::array<double, 3> calculate_vec(std::array<double, 3>& point1, std::array<double, 3>& point2);
    std::array<Vertex, 4>& get_Vertex(void);
    void set_new_vertex(std::array<double, 3>& npos, int index);
    
    std::array<std::array<double, 3>,3> get_springs(void);

    
};
#endif /* Quad_hpp */
