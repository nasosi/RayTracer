#pragma once


#include "Color.hpp"
#include "Common.hpp"

#include <fstream>
#include <span>
#include <vector>

namespace RayTracer
{

    template <class PixelColorType>
    class Image
    {
        private:

            SizeType                    width;
            SizeType                    height;
            std::vector<PixelColorType> buffer;

        public:

            Image( const SizeType& width, const SizeType& height ) : width( width ), height( height ), buffer( width * height )
            {
            }

            const SizeType& GetWidth( ) const
            {
                return width;
            }

            const SizeType& GetHeight( ) const
            {
                return height;
            }

            const PixelColorType& GetPixel( const SizeType column, const SizeType row ) const
            {
                return buffer[ row * width + column ];
            }

            PixelColorType& GetPixel( const SizeType column, const SizeType row )
            {
                return buffer[ row * width + column ];
            }

            std::span<const PixelColorType> GetRowSpan( const SizeType& row ) const
            {
                return std::span<const PixelColorType>( &buffer[ row * width ], width );
            }

            std::span<PixelColorType> GetRowSpan( const SizeType& row )
            {
                return std::span<PixelColorType>( &buffer[ row * width ], width );
            }
    };

    extern template class Image<Rgb8>;
    using RgbImage8 = Image<Rgb8>;

    template <class PixelColorType>
    class ImageView
    {
        private:

            SizeType width           = 0;
            SizeType height          = 0;
            SizeType rowWidthInBytes = 0;
            uint8_t* buffer          = nullptr;

        public:

            ImageView( ) = default;

            ImageView( uint8_t* buffer, const SizeType& width, const SizeType& height, const SizeType& rowWidthInBytes ) :
                buffer( buffer ),
                rowWidthInBytes( rowWidthInBytes ),
                width( width ),
                height( height )
            {
            }

            const SizeType& GetWidth( ) const
            {
                return width;
            }

            const SizeType& GetHeight( ) const
            {
                return height;
            }

            const PixelColorType& GetPixel( const SizeType column, const SizeType row ) const
            {
                return *reinterpret_cast<PixelColorType*>( buffer + row * rowWidthInBytes + column * sizeof( PixelColorType ) );
            }

            PixelColorType& GetPixel( const SizeType column, const SizeType row )
            {
                return *reinterpret_cast<PixelColorType*>( buffer + row * rowWidthInBytes + column * sizeof( PixelColorType ) );
            }

            std::span<const PixelColorType> GetRowSpan( const SizeType& row ) const
            {
                return std::span<const PixelColorType>( reinterpret_cast<PixelColorType*>( buffer + row * rowWidthInBytes ), width );
            }

            std::span<PixelColorType> GetRowSpan( const SizeType& row )
            {
                return std::span<PixelColorType>( reinterpret_cast<PixelColorType*>( buffer + row * rowWidthInBytes ), width );
            }
    };

    extern template class ImageView<Rgba8>;
    using RgbaImageView8 = ImageView<Rgba8>;


    template <class ImageType>
    bool WritePPM( const ImageType& image, const char* fileName )
    {

        std::ofstream imageFileStream( fileName );

        if ( !imageFileStream.is_open( ) )
        {
            return false;
        }

        imageFileStream << "P3\n" << image.GetWidth( ) << ' ' << image.GetHeight( ) << "\n255\n";

        for ( SizeType r = 0; r < image.GetHeight( ); r++ )
        {
            auto row = image.GetRowSpan( r );

            for ( const auto& color : row )
            {
                imageFileStream << int( color.r( ) ) << ' ' << int( color.g( ) ) << ' ' << int( color.b( ) ) << '\n';
            }
        }

        imageFileStream.close( );

        return true;
    }

    template <class ImageType>
    bool WritePPM( const SharedPointer<ImageType> image, const char* fileName )
    {
        return WritePPM( *image.get( ), fileName );
    }


} // namespace RayTracer
