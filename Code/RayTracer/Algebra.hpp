#pragma once

#include "Array.hpp"
#include "Common.hpp"
#include "ConstexprFor.hpp"
#include <cmath>


namespace RayTracer
{


    template <typename T, SizeType Dimension>
    class CartesianArray : public Array<T, Dimension>
    {
        private:

            using Parent = Array<T, Dimension>;


        public:

            const T& x( ) const
            {
                return Parent::data[ 0 ];
            }

            T& x( )
            {
                return Parent::data[ 0 ];
            }

            template <SizeType Dim = Dimension>
            typename std::enable_if<( Dim > 1 ), const T&>::type y( ) const
            {
                return Parent::data[ 1 ];
            }

            template <SizeType Dim = Dimension>
            typename std::enable_if<( Dim > 1 ), T&>::type y( )
            {
                return Parent::data[ 1 ];
            }

            template <SizeType Dim = Dimension>
            typename std::enable_if<( Dim > 2 ), const T&>::type z( ) const
            {
                return Parent::data[ 2 ];
            }

            template <SizeType Dim = Dimension>
            typename std::enable_if<( Dim > 2 ), T&>::type z( )
            {
                return Parent::data[ 2 ];
            }

            template <SizeType Dim = Dimension>
            typename std::enable_if<( Dim > 3 ), const T&>::type w( ) const
            {
                return Parent::data[ 3 ];
            }

            template <SizeType Dim = Dimension>
            typename std::enable_if<( Dim > 3 ), T&>::type w( )
            {
                return Parent::data[ 3 ];
            }
    };


    template <typename T, SizeType Dimension>
    class Vec;


    template <typename T, SizeType Dimension>
    class Point : public CartesianArray<T, Dimension>
    {
        public:

            inline Point& operator+=( const Vec<T, Dimension>& vec )
            {
                Constexpr_For<SizeType, 0, Dimension>(
                    [ this, &vec ]( auto i )
                    {
                        ( *this )[ i ] += vec[ i ];
                    } );

                return *this;
            }

            inline Point& operator-=( const Vec<T, Dimension>& vec )
            {
                Constexpr_For<SizeType, 0, Dimension>(
                    [ this, &vec ]( auto i )
                    {
                        ( *this )[ i ] -= vec[ i ];
                    } );

                return *this;
            }
    };


    template <typename T, SizeType Dimension>
    class Vec : public CartesianArray<T, Dimension>
    {
        public:

            inline Vec& operator+=( const Vec& v )
            {
                Constexpr_For<SizeType, 0, Dimension>(
                    [ this, &v ]( auto i )
                    {
                        ( *this )[ i ] += v[ i ];
                    } );

                return *this;
            }

            inline Vec& operator-=( const Vec& v )
            {
                Constexpr_For<SizeType, 0, Dimension>(
                    [ this, &v ]( auto i )
                    {
                        ( *this )[ i ] -= v[ i ];
                    } );

                return *this;
            }

            inline Vec& operator*=( const T& s )
            {
                Constexpr_For<SizeType, 0, Dimension>(
                    [ this, &s ]( auto i )
                    {
                        ( *this )[ i ] *= s;
                    } );

                return *this;
            }

            inline Vec& operator/=( const T& s )
            {
                *( this ) *= 1.0 / s;

                return *this;
            }

            inline T MagSquare( ) const
            {
                T m = 0;

                Constexpr_For<SizeType, 0, Dimension>(
                    [ this, &m ]( auto i )
                    {
                        m += std::powf( ( *this )[ i ], 2 );
                    } );

                return m;
            }

            inline T Magnitude( ) const
            {
                return std::sqrt( MagSquare( ) );
            }
    };

    template <typename T, SizeType Dimension>
    inline Vec<T, Dimension> operator+( Vec<T, Dimension> a, const Vec<T, Dimension>& b )
    {
        a += b;

        return a;
    }

    template <typename T, SizeType Dimension>
    inline Vec<T, Dimension> operator-( Vec<T, Dimension> a, const Vec<T, Dimension>& b )
    {
        a -= b;

        return a;
    }

    template <typename T, SizeType Dimension>
    inline Vec<T, Dimension> operator*( Vec<T, Dimension> a, const T& s )
    {
        a *= s;

        return a;
    }

    template <typename T, SizeType Dimension>
    inline Vec<T, Dimension> operator*( const T& s, Vec<T, Dimension> a )
    {
        return a * s;
    }

    template <typename T, SizeType Dimension>
    inline Vec<T, Dimension> operator/( Vec<T, Dimension> a, const T& s )
    {
        a /= s;

        return a;
    }

    template <typename T, SizeType Dimension>
    inline Vec<T, Dimension> operator-( Vec<T, Dimension> v )
    {
        Constexpr_For<SizeType, 0, Dimension>(
            [ &v ]( auto i )
            {
                v[ i ] -= v[ i ];
            } );


        return v;
    }

