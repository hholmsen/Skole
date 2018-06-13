//
//  Obj.cpp
//  Generative_design_sim_ga
//
//  Created by Henrik Holmsen on 5/22/18.
//

#include "Obj.hpp"

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
    for(int i = 0; i<num_point; i++)
    {
        ret.push_back(init+(i*inc));
    }
    return ret;
}
double signum(double input){
    if(input>0)
    {
        return 1;
    }else if (input<0)
    {
        return -1;
    }
    return 0;
}

bool Obj::update_angles(int num_height, int num_points){
//    vertical angles
    for(int i = 0;i<verteces.size();i++){
        if((i>num_points) && (i<(verteces.size()-num_points))){
            std::array<double, 3> edge1 {(verteces[i-num_points].get_vertex_xyz()[0] - verteces[i].get_vertex_xyz()[0]), (verteces[i-num_points].get_vertex_xyz()[1] - verteces[i].get_vertex_xyz()[1]), (verteces[i-num_points].get_vertex_xyz()[2] - verteces[i].get_vertex_xyz()[2])};
            std::array<double, 3> edge2 {(verteces[i].get_vertex_xyz()[0] - verteces[i+num_points].get_vertex_xyz()[0]) - (verteces[i].get_vertex_xyz()[1] - verteces[i+num_points].get_vertex_xyz()[1]),(verteces[i].get_vertex_xyz()[2] - verteces[i+num_points].get_vertex_xyz()[2])};
            double sgn = signum((edge1[1]-edge1[0])*(edge2[2]-edge2[0]) - (edge2[1]-edge2[0])*(edge1[2]-edge1[0]));
            double len1 = sqrt(pow(edge1[0],2) + pow(edge1[1],2) + pow(edge1[2], 2));
            double len2 = sqrt(pow(edge2[0],2) + pow(edge2[1],2) + pow(edge2[2], 2));
            double dot_product = edge1[0]*edge2[0] + edge1[1]*edge2[1] + edge1[2]*edge2[2];
            double angle = acos(dot_product/(len1*len2));
            if (sgn<0){
                angle = 3*PI/2.0-angle + PI/2.0;}
            
            vertical_angles.push_back(angle);
        }
    }
    for(int i = 0;i<verteces.size();i++){
        if((i>1) && (i<(verteces.size()-1))){
            std::array<double, 3> edge1 {(verteces[i-1].get_vertex_xyz()[0] - verteces[i].get_vertex_xyz()[0]), (verteces[i-1].get_vertex_xyz()[1] - verteces[i].get_vertex_xyz()[1]), (verteces[i-1].get_vertex_xyz()[2] - verteces[i].get_vertex_xyz()[2])};
            std::array<double, 3> edge2 {(verteces[i].get_vertex_xyz()[0] - verteces[i+1].get_vertex_xyz()[0]) - (verteces[i].get_vertex_xyz()[1] - verteces[i+1].get_vertex_xyz()[1]),(verteces[i].get_vertex_xyz()[2] - verteces[i+1].get_vertex_xyz()[2])};
            double sgn = signum((edge1[1]-edge1[0])*(edge2[2]-edge2[0]) - (edge2[1]-edge2[0])*(edge1[2]-edge1[0]));
            double len1 = sqrt(pow(edge1[0],2) + pow(edge1[1],2) + pow(edge1[2], 2));
            double len2 = sqrt(pow(edge2[0],2) + pow(edge2[1],2) + pow(edge2[2], 2));
            double dot_product = edge1[0]*edge2[0] + edge1[1]*edge2[1] + edge1[2]*edge2[2];
            double angle = acos(dot_product/(len1*len2));
            if (sgn<0){
                angle = 3*PI/2.0-angle + PI/2.0;}
            horizontal_angles.push_back(angle);
        }
    }
    return true;
}
double getRandom(double min, double max)
{
//    double before = rand() % (int)max + (int)min;
//    double after = (double)rand() / RAND_MAX;
//    double result = before + after;
//    if (result < min || result > max) {
//        result = getRandom(min, max);
//    }
//    return result;
    return ((double) rand()*(max-min)/(double)RAND_MAX-min);
}

