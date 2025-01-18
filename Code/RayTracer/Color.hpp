#pragma once


#include "Array.hpp"
#include "Common.hpp"

#include <cassert>
#include <cstdint>
#include <type_traits>

namespace RayTracer
{

    template < typename valueType, SizeType dataArraySize, class colorType >
    class ColorDataBuffer : public Array< valueType, dataArraySize >
    {
        public:

            static const SizeType DataArraySize = dataArraySize;
            using ValueType                     = valueType;
            using ColorType                     = colorType;
    };


    template < class ColorType, SizeType colorComponentCount >
    class ChromaInterface
    {
        public:

            static const SizeType ColorComponentCount = colorComponentCount;

            template < typename Lazy = ColorType >
            inline typename std::enable_if< (std::is_floating_point_v< typename Lazy::ValueType >), Lazy& >::type operator*=( const typename Lazy::ValueType& m )
            {
                assert( m >= 0 );

                ColorType* thisColor = static_cast< ColorType* >( this );

                For_Constexpr< SizeType, 0, ColorComponentCount >(
                    [ thisColor, &m ]( auto i )
                    {
                        ( *thisColor )[ i ] *= m;
                    } );

                return *thisColor;
            }


            template < typename Lazy = ColorType >
            inline typename std::enable_if< (std::is_floating_point_v< typename Lazy::ValueType >), ColorType >::type operator*( const typename Lazy::ValueType& m ) const
            {
                ColorType        out;
                const ColorType* thisColor = static_cast< const ColorType* >( this );

                For_Constexpr< SizeType, 0, ColorComponentCount >(
                    [ thisColor, &out, &m ]( auto i )
                    {
                        out[ i ] = ( *thisColor )[ i ] * m;
                    } );

                For_Constexpr< SizeType, ColorComponentCount, ColorType::DataArraySize >(
                    [ thisColor, &out, &m ]( auto i )
                    {
                        out[ i ] = ( *thisColor )[ i ];
                    } );

                return out;
            }

            template < typename Lazy = ColorType >
            inline typename std::enable_if< (std::is_floating_point_v< typename Lazy::ValueType >), Lazy& >::type operator/=( const typename Lazy::ValueType& d )
            {
                assert( d > std::numeric_limits< Lazy::ValueType >::epsilon( ) );

                ColorType* thisColor = static_cast< ColorType* >( this );

                For_Constexpr< SizeType, 0, ColorComponentCount >(
                    [ thisColor, &d ]( auto i )
                    {
                        ( *thisColor )[ i ] /= d;
                    } );

                return *thisColor;
            }

            template < typename Lazy = ColorType >
            inline typename std::enable_if< (std::is_floating_point_v< typename Lazy::ValueType >), Lazy& >::type operator*=( const ChromaInterface& other )
            {

                ColorType*       thisColor  = static_cast< ColorType* >( this );
                const ColorType* otherColor = static_cast< const ColorType* >( &other );

#ifndef NDEBUG
                For_Constexpr< SizeType, 0, ColorComponentCount >(
                    [ otherColor ]( auto i )
                    {
                        assert( ( *otherColor )[ i ] >= 0 );
                    } );
#endif


                For_Constexpr< SizeType, 0, ColorComponentCount >(
                    [ thisColor, otherColor ]( auto i )
                    {
                        ( *thisColor )[ i ] *= ( *otherColor )[ i ];
                    } );

                return *thisColor;
            }

            template < typename Lazy = ColorType >
            inline typename std::enable_if< (std::is_floating_point_v< typename Lazy::ValueType >), Lazy >::type operator*( ColorType other )
            {
                return other *= *static_cast< ColorType* >( this );
            }
    };


    template < class ColorType >
    class RgbInterface
    {
        public:

            const auto& r( ) const
            {
                return ( *static_cast< const ColorType* >( this ) )[ 0 ];
            }

            auto& r( )
            {
                return ( *static_cast< ColorType* >( this ) )[ 0 ];
            }

            const auto& g( ) const
            {
                return ( *static_cast< const ColorType* >( this ) )[ 1 ];
            }

            auto& g( )
            {
                return ( *static_cast< ColorType* >( this ) )[ 1 ];
            }

            const auto& b( ) const
            {
                return ( *static_cast< const ColorType* >( this ) )[ 2 ];
            }

            auto& b( )
            {
                return ( *static_cast< ColorType* >( this ) )[ 2 ];
            }
    };

    template < class ColorType >
    class AlphaInterface
    {
        public:

            const auto& a( ) const
            {
                return ( *static_cast< ColorType* >( this ) )[ 3 ];
            }

            auto& a( )
            {
                return ( *static_cast< ColorType* >( this ) )[ 3 ];
            }
    };


    template < class ColorType, class flatColorType >
    class FlatChromaInterface
    {
        public:

            using FlatColorType = flatColorType;

