#include "Camera.hpp"
#include "Material.hpp"


namespace RayTracer
{
    Camera::Camera( const double& focalLength, const double& verticalFieldOfViewInDegrees ) :
        focalLength( focalLength ),
        verticalFieldOfViewInDegrees( verticalFieldOfViewInDegrees ),
        center( 0.0, 0.0, 0.0 ),
        lookAt( 0.2, 0.0, -1.0 ),
        upVector( 0.0, 1.0, 0.0 )
    {
    }

    void Camera::CalculateViewportParameters( double windowWidth, double windowHeight )
    {
        double aspectRatio    = double( windowWidth ) / windowHeight;
        double theta          = DegreesToRadians( verticalFieldOfViewInDegrees );
        double h              = std::tan( theta / 2 );
        double viewportHeight = 2.0 * h * focalLength;
        double viewportWidth  = viewportHeight * aspectRatio;

        Vec3D  w              = ( center - lookAt ).GetNormalized( );
        Vec3D  u              = Cross( upVector, w ).GetNormalized( );
        Vec3D  v              = Cross( w, u );

        Vec3D  viewportU      = viewportWidth * u;
        Vec3D  viewportV      = -(viewportHeight)*v;

        pixelDeltaU           = viewportU / double( windowWidth );
        pixelDeltaV           = viewportV / double( windowHeight );

        Vec3D viewportTopLeft = center - ( focalLength * w ) - viewportU / 2.0 - viewportV / 2.0;

        topLeftPixelLocation  = viewportTopLeft + ( pixelDeltaU + pixelDeltaV ) / 2.0;
    }

    RayD Camera::CreateRandomRayAt( const SizeType& i, const SizeType& j )
    {
        double  xOffset                = RandomDouble( ) - 0.5;
        double  yOffset                = RandomDouble( ) - 0.5;

        Point3D pertrubedPixelLocation = topLeftPixelLocation + ( ( i + xOffset ) * pixelDeltaU ) + ( ( j + yOffset ) * pixelDeltaV );
        Vec3D   rayDirection           = pertrubedPixelLocation - center;

        return RayD( center, rayDirection );
    }

    void Camera::Render( const Hittable& world, RgbaImageView8& renderBuffer, SizeType maxBounces, SizeType samplesPerPixel )
    {

        CalculateViewportParameters( renderBuffer.GetWidth( ), renderBuffer.GetHeight( ) );

        double summationDivisor = double( samplesPerPixel );

#pragma omp parallel for
        for ( int j = 0; j < renderBuffer.GetHeight( ); j++ )
        {
            auto imageRow = renderBuffer.GetRowSpan( j );

            for ( int i = 0; i < renderBuffer.GetWidth( ); i++ )
            {
                RgbD pixelColor( 0, 0, 0 );

                for ( int sample = 0; sample < samplesPerPixel; sample++ )
                {
                    RayD ray    = CreateRandomRayAt( i, j );
                    pixelColor += RayColor( ray, maxBounces, world );
                }

                imageRow[ i ] = ConvertToRgba8( LinearToGamma( pixelColor / summationDivisor ) );
            }
        }
    }

    RgbD Camera::RayColor( const RayD& ray, SizeType maxBounces, const Hittable& world ) const
    {
        if ( maxBounces == 0 )
        {
            return RgbD( 0, 0, 0 );
        }

        HitRecord hitRecord;

        if ( world.Hit( ray, IntervalD( 0.001, std::numeric_limits<double>::infinity( ) ), hitRecord ) )
        {
            RayD scatteredRay;
            RgbD attenuation;

            if ( hitRecord.material->Scatter( ray, hitRecord, attenuation, scatteredRay ) )
            {
                return attenuation * RayColor( scatteredRay, maxBounces - 1, world );
            }
            return RgbD( 0, 0, 0 );
        }

        auto a = 0.5 * ( ray.GetDirection( ).GetNormalized( ).y( ) + 1.0 );

        return ( 1.0 - a ) * RgbD( 1.0, 1.0, 1.0 ) + a * RgbD( 0.5, 0.7, 1.0 );
    }

    void Camera::SetLookAt( const Point3D& p )
    {
        lookAt = p;
    }

    void Camera::Rotate( Vec2<double> rotationAnglesDeg )
    {
        lookAt      = RotateAround( center, lookAt, Vec3D { 0.0, 1.0, 0.0 }, rotationAnglesDeg.x( ) );

        Vec3D fwd   = ( center - lookAt ).GetNormalized( );
        Vec3D right = Cross( upVector, fwd ).GetNormalized( );
        lookAt      = RotateAround( center, lookAt, right, rotationAnglesDeg.y( ) );
    }

    void Camera::Pan( Vec2<double> panVector )
    {
        Vec3D fwd   = ( center - lookAt ).GetNormalized( );
        center      = center + fwd * panVector.y( );
        lookAt      = lookAt + fwd * panVector.y( );

        Vec3D right = Cross( upVector, fwd ).GetNormalized( );
        center      = center + right * panVector.x( );
        lookAt      = lookAt + right * panVector.x( );
    }

} // namespace RayTracer