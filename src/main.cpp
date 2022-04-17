#include "tower_sim.hpp"


void test_generic_points()
{
    Point<3, float> p1;
    Point<3, float> p2;
    //Point3D p4 {1.f, 2.f}; // Provoque une erreur

    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3;
    p3 *= 1;
    //p4 *= 1;
}


int main(int argc, char** argv)
{
    test_generic_points();
    TowerSimulation simulation { argc, argv };
    simulation.launch();

    return 0;
}