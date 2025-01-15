#include "Material.hpp"

namespace RayTracer
{

    Lambertian::Lambertian( const RgbD& albedo ) : albedo( albedo )
    {
    }

    bool Lambertian::Scatter( const RayD& incomingRay, const HitRecord& hitRecord, RgbD& attenuation, RayD& scatteredRay ) const
    {
        auto scatterDirection = hitRecord.surfaceNormal + CreateRandomUnitVector<double>( );

        // auto scatter_direction = random_on_hemisphere(rec.normal);

        // Catch degenerate scatter direction
        if ( NearZero( scatterDirection ) )
        {
            scatterDirection = hitRecord.surfaceNormal;
        }

        scatteredRay = RayD( hitRecord.point, scatterDirection );
        attenuation  = albedo; // Todo: should we call attenuation albedo?
        // *dot(scatter_direction / scatter_direction.length(), rec.normal / rec.normal.length()); // Nasos: shouldn't abledo multiplied by cosine (through N.L as I am doing here?)
        return true;
    }


    Metal::Metal( const RgbD& albedo ) : albedo( albedo )
    {
    }

    bool Metal::Scatter( const RayD& incomingRay, const HitRecord& hitRecord, RgbD& attenuation, RayD& scatteredRay ) const
    {
        Vec3D reflected = Reflect( incomingRay.GetDirection( ), hitRecord.surfaceNormal );
        scatteredRay    = RayD( hitRecord.point, reflected );
        attenuation     = albedo;

        return true;
    }


} // namespace RayTracer