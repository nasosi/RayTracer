#pragma once

#include "Array.hpp"
#include "Common.hpp"

#include <cmath>
#include <utility>

namespace RayTracer
{

    namespace V
    {
        template <typename T, SizeType Dimension>
        class CartesianArray : public Array<T, Dimension>
        {
            private:

                using Parent = Array<T, Dimension>;


            public:

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

                Point& operator+=( const Vec<T, Dimension>& vec )
                {
                    Add( vec );

                    return *this;
                }

                Point& operator-=( const Vec<T, Dimension>& vec )
                {
                    Subtract( vec );

                    return *this;
                }

            private:

                using Base = CartesianArray<T, Dimension>;


                template <SizeType i = 0>
                void Add( const Vec<T, Dimension>& other )
                {
                    Base::data[ i ] += other[ i ];

                    if constexpr ( i == Dimension - 1 )
                    {
                        return;
                    }
                    else
                    {
                        Add<i + 1>( other );
                    }
                }

                template <SizeType i = 0>
                void Subtract( const Vec<T, Dimension>& other )
                {
                    Base::data[ i ] -= other[ i ];

                    if constexpr ( i == Dimension - 1 )
                    {
                        return;
                    }
                    else
                    {
                        Add<i + 1>( other );
                    }
                }
        };

        template <typename T, SizeType Dimension>
        class Vec : public CartesianArray<T, Dimension>
        {
            public:

                Vec& operator+=( const Vec& other )
                {
                    Add( other );

                    return *this;
                }

                Vec& operator-=( const Vec& other )
                {
                    Subtract( other );

                    return *this;
                }

                Vec& operator*=( const T& s )
                {
                    Multiply( s );

                    return *this;
                }

                Vec& operator/=( const T& s )
                {
                    Divide( s );

                    return *this;
                }

                T MagSquare( ) const
                {
                    T m = 0;

                    CalcMagSquare( m );

                    return m;
                }

                T Magnitude( ) const
                {
                    return std::sqrt( MagSquare( ) );
                }

            private:

                using Base = CartesianArray<T, Dimension>;

                template <SizeType i = 0>
                void Multiply( const T& s )
                {
                    Base::data[ i ] *= s;

                    if constexpr ( i == Dimension - 1 )
                    {
                        return;
                    }
                    else
                    {
                        Multiply<i + 1>( s );
                    }
                }

                template <SizeType i = 0>
                void Divide( const T& s )
                {
                    Base::data[ i ] /= s;

                    if constexpr ( i == Dimension - 1 )
                    {
                        return;
                    }
                    else
                    {
                        Divide<i + 1>( s );
                    }
                }

                template <SizeType i = 0>
                void Add( const Vec& other )
                {
                    Base::data[ i ] += other[ i ];

                    if constexpr ( i == Dimension - 1 )
                    {
                        return;
                    }
                    else
                    {
                        Add<i + 1>( other );
                    }
                }

                template <SizeType i = 0>
                void Subtract( const Vec& other )
                {
                    Base::data[ i ] -= other[ i ];

                    if constexpr ( i == Dimension - 1 )
                    {
                        return;
                    }
                    else
                    {
                        Add<i + 1>( other );
                    }
                }

