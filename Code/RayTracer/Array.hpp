#pragma once

#include "Common.hpp"

namespace RayTracer
{

    template <typename T, SizeType Dimension>
    struct Array
    {
            T data[ Dimension ? Dimension : 1 ];

            //

            const T& operator[]( const SizeType& i ) const
            {
                return data[ i ];
            }

            T& operator[]( const SizeType& i )
            {
                return data[ i ];
            }

            constexpr SizeType GetDimension( )
            {
                return Dimension;
            }

            const T* GetData( ) const
            {
                return data;
            }

            T* GetData( )
            {
                return data;
            }
    };

#define RAYTRACER_INSTANTIATE_ARRAY( T, Dimension ) template class Array<T, Dimension>;
#define RAYTRACER_EXTERNALIZE_ARRAY( T, Dimension ) extern RAYTRACER_INSTANTIATE_ARRAY( T, Dimension )

    RAYTRACER_EXTERNALIZE_ARRAY( float, 2 )
    RAYTRACER_EXTERNALIZE_ARRAY( double, 2 )
    RAYTRACER_EXTERNALIZE_ARRAY( float, 3 )
    RAYTRACER_EXTERNALIZE_ARRAY( double, 3 )

} // namespace RayTracer