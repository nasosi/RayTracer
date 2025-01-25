#include "Hittable.hpp"

namespace RayTracer
{

    Sphere::Sphere( const Point3& center, double radius, Material material ) : center( center ), radius( std::fmax( 0, radius ) ), material( material )
    {
    }

    bool Sphere::Hit( const RayType& ray, const IntervalD& rayParameterInterval, HitRecord& hitRecord ) const
    {

        Vec3 oc           = this->center - ray.GetOrigin( );
        auto  a            = ray.GetDirection( ).MagSquare( );
        auto  h            = Dot( ray.GetDirection( ), oc );
        auto  c            = oc.MagSquare( ) - radius * radius;

        auto  discriminant = h * h - a * c;
        if ( discriminant < 0 )
        {
            return false;
        }

        auto sqrtd = std::sqrt( discriminant );

        // Find the nearest root that lies in the acceptable range.
        auto root = ( h - sqrtd ) / a;
        if ( !rayParameterInterval.Surrounds( root ) )
        {
            root = ( h + sqrtd ) / a;
            if ( !rayParameterInterval.Surrounds( root ) )
            {
                return false;
            }
        }

        hitRecord.t                = root;
        hitRecord.point            = ray.GetPointAt( hitRecord.t );
        Vec3 surfaceOutwardNormal = ( hitRecord.point - this->center ) / radius;
        hitRecord.SetSurfaceNormal( ray, surfaceOutwardNormal );
        hitRecord.material = material;

        return true;
    }

    bool HittableList::Hit( const RayType& ray, const IntervalD& rayParameterInterval, HitRecord& hitRecord ) const
    {
        HitRecord tempHitRecord;
        bool      hitSomething = false;
        auto      closest      = rayParameterInterval.GetTo( );
        ;

        for ( const auto& object : objects )
        {
            if ( object.Hit( ray, Interval( rayParameterInterval.GetFrom( ), closest ), tempHitRecord ) )
            {
                hitSomething = true;
                closest      = tempHitRecord.t;
                hitRecord    = tempHitRecord;
            }
        }

        return hitSomething;
    }

} // namespace RayTracer