            inline FlatChromaInterface& operator+=( const ColorType& c )
            {
                FlatColorType* thisColor = static_cast< FlatColorType* >( this );

                For_Constexpr< SizeType, 0, ColorType::ColorComponentCount >(
                    [ thisColor, &c ]( auto i )
                    {
                        ( *thisColor )[ i ] += c[ i ];
                    } );

                //
                this->weight( )++;

                return *this;
            }

            inline FlatColorType& operator+=( const FlatColorType& other )
            {
                FlatColorType* thisColor = static_cast< FlatColorType* >( this );

                For_Constexpr< SizeType, 0, ColorType::ColorComponentCount >(
                    [ thisColor, &other ]( auto i )
                    {
                        ( *thisColor )[ i ] += ( other )[ i ];
                    } );

                //
                this->weight( ) += other.weight( );

                return *thisColor;
            }

            inline typename std::enable_if< (std::is_floating_point_v< typename ColorType::ValueType >), FlatColorType >::type operator+( FlatColorType other )
            {
                return other += *static_cast< FlatColorType* >( this );
            }

            inline ColorType GetUnitized( )
            {
                ColorType      c;

                FlatColorType* thisColor = static_cast< FlatColorType* >( this );

                For_Constexpr< SizeType, 0, ColorType::ColorComponentCount >(
                    [ this, thisColor, &c ]( auto i )
                    {
                        c[ i ] = ( *thisColor )[ i ] / this->weight( );
                    } );

                return c;
            }

            inline const auto& weight( ) const
            {
                return ( *static_cast< const FlatColorType* >( this ) )[ FlatColorType::DataArraySize - 1 ];
            }

            inline auto& weight( )
            {
                return ( *static_cast< FlatColorType* >( this ) )[ FlatColorType::DataArraySize - 1 ];
            }
    };

    template < class ValueType, class ColorType >
    class __declspec( empty_bases ) MonochromaticInterface : //
                                                             public ChromaInterface< ColorType, 1 >
    {
    };

    template < class ColorType >
    class __declspec( empty_bases ) TrichromaticInterface : //
                                                            public ChromaInterface< ColorType, 3 >
    {
    };

    template < class ColorType, class FlatColorType >
    class __declspec( empty_bases ) FlatTrichromaticInterface : //
                                                                public FlatChromaInterface< ColorType, FlatColorType >
    {
    };


    template < typename ValueType >
    class __declspec( empty_bases ) Rgb :                                                           //
                                          public ColorDataBuffer< ValueType, 3, Rgb< ValueType > >, //
                                          public RgbInterface< Rgb< ValueType > >,                  //
                                          public TrichromaticInterface< Rgb< ValueType > >


    {
    };

    template < typename ValueType >
    class __declspec( empty_bases ) FlatRgb :                                                               //
                                              public ColorDataBuffer< ValueType, 4, FlatRgb< ValueType > >, //
                                              public RgbInterface< FlatRgb< ValueType > >,                  //
                                              public TrichromaticInterface< FlatRgb< ValueType > >,         //
                                              public FlatTrichromaticInterface< Rgb< ValueType >, FlatRgb< ValueType > >
    {
    };

    template < typename ValueType >
    class __declspec( empty_bases ) Rgba :                                                            //
                                           public ColorDataBuffer< ValueType, 4, Rgba< ValueType > >, //
                                           public RgbInterface< Rgba< ValueType > >,                  //
                                           public AlphaInterface< Rgba< ValueType > >,                //
                                           public TrichromaticInterface< Rgba< ValueType > >
    {
    };

    template < typename ValueType >
    class __declspec( empty_bases ) FlatRgba :                                                                //
                                               public ColorDataBuffer< ValueType, 5, FlatRgba< ValueType > >, //
                                               public RgbInterface< FlatRgba< ValueType > >,                  //
                                               public TrichromaticInterface< Rgba< ValueType > >,             //
                                               public FlatTrichromaticInterface< Rgba< ValueType >, FlatRgba< ValueType > >
    {
    };


    template < typename ColorType, SizeType ColorComponentCount >
    inline ColorType operator*( const typename ColorType::ValueType& s, const ChromaInterface< ColorType, ColorComponentCount >& c )
    {
        return c * s;
    }


    extern template class Rgb< uint8_t >;
    extern template class Rgb< float >;
    extern template class Rgb< double >;

    using Rgb8     = Rgb< uint8_t >;
    using RgbF     = Rgb< float >;
    using RgbD     = Rgb< double >;
    using FlatRgbD = FlatRgb< double >;

    Rgb8 ConvertToRgb8( const RgbD& color );
    RgbD LinearToGamma( const RgbD& color, double gamma = 2.2 );

    extern template class Rgba< uint8_t >;
    extern template class Rgba< float >;
    extern template class Rgba< double >;

    using Rgba8 = Rgba< uint8_t >;
    using RgbaF = Rgba< float >;
    using RgbaD = Rgba< double >;

    Rgba8 ConvertToRgba8( const RgbD& color );

} // namespace RayTracer