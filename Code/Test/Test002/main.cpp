#include <iostream>

#include "Camera.hpp"
#include "Image.hpp"
#include "Material.hpp"

using namespace RayTracer;

HittableList CreateWorld( )
{
    auto groundMaterial       = std::make_shared<Lambertian>( RgbD( 0.8, 0.8, 0.0 ) );
    auto centerSphereMaterial = std::make_shared<Lambertian>( RgbD( 0.1, 0.2, 0.5 ) );
    auto leftSphereMaterial   = std::make_shared<Metal>( RgbD( 0.8, 0.8, 0.8 ) );
    auto rightSphereMaterial  = std::make_shared<Metal>( RgbD( 0.8, 0.6, 0.2 ) );

    //
    HittableList world;
    world.objects.push_back( std::make_shared<Sphere>( Point3D( 0.0, -100.5, -1.0 ), 100.0, groundMaterial ) );
    world.objects.push_back( std::make_shared<Sphere>( Point3D( 0.0, 0, -1.2 ), 0.5, centerSphereMaterial ) );
    world.objects.push_back( std::make_shared<Sphere>( Point3D( -1.0, 0.0, -1.0 ), 0.5, leftSphereMaterial ) );
    world.objects.push_back( std::make_shared<Sphere>( Point3D( 1.0, 0.0, -1.0 ), 0.5, rightSphereMaterial ) );

    return world;
}

int main( )
{
    std::cout << "Test002" << std::endl;

    double             cameraFocalLength            = 1.0;
    double             cameraVerticalFieldOfViewDeg = 90.0;
    SizeType           maxBounces                   = 10;
    SizeType           samplesPerPixel              = 500;

    std::vector<Rgba8> buffer( 640 * 480 );

    RgbaImageView8     renderBuffer = RgbaImageView8( reinterpret_cast<uint8_t*>( buffer.data( ) ), 640, 480, 640 * sizeof( Rgba8 ) );

    HittableList       world        = CreateWorld( );

    //
    Camera camera( cameraFocalLength, cameraVerticalFieldOfViewDeg );
    camera.Render( world, renderBuffer, maxBounces, samplesPerPixel );

    WritePPM( renderBuffer, "image.ppm" );
}