Obj::Obj(std::vector<std::array<double, 3>> new_obj, int np){
//std::cout<<new_obj.size()<<"\n";
    for (int i =0;i<new_obj.size();i++){
        verteces.push_back(Vertex(new_obj[i][0], new_obj[i][1], new_obj[i][2]));
    }
    for(int i= 0; i<new_obj.size() - 1; i++){
        horizontal_edges.push_back(std::array<int, 2> {i, i+1});
    }

//    HER!! kanskje np???
    for(int i=0; i<new_obj.size() - np;i++){
        vertical_edges.push_back(std::array<int, 2> {i, i+np});
        //        std::cout<<i<<"\n";
    }
    for(int i = 0;i<(new_obj.size())-np-1;i++){
        cross_edges.push_back(std::array<int,2> {i,i+np+1});
    }
    for(int i = 0;i<(new_obj.size())-np-1;i++){
        cross_edges.push_back(std::array<int,2> {i+1,i+np});
    }

    //    horizontal lenghts
    for(int i = 0;i<horizontal_edges.size();i++){
        horizontal_lengths.push_back(update_lenghts(verteces[horizontal_edges[i][0]].get_vertex_xyz(), verteces[horizontal_edges[i][1]].get_vertex_xyz()));
        
    }

    //    Vertical lengths
    for(int i = 0;i<vertical_edges.size();i++){
        vertical_lengths.push_back(update_lenghts(verteces[vertical_edges[i][0]].get_vertex_xyz(), verteces[vertical_edges[i][1]].get_vertex_xyz()));
    }

    //    crossing lengths
    for(int i = 0;i<cross_edges.size();i++){
        cross_lengths.push_back(update_lenghts(verteces[cross_edges[i][0]].get_vertex_xyz(), verteces[cross_edges[i][1]].get_vertex_xyz()));
    }

    //    update angles
    update_angles(np, np);

    
}

Obj::Obj(int num_height, int num_points, double radius, double randomness){
    double x,y,z = 0;
    n_p = num_points;
    std::vector<double> points = linspace(0, 2*PI, num_points);

//    double lower_bound = -0.00005;
//    double upper_bound = 0.00005;
//    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
//    std::default_random_engine re;
//    double a_random_double = unif(re);
//    double a_nother = unif(re);
//    std::cout<<"first: "<<a_random_double<<" second: "<< a_nother;
//    std::cout<<num_height<<" "<<points.size()<<" "<<num_points<<"\n";
    
//    for(int i = 0; i<num_height;i++){
//        for(int j = 0; j<points.size();j++){
//
//            x = radius*std::cos(points[j])+ getRandom(-0.00005, 0.00005);
//            y = radius*std::sin(points[j])+ getRandom(-0.00005, 0.00005) ;
////            std::cout<<x<<" "<<y<<" "<<i<<"\n";
////            double z = ((2*PI*radius)/num_points) *i;
//            verteces.push_back(Vertex(x, y, i));
//        }
//    }
    int j = 0;
    double nk = num_points;
    for(int i = 0;i<num_points*num_height;i++){
        double in = i;
        x = radius*std::sin(2*PI*in/nk)+ getRandom(-randomness, randomness);
        y = radius*std::cos(2*PI*in/nk)+ getRandom(-randomness, randomness);
        
        z= 1* in/nk + 0.1;
        j++;
        if(j==points.size()){
            j=0;
        }
//        std::cout<<in/nk<<"\n";
        verteces.push_back(Vertex(x,y,z));
    }

//    connecting horizontal
    for(int i= 0; i<num_height*num_points - 1; i++){
//        account for not the shift up for every rotation
//        if(i%(num_points) == 0 && i!=0){
//            horizontal_edges.push_back(std::array<int, 2>{i,i-num_points+1});
//            std::cout<<i<<"\n";
//        }else{
            horizontal_edges.push_back(std::array<int, 2> {i, i+1});
//            std::cout<<i<<"\n";
//        }
//        std::cout<<i<<"\n";
    }
//    std::cout<<horizontal_edges.size()<<"\n";
//    connecting vertical
    for(int i=0; i<num_points*num_height - num_points;i++){
        vertical_edges.push_back(std::array<int, 2> {i, i+num_points});
//        std::cout<<i<<"\n";
    }
//    std::cout<<"\n"<<vertical_edges.size();
//    connecting crosses
    for(int i = 0;i<(num_points*num_height)-num_points-1;i++){
        cross_edges.push_back(std::array<int,2> {i,i+num_points+1});
    }
    for(int i = 0;i<(num_points*num_height)-num_points-1;i++){
        cross_edges.push_back(std::array<int,2> {i+1,i+num_points});
    }
//    horizontal lenghts
    for(int i = 0;i<horizontal_edges.size();i++){
        horizontal_lengths.push_back(update_lenghts(verteces[horizontal_edges[i][0]].get_vertex_xyz(), verteces[horizontal_edges[i][1]].get_vertex_xyz()));

    }
//    Vertical lengths
    for(int i = 0;i<vertical_edges.size();i++){
        vertical_lengths.push_back(update_lenghts(verteces[vertical_edges[i][0]].get_vertex_xyz(), verteces[vertical_edges[i][1]].get_vertex_xyz()));
    }
//    crossing lengths
    for(int i = 0;i<cross_edges.size();i++){
        cross_lengths.push_back(update_lenghts(verteces[cross_edges[i][0]].get_vertex_xyz(), verteces[cross_edges[i][1]].get_vertex_xyz()));
    }
//    update angles
    update_angles(num_height, num_points);
    
//    add_vector_force();
}

