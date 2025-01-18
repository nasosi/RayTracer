#pragma once


#include "Array.hpp"
#include "Common.hpp"

#include <cassert>
#include <cstdint>
#include <type_traits>

namespace RayTracer
{

    template <typename ValueType, SizeType DataArraySize, class Derived>
    class ColorDataBuffer : public Array<ValueType, DataArraySize>
    {
        public:

            using ColorType = Derived;
    };


    template <class ValueType, SizeType ColorComponentCount, class ColorType>
    class ChromaInterface
    {
        private:

            static const bool ValueType_Is_FloatingPoint = std::is_floating_point_v<ValueType>;

        public:

            static const SizeType ColorCount = ColorComponentCount;

            template <typename Lazy = ColorType>
            inline typename std::enable_if<( ValueType_Is_FloatingPoint ), Lazy&>::type& operator*=( const ValueType& m )
            {
                assert( m >= 0 );

                ColorType* thisColor = static_cast<ColorType*>( this );

                For_Constexpr<SizeType, 0, ColorComponentCount>(
                    [ thisColor, &m ]( auto i )
                    {
                        ( *thisColor )[ i ] *= m;
                    } );

                return *thisColor;
            }

            template <typename Lazy = ColorType>
            inline typename std::enable_if<( ValueType_Is_FloatingPoint ), Lazy&>::type& operator/=( const ValueType& d )
            {
                assert( d > std::numeric_limits<ValueType>::epsilon( ) );

                ColorType* thisColor = static_cast<ColorType*>( this );

                For_Constexpr<SizeType, 0, ColorComponentCount>(
                    [ thisColor, &d ]( auto i )
                    {
                        ( *thisColor )[ i ] /= d;
                    } );

                return *thisColor;
            }

            template <typename Lazy = ColorType>
            inline typename std::enable_if<( ValueType_Is_FloatingPoint ), Lazy&>::type& operator*=( const ColorType& other )
            {

#ifndef NDEBUG
                For_Constexpr<SizeType, 0, ColorComponentCount>(
                    [ &other ]( auto i )
                    {
                        assert( other[ i ] >= 0 );
                    } );
#endif

                ColorType* thisColor = static_cast<ColorType*>( this );

                For_Constexpr<SizeType, 0, ColorComponentCount>(
                    [ thisColor, &other ]( auto i )
                    {
                        ( *thisColor )[ i ] *= other[ i ];
                    } );

                return *thisColor;
            }
    };


    template <class ValueType, class ColorType>
    class __declspec( empty_bases ) MonochromaticInterface : //
                                   public ChromaInterface<ValueType, 1, ColorType>
    {
    };

    template <class ValueType, class ColorType>
    class __declspec( empty_bases ) TrichromaticInterface : //
                                  public ChromaInterface<ValueType, 3, ColorType>
    {
    };

    template <class ValueType, class ColorType>
    class RgbInterface
    {
        public:

            const ValueType& r( ) const
            {
                return ( *static_cast<const ColorType*>( this ) )[ 0 ];
            }

            ValueType& r( )
            {
                return ( *static_cast<ColorType*>( this ) )[ 0 ];
            }

            const ValueType& g( ) const
            {
                return ( *static_cast<const ColorType*>( this ) )[ 1 ];
            }

            ValueType& g( )
            {
                return ( *static_cast<ColorType*>( this ) )[ 1 ];
            }

            const ValueType& b( ) const
            {
                return ( *static_cast<const ColorType*>( this ) )[ 2 ];
            }

            ValueType& b( )
            {
                return ( *static_cast<ColorType*>( this ) )[ 2 ];
            }
    };

    template <class ValueType, class ColorType>
    class AlphaInterface
    {
        public:

            const ValueType& a( ) const
            {
                return ( *static_cast<ColorType*>( this ) )[ 3 ];
            }

            ValueType& a( )
            {
                return ( *static_cast<ColorType*>( this ) )[ 3 ];
            }
    };


    template <typename ValueType, SizeType ColorComponentCount, SizeType ArraySize, class ColorType, class FlatColorType>
    class FlatChromaInterface
    {
        public:

            using flatColorType = FlatColorType;

            inline FlatColorType& operator+=( const ColorType& c )
            {
                FlatColorType* thisColor = static_cast<FlatColorType*>( this );

                For_Constexpr<SizeType, 0, ColorComponentCount>(
                    [ thisColor, &c ]( auto i )
                    {
                        ( *thisColor )[ i ] += c[ i ];
                    } );

                //
                this->weight( )++;

                return *thisColor;
            }

            inline FlatColorType& operator+=( const FlatColorType& fc )
            {
                FlatColorType* thisColor = static_cast<FlatColorType*>( this );

                For_Constexpr<SizeType, 0, ColorComponentCount>(
                    [ thisColor, &fc ]( auto i )
                    {
                        ( *thisColor )[ i ] += fc[ i ];
                    } );

                //
                this->weight( ) += fc.weight( );

                return *thisColor;
            }

