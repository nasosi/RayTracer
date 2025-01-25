#pragma once

#include "Algebra.hpp"

namespace RayTracer
{

    template <class Type>
    class Ray
    {
        private:

            Point<Type, 3> origin;
            Vec<Type, 3>   direction;


        public:

            Ray( )
            {
            }

            Ray( const Point<Type, 3>& origin, const Vec<Type, 3>& direction ) : origin( origin ), direction( direction )
            {
            }

            const Point<Type, 3>& GetOrigin( ) const
            {
                return origin;
            }
            const Vec<Type, 3>& GetDirection( ) const
            {
                return direction;
            }

            inline Point<Type, 3> GetPointAt( Type t ) const
            {
                return origin + t * direction;
            }
    };


    extern template class Ray<float>;
    extern template class Ray<double>;

    using RayF = Ray<float>;
    using RayD = Ray<double>;

    using RayType = Ray<RealType>;

} // namespace RayTracer