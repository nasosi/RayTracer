#include "Camera.hpp"
#include "Material.hpp"

#include "omp.h"

namespace RayTracer
{
    Camera::Camera( const double& focalLength, const double& verticalFieldOfViewInDegrees ) :
        focalLength( focalLength ),
        verticalFieldOfViewInDegrees( verticalFieldOfViewInDegrees ),
        center { 0.0, 0.0, 0.0 },
        lookAt { 0.2, 0.0, -1.0 },
        upVector { 0.0, 1.0, 0.0 }
    {
    }

    void Camera::CalculateViewportParameters( double windowWidth, double windowHeight )
    {
        RealType aspectRatio    = double( windowWidth ) / windowHeight;
        RealType theta          = DegreesToRadians( verticalFieldOfViewInDegrees );
        RealType h              = std::tan( theta / 2.0 );
        RealType viewportHeight = 2.0 * h * focalLength;
        RealType viewportWidth  = viewportHeight * aspectRatio;

        Vec3     w              = Normalize( center - lookAt );
        Vec3     u              = Normalize( Cross( upVector, w ) );
        Vec3     v              = Cross( w, u );

        Vec3     viewportU      = viewportWidth * u;
        Vec3     viewportV      = -(viewportHeight)*v;

        pixelDeltaU             = viewportU / RealType( windowWidth );
        pixelDeltaV             = viewportV / RealType( windowHeight );

        Point3 viewportTopLeft  = center - ( focalLength * w ) - viewportU / RealType( 2.0 ) - viewportV / RealType( 2.0 );

        topLeftPixelLocation    = viewportTopLeft + ( pixelDeltaU + pixelDeltaV ) / RealType( 2.0 );
    }

    RayType Camera::CreateRayAt( const SizeType& i, const SizeType& j )
    {
        Point3 pertrubedPixelLocation = topLeftPixelLocation + ( RealType( i ) * pixelDeltaU ) + ( RealType( j ) * pixelDeltaV );
        Vec3   rayDirection           = pertrubedPixelLocation - center;

        return RayType( center, rayDirection );
    }

    RayType Camera::CreateRandomRayAt( const SizeType& i, const SizeType& j )
    {
        RealType xOffset                = RandomReal< RealType >( ) - 0.5;
        RealType yOffset                = RandomReal< RealType >( ) - 0.5;

        Point3   pertrubedPixelLocation = topLeftPixelLocation + ( ( i + xOffset ) * pixelDeltaU ) + ( ( j + yOffset ) * pixelDeltaV );
        Vec3     rayDirection           = pertrubedPixelLocation - center;

        return RayType( center, rayDirection );
    }

    void Camera::Render( const Hittable& world, const TriangleMesh& triangleMesh, RgbaImageView8& renderBuffer, SizeType maxBounces, SizeType samplesPerPixel )
    {
        CalculateViewportParameters( renderBuffer.GetWidth( ), renderBuffer.GetHeight( ) );

        double summationDivisor = double( samplesPerPixel );

#pragma omp parallel
        {
#pragma omp for
            for ( int j = 0; j < renderBuffer.GetHeight( ); j++ )
            {
                auto imageRow = renderBuffer.GetRowSpan( j );

                for ( int i = 0; i < renderBuffer.GetWidth( ); i++ )
                {
                    FlatRgbColor pixelColor { 0, 0, 0, 0 };

                    while ( pixelColor.weight( ) < samplesPerPixel )
                    {
                        //RayType ray = CreateRandomRayAt( i, j );
                        RayType ray = CreateRayAt( i, j );

                        // triangleMesh.Intersect( ray );
                        pixelColor += RayColor( ray, maxBounces, world );
                    }

                    imageRow[ i ] = ConvertToRgba8( LinearToGamma( pixelColor.GetUnitized( ) ) );
                }

                /*             if (j % 100 == 0)
                             {
                                 std::cout << j << std::endl;
                             }*/
            }
        }
    }

    RgbColor Camera::RayColor( const RayType& ray, SizeType maxBounces, const Hittable& world ) const
    {
        if ( maxBounces == 0 )
        {
            return RgbColor { 0, 0, 0 };
        }

        HitRecord hitRecord;

        if ( world.Hit( ray, IntervalD( 0.001, std::numeric_limits< double >::infinity( ) ), hitRecord ) )
        {
            RayType  scatteredRay;
            RgbColor attenuation;

            if ( hitRecord.material.Scatter( ray, hitRecord, attenuation, scatteredRay ) )
            {
                return attenuation * RayColor( scatteredRay, maxBounces - 1, world );
            }
            return RgbColor { 0, 0, 0 };
        }

        auto a = 0.5 * ( Normalize( ray.GetDirection( ) ).y( ) + 1.0 );

        return ( ( ( 1.0 - a ) * FlatRgbColor { 1.0, 1.0, 1.0, 0.0 } ) + a * FlatRgbColor { 0.5, 0.7, 1.0, 1.0 } ).GetUnitized( );
    }

    void Camera::SetLookAt( const Point3& p )
    {
        lookAt = p;
    }

    void Camera::Rotate( Vec< RealType, 2 > rotationAnglesDeg )
    {
        lookAt     = RotatePointAround( center, lookAt, Vec3 { 0.0, 1.0, 0.0 }, rotationAnglesDeg.x( ) );

        Vec3 fwd   = Normalize( center - lookAt );
        Vec3 right = Normalize( Cross( upVector, fwd ) );
        lookAt     = RotatePointAround( center, lookAt, right, rotationAnglesDeg.y( ) );
    }

    void Camera::Pan( Vec< RealType, 2 > panVector )
    {
        Vec3 fwd   = Normalize( center - lookAt );
        center     = center + fwd * panVector.y( );
        lookAt     = lookAt + fwd * panVector.y( );

        Vec3 right = Normalize( Cross( upVector, fwd ) );
        center     = center + right * panVector.x( );
        lookAt     = lookAt + right * panVector.x( );
    }

} // namespace RayTracer