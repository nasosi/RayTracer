#include "Algebra.hpp"


namespace RayTracer
{
    
        RAYTRACER_VECTOR_TYPE_INSTANTIATE( float, 2 )
        RAYTRACER_VECTOR_TYPE_INSTANTIATE( float, 3 )
        RAYTRACER_VECTOR_TYPE_INSTANTIATE( double, 2 )
        RAYTRACER_VECTOR_TYPE_INSTANTIATE( double, 3 )

        RAYTRACER_POINT_TYPE_INSTANTIATE( float, 2 )
        RAYTRACER_POINT_TYPE_INSTANTIATE( float, 3 )
        RAYTRACER_POINT_TYPE_INSTANTIATE( double, 2 )
        RAYTRACER_POINT_TYPE_INSTANTIATE( double, 3 )
 
} // namespace RayTracer