#pragma once

#include "Common.hpp"

#include <cmath>

namespace RayTracer
{
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
