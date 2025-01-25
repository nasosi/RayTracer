#pragma once

#include "Array.hpp"
#include "Common.hpp"
#include "ConstexprFor.hpp"
#include <cmath>


namespace RayTracer
{


    template < typename T, SizeType Dimension >
    class CartesianArray : public Array< T, Dimension >
    {
        protected:

            using BaseArray = Array< T, Dimension >;

        public:

            inline const T& x( ) const
            {
                return ( *this )[ 0 ];
            }

            inline T& x( )
            {
                return ( *this )[ 0 ];
            }

            template < SizeType Dim = Dimension >
            inline typename std::enable_if< ( Dim > 1 ), const T& >::type y( ) const
            {
                return ( *this )[ 1 ];
            }

            template < SizeType Dim = Dimension >
            inline typename std::enable_if< ( Dim > 1 ), T& >::type y( )
            {
                return ( *this )[ 1 ];
            }

            template < SizeType Dim = Dimension >
            inline typename std::enable_if< ( Dim > 2 ), const T& >::type z( ) const
            {
                return ( *this )[ 2 ];
            }

            template < SizeType Dim = Dimension >
            inline typename std::enable_if< ( Dim > 2 ), T& >::type z( )
            {
                return ( *this )[ 2 ];
            }

            template < SizeType Dim = Dimension >
            inline typename std::enable_if< ( Dim > 3 ), const T& >::type w( ) const
            {
                return ( *this )[ 3 ];
            }

            template < SizeType Dim = Dimension >
            inline typename std::enable_if< ( Dim > 3 ), T& >::type w( )
            {
                return ( *this )[ 3 ];
            }
    };


    template < typename T, SizeType Dimension >
    class Vec : public CartesianArray< T, Dimension >
    {
        protected:

            using BaseArray = CartesianArray< T, Dimension >::BaseArray;

        public:

            inline Vec& operator+=( const Vec& v )
            {
                BaseArray::Loop_Constexpr(
                    [ this, &v ]( auto i )
                    {
                        ( *this )[ i ] += v[ i ];
                    } );

                return *this;
            }

            inline Vec& operator-=( const Vec& v )
            {
                BaseArray::Loop_Constexpr(
                    [ this, &v ]( auto i )
                    {
                        ( *this )[ i ] -= v[ i ];
                    } );

                return *this;
            }

            inline Vec& operator*=( const T& s )
            {
                BaseArray::Loop_Constexpr(
                    [ this, &s ]( auto i )
                    {
                        ( *this )[ i ] *= s;
                    } );

                return *this;
            }

            inline Vec& operator/=( const T& s )
            {
                BaseArray::Loop_Constexpr(
                    [ this, &s ]( auto i )
                    {
                        ( *this )[ i ] /= s;
                    } );

                return *this;
            }

            inline T MagSquare( ) const
            {
                T m = 0;

                BaseArray::Loop_Constexpr(
                    [ this, &m ]( auto i )
                    {
                        m += std::pow( ( *this )[ i ], 2 );
                    } );

                return m;
            }

            inline T Magnitude( ) const
            {
                return std::sqrt( MagSquare( ) );
            }
    };


    template < typename T, SizeType Dimension >
    inline Vec< T, Dimension > operator+( Vec< T, Dimension > a, const Vec< T, Dimension >& b )
    {
        a += b;

        return a;
    }

    template < typename T, SizeType Dimension >
    inline Vec< T, Dimension > operator-( Vec< T, Dimension > a, const Vec< T, Dimension >& b )
    {
        a -= b;

        return a;
    }

    template < typename T, SizeType Dimension >
    inline Vec< T, Dimension > operator*( Vec< T, Dimension > a, const T& s )
    {
        a *= s;

        return a;
    }

    template < typename T, SizeType Dimension >
    inline Vec< T, Dimension > operator*( const T& s, Vec< T, Dimension > a )
    {
        return a * s;
    }

    template < typename T, SizeType Dimension >
    inline Vec< T, Dimension > operator/( Vec< T, Dimension > a, const T& s )
    {
        a /= s;

        return a;
    }

    template < typename T, SizeType Dimension >
    inline Vec< T, Dimension > operator-( Vec< T, Dimension > v )
    {
        Vec< T, Dimension >::Loop_Constexpr(
            [ &v ]( auto i )
            {
                v[ i ] -= v[ i ];
            } );


        return v;
    }


    template < typename T, SizeType Dimension >
    class Point : public CartesianArray< T, Dimension >
    {
        protected:

            using BaseArray = CartesianArray< T, Dimension >::BaseArray;


