#include "Gui.hpp"
#include "Camera.hpp"
#include "Material.hpp"

#define SDL_MAIN_USE_CALLBACKS 1 // use callbacks instead of main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


#include <cmath>

namespace RayTracer
{

    HittableList CreateDemoWorld( )
    {
        auto groundMaterial       = std::make_shared<Lambertian>( RgbD( 0.8, 0.8, 0.0 ) );
        auto centerSphereMaterial = std::make_shared<Lambertian>( RgbD( 0.1, 0.2, 0.5 ) );
        auto otherSphereMaterial  = std::make_shared<Lambertian>( RgbD( 0.5, 0.2, 0.1 ) );
        auto leftSphereMaterial   = std::make_shared<Metal>( RgbD( 0.8, 0.8, 0.8 ) );
        auto rightSphereMaterial  = std::make_shared<Metal>( RgbD( 0.8, 0.6, 0.2 ) );

        //
        HittableList world;
        world.objects.push_back( std::make_shared<Sphere>( Point3D( 0.0, -100.5, -1.0 ), 100.0, groundMaterial ) );
        world.objects.push_back( std::make_shared<Sphere>( Point3D( 0.0, 0, -1.2 ), 0.5, centerSphereMaterial ) );
        world.objects.push_back( std::make_shared<Sphere>( Point3D( 0.0, 0, -4.5 ), 0.3, otherSphereMaterial ) );

        world.objects.push_back( std::make_shared<Sphere>( Point3D( -1.0, 0.0, -1.0 ), 0.5, leftSphereMaterial ) );
        world.objects.push_back( std::make_shared<Sphere>( Point3D( 1.0, 0.0, -1.0 ), 0.5, rightSphereMaterial ) );

        return world;
    }

    class GuiManager
    {
        private:

            SDL_Window*      window         = nullptr;
            SDL_Renderer*    renderer       = nullptr;
            SDL_Surface*     renderSurface  = nullptr;
            SDL_Texture*     surfaceTexture = nullptr;

            ImageView<Rgba8> renderBuffer;

            int              windowWidth  = 0;
            int              windowHeight = 0;

            Application*     application;

        public:

            GuiManager( )
            {
                application = CreateApplication( );
            }

            ~GuiManager( )
            {
                if ( renderSurface != nullptr )
                {
                    SDL_DestroySurface( renderSurface );
                }

                if ( surfaceTexture != nullptr )
                {
                    SDL_DestroyTexture( surfaceTexture );
                }

                delete application;
            }

            SDL_AppResult InitSdl( void** appstate, int argc, char* argv[] )
            {
                application->InitGui( this->windowWidth, this->windowHeight );

                SDL_SetAppMetadata( "RayTracer GUI", "1.0", "https://github.com/nasosi" );

                if ( !SDL_Init( SDL_INIT_VIDEO ) )
                {
                    SDL_Log( "Couldn't initialize SDL: %s", SDL_GetError( ) );
                    return SDL_APP_FAILURE;
                }

                if ( !SDL_CreateWindowAndRenderer( "RayTracer", this->windowWidth, this->windowHeight, 0, &window, &renderer ) )
                {
                    SDL_Log( "Couldn't create window/renderer: %s", SDL_GetError( ) );
                    return SDL_APP_FAILURE;
                }

                if ( renderSurface != nullptr )
                {
                    SDL_DestroySurface( renderSurface );
                }

                this->renderSurface = SDL_CreateSurface( this->windowWidth, this->windowHeight, SDL_PIXELFORMAT_RGBA32 );
                this->renderBuffer  = ImageView<Rgba8>( static_cast<uint8_t*>( renderSurface->pixels ), renderSurface->w, renderSurface->h, renderSurface->pitch );

                application->InitRenderBuffer( this->renderBuffer );

                if ( renderSurface != nullptr )
                {
                    surfaceTexture = SDL_CreateTextureFromSurface( renderer, renderSurface );
                }

                return SDL_APP_CONTINUE;
            }

