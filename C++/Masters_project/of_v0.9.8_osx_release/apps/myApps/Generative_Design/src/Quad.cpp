//
//  Quad.cpp
//  Generative_Design
//
//  Created by Henrik Holmsen on 5/1/18.
//

#include "Quad.hpp"

Quad::Quad(std::array<Vertex, 4> q)
{
    qu = q;
    prev_lenghts[0] = calculate_len(qu[0].get_pos(), qu[1].get_pos());
    prev_lenghts[1] = calculate_len(qu[0].get_pos(), qu[2].get_pos());
    prev_lenghts[2] = calculate_len(qu[0].get_pos(), qu[3].get_pos());
}

Quad::Quad(Vertex v1,Vertex v2,Vertex v3,Vertex v4)
{
    qu[0] = v1;
    qu[1] = v2;
    qu[2] = v3;
    qu[3] = v4;
    prev_lenghts[0] = calculate_len(qu[0].get_pos(), qu[1].get_pos());
    prev_lenghts[1] = calculate_len(qu[0].get_pos(), qu[2].get_pos());
    prev_lenghts[2] = calculate_len(qu[0].get_pos(), qu[3].get_pos());
}
Quad::Quad(std::array<double, 3> v1,std::array<double, 3> v2,std::array<double, 3> v3,std::array<double, 3> v4)
{
    qu[0] = Vertex(v1);
    qu[1] = Vertex(v2);
    qu[2] = Vertex(v3);
    qu[3] = Vertex(v4);
    prev_lenghts[0] = calculate_len(qu[0].get_pos(), qu[1].get_pos());
    prev_lenghts[1] = calculate_len(qu[0].get_pos(), qu[2].get_pos());
    prev_lenghts[2] = calculate_len(qu[0].get_pos(), qu[3].get_pos());
}
double Quad::calculate_len(std::array<double, 3>& point1, std::array<double, 3>&  point2)
{
    
    double ret = 0.0;
    for(int i = 0; i<3; i++)
    {
        ret += pow(point1[i]-point2[i], 2);
    }
    return sqrt(ret);
}
std::array<double, 3> Quad::calculate_vec(std::array<double, 3>& point1, std::array<double,3>& point2)
{
    std::array<double, 3> ret = {(point1[0] - point2[0]), (point1[1] - point2[1]), (point1[2] - point2[2])};
//    std::cout<<point1[2]<<"\n";
    return ret;
    
}
void Quad::set_spring(std::array<std::array<double, 3>,3>& s)
{
    springs = s;
}


void Quad::add_to_springs(int is_h, int x_y_z, double value)
{
    if(is_h == 1){
        springs[1][x_y_z] += value;
    }else if (is_h == 0){
        springs[0][x_y_z] +=value;
    }
}



// TODO: set spring for each Vertex to be the delta-length from the old length passed as an argument, to the new actual length, this is the force changed between the two.


// TODO: fikse på dette sånn at jeg bare 
void Quad::update_spring(double constant)
{
//    std::array<std::array<double, 3>,3> sp;
//    std::cout<<qu[0].get_X()<<"\n";
    springs[0] = calculate_vec(qu[0].get_pos(), qu[1].get_pos());
//    std::cout<<springs[0][0]<<"\n";
    springs[1] = calculate_vec(qu[0].get_pos(), qu[2].get_pos());
    springs[2] = calculate_vec(qu[0].get_pos(), qu[3].get_pos());
    for(int i = 0;i<3; i++)
    {
        springs[0][i] = springs[0][i]*(calculate_len(qu[0].get_pos(), qu[1].get_pos()) - prev_lenghts[0])*constant;
        springs[1][i] = springs[1][i]*(calculate_len(qu[0].get_pos(), qu[2].get_pos())- prev_lenghts[1])*constant;
        springs[2][i] = springs[2][i]*(calculate_len(qu[0].get_pos(), qu[3].get_pos())-prev_lenghts[2])*constant;
    }
}

std::array<Vertex, 4>& Quad::get_Vertex(void)
{
    return qu;
}

void Quad::set_new_vertex(std::array<double, 3>& npos, int index)
{
    qu[index].set_pos(npos);
    prev_lenghts = curr_lenghts;
    curr_lenghts[0] = calculate_len(qu[0].get_pos(), qu[1].get_pos());
    curr_lenghts[1] = calculate_len(qu[0].get_pos(), qu[2].get_pos());
    curr_lenghts[2] = calculate_len(qu[0].get_pos(), qu[3].get_pos());
    
    
//    std::cout<<springs[1][1]<<"\n";
}
std::array<std::array<double, 3>,3> Quad::get_springs(void)
{
    return springs;
}
void Quad::set_h_angles(float hangle){
    prev_angles[1] = curr_angles[1];
    curr_angles[1] = hangle;
//    std::cout<< prev_angles[1]<<" "<<hangle<<"\n";
}
void Quad::set_v_angles(float vangle){
    prev_angles[0] = curr_angles[0];
    curr_angles[0] = vangle;
}
float Quad::get_h_angle(void){
    return prev_angles[1];
}
float Quad::get_v_angle(void){
    return prev_angles[0];
}
