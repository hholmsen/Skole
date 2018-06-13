//
//  Vertex.cpp
//  Generative_design_sim_ga
//
//  Created by Henrik Holmsen on 5/22/18.
//

#include "Vertex.hpp"
Vertex::Vertex(double initX,double initY,double initZ){
    this->X = initX;
    this->Y = initY;
    this->Z = initZ;
}
bool Vertex::set_new_vertex(std::array<double, 3> XYZ){
    this->X = XYZ[0];
    this->Y = XYZ[1];
    this->Z = XYZ[2];
    return true;
}

bool Vertex::add_to_vertex(std::array<double, 3> XYZ){
    this->X+=XYZ[0];
    this->Y+=XYZ[1];
    this->Z+=XYZ[2];
    return true;
}
bool Vertex::set_new_force(std::array<double, 3> XYZ){
    this->force_X = XYZ[0];
    this->force_Y = XYZ[1];
    this->force_Z = XYZ[2];
    return true;
}
bool Vertex::add_to_forces(std::array<double, 3> XYZ){
    this->force_X+=XYZ[0];
    this->force_Y+=XYZ[1];
    this->force_Z+=XYZ[2];
}

std::array<double, 3> Vertex::get_vertex_xyz(void){
    return std::array<double, 3> {X, Y, Z};
}
std::array<double, 3> Vertex::get_force_xyz(void){
    return std::array<double, 3> {this->force_X, this->force_Y,this->force_Z};
}

