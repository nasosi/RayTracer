#include "Material.hpp"
#include "Hittable.hpp"

namespace RayTracer
{

    bool Material::Scatter( const RayType& incomingRay, const HitRecord& hitRecord, RgbColor& attenuation, RayType& scatteredRay ) const
    {
        auto albedo    = RgbColor { 0.9, 0.9, 0.9 };

        Vec3 reflected = Reflect( incomingRay.GetDirection( ), hitRecord.surfaceNormal );
        scatteredRay   = RayType( hitRecord.point, reflected );
        attenuation    = albedo;

        return true;
    }

    Lambertian::Lambertian( const RgbColor& albedo ) : albedo( albedo )
    {
    }

    bool Lambertian::Scatter( const RayType& incomingRay, const HitRecord& hitRecord, RgbColor& attenuation, RayType& scatteredRay ) const
    {
        auto scatterDirection = hitRecord.surfaceNormal + CreateRandomNormalizedVector< RealType >( );

        // auto scatter_direction = random_on_hemisphere(rec.normal);

        // Catch degenerate scatter direction
        if ( NearZero( scatterDirection ) )
        {
            scatterDirection = hitRecord.surfaceNormal;
        }

        scatteredRay = RayType( hitRecord.point, scatterDirection );
        attenuation  = albedo; // Should we call attenuation albedo?
        // *dot(scatter_direction / scatter_direction.length(), rec.normal / rec.normal.length()); // Nasos: shouldn't abledo multiplied by cosine (through N.L as I am doing here?)
        return true;
    }


    Metal::Metal( const RgbColor& albedo ) : albedo( albedo )
    {
    }

    bool Metal::Scatter( const RayType& incomingRay, const HitRecord& hitRecord, RgbColor& attenuation, RayType& scatteredRay ) const
    {
        Vec3 reflected = Reflect( incomingRay.GetDirection( ), hitRecord.surfaceNormal );
        scatteredRay   = RayType( hitRecord.point, reflected );
        attenuation    = albedo;

        return true;
    }


} // namespace RayTracer