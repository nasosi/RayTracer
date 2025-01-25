#include "Algebra.hpp"
#include "Gui.hpp"
#include "TriangleMesh.hpp"
#include "Octree.hpp"

#include "Eumorphic.hpp"


extern "C"
{
    RayTracer::Application* CreateApplication( )
    {
        using namespace RayTracer;

        Eumorphic::collection< //
            double,            //
            int,               //
            std::string >
            collection;

        collection.AppendArrayElement( 1.22 );
        collection.AppendArrayElement( int( 2 ) );
        collection.AppendArrayElement( std::string( "Hello" ) );


        collection.Loop(
            []( const auto& elem )
            {
                std::cout << elem << std::endl;
            } );


        TriangleMesh mesh;
        mesh.LoadObj( "TwoCubes.obj" );

        std::cout << "Triangles:\n";
        for (auto t : mesh.triangleList)
        {
            std::cout << t << std::endl;
        }
        std::cout << "\n";
       
        Octree octree( mesh );

        auto app = new Application;

        return app;

        app->LoadObj( "sponza.obj" );

        return app;
    }
}
