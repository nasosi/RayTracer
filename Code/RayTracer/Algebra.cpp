#include "Algebra.hpp"


namespace RayTracer
{
    template class Vec3<double>;

    template Vec3D  operator+( const Vec3D& u, const Vec3D& v );
    template Vec3D  operator-( const Vec3D& u, const Vec3D& v );
    template Vec3D  operator*( const Vec3D& u, const Vec3D& v );
    template Vec3D  operator*( const double& t, const Vec3D& v );
    template Vec3D  operator*( const Vec3D& v, const double& t );
    template Vec3D  operator/( const Vec3D& v, const double& t );
    template double Dot( const Vec3D& u, const Vec3D& v );
    template Vec3D  Cross( const Vec3D& u, const Vec3D& v );


    template class Vec3<float>;

    template Vec3F operator+( const Vec3F& u, const Vec3F& v );
    template Vec3F operator-( const Vec3F& u, const Vec3F& v );
    template Vec3F operator*( const Vec3F& u, const Vec3F& v );
    template Vec3F operator*( const float& t, const Vec3F& v );
    template Vec3F operator*( const Vec3F& v, const float& t );
    template Vec3F operator/( const Vec3F& v, const float& t );
    template float Dot( const Vec3F& u, const Vec3F& v );
    template Vec3F Cross( const Vec3F& u, const Vec3F& v );

    namespace V
    {
        RAYTRACER_VECTOR_TYPE_INSTANTIATE( float, 2 )
        RAYTRACER_VECTOR_TYPE_INSTANTIATE( float, 3 )
        RAYTRACER_VECTOR_TYPE_INSTANTIATE( double, 2 )
        RAYTRACER_VECTOR_TYPE_INSTANTIATE( double, 3 )

        RAYTRACER_POINT_TYPE_INSTANTIATE( float, 2 )
        RAYTRACER_POINT_TYPE_INSTANTIATE( float, 3 )
        RAYTRACER_POINT_TYPE_INSTANTIATE( double, 2 )
        RAYTRACER_POINT_TYPE_INSTANTIATE( double, 3 )
    } // namespace V
} // namespace RayTracer