std::vector<Vertex>& Obj::get_verteces(void){
    return verteces;
}


double Obj::update_lenghts(std::array<double, 3> v1, std::array<double, 3> v2)
{
    
    double ret = 0.0;
    for(int i = 0; i<3; i++)
    {
        ret += pow(v1[i]-v2[i], 2);
    }
    return sqrt(ret);
}
std::array<double, 3> array_subtract_3(std::array<double, 3> one, std::array<double, 3> two){
    return std::array<double, 3> {two[0]-one[0],two[1]-one[1],two[2]-one[2]};
}
bool Obj::add_vector_force(void){
    double constant = 0.01;
    for(int i=0;i<horizontal_edges.size();i++){
        std::array<double, 3> edge_vector = array_subtract_3(verteces[horizontal_edges[i][0]].get_vertex_xyz(), verteces[horizontal_edges[i][1]].get_vertex_xyz());
        double new_length = sqrt(pow(edge_vector[0],2) + pow(edge_vector[1], 2) + pow(edge_vector[2],2));
        double delta_length = horizontal_lengths[i] - new_length;
        
//        VET IKKE OM DETTE ER RIKTIG
//        horizontal_lengths[i] = new_length;
        
        
        verteces[horizontal_edges[i][0]].add_to_forces(std::array<double, 3> {-(delta_length*constant*edge_vector[0]),-(delta_length*constant*edge_vector[1]),-(delta_length*constant*edge_vector[2])});
        verteces[horizontal_edges[i][1]].add_to_forces(std::array<double, 3> {(delta_length*constant*edge_vector[0]),(delta_length*constant*edge_vector[1]),(delta_length*constant*edge_vector[2])});
    }
    for(int i=0;i<vertical_edges.size();i++){
        std::array<double, 3> edge_vector = array_subtract_3(verteces[vertical_edges[i][0]].get_vertex_xyz(), verteces[vertical_edges[i][1]].get_vertex_xyz());
        double new_length = sqrt(pow(edge_vector[0],2) + pow(edge_vector[1], 2) + pow(edge_vector[2],2));
        double delta_length = vertical_lengths[i] - new_length;
        
//        VET IKKE OM DETTE ER RIKTIG
//        vertical_lengths[i] = new_length;
        
        
        verteces[vertical_edges[i][0]].add_to_forces(std::array<double, 3> {-(delta_length*constant*edge_vector[0]),-(delta_length*constant*edge_vector[1]),-(delta_length*constant*edge_vector[2])});
        verteces[vertical_edges[i][1]].add_to_forces(std::array<double, 3> {(delta_length*constant*edge_vector[0]),(delta_length*constant*edge_vector[1]),(delta_length*constant*edge_vector[2])});
    }
    for(int i=0;i<cross_edges.size();i++){
        std::array<double, 3> edge_vector = array_subtract_3(verteces[cross_edges[i][0]].get_vertex_xyz(), verteces[cross_edges[i][1]].get_vertex_xyz());
        double new_length = sqrt(pow(edge_vector[0],2) + pow(edge_vector[1], 2) + pow(edge_vector[2],2));
        double delta_length = cross_lengths[i] - new_length;
        
//        VET IKKE OM DETTE ER RIKTIG
//        cross_lengths[i] = new_length;
        
        
        verteces[cross_edges[i][0]].add_to_forces(std::array<double, 3> {-(delta_length*constant*edge_vector[0]),-(delta_length*constant*edge_vector[1]),-(delta_length*constant*edge_vector[2])});
        verteces[cross_edges[i][1]].add_to_forces(std::array<double, 3> {(delta_length*constant*edge_vector[0]),(delta_length*constant*edge_vector[1]),(delta_length*constant*edge_vector[2])});
        

    }
    return true;
}
//byttet v1v2 for å få rikitg vek prodkt
std::array<double, 3> get_vector_product_3d(std::array<double, 3> v2, std::array<double, 3> v1, double sgn){
    return std::array<double, 3> {sgn*(v1[1]*v2[2]-v1[2]*v2[1]),sgn*(v1[2]*v2[0]-v1[0]*v2[2]),sgn*(v1[0]*v2[1]-v1[1]*v2[0])};
}

