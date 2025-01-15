#include "Common.hpp"


namespace RayTracer
{

    template uint8_t FloatingToByte<float>( const float& );
    template uint8_t FloatingToByte<double>( const double& );

} // namespace RayTracer