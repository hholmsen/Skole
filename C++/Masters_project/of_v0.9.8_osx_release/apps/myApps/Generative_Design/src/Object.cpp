//
//  Object.cpp
//  Generative_Design
//
//  Created by Henrik Holmsen on 5/1/18.
//

#include "Object.hpp"

std::vector<double> linspace(double init, double end, int num_point)
{
    double dist = 0;
    if(init<end)
    {
        dist = end-init;
    }else
    {
        dist = init-end;
    }
    double inc = dist/num_point;
    std::vector<double> ret;
    for(int i = 0; i<=num_point; i++)
    {
        ret.push_back(init+(i*inc));
    }
    return ret;
}

Object::Object(int num_height, int num_points, double radius)
{
    if (num_height%2 ==0){
        num_height+=2;
    }else{
        num_height+=1;
    }
    circumference_resolution = num_points;
    float x,y = 0;
    std::vector<double> points = linspace(0,2*PI, num_points);
    
    std::vector<Vertex> v;
    for(int i = 0; i<num_height;i++){
        for(int j = 0; j<points.size();j++){
            x = radius*cos(points[j]);
            y = radius*std::sin(points[j]);
//            std::cout<<y<<"\n";
            v.push_back(Vertex(x, y, i));
            
        }
    }
//    std::vector<std::array<Vertex, 4>> q;
    for(int i = 0; i<v.size();i++)
    {
        if(i+num_points+2<v.size()){
            std::array<Vertex,4> gf;
            gf[0] = v[i];
            gf[1] = v[i+1];
            gf[2] = v[i+num_points+1];
            gf[3] = v[i+num_points+2];
            
//            std::cout<<i<<": point 1 "<<gf[0].get_X()<<" "<<gf[0].get_Y()<<" "<<gf[0].get_Z()<<"\n";
//            std::cout<<i<<": point 2 "<<gf[1].get_X()<<" "<<gf[1].get_Y()<<" "<<gf[1].get_Z()<<"\n";
//            std::cout<<i<<": point 3 "<<gf[2].get_X()<<" "<<gf[2].get_Y()<<" "<<gf[2].get_Z()<<"\n";
//            std::cout<<i<<": point 4 "<<gf[3].get_X()<<" "<<gf[3].get_Y()<<" "<<gf[3].get_Z()<<"\n";
            
            obj.push_back(Quad(gf));
        }
    }
    sim_routine();
//    std::cout<<"obj: "<< obj.size()<< " v: "<<v.size();
}

std::vector<Quad>& Object::get_quads(void)
{
    return obj;
}
std::array<double, 3> Object::vector_product_3d(double vec_1_x, double vec_1_y, double vec_1_z, double vec_2_x, double vec_2_y, double vec_2_z, float sgn)
{
    std::array<double, 3> ret;
    ret[0] = sgn* (vec_1_y*vec_2_z)-(vec_1_z*vec_2_y);
    ret[1] =sgn*(vec_1_z*vec_2_x)-(vec_1_x*vec_2_z);
    ret[2] = sgn*(vec_1_x*vec_2_y)-(vec_1_y*vec_2_x);
    return ret;
}

void Object::set_vertex(std::array<double, 3>& pos, int indexobj, int indexquad)
{
    obj[indexobj].set_new_vertex(pos,indexquad);
    obj[indexobj].update_spring(0.001);
}
float signum(float input){
    if(input>0)
    {
        return 1;
    }else if (input<0)
    {
        return -1;
    }
    return 0;
}
void Object::calc_boi(std::array<double, 3> p1, std::array<double, 3> pX, std::array<double, 3> p2, int i, int is_h)
{
    std::array<double, 3> v1 {p1[0]-pX[0],p1[1]-pX[1], p1[2]-pX[2]};
    std::array<double, 3> v2 {p2[0]-pX[0],p2[1]-pX[1], p2[2]-pX[2]};
    float sgn = signum((v1[1]-v1[0])* (v2[2]-v2[0]) - (v2[1]-v2[0])*(v1[2]-v1[0]));
    std::array<double,3> xV2 = vector_product_3d(v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], sgn);
    std::array<double,3> xV1 = vector_product_3d(v1[0], v1[1], v1[2], xV2[0], xV2[1], xV2[2], 1.0);
    std::array<double, 3> xV3 = vector_product_3d(xV2[0], xV2[1], xV2[2], v2[0], v2[1], v2[2], 1.0);
    
    double len = sqrt(xV1[0]*xV1[0] + xV1[1]*xV1[1] + xV1[2]*xV1[2]);
    if(len== 0){
        len = 0.00001;
    }
    xV1[0] = xV1[0]/len;
    xV1[1] = xV1[1]/len;
    xV1[2] = xV1[2]/len;
    double len2 = sqrt(xV3[0]*xV3[0] + xV3[1]*xV3[1] + xV3[2]*xV3[2]);
    if(len== 0){
        len = 0.00001;
    }
    xV3[0] = xV3[0]/len2;
    xV3[1] = xV3[1]/len2;
    xV3[2] = xV3[2]/len2;
    
    float lengde1 = sqrt( v1[0]*v1[0] + v1[1]*v1[1] + v1[2]*v1[2] );
    float lengde2 = sqrt( v2[0]*v2[0] + v2[1]*v2[1] + v2[2]*v2[2] );
    float dott = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
    float sikker = dott/(lengde1*lengde2);
    if (sikker<-0.99999){
        sikker = -1;}
    else if (sikker>0.99999){
        sikker =1;}
    float angCurrent = acos( sikker );
    if (sgn<0){
        angCurrent = 3*PI/2.0 - angCurrent + PI/2.0;
    }
    
    double delta_angle;
    if(is_h == 1){
        double delta_angle = obj[i].get_h_angle() - angCurrent;
        obj[i].set_h_angles(angCurrent);
    }else if(is_h == 0){
        double delta_angle = obj[i].get_v_angle() - angCurrent;
//        std::cout<<"ang: "<< obj[i].get_h_angle()<<"\n";
        obj[i].set_v_angles(angCurrent);
    }
    
    float F1 = delta_angle * 0.002 / lengde1;
    float F3 = delta_angle * 0.002 / lengde2;
    if (is_h ==1){
        obj[i-circumference_resolution].add_to_springs(is_h, 0, xV1[0] * F1 *4);
        obj[i-circumference_resolution].add_to_springs(is_h, 1, xV1[1] * F1 *4);
        obj[i-circumference_resolution].add_to_springs(is_h, 2, xV1[2] * F1 *4);
        
        obj[i].add_to_springs(is_h, 0, xV3[0]*F3*4);
        obj[i].add_to_springs(is_h, 1, xV3[1]*F3*4);
        obj[i].add_to_springs(is_h, 2, xV3[2]*F3*4);
    }else {
        obj[i-1].add_to_springs(is_h, 0, xV1[0] * F1 *4);
        obj[i-1].add_to_springs(is_h, 1, xV1[1] * F1 *4);
        obj[i-1].add_to_springs(is_h, 2, xV1[2] * F1 *4);
        
        obj[i].add_to_springs(is_h, 0, xV3[0]*F3*4);
        obj[i].add_to_springs(is_h, 1, xV3[1]*F3*4);
        obj[i].add_to_springs(is_h, 2, xV3[2]*F3*4);
    }
    