        public:

            using ValueType = BaseArray::ValueType;

            inline Point& operator+=( const Vec< T, Dimension >& vec )
            {
                BaseArray::Loop_Constexpr(
                    [ this, &vec ]( auto i )
                    {
                        ( *this )[ i ] += vec[ i ];
                    } );

                return *this;
            }

            inline Point& operator-=( const Vec< T, Dimension >& vec )
            {
                BaseArray::Loop_Constexpr(
                    [ this, &vec ]( auto i )
                    {
                        ( *this )[ i ] -= vec[ i ];
                    } );

                return *this;
            }
    };

    template < typename T, SizeType Dimension >
    inline Vec< T, Dimension > operator-( const Point< T, Dimension >& a, const Point< T, Dimension >& b )
    {
        Vec< T, Dimension > vec;

        Vec< T, Dimension >::Loop_Constexpr(
            [ &vec, &a, &b ]( auto i )
            {
                vec[ i ] = a[ i ] - b[ i ];
            } );

        return vec;
    }

    template < typename T, SizeType Dimension >
    inline Point< T, Dimension > operator+( Point< T, Dimension > p, const Vec< T, Dimension >& v )
    {
        p += v;

        return p;
    }

    template < typename T, SizeType Dimension >
    inline Point< T, Dimension > operator+( const Vec< T, Dimension >& v, Point< T, Dimension > p )
    {
        return p + v;
    }

    template < typename T, SizeType Dimension >
    inline Point< T, Dimension > operator-( Point< T, Dimension > p, const Vec< T, Dimension >& v )
    {
        p -= v;

        return p;
    }


    template < typename T, SizeType Dimension >
    inline Vec< T, Dimension > Normalize( const Vec< T, Dimension >& v )
    {
        return v / v.Magnitude( );
    }

    template < typename T, SizeType Dimension >
    inline T Dot( const Vec< T, Dimension >& u, const Vec< T, Dimension >& v )
    {
        T d = 0.0;

        Vec< T, Dimension >::Loop_Constexpr(
            [ &d, &u, &v ]( auto i )
            {
                d += u[ i ] * v[ i ];
            } );

        return d;
    }


    template < typename T >
    inline Vec< T, 3 > Cross( const Vec< T, 3 >& u, const Vec< T, 3 >& v )
    {
        return Vec< T, 3 > { u[ 1 ] * v[ 2 ] - u[ 2 ] * v[ 1 ], u[ 2 ] * v[ 0 ] - u[ 0 ] * v[ 2 ], u[ 0 ] * v[ 1 ] - u[ 1 ] * v[ 0 ] };
    }

    template < typename T >
    inline Vec< T, 3 > Reflect( const Vec< T, 3 >& vec, const Vec< T, 3 >& normal )
    {
        return vec - T( 2.0 ) * Dot( vec, normal ) * normal;
    }


    template < typename T >
    inline Vec< T, 3 > RotateVector( const Vec< T, 3 >& vec, const Vec< T, 3 >& normalizedRotationAxis, const T& angleDeg )
    {
        T cosTheta = std::cos( DegreesToRadians( angleDeg ) );
        T sinTheta = std::sin( DegreesToRadians( angleDeg ) );

        return vec * cosTheta + Cross( normalizedRotationAxis, vec ) * sinTheta + normalizedRotationAxis * Dot( normalizedRotationAxis, vec ) * ( T( 1.0 ) - cosTheta );
    }

    template < typename T >
    inline Point< T, 3 > RotatePointAround( Point< T, 3 > rotationPoint, const Point< T, 3 >& point, const Vec< T, 3 >& normalizedRotationAxis, const T& angleDeg )
    {
        Vec< T, 3 > vec       = point - rotationPoint;
        vec                   = RotateVector( vec, normalizedRotationAxis, angleDeg );

        return rotationPoint += vec;
    }

    template < class T >
    Vec< T, 3 > CreateRandomVector( )
    {
        return Vec< T, 3 > { RandomReal< T >( ), RandomReal< T >( ), RandomReal< T >( ) };
    }

    template < typename T >
    Vec< T, 3 > CreateRandomVector( const T& min, const T& max )
    {
        return Vec< T, 3 > { RandomReal< T >( min, max ), RandomReal< T >( min, max ), RandomReal< T >( min, max ) };
    }

