#include "TriangleMesh.hpp"

#include "OBJ_Loader.h"

namespace RayTracer
{
    //

    int TriangleMesh::Partition( std::vector< Triangle >& arr, Point3 origin, int low, int high )
    {
        Triangle pivot         = arr[ high ];
        int      i             = low - 1;
        auto     pivotInterval = pivot.GetDistSquareIntervalFrom( origin );


        for ( int j = low; j <= high - 1; j++ )
        {
            auto pointJInterval = arr[ j ].GetDistSquareIntervalFrom( origin );

            if ( pointJInterval.GetFrom( ) < pivotInterval.GetFrom( ) )
            {
                i++;
                std::swap( arr[ i ], arr[ j ] );
            }
        }

        //  std::cout << low << " " << high << std::endl;
        // std::cout << arr[ i + 1 ] << " | " << arr[high] << std::endl;

        std::swap( arr[ i + 1 ], arr[ high ] );

        return i + 1;
    }
    inline void TriangleMesh::QuickSort( const Point3 origin, int low, int high )
    {
        if ( low < high )
        {
            int pi = Partition( triangleList, origin, low, high );

            QuickSort( origin, low, pi - 1 );
            QuickSort( origin, pi + 1, high );
        }
    }

    void TriangleMesh::InsertionSort( const Point3& origin, int n )
    {
        int swaps = 0;

        for ( int i = 1; i < n; ++i )
        {
            Triangle triangleI      = triangleList[ i ];
            auto     pointIInterval = triangleI.GetDistSquareIntervalFrom( origin );
            int      j              = i - 1;

            while ( j >= 0 && triangleList[ j ].GetDistSquareIntervalFrom( origin ).GetFrom( ) > pointIInterval.GetFrom( ) )
            {
                triangleList[ j + 1 ] = triangleList[ j ];
                j                     = j - 1;
                swaps++;
            }
            triangleList[ j + 1 ] = triangleI;
        }

       // std::cout << "swaps: " << swaps << std::endl;
    }

    std::optional< Vec3 > TriangleMesh::Intersect( const RayType& ray ) const
    {
        std::size_t count = 0;

        for ( const auto& triangle : triangleList )
        {
            auto intersectionPoint = triangle.Intersect( ray );
            count++;

            if ( intersectionPoint.has_value( ) )
            {
                std::cout << count << std::endl;
                return intersectionPoint;
            }
        }

        return { };
    }

    std::vector< Triangle >::const_iterator TriangleMesh::begin( ) const
    {
        return triangleList.begin( );
    }

    std::vector< Triangle >::iterator TriangleMesh::begin( )
    {
        return triangleList.begin( );
    }

    std::vector< Triangle >::const_iterator TriangleMesh::end( ) const
    {
        return triangleList.end( );
    }

    std::vector< Triangle >::iterator TriangleMesh::end( )
    {
        return triangleList.end( );
    }


    TriangleMesh::TriangleMesh( )
    {
    }

    bool TriangleMesh::LoadObj( const char* fileName )
    {
        using namespace objl;
        using std::cerr;
        using std::cout;
        using std::endl;

        bool error = false;

        cout << "Loading " << fileName << "..." << endl;

        Loader loader;
        loader.LoadFile( fileName );

        cout << "Mesh count: " << loader.LoadedMeshes.size( ) << endl;

        for ( auto i = 0; i != loader.LoadedMeshes.size( ); i++ )
        {

            const auto& mesh = loader.LoadedMeshes[ i ];


            // cout << "Adding : " << mesh.MeshName << mesh.Indices.size( );

            if ( mesh.Indices.size( ) % 3 != 0 )
            {
                cerr << "Error for " << mesh.MeshName << ": Indices must be a multiple of 3.";

                cout << endl;

                error = true;

                continue;
            }

            // cout << endl;

            for ( auto a = 0; a < mesh.Indices.size( ); a += 3 )
            {
                auto i0 = mesh.Indices[ a ];
                auto i1 = mesh.Indices[ a + 1 ];
                auto i2 = mesh.Indices[ a + 2 ];

                triangleList.emplace_back(                                                                                      //
                    Triangle { mesh.Vertices[ i0 ].Position.X, mesh.Vertices[ i0 ].Position.Y, mesh.Vertices[ i0 ].Position.Z,  //
                               mesh.Vertices[ i1 ].Position.X, mesh.Vertices[ i1 ].Position.Y, mesh.Vertices[ i1 ].Position.Z,  //
                               mesh.Vertices[ i2 ].Position.X, mesh.Vertices[ i2 ].Position.Y, mesh.Vertices[ i2 ].Position.Z } //
                );
            }
        }

        cout << "Triangle count: " << triangleList.size( ) << endl;

        return error;
    }

    void TriangleMesh::InitialSort( const Point3& origin )
    {
        QuickSort( origin, 0, triangleList.size( ) - 1 );
    }

    void TriangleMesh::Sort( const Point3& origin )
    {
        // QuickSort( origin, 0, triangleList.size( ) - 1 );

        InsertionSort( origin, triangleList.size( ) );
    }

    std::optional< Vec3 > Triangle::Intersect( const RayType& ray ) const
    {
        constexpr float eps    = std::numeric_limits< float >::epsilon( );

        Vec3            e1     = b( ) - a( );
        Vec3            e2     = c( ) - a( );
        Vec3            dirXe2 = Cross( ray.GetDirection( ), e2 );
        float           det    = Dot( e1, dirXe2 );

        if ( det > -eps && det < eps )
        { // Ray is parallel to triangle
            return { };
        }

        float invDet = 1.0 / det;
        Vec3  s      = ray.GetOrigin( ) - a( );
        float u      = invDet * Dot( s, dirXe2 );

        if ( ( u < 0 && abs( u ) > eps ) || ( u > 1 && abs( u - 1 ) > eps ) )
        {
            return { };
        }

        Vec3  sXe1 = Cross( s, e1 );
        float v    = invDet * Dot( ray.GetDirection( ), sXe1 );

        if ( ( v < 0 && abs( v ) > eps ) || ( u + v > 1 && abs( u + v - 1 ) > eps ) )
        {
            return { };
        }

        // At this stage we can compute t to find out where the intersection point is on the line.
        float t = invDet * Dot( e2, sXe1 );

        if ( t > eps ) // ray intersection
        {
            return Vec3 { ray.GetPointAt( t ) };
        }
        else
        {
            return { };
        }
    }

} // namespace RayTracer
