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
            SizeType     maxBounces      = 10;
            SizeType     samplesPerPixel = 1;

            HittableList world;

            Camera       camera;

            bool         rotate = false;
            Point2F      rotateStart;

            bool         moveBack                 = false;
            bool         moveForward              = false;
            bool         moveLeft                 = false;
            bool         moveRight                = false;

            double       minMoveVelocityPerSec    = 0.5;
            double       moveVelocityPerSec       = minMoveVelocityPerSec;
            double       moveAccelerationPerSecSq = 4.0;


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
            virtual void HandleBothMouseButtonsUnclickedEvent( float x, float y );
    };


} // namespace RayTracer

extern "C"
{
    RayTracer::Application* CreateApplication( );
}