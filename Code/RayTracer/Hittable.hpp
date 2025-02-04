#pragma once

#include "Common.hpp"
#include "Interval.hpp"
#include "Ray.hpp"

#include <vector>


namespace RayTracer
{
    class Material;

    struct HitRecord
    {
            Point3D                 point;
            Vec3D                   surfaceNormal;
            double                  t;
            bool                    frontFace;
            SharedPointer<Material> material;

            void                    SetSurfaceNormal( const RayD& ray, const Vec3D& surfaceOutwardNormal )
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
            virtual bool Hit( const RayD& ray, const IntervalD& rayParameterInterval, HitRecord& hitRecord ) const = 0;
    };

    class HittableList : public Hittable
    {
        public:

            std::vector<SharedPointer<Hittable>> objects;

            //

            bool Hit( const RayD& ray, const IntervalD& rayParameterInterval, HitRecord& hitRecord ) const override;
    };


    class Sphere : public Hittable
    {
        private:

            Point3D                 center;
            double                  radius;
            SharedPointer<Material> material;

        public:

            Sphere( const Point3D& center, double radius, SharedPointer<Material> material );

            bool Hit( const RayD& ray, const IntervalD& rayParameterInterval, HitRecord& hitRecord ) const override;
    };
} // namespace RayTracer
