#include "Algebra.hpp"
#include "Gui.hpp"


extern "C"
{
    RayTracer::Application* CreateApplication( )
    {
        using namespace RayTracer;


        return new Application;
    }
}