    template <typename T, SizeType Dimension>
    inline Vec<T, Dimension> operator-( const Point<T, Dimension>& a, const Point<T, Dimension>& b )
    {
        Vec<T, Dimension> vec;

        Constexpr_For<SizeType, 0, Dimension>(
            [ &vec, &a, &b ]( auto i )
            {
                vec[ i ] = a[ i ] - b[ i ];
            } );

        return vec;
    }

    template <typename T, SizeType Dimension>
    inline Point<T, Dimension> operator+( Point<T, Dimension> p, const Vec<T, Dimension>& v )
    {
        p += v;

        return p;
    }

    template <typename T, SizeType Dimension>
    inline Point<T, Dimension> operator+( const Vec<T, Dimension>& v, Point<T, Dimension> p )
    {
        return p + v;
    }

    template <typename T, SizeType Dimension>
    inline Point<T, Dimension> operator-( Point<T, Dimension> p, const Vec<T, Dimension>& v )
    {
        p -= v;

        return p;
    }


    template <typename T, SizeType Dimension>
    inline Vec<T, Dimension> Normalize( const Vec<T, Dimension>& v )
    {
        return v / v.Magnitude( );
    }

    template <typename T, SizeType Dimension>
    inline T Dot( const Vec<T, Dimension>& u, const Vec<T, 3>& v )
    {
        T d = 0.0;

        Constexpr_For<SizeType, 0, Dimension>(
            [ &d, &u, &v ]( auto i )
            {
                d += u[ i ] * v[ i ];
            } );

        return d;
    }


    template <typename T>
    inline Vec<T, 3> Cross( const Vec<T, 3>& u, const Vec<T, 3>& v )
    {
        return Vec<T, 3> { u[ 1 ] * v[ 2 ] - u[ 2 ] * v[ 1 ], u[ 2 ] * v[ 0 ] - u[ 0 ] * v[ 2 ], u[ 0 ] * v[ 1 ] - u[ 1 ] * v[ 0 ] };
    }

    template <typename T>
    inline Vec<T, 3> Reflect( const Vec<T, 3>& vec, const Vec<T, 3>& normal )
    {
        return vec - 2.0 * Dot( vec, normal ) * normal;
    }


    template <typename T>
    inline Vec<T, 3> Rotate( const Vec<T, 3>& vec, const Vec<T, 3>& normalizedRotationAxis, T angleDeg )
    {
        T cosTheta = std::cos( DegreesToRadians( angleDeg ) );
        T sinTheta = std::sin( DegreesToRadians( angleDeg ) );

        return vec * cosTheta + Cross( normalizedRotationAxis, vec ) * sinTheta + normalizedRotationAxis * Dot( normalizedRotationAxis, vec ) * ( 1.0 - cosTheta );
    }

    template <typename T>
    inline Point<T, 3> RotateAround( Point<T, 3> rotationPoint, Point<T, 3> point, const Vec<T, 3>& normalizedRotationAxis, T angleDeg )
    {
        T         cosTheta    = std::cos( DegreesToRadians( angleDeg ) );
        T         sinTheta    = std::sin( DegreesToRadians( angleDeg ) );

        Vec<T, 3> vec         = point - rotationPoint;
        vec                   = vec * cosTheta + Cross( normalizedRotationAxis, vec ) * sinTheta + normalizedRotationAxis * Dot( normalizedRotationAxis, vec ) * ( 1.0 - cosTheta );

        return rotationPoint += vec;
    }

    template <class T>
    Vec<T, 3> CreateRandomVector( )
    {
        return Vec<T, 3> { RandomReal<T>( ), RandomReal<T>( ), RandomReal<T>( ) };
    }

    template <typename T>
    Vec<T, 3> CreateRandomVector( const T& min, const T& max )
    {
        return Vec<T, 3> { RandomReal<T>( min, max ), RandomReal<T>( min, max ), RandomReal<T>( min, max ) };
    }

    template <typename T>
    Vec<T, 3> CreateRandomUnitVector( )
    {
        while ( true )
        {
            Vec<T, 3> p         = CreateRandomVector( -1.0, 1.0 );
            T         magSquare = p.MagSquare( );

            if ( 1e-16 < magSquare && magSquare <= 1.0 )
            {
                return p / sqrt( magSquare );
            }
        }
    }

