#include "Gui.hpp"

#include <iostream>
#include <omp.h>

extern "C"
{
    RayTracer::Application* CreateApplication( )
    {
        return new RayTracer::Application;
    }
}