bool Obj::bouyancy_routine(int index_first_vertex, int index_middle_vertex, int index_second_vertex, int is_vertical){
    std::array<double, 3> edge1 {(verteces[index_first_vertex].get_vertex_xyz()[0] - verteces[index_middle_vertex].get_vertex_xyz()[0]), (verteces[index_first_vertex].get_vertex_xyz()[1] - verteces[index_middle_vertex].get_vertex_xyz()[1]), (verteces[index_first_vertex].get_vertex_xyz()[2] - verteces[index_middle_vertex].get_vertex_xyz()[2])};
    std::array<double, 3> edge2 {(verteces[index_middle_vertex].get_vertex_xyz()[0] - verteces[index_second_vertex].get_vertex_xyz()[0]), (verteces[index_middle_vertex].get_vertex_xyz()[1] - verteces[index_second_vertex].get_vertex_xyz()[1]), (verteces[index_middle_vertex].get_vertex_xyz()[2] - verteces[index_second_vertex].get_vertex_xyz()[2])};
    
    double sgn =signum((edge1[1]-edge1[0])*(edge2[2]-edge2[0]) - (edge2[1]-edge2[0])*(edge1[2]-edge1[0]));
    
    std::array<double, 3> cross_e1_e2 = get_vector_product_3d(edge1, edge2, sgn);
    std::array<double, 3> cross_prev_e1 = get_vector_product_3d(cross_e1_e2, edge1, 1);
    std::array<double, 3> cross_prev_e2 = get_vector_product_3d(edge2, cross_e1_e2, 1);
    
    
//    avventer normalisering
    
    float l1 = sqrt(cross_prev_e1[0]*cross_prev_e1[0] + cross_prev_e1[1]*cross_prev_e1[1] + cross_prev_e1[2]*cross_prev_e1[2] );
    if (l1 == 0){
        l1 = 0.00001;
    }
    cross_prev_e1[0] = cross_prev_e1[0]/l1;
    cross_prev_e1[1] = cross_prev_e1[1]/l1;
    cross_prev_e1[2] = cross_prev_e1[2]/l1;
    
    float l3 = sqrt(cross_prev_e2[0]*cross_prev_e2[0] + cross_prev_e2[1]*cross_prev_e2[1] + cross_prev_e2[2]*cross_prev_e2[2]);
    if (l3 == 0)
        l3 = 0.00001;
    cross_prev_e2[0] = cross_prev_e2[0]/l3;
    cross_prev_e2[1] = cross_prev_e2[1]/l3;
    cross_prev_e2[2] = cross_prev_e2[2]/l3;
    
    
    double len1 = sqrt(pow(edge1[0],2) +pow(edge1[1], 2)+pow(edge1[2], 2));
    double len2 = sqrt(pow(edge2[0],2) +pow(edge2[1], 2)+pow(edge2[2], 2));
    double dot_product = edge1[0]*edge2[0] + edge1[1]*edge2[1] + edge1[2]*edge2[2];
    double angle_Test = dot_product/(len1*len2);
    
//    avventer sikker
//
        if (angle_Test<-0.99999){
        angle_Test = -1;
}
    else{
        if (angle_Test>0.99999){
            angle_Test =1;
        }}
    double angle = acos( angle_Test );
    
    if (sgn<0){
    angle = 3*PI/2.0 - angle + PI/2.0;
    }

//    double angle = acos((dot_product/(len1*len2)));
    double delta_angle=0;
    if(is_vertical ==1){
        delta_angle = vertical_angles[index_middle_vertex] - angle;
//        vertical_angles[index_middle_vertex] = angle;
    }else{
        delta_angle = horizontal_angles[index_middle_vertex] - angle;
//        horizontal_angles[index_middle_vertex] = angle;
    }
    double force_to_be_added_to_vertex1 = delta_angle * 0.002 / len1;
    double force_to_be_added_to_vertex2 = delta_angle * 0.002 / len2;
    
//    horizontal_angles[index_middle_vertex] = angle;
//    vertical_angles[index_middle_vertex] = angle;
    
//    std::cout<< force_to_be_added_to_vertex1<<"\n";
    double four = 4;
    std::array<double,3> force_vector_2_add_v1 {four*force_to_be_added_to_vertex1*cross_prev_e1[0],four*force_to_be_added_to_vertex1*cross_prev_e1[1],four*force_to_be_added_to_vertex1*cross_prev_e1[2]};
    std::array<double,3> force_vector_2_add_v2 {four*force_to_be_added_to_vertex2*cross_prev_e2[0],four*force_to_be_added_to_vertex2*cross_prev_e2[1],four*force_to_be_added_to_vertex2*cross_prev_e2[2]};
    std::array<double, 3> opposing_force {four*(-force_vector_2_add_v1[0] - force_vector_2_add_v2[0]), four*(-force_vector_2_add_v1[1] - force_vector_2_add_v2[1]), four*(-force_vector_2_add_v1[2] - force_vector_2_add_v2[2])};
    
//    std::cout<<force_vector_2_add_v1[0]<<"\n";
//    std::cout<<force_vector_2_add_v2[0]<<"\n";
//    std::cout<<opposing_force[0]<<"\n";
//
    verteces[index_first_vertex].add_to_forces(force_vector_2_add_v1);
    verteces[index_second_vertex].add_to_forces(force_vector_2_add_v2);
    verteces[index_middle_vertex].add_to_forces(opposing_force);
}