    template <typename T>
    inline bool NearZero( const Vec<T, 3>& v )
    {
        T s = std::numeric_limits<T>::epsilon( );
        return ( std::fabs( v[ 0 ] ) < s ) && ( std::fabs( v[ 1 ] ) < s ) && ( std::fabs( v[ 2 ] ) < s );
    }

#define RAYTRACER_VECTOR_STRUCT_EXTERN( T, Dimension ) extern template class Vec<T, Dimension>;
#define RAYTRACER_POINT_STRUCT_EXTERN( T, Dimension )  extern template class Point<T, Dimension>;


#define RAYTRACER_VECTOR_OPERATIONS_EXTERN( T, Dimension )                                      \
    extern template Vec<T, Dimension> operator+( Vec<T, Dimension>, const Vec<T, Dimension>& ); \
    extern template Vec<T, Dimension> operator-( Vec<T, Dimension>, const Vec<T, Dimension>& ); \
    extern template Vec<T, Dimension> operator*( Vec<T, Dimension>, const T& );                 \
    extern template Vec<T, Dimension> operator*( const T&, Vec<T, Dimension> );                 \
    extern template Vec<T, Dimension> operator/( Vec<T, Dimension>, const T& );                 \
    extern template Vec<T, Dimension> operator-( Vec<T, Dimension> );

#define RAYTRACER_POINT_OPERATIONS_EXTERN( T, Dimension )                                                        \
    extern template Vec<T, Dimension>   operator-( const Point<T, Dimension>& a, const Point<T, Dimension>& b ); \
    extern template Point<T, Dimension> operator+( Point<T, Dimension> p, const Vec<T, Dimension>& v );          \
    extern template Point<T, Dimension> operator+( const Vec<T, Dimension>& v, Point<T, Dimension> p );          \
    extern template Point<T, Dimension> operator-( Point<T, Dimension> p, const Vec<T, Dimension>& v );


#define RAYTRACER_VECTOR_STRUCT_INSTANTIATE( T, Dimension ) template class Vec<T, Dimension>;
#define RAYTRACER_POINT_STRUCT_INSTANTIATE( T, Dimension )  template class Point<T, Dimension>;


#define RAYTRACER_VECTOR_OPERATIONS_INSTANTIATE( T, Dimension )                          \
    template Vec<T, Dimension> operator+( Vec<T, Dimension>, const Vec<T, Dimension>& ); \
    template Vec<T, Dimension> operator-( Vec<T, Dimension>, const Vec<T, Dimension>& ); \
    template Vec<T, Dimension> operator*( Vec<T, Dimension>, const T& );                 \
    template Vec<T, Dimension> operator*( const T&, Vec<T, Dimension> );                 \
    template Vec<T, Dimension> operator/( Vec<T, Dimension>, const T& );                 \
    template Vec<T, Dimension> operator-( Vec<T, Dimension> );

#define RAYTRACER_POINT_OPERATIONS_INSTANTIATE( T, Dimension )                                            \
    template Vec<T, Dimension>   operator-( const Point<T, Dimension>& a, const Point<T, Dimension>& b ); \
    template Point<T, Dimension> operator+( Point<T, Dimension> p, const Vec<T, Dimension>& v );          \
    template Point<T, Dimension> operator+( const Vec<T, Dimension>& v, Point<T, Dimension> p );          \
    template Point<T, Dimension> operator-( Point<T, Dimension> p, const Vec<T, Dimension>& v );


#define RAYTRACER_VECTOR_TYPE_EXTERN( T, Dimension ) \
    RAYTRACER_VECTOR_STRUCT_EXTERN( T, Dimension )   \
    RAYTRACER_VECTOR_OPERATIONS_EXTERN( T, Dimension )

#define RAYTRACER_POINT_TYPE_EXTERN( T, Dimension ) \
    RAYTRACER_POINT_STRUCT_EXTERN( T, Dimension )   \
    RAYTRACER_POINT_OPERATIONS_EXTERN( T, Dimension )

#define RAYTRACER_VECTOR_TYPE_INSTANTIATE( T, Dimension ) \
    RAYTRACER_VECTOR_STRUCT_INSTANTIATE( T, Dimension )   \
    RAYTRACER_VECTOR_OPERATIONS_INSTANTIATE( T, Dimension )

#define RAYTRACER_POINT_TYPE_INSTANTIATE( T, Dimension ) \
    RAYTRACER_POINT_STRUCT_INSTANTIATE( T, Dimension )   \
    RAYTRACER_POINT_OPERATIONS_INSTANTIATE( T, Dimension )


    RAYTRACER_VECTOR_TYPE_EXTERN( float, 2 )
    RAYTRACER_VECTOR_TYPE_EXTERN( float, 3 )
    RAYTRACER_VECTOR_TYPE_EXTERN( double, 2 )
    RAYTRACER_VECTOR_TYPE_EXTERN( double, 3 )

    RAYTRACER_POINT_TYPE_EXTERN( float, 2 )
    RAYTRACER_POINT_TYPE_EXTERN( float, 3 )
    RAYTRACER_POINT_TYPE_EXTERN( double, 2 )
    RAYTRACER_POINT_TYPE_EXTERN( double, 3 )
    // extern template Vec3D operator+( const Vec3D& u, const Vec3D& v );

    using Point2F = Point<float, 2>;

    using Vec3D   = Vec<double, 3>;
    using Point3D = Point<double, 3>;


    // extern template double Dot( const Vec3D& u, const Vec3D& v );
    //  extern template Vec3D  Cross( const Vec3D& u, const Vec3D& v );


    using Vec3F   = Vec<float, 3>;
    using Point3F = Point<float, 3>;


    // extern template float Dot( const Vec3F& u, const Vec3F& v );
    // extern template Vec3F Cross( const Vec3F& u, const Vec3F& v );
} // namespace RayTracer
