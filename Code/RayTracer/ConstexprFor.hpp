#pragma once

#include <tuple>
#include <utility>

namespace RayTracer
{

    namespace Detail
    {
        template <typename T, T Begin, class Func, T... Is>
        constexpr void ConstexprForImpl( Func&& f, std::integer_sequence<T, Is...> )
        {
            ( f( std::integral_constant<T, Begin + Is> { } ), ... );
        }


    } // namespace Detail

    template <typename T, T Begin, T End, class Func>
    constexpr void Constexpr_For( Func&& f )
    {
        Detail::ConstexprForImpl<T, Begin>( std::forward<Func>( f ), std::make_integer_sequence<T, End - Begin> { } );
    }

    template <class Tuple>
    constexpr std::size_t TupleSize( const Tuple& )
    {
        return std::tuple_size<Tuple>::value;
    }

} // namespace RayTracer