    template < typename T >
    Vec< T, 3 > CreateRandomNormalizedVector( )
    {
        constexpr T eps = std::numeric_limits< T >::epsilon( ); // Could be eps^2

        while ( true )
        {
            Vec< T, 3 > p         = CreateRandomVector( T( -1.0 ), T( 1.0 ) );
            T           magSquare = p.MagSquare( );

            if ( eps < magSquare && magSquare <= 1.0 )
            {
                return p / sqrt( magSquare );
            }
        }
    }

    template < typename T >
    inline bool NearZero( const Vec< T, 3 >& v )
    {
        constexpr T eps = std::numeric_limits< T >::epsilon( );

        return ( std::fabs( v[ 0 ] ) < eps ) && ( std::fabs( v[ 1 ] ) < eps ) && ( std::fabs( v[ 2 ] ) < eps );
    }


    using Point2f = Point< float, 2 >;
    using Point2d = Point< double, 2 >;
    using Point3f = Point< float, 3 >;
    using Point3d = Point< double, 3 >;

    using Vec2f   = Vec< float, 2 >;
    using Vec2d   = Vec< double, 2 >;
    using Vec3f   = Vec< float, 3 >;
    using Vec3d   = Vec< double, 3 >;


#define RAYTRACER_ALGEBRA_INSTANTIATE_PROTO( PREAMBLE, T, Dimension )                                                                                                                   \
    PREAMBLE template class Vec< T, Dimension >;                                                                                                                                        \
    PREAMBLE template class Point< T, Dimension >;                                                                                                                                      \
    PREAMBLE template Vec< T, Dimension >   operator+( Vec< T, Dimension > a, const Vec< T, Dimension >& b );                                                                           \
    PREAMBLE template Vec< T, Dimension >   operator-( Vec< T, Dimension > a, const Vec< T, Dimension >& b );                                                                           \
    PREAMBLE template Vec< T, Dimension >   operator*( Vec< T, Dimension > a, const T& s );                                                                                             \
    PREAMBLE template Vec< T, Dimension >   operator*( const T& s, Vec< T, Dimension > a );                                                                                             \
    PREAMBLE template Vec< T, Dimension >   operator/( Vec< T, Dimension > a, const T& s );                                                                                             \
    PREAMBLE template Vec< T, Dimension >   operator-( Vec< T, Dimension > v );                                                                                                         \
    PREAMBLE template Vec< T, Dimension >   operator-( const Point< T, Dimension >& a, const Point< T, Dimension >& b );                                                                \
    PREAMBLE template Point< T, Dimension > operator+( Point< T, Dimension > p, const Vec< T, Dimension >& v );                                                                         \
    PREAMBLE template Point< T, Dimension > operator+( const Vec< T, Dimension >& v, Point< T, Dimension > p );                                                                         \
    PREAMBLE template Point< T, Dimension > operator-( Point< T, Dimension > p, const Vec< T, Dimension >& v );                                                                         \
    PREAMBLE template Vec< T, Dimension >   Normalize( const Vec< T, Dimension >& v );                                                                                                  \
    PREAMBLE template T                     Dot( const Vec< T, Dimension >& u, const Vec< T, Dimension >& v );                                                                          \
    PREAMBLE template Vec< T, 3 >           Cross( const Vec< T, 3 >& u, const Vec< T, 3 >& v );                                                                                        \
    PREAMBLE template Vec< T, 3 >           Reflect( const Vec< T, 3 >& vec, const Vec< T, 3 >& normal );                                                                               \
    PREAMBLE template Vec< T, 3 >           RotateVector( const Vec< T, 3 >& vec, const Vec< T, 3 >& normalizedRotationAxis, const T& angleDeg );                                       \
    PREAMBLE template Point< T, 3 >         RotatePointAround( Point< T, 3 > rotationPoint, const Point< T, 3 >& point, const Vec< T, 3 >& normalizedRotationAxis, const T& angleDeg ); \
    PREAMBLE template Vec< T, 3 >           CreateRandomVector( );                                                                                                                      \
    PREAMBLE template Vec< T, 3 >           CreateRandomVector( const T& min, const T& max );                                                                                           \
    PREAMBLE template Vec< T, 3 >           CreateRandomNormalizedVector( );

    RAYTRACER_ALGEBRA_INSTANTIATE_PROTO( extern, float, 2 )
    RAYTRACER_ALGEBRA_INSTANTIATE_PROTO( extern, float, 3 )
    RAYTRACER_ALGEBRA_INSTANTIATE_PROTO( extern, double, 2 )
    RAYTRACER_ALGEBRA_INSTANTIATE_PROTO( extern, double, 3 )


    using Vec3   = Vec< RealType, 3 >;
    using Point3 = Point< RealType, 3 >;

} // namespace RayTracer
