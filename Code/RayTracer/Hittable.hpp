#pragma once

#include "Common.hpp"
#include "Interval.hpp"
#include "Material.hpp"
#include "Ray.hpp"

#include <vector>


namespace RayTracer
{

    struct HitRecord
    {
            Point3   point;
            Vec3     surfaceNormal;
            double   t;
            bool     frontFace;
            Material material;

            void     SetSurfaceNormal( const RayType& ray, const Vec3& surfaceOutwardNormal )
            {
                this->frontFace     = Dot( ray.GetDirection( ), surfaceOutwardNormal );
                this->surfaceNormal = this->frontFace ? surfaceOutwardNormal : -surfaceOutwardNormal;
            }
    };

    class Hittable
    {

        public:

            virtual ~Hittable( ) = default;

            //
            virtual bool Hit( const RayType& ray, const IntervalD& rayParameterInterval, HitRecord& hitRecord ) const
            {
                return false;
            };
    };


    class Sphere : public Hittable
    {
        private:

            Point3   center;
            RealType radius;
            Material material;

        public:

            Sphere( const Point3& center, double radius, Material material );

            bool Hit( const RayType& ray, const IntervalD& rayParameterInterval, HitRecord& hitRecord ) const override;
    };

    class HittableList : public Hittable
    {
        public:

            std::vector< Sphere > objects;

            //

            bool Hit( const RayType& ray, const IntervalD& rayParameterInterval, HitRecord& hitRecord ) const override;
    };

} // namespace RayTracer
