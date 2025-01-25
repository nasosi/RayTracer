#pragma once

#include "Color.hpp"
//#include "Hittable.hpp"
#include "Ray.hpp"

namespace RayTracer
{

    class HitRecord;

    class Material
    {
        public:


            virtual ~Material( ) = default;

            virtual bool Scatter( const RayType& incomingRay, const HitRecord& hitRecord, RgbColor& attenuation, RayType& scatteredRay ) const;
    };


    class Lambertian : public Material
    {
        private:

            RgbColor albedo;


        public:

            Lambertian( const RgbColor& albedo );

            bool Scatter( const RayType& incomingRay, const HitRecord& hitRecord, RgbColor& attenuation, RayType& scatteredRay ) const override;
    };


    class Metal : public Material
    {
        public:

            Metal( const RgbColor& albedo );

            bool Scatter( const RayType& incomingRay, const HitRecord& hitRecord, RgbColor& attenuation, RayType& scatteredRay ) const override;

        private:

            RgbColor albedo;
    };

} // namespace RayTracer