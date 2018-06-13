//
//  sim.cpp
//  gen
//
//  Created by Henrik Holmsen on 4/21/18.
//

#include "sim.hpp"

Sim::Sim(float fx, float fy, float fz, std::vector<float> bx,std::vector<float> by, std::vector<float> bz, Vertex_Object verto)
{
    force_vector_x = fx;
    force_vector_y = fy;
    force_vector_z = fz;
    force_begin_x = bx;
    force_begin_y = by;
    force_begin_z = bz;
    v0 = verto;
}

std::array<float,3> Sim::translate_into_coordinates(std::array<float,3>& vec, std::array<float,3>& co)
{
    std::array<float, 3> ret;
    ret[0] = co[0]+vec[0];
    ret[1] = co[1]+vec[1];
    ret[2] = co[2]+vec[2];
    
    return ret;
}
//vil vel kanskje stabilisere seg veldig fort når jeg tar å kjører samme vektormultiplikasjon hver gang?
void Sim::calculate_update(void)
{
    for(int i = 0; i<v0.get_object().size();i++)
    {
        std::array<float, 3> up_n;
        
        std::array<float, 3> vec_orig_neigh = v0.get_object()[i].get_neighbor_spring();
        up_n = vector_product_3d(vec_orig_neigh[0], vec_orig_neigh[0], vec_orig_neigh[0], force_vector_x, force_vector_y, force_vector_z);
        
        std::array<float, 3> up_a;
        std::array<float, 3> vec_orig_abov = v0.get_object()[i].get_above_spring();
        up_a = vector_product_3d(vec_orig_abov[0], vec_orig_abov[0], vec_orig_abov[0], force_vector_x, force_vector_y, force_vector_z);
        
        std::array<float, 3> up_ar;
        std::array<float, 3> vec_orig_abovr = v0.get_object()[i].get_above_right_spring();
        up_ar = vector_product_3d(vec_orig_abovr[0], vec_orig_abovr[0], vec_orig_abovr[0], force_vector_x, force_vector_y, force_vector_z);

//        v0.get_object()[i].update_all(translate_into_coordinates(up_n, v0.get_object()[i].get_all_pos()));
        std::array<float, 3> nupp {v0.get_object()[i].get_posX() + up_n[0], v0.get_object()[i].get_posY() + up_n[1], v0.get_object()[i].get_posZ() + up_n[2]};
        v0.get_object()[i].update_all(nupp);
//        v0.get_object()[i].update_all(translate_into_coordinates(up_n, v0.get_object()[i].get_all_pos()));
        std::array<float, 3> nuppi {v0.get_object()[i].get_posX() + up_a[0], v0.get_object()[i].get_posY() + up_a[1], v0.get_object()[i].get_posZ() + up_a[2]};
        v0.get_object()[i].update_all(nuppi);
       
//        v0.get_object()[i].update_all(translate_into_coordinates(up_a, v0.get_object()[i].get_all_pos()));
//        v0.get_object()[i].update_all(translate_into_coordinates(up_ar, v0.get_object()[i].get_all_pos()));
        
        std::array<float, 3> nuppu {v0.get_object()[i].get_posX() + up_ar[0], v0.get_object()[i].get_posY()+ up_ar[1], v0.get_object()[i].get_posZ() + up_ar[2]};
        v0.get_object()[i].update_all(nuppu);
//
//        v0.update_vertex(translate_into_coordinates(up_n, v0.get_object()[i].get_all_pos()), i);
//        v0.update_vertex(translate_into_coordinates(up_a, v0.get_object()[i].get_all_pos()), i);
//        v0.update_vertex(translate_into_coordinates(up_ar, v0.get_object()[i].get_all_pos()), i);
    }
}

std::array<float, 3> Sim::vector_product_3d(float vec_1_x, float vec_1_y, float vec_1_z, float vec_2_x, float vec_2_y, float vec_2_z)
{
    std::array<float, 3> ret;
    ret[0] =(vec_1_y*vec_2_z)-(vec_1_z*vec_2_y);
    ret[1] =-(vec_1_z*vec_2_x)-(vec_1_x*vec_2_z);
    ret[2] = (vec_1_x*vec_2_y)-(vec_1_y*vec_2_x);
    return ret;
}
Vertex_Object Sim::_v0_return(void){
    return v0;
}
