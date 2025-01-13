#pragma once

#include "Algebra.hpp"

namespace RayTracer
{

    template <class Type>
    class Ray
    {
        private:

            Point3<Type> origin;
            Vec3<Type>   direction;


        public:

            Ray( )
            {
            }

            Ray( const Point3<Type>& origin, const Vec3<Type>& direction ) : origin( origin ), direction( direction )
            {
            }

            const Point3<Type>& GetOrigin( ) const
            {
                return origin;
            }
            const Vec3<Type>& GetDirection( ) const
            {
                return direction;
            }

            Point3<Type> GetPointAt( Type t ) const
            {
                return origin + t * direction;
            }
    };


    extern template class Ray<float>;
    extern template class Ray<double>;

    using RayF = Ray<float>;
    using RayD = Ray<double>;

} // namespace RayTracer