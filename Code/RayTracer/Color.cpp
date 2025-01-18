#include "Color.hpp"

#include <cmath>

template class RayTracer::Rgb<uint8_t>;
template class RayTracer::Rgba<uint8_t>;

namespace RayTracer
{

    Rgb8 ConvertToRgb8( const RgbD& color )
    {
        return Rgb8 { FloatingToByte( color.r() ), FloatingToByte( color.g() ), FloatingToByte( color.b() ) };
    }

    Rgba8 ConvertToRgba8( const RgbD& color )
    {
        return Rgba8 { FloatingToByte( color.r( ) ), FloatingToByte( color.g( ) ), FloatingToByte( color.b( ) ), 255 };
    }

    RgbD LinearToGamma( const RgbD& color, double gamma )
    {
        return RgbD { std::pow( color.r( ), 1.0 / gamma ), std::pow( color.g( ), 1.0 / gamma ), std::pow( color.b( ), 1.0 / gamma ) };
    }

} // namespace RayTracer
