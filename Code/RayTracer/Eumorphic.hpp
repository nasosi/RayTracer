#pragma once


#include <tuple>

namespace Eumorphic
{
    namespace Detail
    {
        template < typename T, typename Tuple >
        struct TupleElementIndexHelper;

        template < typename T >
        struct TupleElementIndexHelper< T, std::tuple<> >
        {
                static constexpr std::size_t value = 0;
        };

        template < typename T, typename... Rest >
        struct TupleElementIndexHelper< T, std::tuple< T, Rest... > >
        {
                static constexpr std::size_t value = 0;
                using RestTuple                    = std::tuple< Rest... >;
                static_assert( TupleElementIndexHelper< T, RestTuple >::value == std::tuple_size_v< RestTuple >, "type appears more than once in tuple" );
        };

        template < typename T, typename First, typename... Rest >
        struct TupleElementIndexHelper< T, std::tuple< First, Rest... > >
        {
                using RestTuple                    = std::tuple< Rest... >;
                static constexpr std::size_t value = 1 + TupleElementIndexHelper< T, RestTuple >::value;
        };


    } // namespace Detail


    template < typename T, typename Tuple >
    struct TupleElementIndex
    {
            static constexpr std::size_t value = Detail::TupleElementIndexHelper< T, Tuple >::value;
            static_assert( value < std::tuple_size_v< Tuple >, "type is not a member of the tuple" );
    };

    template < typename T, typename Tuple >
    inline constexpr std::size_t TupleElementIndex_v = TupleElementIndex< T, Tuple >::value;

    template < class C, class Func >
    void ForEach( C& c, Func& f )
    {
        for ( auto& elem : c )
        {
            f( elem );
        }
    }

    template < class... Types >
    struct collection
    {
        private:


            using ContainerTuple = typename std::tuple< std::vector< Types >... >;

            ContainerTuple containerTuple;

            template < class T >
            auto& GetContainer( )
            {
                constexpr std::size_t i = TupleElementIndex_v< std::vector< T >, ContainerTuple >;

                return std::get< i >( containerTuple );
            }


        public:

            template < class T >
            void AppendArrayElement( T t )
            {
                GetContainer< T >( ).push_back( t );
            }

            template < class Func >
            void Loop( Func&& f )
            {
                std::apply(
                    [ & ]( auto&&... args )
                    {
                        ( ForEach( args, f ), ... );
                    },
                    containerTuple );
            }
    };


} // namespace Eumorphic