            inline ColorType GetUnitized( )
            {
                ColorType      c;

                FlatColorType* thisColor = static_cast<FlatColorType*>( this );

                For_Constexpr<SizeType, 0, ColorComponentCount>(
                    [ this, thisColor, &c ]( auto i )
                    {
                        c[ i ] = ( *thisColor )[ i ] / this->weight( );
                    } );

                return c;
            }

            inline const ValueType& weight( ) const
            {
                return ( *static_cast<const FlatColorType*>( this ) )[ ArraySize - 1 ];
            }

            inline ValueType& weight( )
            {
                return ( *static_cast<FlatColorType*>( this ) )[ ArraySize - 1 ];
            }
    };

    template <SizeType ArraySize, class ValueType, class ColorType, class FlatColorType>
    class __declspec( empty_bases ) FlatTrichromaticInterface : //
                                      public FlatChromaInterface<ValueType, 3, ArraySize, ColorType, FlatColorType>
    {
    };


    template <typename ValueType>
    class __declspec( empty_bases ) Rgb :                                                       //
                                          public ColorDataBuffer<ValueType, 3, Rgb<ValueType>>, //
                                          public RgbInterface<ValueType, Rgb<ValueType>>,       //
                                          public TrichromaticInterface<ValueType, Rgb<ValueType>>


    {
        public:

            using ChromaInterface = TrichromaticInterface<ValueType, Rgb<ValueType>>;
    };

    template <typename ValueType>
    class __declspec( empty_bases ) FlatRgb :                                                              //
                                              public ColorDataBuffer<ValueType, 4, FlatRgb<ValueType>>,    //
                                              public RgbInterface<ValueType, FlatRgb<ValueType>>,          //
                                              public TrichromaticInterface<ValueType, FlatRgb<ValueType>>, //
                                              public FlatTrichromaticInterface<4, ValueType, Rgb<ValueType>, FlatRgb<ValueType>>
    {
    };

    template <typename ValueType>
    class __declspec( empty_bases ) Rgba : //
                                           public ColorDataBuffer<ValueType, 4, Rgba<ValueType>>,
                                           public RgbInterface<ValueType, Rgba<ValueType>>,
                                           public AlphaInterface<ValueType, Rgba<ValueType>>,
                                           public TrichromaticInterface<ValueType, Rgba<ValueType>>
    {
    };

    template <typename ValueType>
    class __declspec( empty_bases ) FlatRgba :                                                            //
                                               public ColorDataBuffer<ValueType, 5, FlatRgba<ValueType>>, //
                                               public RgbInterface<ValueType, FlatRgba<ValueType>>,       //
                                               public TrichromaticInterface<ValueType, Rgba<ValueType>>,  //
                                               public FlatTrichromaticInterface<5, ValueType, Rgba<ValueType>, FlatRgba<ValueType>>
    {
    };


    template <typename ValueType, SizeType DataArraySize, class ColorType>
    inline auto operator*( ColorDataBuffer<ValueType, DataArraySize, ColorType> a, const ColorDataBuffer<ValueType, DataArraySize, ColorType>& b )
    {
        return ( *static_cast<ColorType*>( &a ) ) *= ( *static_cast<const ColorType*>( &b ) );
    }

    template <typename ValueType, SizeType DataArraySize, class ColorType>
    inline auto operator*( ColorDataBuffer<ValueType, DataArraySize, ColorType> c, const ValueType& s )
    {
        return ( *static_cast<ColorType*>( &c ) ) *= s;
    }

    template <template <typename> class ColorType, typename ValueType>
    inline ColorType<ValueType> operator*( const ValueType& s, ColorType<ValueType> color )
    {
        return color *= s;
    }

  /*  template <typename ValueType, SizeType ColorComponentCount, SizeType ArraySize, class ColorType, class FlatColorType>
    inline FlatRgb<ValueType> operator+( FlatChromaInterface<ValueType, ColorComponentCount, ArraySize, ColorType, FlatColorType>        a,
                                         const FlatChromaInterface<ValueType, ColorComponentCount, ArraySize, ColorType, FlatColorType>& b )
    {
        return ( *static_cast<FlatColorType*>( &a ) ) += ( *static_cast<const FlatColorType*>( &b ) );
    }*/

    template <typename ValueType>
    FlatRgb<ValueType> operator+( FlatRgb<ValueType> a, const FlatRgb<ValueType>& b )
    {
        return a += b;
    }

    extern template class Rgb<uint8_t>;
    extern template class Rgb<float>;
    extern template class Rgb<double>;

    using Rgb8     = Rgb<uint8_t>;
    using RgbF     = Rgb<float>;
    using RgbD     = Rgb<double>;
    using FlatRgbD = FlatRgb<double>;

    Rgb8 ConvertToRgb8( const RgbD& color );
    RgbD LinearToGamma( const RgbD& color, double gamma = 2.2 );

    extern template class Rgba<uint8_t>;
    extern template class Rgba<float>;
    extern template class Rgba<double>;

    using Rgba8 = Rgba<uint8_t>;
    using RgbaF = Rgba<float>;
    using RgbaD = Rgba<double>;

    Rgba8 ConvertToRgba8( const RgbD& color );

} // namespace RayTracer