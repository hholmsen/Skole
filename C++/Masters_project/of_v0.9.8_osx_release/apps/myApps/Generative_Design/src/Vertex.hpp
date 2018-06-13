//
//  Vertex.hpp
//  Generative_Design
//
//  Created by Henrik Holmsen on 5/1/18.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include <iostream>
#include <array>
class Vertex
{
private:
    std::array<double,3> pos;
public:
    Vertex() = default;
    Vertex(std::array<double, 3> p);
    Vertex(double X, double Y, double Z);
    void set_pos(std::array<double, 3>& npos);
    void set_X(double& nX);
    void set_Y(double& nY);
    void set_Z(double& nZ);
    std::array<double, 3>& get_pos(void);
    double& get_X(void);
    double& get_Y(void);
    double& get_Z(void);
    
};

#endif /* Vertex_hpp */
