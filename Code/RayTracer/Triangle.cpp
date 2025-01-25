#pragma once

#include "Triangle.hpp"

#include <ostream>

namespace RayTracer
{

    std::ostream& operator<<( std::ostream& os, const Triangle& t )
    {
        os << t.a( ) << '|' << t.b( ) << '|' << t.c( );

        return os;
    }

} // namespace RayTracer
