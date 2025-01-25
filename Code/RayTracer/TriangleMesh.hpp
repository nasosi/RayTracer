#pragma once
#include "Algebra.hpp"
#include "Common.hpp"
#include "Interval.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"

#include <optional>
#include <vector>

namespace RayTracer
{


    class TriangleMesh
    {
        private:


            int  Partition( std::vector< Triangle >& arr, Point3 origin, int low, int high );
            void QuickSort( const Point3 origin, int low, int high );

            void InsertionSort( const Point3& origin, int n );


        public:

            std::vector< Triangle > triangleList;

            TriangleMesh( );

            bool                                    LoadObj( const char* fileName );

            void                                    InitialSort( const Point3& origin );

            void                                    Sort( const Point3& origin );

            std::optional< Vec3 >                   Intersect( const RayType& ray ) const;

            std::vector< Triangle >::const_iterator begin( ) const;
            std::vector< Triangle >::iterator       begin( );

            std::vector< Triangle >::const_iterator end( ) const;
            std::vector< Triangle >::iterator       end( );
    };

} // namespace RayTracer