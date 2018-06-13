//
//  Vertex.cpp
//  Generative_Design
//
//  Created by Henrik Holmsen on 5/1/18.
//

#include "Vertex.hpp"
Vertex::Vertex(std::array<double, 3> p)
{
    pos = p;
}
Vertex::Vertex(double X, double Y, double Z)
{
    pos[0] = X;
    pos[1] = Y;
    pos[2] = Z;
}
void Vertex::set_pos(std::array<double, 3> &npos)
{
//    std::cout<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<"\n";
    pos = npos;
//    std::cout<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<"\n";
}
void Vertex::set_X(double& nX)
{
    pos[0] = nX;
}
void Vertex::set_Y(double& nY)
{
    pos[1] = nY;
}
void Vertex::set_Z(double& nZ)
{
    pos[2] = nZ;
}
std::array<double, 3>& Vertex::get_pos(void)
{
    return pos;
}
double& Vertex::get_X(void)
{
    return pos[0];
}
double& Vertex::get_Y(void)
{
    return pos[1];
}
double& Vertex::get_Z(void)
{
    return pos[2];
}