            SDL_AppResult IterateSdl( void* appstate )
            {
                const double timeSec = ( double( SDL_GetTicks( ) ) ) / 1000.0;

                if ( application->Iterate( timeSec, this->renderBuffer ) )
                {
                    if ( surfaceTexture != nullptr )
                    {
                        SDL_DestroyTexture( surfaceTexture );
                    }

                    surfaceTexture = SDL_CreateTextureFromSurface( renderer, renderSurface );
                }

                SDL_SetRenderDrawColorFloat( renderer, 0.0, 0.0, 0.0, SDL_ALPHA_OPAQUE_FLOAT );
                SDL_RenderClear( renderer );
                SDL_RenderTexture( renderer, surfaceTexture, NULL, NULL );
                SDL_RenderPresent( renderer );

                return SDL_APP_CONTINUE;
            }

            SDL_AppResult HandleSdlEvent( void* appstate, SDL_Event* event )
            {
                switch ( event->type )
                {
                case SDL_EVENT_QUIT: return SDL_APP_SUCCESS;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                {
                    float                x, y;
                    SDL_MouseButtonFlags flags = SDL_GetMouseState( &x, &y );

                    if ( flags & SDL_BUTTON_MASK( 1 ) & SDL_BUTTON_MASK( 2 ) )
                    {
                        application->HandleBothMouseButtonsClickEvent( x, y );
                    }

                    if ( flags & SDL_BUTTON_MASK( 1 ) )
                    {
                        application->HandleLeftMouseButtonClickEvent( x, y );
                    }

                    if ( flags & SDL_BUTTON_MASK( 2 ) )
                    {
                        application->HandleRightMouseButtonClickEvent( x, y );
                    }

                    return SDL_APP_CONTINUE;
                }
                case SDL_EVENT_MOUSE_BUTTON_UP:
                {
                    float                x, y;
                    SDL_MouseButtonFlags flags = SDL_GetMouseState( &x, &y );

                    if ( ( flags & SDL_BUTTON_MASK( 1 ) ) == 0 && ( flags & SDL_BUTTON_MASK( 2 ) ) == 0 )
                    {
                        application->HandleBothMouseButtonsUnclickEvent( x, y );
                    }

                    if ( ( flags & SDL_BUTTON_MASK( 1 ) ) == 0 )
                    {
                        application->HandleLeftMouseButtonUnclickEvent( x, y );
                    }

                    if ( ( flags & SDL_BUTTON_MASK( 1 ) ) == 0 )
                    {
                        application->HandleRightMouseButtonUnclickEvent( x, y );
                    }

                    return SDL_APP_CONTINUE;
                }
                case SDL_EVENT_KEY_DOWN:
                {
                    application->HandleKeyDown( event->key.scancode );
                    return SDL_APP_CONTINUE;
                }

                case SDL_EVENT_KEY_UP:
                {
                    application->HandleKeyUp( event->key.scancode );
                    return SDL_APP_CONTINUE;
                }

                default: break;
                }

                return SDL_APP_CONTINUE;
            }
    };

    GuiManager guiManager;


    Application::Application( ) : camera( 1.0, 68.0 )
    {
        world = CreateDemoWorld( );
    }

    void Application::InitGui( int& windowWidth, int& windowHeight )
    {
        windowWidth  = 640;
        windowHeight = 480;
    }

    void Application::InitRenderBuffer( ImageView<Rgba8>& renderBuffer )
    {
        for ( int row = 0; row != renderBuffer.GetHeight( ); row++ )
        {
            std::span<Rgba8> rowSpan = renderBuffer.GetRowSpan( row );

            for ( int col = 0; col != rowSpan.size( ); col++ )
            {
                Rgba8& p = rowSpan[ col ];

                double x = double( col ) / renderBuffer.GetWidth( );
                double y = double( row ) / renderBuffer.GetHeight( );

                p.r      = RayTracer::FloatingToByte( ( 1.0 - y ) * x );
                p.g      = RayTracer::FloatingToByte( ( 1.0 - y ) * ( 1 - x ) );
                p.b      = RayTracer::FloatingToByte( ( 1.0 - x ) * y );
                p.a      = 255;
            }
        }
    }

