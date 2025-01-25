#include <iostream>

#include "Camera.hpp"
#include "Image.hpp"
#include "Material.hpp"

using namespace RayTracer;

HittableList CreateWorld( )
{
    auto groundMaterial       = Lambertian( RgbColor { 0.8f, 0.8f, 0.0f } );
    auto centerSphereMaterial = Lambertian( RgbColor { 0.1f, 0.2f, 0.5f } );
    auto leftSphereMaterial   = Metal( RgbColor { 0.8f, 0.8f, 0.8f } );
    auto rightSphereMaterial  = Metal( RgbColor { 0.8f, 0.6f, 0.2f } );

    //
    HittableList world;
    world.objects.push_back( Sphere( Point3{ 0.0, -100.5, -1.0 }, 100.0, groundMaterial ) );
    world.objects.push_back( Sphere( Point3{ 0.0, 0, -1.2 }, 0.5, centerSphereMaterial ) );
    world.objects.push_back( Sphere( Point3 { -1.0, 0.0, -1.0 }, 0.5, leftSphereMaterial ) );
    world.objects.push_back( Sphere( Point3{ 1.0, 0.0, -1.0 }, 0.5, rightSphereMaterial ) );

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

    TriangleMesh       triangleMesh;
    //
    Camera camera( cameraFocalLength, cameraVerticalFieldOfViewDeg );
    camera.Render( world, triangleMesh, renderBuffer, maxBounces, samplesPerPixel );

    WritePPM( renderBuffer, "image.ppm" );
}