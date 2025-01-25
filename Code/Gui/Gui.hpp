#pragma once

#include "Camera.hpp"
#include "Color.hpp"
#include "Common.hpp"
#include "Hittable.hpp"
#include "Image.hpp"
#include "ThreadPool.hpp"
#include "TriangleMesh.hpp"

namespace RayTracer
{

    class Application
    {
            ThreadPool       threadPool;

            SizeType         maxBounces      = 10;
            SizeType         samplesPerPixel = 1;

            HittableList     world;

            Camera           camera;

            bool             rotate = false;
            Point2f          rotateStart;

            bool             moveBack                 = false;
            bool             moveForward              = false;
            bool             moveLeft                 = false;
            bool             moveRight                = false;

            RealType         minMoveVelocityPerSec    = 0.5;
            RealType         moveVelocityPerSec       = minMoveVelocityPerSec;
            RealType         moveAccelerationPerSecSq = 4.0;

            Array< TriangleMesh, 2 > triangleMeshList;

            TriangleMesh*            renderingTriangleMesh;
            TriangleMesh*            sortingTriangleMesh;
            std::mutex               swapMutex;
            std::atomic_bool sorting = false;

        public:

            Application( );

            void         InitGui( int& windowWidth, int& windowHeight );
            void         InitRenderBuffer( ImageView< Rgba8 >& renderBuffer );
            bool         Iterate( const float& timeSec, ImageView< Rgba8 >& renderBuffer );


            Point2f      GetMousePosition( ) const;

            virtual void HandleKeyDown( int keyCode );
            virtual void HandleKeyUp( int keyCode );

            virtual void HandleLeftMouseButtonClickEvent( float x, float y );
            virtual void HandleRightMouseButtonClickEvent( float x, float y );
            virtual void HandleBothMouseButtonsClickedEvent( float x, float y );

            virtual void HandleLeftMouseButtonUnclickEvent( float x, float y );
            virtual void HandleRightMouseButtonUnclickEvent( float x, float y );
            virtual void HandleBothMouseButtonsUnclickedEvent( float x, float y );

            void         LoadObj( const char* fileName );
    };


} // namespace RayTracer

extern "C"
{
    RayTracer::Application* CreateApplication( );
}