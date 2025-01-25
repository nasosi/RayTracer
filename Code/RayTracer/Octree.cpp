#include "Octree.hpp"

#include <iostream>

namespace RayTracer
{


    Octree::Octree( const TriangleMesh& mesh ) : mesh( mesh )
    {
        constexpr RealType infinity  = std::numeric_limits< RealType >::max( );

        Point3             lowPoint  = { infinity, infinity, infinity };
        Point3             highPoint = { -infinity, -infinity, -infinity };

        for ( const auto& triangle : mesh )
        {
            triangle.Loop_Constexpr(
                [ & ]( auto i )
                {
                    Point3 point = triangle[ i ];

                    point.Loop_Constexpr(
                        [ & ]( auto i )
                        {
                            lowPoint[ i ]  = std::min( lowPoint[ i ], point[ i ] );
                            highPoint[ i ] = std::max( highPoint[ i ], point[ i ] );
                        } );
                } );
        }
        lowPoint.Loop_Constexpr(
            [ & ]( auto i )
            {
                auto dC         = 0.01 * ( highPoint[ i ] - lowPoint[ i ] );

                highPoint[ i ] += dC;
                lowPoint[ i ]  -= dC;
            } );

        nodeList.reserve( std::pow( 8, maxLevels - 1 ) );
        nodeList.emplace_back( Node { lowPoint, highPoint, 0, 0 } );
        nodeList[ 0 ].meshFinish = mesh.triangleList.size( ) - 1;

        nodeList[ 0 ].Include( *this, 0, mesh.triangleList.size( ) - 1, maxLevels );
    }

    void Octree::Node::SubDivide( Octree& octree )
    {
        Point3 middlePoint = aabb.lowPoint + ( aabb.highPoint - aabb.lowPoint ) / RealType( 2.0 );

        // clang-format off

        octree.nodeList.emplace_back( Node{ { { aabb.lowPoint.x( ), aabb.lowPoint.y( ), aabb.lowPoint.z( ) }, { middlePoint.   x( ), middlePoint.   y( ), middlePoint.   z( ) } }, level + 1, octree.nodeList.size() } );
        octree.nodeList.emplace_back( Node{ { { middlePoint.  x( ), aabb.lowPoint.y( ), aabb.lowPoint.z( ) }, { aabb.highPoint.x( ), middlePoint.   y( ), middlePoint.   z( ) } }, level + 1, octree.nodeList.size() } );
        octree.nodeList.emplace_back( Node{ { { aabb.lowPoint.x( ), middlePoint.  y( ), aabb.lowPoint.z( ) }, { middlePoint.   x( ), aabb.highPoint.y( ), middlePoint.   z( ) } }, level + 1, octree.nodeList.size() } );
        octree.nodeList.emplace_back( Node{ { { middlePoint.  x( ), middlePoint.  y( ), aabb.lowPoint.z( ) }, { aabb.highPoint.x( ), aabb.highPoint.y( ), middlePoint.   z( ) } }, level + 1, octree.nodeList.size() } );
        octree.nodeList.emplace_back( Node{ { { aabb.lowPoint.x( ), aabb.lowPoint.y( ), middlePoint.  z( ) }, { middlePoint.   x( ), middlePoint.   y( ), aabb.highPoint.z( ) } }, level + 1, octree.nodeList.size() } );
        octree.nodeList.emplace_back( Node{ { { middlePoint.  x( ), aabb.lowPoint.y( ), middlePoint.  z( ) }, { aabb.highPoint.x( ), middlePoint.   y( ), aabb.highPoint.z( ) } }, level + 1, octree.nodeList.size() } );
        octree.nodeList.emplace_back( Node{ { { aabb.lowPoint.x( ), middlePoint.  y( ), middlePoint.  z( ) }, { middlePoint.   x( ), aabb.highPoint.y( ), aabb.highPoint.z( ) } }, level + 1, octree.nodeList.size() } );
        octree.nodeList.emplace_back( Node{ { { middlePoint.  x( ), middlePoint.  y( ), middlePoint.  z( ) }, { aabb.highPoint.x( ), aabb.highPoint.y( ), aabb.highPoint.z( ) } }, level + 1, octree.nodeList.size() } );

        // clang-format on
    }

    SizeType Octree::Node::Include( Octree& octree, SizeType meshStart, SizeType meshFinish, SizeType maxLevels )
    {
        std::cout << "Level: " <<  this->level << std::endl;

        this->meshStart  = meshFinish;
        this->meshFinish = meshFinish;

        for ( int i = meshFinish - 1; i >= meshStart && i >= 0; i-- )
        {
            const auto& triangle = octree.mesh.triangleList[ i ];
            if ( aabb.Contains( triangle ) )
            {
                this->meshStart--;
                std::iter_swap( octree.mesh.triangleList.begin( ) + i, octree.mesh.triangleList.begin( ) + this->meshStart );
            }
        }

        if ( this->level != maxLevels )
        {
            SubDivide( octree );

            for ( auto a = this->nodeListStart + 1; a != 9; a++ )
            {
                std ::cout << " a: " << a ;
                meshFinish -= octree.nodeList[ a ].Include( octree, this->meshStart, this->meshFinish, maxLevels );
            }
        }


        return meshFinish - meshStart;
    }

} // namespace RayTracer