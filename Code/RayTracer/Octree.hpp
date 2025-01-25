#pragma once

#include "Aabb.hpp"
#include "TriangleMesh.hpp"


namespace RayTracer
{

    class Octree
    {
        private:

            SizeType maxLevels = 6;

        public:


            struct Node
            {
                    BoundingBox aabb;
                    SizeType    level         = 0;
                    SizeType    nodeListStart = 0;
                    SizeType    meshStart     = 0;
                    SizeType    meshFinish    = 0;

                    void        SubDivide( Octree& octree );
                    SizeType    Include( Octree& octree, SizeType triangleBegin, SizeType triangleEnd, SizeType maxLevels );
            };


            std::vector< Node > nodeList;
            TriangleMesh        mesh;

            Octree( const TriangleMesh& mesh );
    };

} // namespace RayTracer