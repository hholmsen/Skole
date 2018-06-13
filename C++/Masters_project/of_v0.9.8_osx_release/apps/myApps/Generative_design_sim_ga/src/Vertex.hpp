//
//  Vertex.hpp
//  Generative_design_sim_ga
//
//  Created by Henrik Holmsen on 5/22/18.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include <array>

class Vertex{
private:
    double X;
    double Y;
    double Z;
    double force_X;
    double force_Y;
    double force_Z;

public:
    Vertex() = default;
    Vertex(double initX,double initY,double initZ);
    bool set_new_vertex(std::array<double, 3> XYZ);
    bool add_to_vertex(std::array<double, 3> XYZ);
    bool set_new_force(std::array<double, 3> XYZ);
    bool add_to_forces(std::array<double, 3> XYZ);
    std::array<double, 3> get_vertex_xyz(void);
    std::array<double, 3> get_force_xyz(void);
};

#endif /* Vertex_hpp */
