#include "Gui.hpp"

#include "Algebra.hpp"


extern "C"
{
    RayTracer::Application* CreateApplication( )
    {
        using namespace RayTracer;

        V::Vec<double, 3> v { 2, 3, 5 };
        V::Vec<double, 3> c { 1, 2, 2 };

        v += c;

        c  = -v;

        c.x( );


        V::Point<double, 3> p1 { 5, 6, 7 };
        V::Point<double, 3> p2 { 2, 2, 2 };

        auto                v2 = p1 - p2;


        

        return new Application;
    }
}