//    obj[i].add_to_springs(is_h, 0, xV3[0]*F3*4);
//    obj[i].add_to_springs(is_h, 1, xV3[1]*F3*4);
//    obj[i].add_to_springs(is_h, 2, xV3[2]*F3*4);
    
}
void Object::mod(void){
    std::array<double, 3> n = {0, 0, 5}; 
    
    for (int i=0; i<obj.size(); i++)
        if ( (i + i/3200)%20 == 0  )
        {
            float f =  6000/(pow(obj[i].get_Vertex()[0].get_X()-n[0],2) + pow(obj[i].get_Vertex()[0].get_Y()-n[0],2) + pow(obj[i].get_Vertex()[0].get_Z()-n[0],2));
            std::array<double, 3> dragVect = { n[0]-obj[i].get_Vertex()[0].get_X()-n[0], n[1]-obj[i].get_Vertex()[0].get_X()-n[0], n[2]-obj[i].get_Vertex()[0].get_X()-n[0]};
            obj[i].add_to_springs(0, 0, dragVect[0]*f*0.00001);
            obj[i].add_to_springs(0, 1, dragVect[1]*f*0.00001);
            obj[i].add_to_springs(0, 2, dragVect[2]*f*0.00001);
        }
}
int Object::get_c_res(void){
    return circumference_resolution;
}
void Object::sim_routine()
{
    for(int i = 0; i<obj.size();i++)
    {
        obj[i].update_spring(0.01);
    }
    //    TODO: Go thorough each Vertex apart from the top and bottom
    //    Calculate each Vertical angle force and add it to the spring force for each mofo
    for(int i = circumference_resolution; i<obj.size() - circumference_resolution; i++)
    {
        std::array<double, 3> p1 = obj[i-circumference_resolution].get_Vertex()[0].get_pos();
        std::array<double, 3> pX = obj[i].get_Vertex()[0].get_pos();
        std::array<double, 3> p2 = obj[i].get_Vertex()[2].get_pos();
        calc_boi(p1, pX, p2, i, 1);
        

    }for (int i = 0; i<obj.size()-1; i++) {
        std::array<double, 3> p1 = obj[i-1].get_Vertex()[0].get_pos();
        std::array<double, 3> pX = obj[i].get_Vertex()[0].get_pos();
        std::array<double, 3> p2 = obj[i].get_Vertex()[1].get_pos();
        calc_boi(p1, pX, p2, i, 0);
    }
//    std::cout<<"prev_pos_quad_7_vertex1 x: "<<obj[7].get_Vertex()[0].get_X()<<" y: "<<obj[7].get_Vertex()[0].get_Y()<<" z: "<<obj[7].get_Vertex()[0].get_Z()<<"\n";
    mod();
    for (int i = 0;i<obj.size(); i++){
        for(int j = 0;j<3;j++){
            std::array<double, 3> newpos = obj[i].get_Vertex()[j].get_pos();
            newpos[0] += (obj[i].get_springs()[0][0] + obj[i].get_springs()[1][0] + obj[i].get_springs()[2][0]) ;
            newpos[1] += (obj[i].get_springs()[0][1] + obj[i].get_springs()[1][1] + obj[i].get_springs()[2][1] );
            newpos[2] += (obj[i].get_springs()[0][2] + obj[i].get_springs()[1][2] + obj[i].get_springs()[2][2] ) ;
            obj[i].set_new_vertex(newpos, j);
        }
    }
//    std::cout<<"updated_pos_quad_7_vertex1 x: "<<obj[7].get_Vertex()[0].get_X()<<" y: "<<obj[7].get_Vertex()[0].get_Y()<<" z: "<<obj[7].get_Vertex()[0].get_Z()<<"\n";
    
    //TODO: go throug all vertices then:
//    calculate each Horisontal angle force and then add it to the spring force for each
//    then add the ewxternal force to each of the SoBs
//    then update all of the verteces.
}



