#include "Algebra.hpp"
#include "Gui.hpp"
#include "TriangleMesh.hpp"

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

        mesh.LoadObj( "sponza.obj" );


        return new Application;
    }
}
