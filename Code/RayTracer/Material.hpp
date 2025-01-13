#pragma once

#include "Color.hpp"
#include "Hittable.hpp"
#include "Ray.hpp"

namespace RayTracer
{

    class Material
    {
        public:

            virtual ~Material( ) = default;

            virtual bool Scatter( const RayD& incomingRay, const HitRecord& rec, RgbD& attenuation, RayD& scatteredRay ) const
            {
                return false;
            }
    };


    class Lambertian : public Material
    {
        private:

            RgbD albedo;


        public:

            Lambertian( const RgbD& albedo );

            bool Scatter( const RayD& incomingRay, const HitRecord& hitRecord, RgbD& attenuation, RayD& scatteredRay ) const override;
    };


    class Metal : public Material
    {
        public:

            Metal( const RgbD& albedo );

            bool Scatter( const RayD& incomingRay, const HitRecord& hitRecord, RgbD& attenuation, RayD& scatteredRay ) const override;

        private:

            RgbD albedo;
    };

} // namespace RayTracer