                template <SizeType i = 0>
                void CalcMagSquare( T& m ) const
                {
                    m += std::pow( Base::data[ i ], 2 );

                    if constexpr ( i == Dimension - 1 )
                    {
                        return;
                    }
                    else
                    {
                        CalcMagSquare<i + 1>( m );
                    }
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

        namespace Detail
        {
            template <typename T, SizeType Dimension, SizeType i = 0>
            void VecNegate( const Vec<T, Dimension>& in, Vec<T, Dimension>& out )
            {
                out[ i ] = -in[ i ];

                if constexpr ( i == Dimension - 1 )
                {
                    return;
                }
                else
                {
                    Detail::VecNegate<T, Dimension, i + 1>( in, out );
                }
            }

            template <typename T, SizeType Dimension, SizeType i = 0>
            void PointSubtract( const Point<T, Dimension>& pa, const Point<T, Dimension>& pb, Vec<T, Dimension>& out )
            {
                out[ i ] = pa[ i ] - pb[ i ];

                if constexpr ( i == Dimension - 1 )
                {
                    return;
                }
                else
                {
                    PointSubtract<T, Dimension, i + 1>( pa, pb, out );
                }
            }
        } // namespace Detail

        template <typename T, SizeType Dimension>
        inline Vec<T, Dimension> operator-( const Vec<T, Dimension>& v )
        {
            Vec<T, Dimension> nv;

            Detail::VecNegate( v, nv );

            return nv;
        }

        template <typename T, SizeType Dimension>
        inline Vec<T, Dimension> operator-( const Point<T, Dimension>& a, const Point<T, Dimension>& b )
        {
            Vec<T, Dimension> vec;

            Detail::PointSubtract( a, b, vec );

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


#define RAYTRACER_VECTOR_STRUCT_EXTERN( T, Dimension ) extern template class Vec<T, Dimension>;
#define RAYTRACER_POINT_STRUCT_EXTERN( T, Dimension )  extern template class Point<T, Dimension>;


#define RAYTRACER_VECTOR_OPERATIONS_EXTERN( T, Dimension )                                      \
    extern template Vec<T, Dimension> operator+( Vec<T, Dimension>, const Vec<T, Dimension>& ); \
    extern template Vec<T, Dimension> operator-( Vec<T, Dimension>, const Vec<T, Dimension>& ); \
    extern template Vec<T, Dimension> operator*( Vec<T, Dimension>, const T& );                 \
    extern template Vec<T, Dimension> operator*( const T&, Vec<T, Dimension> );                 \
    extern template Vec<T, Dimension> operator/( Vec<T, Dimension>, const T& );                 \
    extern template Vec<T, Dimension> operator-( const Vec<T, Dimension>& );

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
    template Vec<T, Dimension> operator-( const Vec<T, Dimension>& );

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


    } // namespace V

    template <typename Type>
    struct Vec2
    {
            Type e[ 2 ];

            Vec2( ) : e { 0, 0 }
            {
            }

            Vec2( Type x, Type y ) : e { x, y }
            {
            }

            Type x( ) const
            {
                return e[ 0 ];
            }
            Type y( ) const
            {
                return e[ 1 ];
            }
    };

    template <class T>
    using Point2  = Vec2<T>;
    using Point2F = Point2<float>;


    template <typename Type>
    struct Vec3
    {
            Type e[ 3 ];

            Vec3( ) : e { 0, 0, 0 }
            {
            }

            Vec3( Type e0, Type e1, Type e2 ) : e { e0, e1, e2 }
            {
            }

            Type x( ) const
            {
                return e[ 0 ];
            }
            Type y( ) const
            {
                return e[ 1 ];
            }
            Type z( ) const
            {
                return e[ 2 ];
            }

            Vec3 operator-( ) const
            {
                return Vec3( -e[ 0 ], -e[ 1 ], -e[ 2 ] );
            }

            const Type& operator[]( const SizeType& i ) const
            {
                return e[ i ];
            }

            Type& operator[]( const SizeType& i )
            {
                return e[ i ];
            }

            Vec3& operator+=( const Vec3& v )
            {
                e[ 0 ] += v.e[ 0 ];
                e[ 1 ] += v.e[ 1 ];
                e[ 2 ] += v.e[ 2 ];

                return *this;
            }

            Vec3& operator-=( const Vec3& v )
            {
                e[ 0 ] -= v.e[ 0 ];
                e[ 1 ] -= v.e[ 1 ];
                e[ 2 ] -= v.e[ 2 ];

                return *this;
            }

            Vec3& operator*=( Type t )
            {
                e[ 0 ] *= t;
                e[ 1 ] *= t;
                e[ 2 ] *= t;

                return *this;
            }

            Vec3& operator/=( Type t )
            {
                e[ 0 ] /= t;
                e[ 1 ] /= t;
                e[ 2 ] /= t;

                return *this;
            }

            Type GetLengthSquared( ) const
            {
                return e[ 0 ] * e[ 0 ] + e[ 1 ] * e[ 1 ] + e[ 2 ] * e[ 2 ];
            }

            Type GetLength( ) const
            {
                return std::sqrt( GetLengthSquared( ) );
            }

            Vec3 GetNormalized( ) const
            {
                return ( *this / this->GetLength( ) );
            }

            static Vec3 CreateRandomVector( )
            {
                return Vec3( RandomDouble( ), RandomDouble( ), RandomDouble( ) );
            }

            static Vec3 CreateRandomVector( const Type& min, const Type& max )
            {
                return Vec3( RandomDouble( min, max ), RandomDouble( min, max ), RandomDouble( min, max ) );
            }

            static Vec3 CreateRandomUnitVector( )
            {
                while ( true )
                {
                    Vec3 p             = CreateRandomVector( -1.0, 1.0 );
                    Type lengthSquared = p.GetLengthSquared( );

                    if ( 1e-16 < lengthSquared && lengthSquared <= 1 )
                    {
                        return p / sqrt( lengthSquared );
                    }
                }
            }

            bool NearZero( ) const
            {
                Type s = 1e-8;
                return ( std::fabs( e[ 0 ] ) < s ) && ( std::fabs( e[ 1 ] ) < s ) && ( std::fabs( e[ 2 ] ) < s );
            }
    };

    template <typename Type>
    Vec3<Type> operator+( const Vec3<Type>& u, const Vec3<Type>& v )
    {
        return Vec3<Type>( u.e[ 0 ] + v.e[ 0 ], u.e[ 1 ] + v.e[ 1 ], u.e[ 2 ] + v.e[ 2 ] );
    }

    template <typename Type>
    Vec3<Type> operator-( const Vec3<Type>& u, const Vec3<Type>& v )
    {
        return Vec3<Type>( u.e[ 0 ] - v.e[ 0 ], u.e[ 1 ] - v.e[ 1 ], u.e[ 2 ] - v.e[ 2 ] );
    }

    template <typename Type>
    Vec3<Type> operator*( const Vec3<Type>& u, const Vec3<Type>& v )
    {
        return Vec3<Type>( u.e[ 0 ] * v.e[ 0 ], u.e[ 1 ] * v.e[ 1 ], u.e[ 2 ] * v.e[ 2 ] );
    }

    template <typename Type>
    Vec3<Type> operator*( const Type& t, const Vec3<Type>& v )
    {
        return Vec3<Type>( t * v.e[ 0 ], t * v.e[ 1 ], t * v.e[ 2 ] );
    }

    template <typename Type>
    Vec3<Type> operator*( const Vec3<Type>& v, const Type& t )
    {
        return t * v;
    }

    template <typename Type>
    Vec3<Type> operator/( const Vec3<Type>& v, const Type& t )
    {
        return Vec3<Type> { v[ 0 ] / t, v[ 1 ] / t, v[ 2 ] / t };
    }

    template <typename Type>
    Type Dot( const Vec3<Type>& u, const Vec3<Type>& v )
    {
        return u.e[ 0 ] * v.e[ 0 ] + u.e[ 1 ] * v.e[ 1 ] + u.e[ 2 ] * v.e[ 2 ];
    }

    template <typename Type>
    Vec3<Type> Cross( const Vec3<Type>& u, const Vec3<Type>& v )
    {
        return Vec3<Type>( u.e[ 1 ] * v.e[ 2 ] - u.e[ 2 ] * v.e[ 1 ], u.e[ 2 ] * v.e[ 0 ] - u.e[ 0 ] * v.e[ 2 ], u.e[ 0 ] * v.e[ 1 ] - u.e[ 1 ] * v.e[ 0 ] );
    }

    template <typename Type>
    inline Vec3<Type> Reflect( const Vec3<Type>& vec, const Vec3<Type>& normal )
    {
        return vec - 2.0 * Dot( vec, normal ) * normal;
    }


    template <typename Type>
    inline Vec3<Type> Rotate( const Vec3<Type>& vec, const Vec3<Type>& normalizedRotationAxis, Type angleDeg )
    {
        Type cosTheta = std::cos( DegreesToRadians( angleDeg ) );
        Type sinTheta = std::sin( DegreesToRadians( angleDeg ) );

        return vec * cosTheta + Cross( normalizedRotationAxis, vec ) * sinTheta + normalizedRotationAxis * Dot( normalizedRotationAxis, vec ) * ( 1.0 - cosTheta );
    }

    template <typename Type>
    inline Vec3<Type> RotateAround( const Vec3<Type>& rotationPoint, Vec3<Type> vec, const Vec3<Type>& normalizedRotationAxis, Type angleDeg )
    {
        Type cosTheta       = std::cos( DegreesToRadians( angleDeg ) );
        Type sinTheta       = std::sin( DegreesToRadians( angleDeg ) );

        vec                -= rotationPoint;
        Vec3<Type> rotated  = vec * cosTheta + Cross( normalizedRotationAxis, vec ) * sinTheta + normalizedRotationAxis * Dot( normalizedRotationAxis, vec ) * ( 1.0 - cosTheta );

        return rotated     += rotationPoint;
    }


    template <typename T>
    using Point3  = Vec3<T>;


    using Vec3D   = Vec3<double>;
    using Point3D = Point3<double>;
    extern template class Vec3<double>;

    extern template Vec3D  operator+( const Vec3D& u, const Vec3D& v );
    extern template Vec3D  operator-( const Vec3D& u, const Vec3D& v );
    extern template Vec3D  operator*( const Vec3D& u, const Vec3D& v );
    extern template Vec3D  operator*( const double& t, const Vec3D& v );
    extern template Vec3D  operator*( const Vec3D& v, const double& t );
    extern template Vec3D  operator/( const Vec3D& v, const double& t );
    extern template double Dot( const Vec3D& u, const Vec3D& v );
    extern template Vec3D  Cross( const Vec3D& u, const Vec3D& v );


    using Vec3F   = Vec3<float>;
    using Point3F = Point3<float>;
    extern template class Vec3<float>;

    extern template Vec3F operator+( const Vec3F& u, const Vec3F& v );
    extern template Vec3F operator-( const Vec3F& u, const Vec3F& v );
    extern template Vec3F operator*( const Vec3F& u, const Vec3F& v );
    extern template Vec3F operator*( const float& t, const Vec3F& v );
    extern template Vec3F operator*( const Vec3F& v, const float& t );
    extern template Vec3F operator/( const Vec3F& v, const float& t );
    extern template float Dot( const Vec3F& u, const Vec3F& v );
    extern template Vec3F Cross( const Vec3F& u, const Vec3F& v );
} // namespace RayTracer