    bool Application::Iterate( const double& timeSec, ImageView<Rgba8>& renderBuffer )
    {
        SizeType maxBounces      = 10;
        SizeType samplesPerPixel = 1;

        if ( rotate )
        {
            auto   mousePos = GetMousePosition( );

            double deltaX   = mousePos.x( ) - rotateStart.x( );
            double deltaY   = mousePos.y( ) - rotateStart.y( );

            camera.Rotate( Vec2<double> { -deltaX / 5.0, -deltaY / 5.0 } );

            rotateStart = mousePos;
        }

        if ( moveBack )
        {
            camera.Pan( Vec2<double> { 0, 0.1 } );
        }

        if ( moveForward )
        {
            camera.Pan( Vec2<double> { 0, -0.1 } );
        }

        if ( moveLeft )
        {
            camera.Pan( Vec2<double> { -0.1, 0.0 } );
        }

        if ( moveRight )
        {
            camera.Pan( Vec2<double> { 0.1, 0.0 } );
        }

        camera.Render( world, renderBuffer, maxBounces, samplesPerPixel );

        return true;
    }

    Point2F Application::GetMousePosition( ) const
    {
        float x, y;
        SDL_GetMouseState( &x, &y );

        return Point2F { x, y };
    }

    void Application::HandleKeyDown( int keyCode )
    {
        switch ( keyCode )
        {
        case SDL_SCANCODE_W:
        {
            moveForward = true;
            return;
        }
        case SDL_SCANCODE_S:
        {
            moveBack = true;
            return;
        }
        case SDL_SCANCODE_A:
        {
            moveLeft = true;
            return;
        }
        case SDL_SCANCODE_D:
        {
            moveRight = true;
            return;
        }
        }
    }

    void Application::HandleKeyUp( int keyCode )
    {
        switch ( keyCode )
        {
        case SDL_SCANCODE_W:
        {
            moveForward = false;
            return;
        }
        case SDL_SCANCODE_S:
        {
            moveBack = false;
            return;
        }
        case SDL_SCANCODE_A:
        {
            moveLeft = false;
            return;
        }
        case SDL_SCANCODE_D:
        {
            moveRight = false;
            return;
        }
        }
    }

    void Application::HandleLeftMouseButtonClickEvent( float x, float y )
    {
        rotate      = true;
        rotateStart = Point2F { x, y };
    }

    void Application::HandleRightMouseButtonClickEvent( float x, float y )
    {
    }

    void Application::HandleBothMouseButtonsClickEvent( float x, float y )
    {
    }

    void Application::HandleLeftMouseButtonUnclickEvent( float x, float y )
    {
        rotate = false;
    }

    void Application::HandleRightMouseButtonUnclickEvent( float x, float y )
    {
    }

    void Application::HandleBothMouseButtonsUnclickEvent( float x, float y )
    {
        rotate = false;
    }

} // namespace RayTracer


using namespace RayTracer;


SDL_AppResult SDL_AppInit( void** appstate, int argc, char* argv[] )
{
    return guiManager.InitSdl( appstate, argc, argv );
}


SDL_AppResult SDL_AppEvent( void* appstate, SDL_Event* event )
{
    return guiManager.HandleSdlEvent( appstate, event );
}

SDL_AppResult SDL_AppIterate( void* appstate )
{
    return guiManager.IterateSdl( appstate );
}

void SDL_AppQuit( void* appstate, SDL_AppResult result )
{
    // SDL will clean up the window/renderer for us.
}
