#pragma once


#include <algorithm>
#include <cstddef>
#include <memory>

namespace RayTracer
{

    using SizeType = std::size_t;

    constexpr double pi = 3.1415926535897932385;

    template <typename T>
    using SharedPointer = std::shared_ptr<T>;


    template <class FloatingType>
    uint8_t FloatingToByte( const FloatingType& v )
    {
        return uint8_t( std::max( 0, std::min( 255, int( floor( v * FloatingType( 256.0 ) ) ) ) ) );
    }

    inline double RandomDouble( )
    {
        return std::rand( ) / ( RAND_MAX + 1.0 );
    }

    inline double RandomDouble( double min, double max )
    {
        return min + ( max - min ) * RandomDouble( );
    }

    inline double DegreesToRadians( double deg )
    {
        return deg * pi / 180.0;
    }


} // namespace RayTracer


extern template uint8_t RayTracer::FloatingToByte<float>( const float& );
extern template uint8_t RayTracer::FloatingToByte<double>( const double& );