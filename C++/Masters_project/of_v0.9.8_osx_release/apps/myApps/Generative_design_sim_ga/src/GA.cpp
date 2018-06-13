//
//  GA.cpp
//  Generative_design_sim_ga
//
//  Created by Henrik Holmsen on 5/25/18.
//

#include "GA.hpp"


GA::GA(int num_specimens, int num_iterations){
    init_specimens(10, 2, 30, 30);
    double size = 30;
    calculate_fitness(size, num_iterations, size);
    compare_specimens();
    mate_specimens(30);
    fitness.erase(fitness.begin(),fitness.end());
    
    
}
void GA::run_one_gen(void){
    calculate_fitness(30, 2, 30);
    compare_specimens();
    mate_specimens(30);
    fitness.erase(fitness.begin(), fitness.end());
}
void GA::init_specimens(int num_specimens, double set_random, int size, double radius){
    for(int i = 0; i<num_specimens; i++){
        specimens.push_back(Obj(size,size,radius, set_random));
        
        
    }
    for(int i =0; i< num_specimens; i++){
        specimens[i].set_bb();
    }
    initial_specimens = specimens;
}
void GA::print_fitness(void){
    for(int i =0;i<fitness.size();i++){
        std::cout<<"fitness: "<<fitness[i][0]<<" fitness_index: "<<fitness[i][1]<<"\n";
    }
}
void GA::calculate_fitness(double size, int num_iterations, double height){
    for(int i = 0; i<specimens.size();i++){
        std::cout<<specimens[i].get_verteces()[350].get_vertex_xyz()[0]<<"\n";
        
        for (int j = 0;j<10000;j++){
            specimens[i].run_one_sim();
        }
        std::cout<<specimens[i].get_verteces()[350].get_vertex_xyz()[0]<<"\n";
        std::vector<double> z_top_values;
        std::vector<double> z_bottom_values;
        for(int j = 0;j<size*2;j++){
            if(j>size){
                z_top_values.push_back(specimens[i].get_verteces()[specimens[i].get_verteces().size() - (j-size)].get_vertex_xyz()[2]);
            }else{
                z_bottom_values.push_back(specimens[i].get_verteces()[j].get_vertex_xyz()[2]);
            }
        }
//        fitness is harmonic mean of sum of displacement of z- point in top and bottom
        double fitness_top = 0;
        double fitness_bot = 0;
        for(int j = 0; j<z_top_values.size();j++){
            fitness_top += height -z_top_values[j];
            fitness_bot += z_bottom_values[j];
        }
        fitness.push_back(std::array<double, 2> {sqrt((fitness_top + fitness_bot)/2) , static_cast<double>(i)});
    }
    std::cout<<"hoho"<<"\n";
}

int partition(std::vector<std::array<double, 2>>& A, int p,int q)
{
    double x= A[p][0];
    int i=p;
    int j;
    
    for(j=p+1; j<q; j++)
    {
        if(A[j][0]<=x)
        {
            i=i+1;
            std::swap(A[i],A[j]);
        }
        
    }
    std::swap(A[i],A[p]);
    return i;
}
void quickSort(std::vector<std::array<double,2>>& A, int p,int q)
{
    int r;
    if(p<q)
    {
        r=partition(A, p,q);
        quickSort(A,p,r);
        quickSort(A,r+1,q);
    }
}
std::vector<Obj>& GA::get_specimens(void){
    return specimens;
}

void GA::compare_specimens(){
    print_fitness();
    quickSort(fitness, 0, fitness.size());
    std::cout<<"after quicksort: \n";
    print_fitness();
    
}
//driter i mutasjon fåløpi
void GA::mate_specimens(int size){
    std::vector<Obj> temp_new;
    std::vector<std::array<double, 3>> temp_obj1;
    std::vector<std::array<double,3>> temp_obj2;
    for(int i =0;i<specimens.size()-1;i++){
        if(i>specimens.size()*0.3){
//            std::cout<<"hei";
            for(int j =0;j<specimens[i].get_verteces().size();j++){
                if(j<(specimens[i].get_verteces().size())/2/* || i+1!=specimens[i+1].get_verteces().size()*/){
                    temp_obj1.push_back(specimens[i].get_verteces()[j].get_vertex_xyz());
                    temp_obj2.push_back(specimens[i+1].get_verteces()[j].get_vertex_xyz());
//                    std::cout<<"hei\n";
                }else{
//                    if(i+1!=(specimens[i+1].get_verteces().size())){
                        temp_obj1.push_back(specimens[i+1].get_verteces()[j].get_vertex_xyz());
                        temp_obj2.push_back(specimens[i].get_verteces()[j].get_vertex_xyz());
//                        std::cout<<"hei\n";
//                    }
                }
//                std::cout<< j <<"\n";
            }

            temp_new.push_back(Obj(temp_obj1,size));
            temp_new.push_back(Obj(temp_obj2,size));
            
            temp_obj1.erase(temp_obj1.begin(),temp_obj1.end());
            temp_obj2.erase(temp_obj2.begin(),temp_obj2.end());

        }

    }

    specimens.erase(specimens.begin(), specimens.end());

//    std::cout<<temp_new.size();

    specimens = temp_new;

    temp_new.erase(temp_new.begin(),temp_new.end());

}