void Obj::external_forces(void){
    float maxH = 1 * (verteces.size() / n_p);
    for (int i=0; i<verteces.size(); i++)
    {
        float h = 1 * ((double)i / (double)n_p);
        float f = 0.06 * (pow(maxH/2.0,2) - pow((maxH/2.0 - h),2));
        std::array<double, 3> dragVect  { verteces[i].get_vertex_xyz()[0], verteces[i].get_vertex_xyz()[0], 0};
        verteces[i].add_to_forces(std::array<double,3> {dragVect[0]*f*0.0001,dragVect[1]*f*0.0001,dragVect[2]*f*0.0001});

    }
}
void Obj::set_bb(void){
    if(ext == false){
        ext =true;
        std::cout<<"force = true\n";
    }
    else{ext = false; std::cout<<"force = false\n";}
}

std::vector<std::array<double, 3>> Obj::run_one_sim(void){
    double convergence =0.08;
    std::vector<std::array<double, 3>> retur;
    add_vector_force();

//    for(int i= n_p; i<verteces.size()-n_p;i++){
//        if ( (i>n_p) && (i<(verteces.size()-n_p)) )
//            bouyancy_routine(i-n_p, i, i+n_p, 1);
//
//    }
//    for (int i=1; i<(verteces.size()-1); i++){
//        bouyancy_routine(i-1, i, i+1, 0);}
    if(ext==true){
        external_forces();}
    for(int i = 0; i<verteces.size();i++){
//                std::cout<<verteces[i].get_vertex_xyz()[0]<<" "<<verteces[i].get_vertex_xyz()[1]<<" "<<verteces[i].get_vertex_xyz()[2]<<"\n";
//                        std::cout<<verteces[i].get_force_xyz()[0]<<" "<<verteces[i].get_force_xyz()[1]<<" "<<verteces[i].get_force_xyz()[2]<<"\n";
        
        std::array<double, 3> to_be_added {verteces[i].get_force_xyz()[0]*convergence, verteces[i].get_force_xyz()[1]*convergence,verteces[i].get_force_xyz()[2]*convergence};
        verteces[i].add_to_vertex(to_be_added);
        retur.push_back(to_be_added);
//        std::cout<<verteces[i].get_vertex_xyz()[0]<<" "<<verteces[i].get_vertex_xyz()[1]<<" "<<verteces[i].get_vertex_xyz()[2]<<"\n";
        verteces[i].set_new_force(std::array<double, 3> {0,0,0});
        
    }

    return retur;
}




std::vector<std::array<int, 2>> Obj::get_horizontal_edges(void){
    return horizontal_edges;
}
std::vector<std::array<int, 2>> Obj::get_vertical_edges(void){
    return vertical_edges;
}
std::vector<std::array<int, 2>> Obj::get_cross_edges(void){
    return cross_edges;
}
