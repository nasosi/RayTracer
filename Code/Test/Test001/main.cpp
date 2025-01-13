#include <iostream>

#include "Image.hpp"

int main( )
{
    std::cout << "Test001" << std::endl;

    using namespace RayTracer;

    RgbImage8    image( 300, 200 );
    const double xStep = 1.0 / image.GetWidth( );
    const double yStep = 1.0 / image.GetHeight( );
    double       y     = 0;

    for ( SizeType row = 0; row < image.GetHeight( ); row++ )
    {
        double x       = 0;
        auto   rowSpan = image.GetRowSpan( row );

        for ( Rgb8& pixel8 : rowSpan )
        {
            pixel8  = ConvertToRgb8( RgbD { x * ( 1.0 - y ), ( 1.0 - x ) * ( 1.0 - y ), y * ( 1.0 - x ) } );
            x      += xStep;
        }
        y += yStep;
    }

    WritePPM( image, "image.ppm" );
}