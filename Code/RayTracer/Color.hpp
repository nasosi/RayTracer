#pragma once


#include "Common.hpp"
#include <cstdint>


namespace RayTracer
{

    template <class Type>
    class Rgb
    {

        public:

            Type r = 0;
            Type g = 0;
            Type b = 0;

            Rgb& operator*=( Type t )
            {
                r *= t;
                g *= t;
                b *= t;

                return *this;
            }

            Rgb& operator+=( const Rgb& other )
            {
                this->r += other.r;
                this->g += other.g;
                this->b += other.b;

                return *this;
            }

            Rgb& operator/=( Type t )
            {
                r /= t;
                g /= t;
                b /= t;

                return *this;
            }
    };

    template <typename T>
    inline Rgb<T> operator*( T a, Rgb<T> c )
    {
        c *= a;

        return c;
    }


    template <typename T>
    inline Rgb<T> operator/( Rgb<T> c, T a )
    {
        c /= a;

        return c;
    }

    template <typename T>
    Rgb<T> operator*( const Rgb<T>& a, const Rgb<T>& b )
    {
        return Rgb<T>( a.r * b.r, a.g * b.g, a.b * b.b );
    }

    template <typename T>
    Rgb<T> operator+( Rgb<T> a, const Rgb<T>& b )
    {
        a += b;
        return a;
    }


    extern template class Rgb<uint8_t>;
    extern template class Rgb<float>;
    extern template class Rgb<double>;

    using Rgb8 = Rgb<uint8_t>;
    using RgbF = Rgb<float>;
    using RgbD = Rgb<double>;

    Rgb8  ConvertToRgb8( const RgbD& color );

    RgbD  LinearToGamma( const RgbD& color, double gamma = 2.2 );


    template <class Type>
    class Rgba
    {

        public:

            Type  r = 0;
            Type  g = 0;
            Type  b = 0;
            Type  a = 0;

            Rgba& operator*=( Type t )
            {
                r *= t;
                g *= t;
                b *= t;

                return *this;
            }

            Rgba& operator+=( const Rgba& other )
            {
                this->r += other.r;
                this->g += other.g;
                this->b += other.b;

                return *this;
            }

            Rgba& operator/=( Type t )
            {
                r /= t;
                g /= t;
                b /= t;

                return *this;
            }
    };

    template <typename T>
    inline Rgba<T> operator*( T a, Rgba<T> c )
    {
        c *= a;

        return c;
    }


    template <typename T>
    inline Rgba<T> operator/( Rgba<T> c, T a )
    {
        c /= a;

        return c;
    }

    template <typename T>
    Rgba<T> operator*( const Rgba<T>& a, const Rgba<T>& b )
    {
        return Rgb<T>( a.r * b.r, a.g * b.g, a.b * b.b );
    }

    template <typename T>
    Rgba<T> operator+( Rgba<T> a, const Rgba<T>& b )
    {
        a += b;
        return a;
    }


    extern template class Rgba<uint8_t>;
    extern template class Rgba<float>;
    extern template class Rgba<double>;

    using Rgba8 = Rgba<uint8_t>;
    using RgbaF = Rgba<float>;
    using RgbaD = Rgba<double>;

    Rgba8 ConvertToRgba8( const RgbD& color );

} // namespace RayTracer