#include "Aabb.hpp"

namespace RayTracer
{

    bool BoundingBox::Contains( const Point3& p ) const
    {
        return (                                                  //
            lowPoint.x( ) <= p.x( ) && highPoint.x( ) > p.x( ) && //
            lowPoint.y( ) <= p.y( ) && highPoint.y( ) > p.y( ) && //
            lowPoint.z( ) <= p.z( ) && highPoint.z( ) > p.z( )    //
        );
    }

    bool BoundingBox::Contains( const Triangle& t ) const
    {
        bool contains = true;

        t.Loop_Constexpr(
            [ & ]( auto i )
            {
                contains &= Contains( t[ i ] );
            } );

        return contains;
    }

} // namespace RayTracer