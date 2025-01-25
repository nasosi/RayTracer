#pragma once

#include "Algebra.hpp"
#include "Triangle.hpp"

namespace RayTracer
{

    class BoundingBox
    {


        public:

            Point3   lowPoint;
            Point3   highPoint;

            bool     Contains( const Point3& p ) const;
            bool     Contains( const Triangle& t ) const;
    };

} // namespace RayTracer