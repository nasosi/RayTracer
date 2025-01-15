#include "Gui.hpp"
#include "Algebra.hpp"



extern "C"
{
    RayTracer::Application* CreateApplication( )
    {
        using namespace RayTracer;

        return new Application;
    }
}
