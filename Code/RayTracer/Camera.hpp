#pragma once

#include "Algebra.hpp"
#include "Hittable.hpp"
#include "Image.hpp"
#include "Ray.hpp"

#include <iostream>
#include <limits>
#include <memory>

namespace RayTracer
{

    class Camera
    {
        private:

            double  focalLength;
            double  verticalFieldOfViewInDegrees = 90;

            Point3D center;
            Point3D lookAt;
            Vec3D   upVector;
            Point3D topLeftPixelLocation;

            Vec3D   pixelDeltaU;
            Vec3D   pixelDeltaV;

            void    CalculateViewportParameters( double viewportWidth, double viewportHeight );

        public:

            Camera( const double& focalLength, const double& verticalFieldOfViewInDegrees );

            RayD           CreateRandomRayAt( const SizeType& i, const SizeType& j );

            void           Render( const Hittable& world, RgbaImageView8& renderBuffer, SizeType maxBounces = 10, SizeType samplesPerPixel = 10 );

            RgbD           RayColor( const RayD& ray, SizeType maxBounces, const Hittable& world ) const;

            const Point3D& GetLookAt( ) const
            {
                return lookAt;
            }

            void SetLookAt( const Point3D& p );

            void Rotate( Vec2<double> rotationAnglesDeg );

            void Pan( Vec2<double> panVector );
    };


} // namespace RayTracer