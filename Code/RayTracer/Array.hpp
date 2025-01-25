#pragma once

#include "Common.hpp"
#include <ostream>

namespace RayTracer
{

    template < typename T, SizeType Dimension >
    struct Array
    {

            using ValueType = T;

            T data[ Dimension ? Dimension : 1 ];

            //

            inline const T& operator[]( const SizeType& i ) const
            {
                return data[ i ];
            }

            inline T& operator[]( const SizeType& i )
            {
                return data[ i ];
            }

            inline constexpr SizeType GetDimension( )
            {
                return Dimension;
            }

            inline const T* GetData( ) const
            {
                return data;
            }

            inline T* GetData( )
            {
                return data;
            }

            template < class Func >
            static constexpr inline void Loop_Constexpr( Func&& f )
            {
                For_Constexpr< SizeType, SizeType( 0 ), Dimension >( std::forward< Func >( f ) );
            }
    };

    template < typename T, SizeType Dimension >
    std::ostream& operator<<( std::ostream& os, const Array< T, Dimension >& a )
    {
        a.Loop_Constexpr(
            [ & ]( auto i )
            {
                os << a[ i ];

                if constexpr ( i != Dimension - 1 )
                {
                    os << ' ';
                }
            } );

        return os;
    }


#define RAYTRACER_EXTERNALIZE_ARRAY( T, Dimension ) extern template class Array< T, Dimension >;
#define RAYTRACER_INSTANTIATE_ARRAY( T, Dimension ) template class Array< T, Dimension >;

    RAYTRACER_EXTERNALIZE_ARRAY( float, 2 )
    RAYTRACER_EXTERNALIZE_ARRAY( double, 2 )
    RAYTRACER_EXTERNALIZE_ARRAY( float, 3 )
    RAYTRACER_EXTERNALIZE_ARRAY( double, 3 )


} // namespace RayTracer