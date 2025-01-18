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
            double  verticalFieldOfViewInDegrees;

            Point3d center;
            Point3d lookAt;
            Vec3d   upVector;
            Point3d topLeftPixelLocation;

            Vec3d   pixelDeltaU;
            Vec3d   pixelDeltaV;

            void    CalculateViewportParameters( double windowWidth, double windowHeight );

        public:

            Camera( const double& focalLength, const double& verticalFieldOfViewInDegrees );

            RayD           CreateRandomRayAt( const SizeType& i, const SizeType& j );

            void           Render( const Hittable& world, RgbaImageView8& renderBuffer, SizeType maxBounces = 10, SizeType samplesPerPixel = 10 );

            RgbD           RayColor( const RayD& ray, SizeType maxBounces, const Hittable& world ) const;

            const Point3d& GetLookAt( ) const
            {
                return lookAt;
            }

            void SetLookAt( const Point3d& p );

            void Rotate( Vec<double, 2> rotationAnglesDeg );

            void Pan( Vec<double, 2> panVector );
    };


} // namespace RayTracer