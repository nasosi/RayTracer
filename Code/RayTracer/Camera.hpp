#pragma once

#include "Algebra.hpp"
#include "Hittable.hpp"
#include "Image.hpp"
#include "Ray.hpp"
#include "TriangleMesh.hpp"


#include <iostream>
#include <limits>
#include <memory>

namespace RayTracer
{

    class Camera
    {
        private:

            RealType focalLength;
            RealType verticalFieldOfViewInDegrees;

            Point3   center;
            Point3   lookAt;
            Vec3     upVector;
            Point3   topLeftPixelLocation;

            Vec3     pixelDeltaU;
            Vec3     pixelDeltaV;

            void     CalculateViewportParameters( double windowWidth, double windowHeight );

        public:

            Camera( const double& focalLength, const double& verticalFieldOfViewInDegrees );

            RayType              CreateRayAt( const SizeType& i, const SizeType& j );
            RayType              CreateRandomRayAt( const SizeType& i, const SizeType& j );

            void                 Render( const Hittable& world, const TriangleMesh& triangleMesh, RgbaImageView8& renderBuffer, SizeType maxBounces = 10, SizeType samplesPerPixel = 10 );

            RgbColor             RayColor( const RayType& ray, SizeType maxBounces, const Hittable& world ) const;

            inline const Point3& GetLookAt( ) const
            {
                return lookAt;
            }

            inline const Point3& GetCenter( ) const
            {
                return center;
            }


            void SetLookAt( const Point3& p );

            void Rotate( Vec< RealType, 2 > rotationAnglesDeg );

            void Pan( Vec< RealType, 2 > panVector );
    };


} // namespace RayTracer