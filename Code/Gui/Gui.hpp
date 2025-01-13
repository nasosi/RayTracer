#pragma once

#include "Camera.hpp"
#include "Color.hpp"
#include "Common.hpp"
#include "Hittable.hpp"
#include "Image.hpp"

namespace RayTracer
{

    class Application
    {
            double       cameraFocalLength    = 1.0;
            double       cameraViewportHeight = 2.0;
            SizeType     maxBounces           = 10;
            SizeType     samplesPerPixel      = 500;

            HittableList world;

            Camera       camera;

            bool         rotate = false;
            Point2F      rotateStart;

            bool         moveBack    = false;
            bool         moveForward = false;
            bool         moveLeft    = false;
            bool         moveRight   = false;


        public:

            Application( );

            void         InitGui( int& windowWidth, int& windowHeight );
            void         InitRenderBuffer( ImageView<Rgba8>& renderBuffer );
            bool         Iterate( const double& timeSec, ImageView<Rgba8>& renderBuffer );


            Point2F      GetMousePosition( ) const;

            virtual void HandleKeyDown( int keyCode );
            virtual void HandleKeyUp( int keyCode );

            virtual void HandleLeftMouseButtonClickEvent( float x, float y );
            virtual void HandleRightMouseButtonClickEvent( float x, float y );
            virtual void HandleBothMouseButtonsClickEvent( float x, float y );

            virtual void HandleLeftMouseButtonUnclickEvent( float x, float y );
            virtual void HandleRightMouseButtonUnclickEvent( float x, float y );
            virtual void HandleBothMouseButtonsUnclickEvent( float x, float y );
    };


} // namespace RayTracer

extern "C"
{
    RayTracer::Application* CreateApplication( );
}