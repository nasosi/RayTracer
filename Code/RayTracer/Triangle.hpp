#pragma once

#include "Algebra.hpp"
#include "Interval.hpp"
#include "Ray.hpp"

#include <optional>

namespace RayTracer
{

    struct Triangle : public Array< Point3, 3 >
    {
            using IntervalType = Interval< Point3::ValueType >;

            inline IntervalType GetDistSquareIntervalFrom( const Point3& other ) const
            {

                auto d0 = ( ( *this )[ 0 ] - other ).MagSquare( );
                auto d1 = ( ( *this )[ 1 ] - other ).MagSquare( );
                auto d2 = ( ( *this )[ 2 ] - other ).MagSquare( );

                return IntervalType { std::min( std::min( d0, d1 ), d2 ), std::max( std::max( d0, d1 ), d2 ) };
            }


            const Point3& a( ) const
            {
                return ( *this )[ 0 ];
            }

            Point3& a( )
            {
                return ( *this )[ 0 ];
            }

            const Point3& b( ) const
            {
                return ( *this )[ 1 ];
            }
            Point3& b( )
            {
                return ( *this )[ 1 ];
            }

            const Point3& c( ) const
            {
                return ( *this )[ 2 ];
            }
            Point3& c( )
            {
                return ( *this )[ 2 ];
            }

            std::optional< Vec3 > Intersect( const RayType& ray ) const;
    };

    std::ostream& operator<<( std::ostream& os, const Triangle& t );


} // namespace RayTracer