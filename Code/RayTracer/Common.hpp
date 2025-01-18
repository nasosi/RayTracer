#pragma once


#include <algorithm>
#include <cstddef>
#include <memory>

namespace RayTracer
{
    using SizeType        = std::size_t;
    using RealType        = double;

    constexpr RealType pi = 3.1415926535897932385;

    template <typename T>
    using SharedPointer = std::shared_ptr<T>;


    template <class FloatingType>
    inline uint8_t FloatingToByte( const FloatingType& v )
    {
        return uint8_t( std::max( 0, std::min( 255, int( floor( v * FloatingType( 256.0 ) ) ) ) ) );
    }

    template <typename T>
    inline T RandomReal( )
    {
        return T( std::rand() ) / ( RAND_MAX + 1.0 );
    }

    template <typename T>
    inline T RandomReal( T min, T max )
    {
        return min + ( max - min ) * RandomReal<T>( );
    }

    template <typename T>
    inline T DegreesToRadians( T deg )
    {
        return deg * pi / 180.0;
    }


} // namespace RayTracer


extern template uint8_t RayTracer::FloatingToByte<float>( const float& );
extern template uint8_t RayTracer::FloatingToByte<double>( const double& );