#pragma once

#include <algorithm>

namespace RayTracer
{

    template <typename Type>
    class Interval
    {
        private:

            Type from, to;

        public:

            Interval( Type from, Type to ) : from( from ), to( to )
            {
            }

            Type Range( )
            {
                return to - from;
            }

            bool Contains( const Type& x )
            {
                return from <= x && x <= to;
            }

            bool Surrounds( const Type& x ) const
            {
                return from < x && x < to;
            }

            const Type &GetFrom() const
            {
                return from;
            }

            const Type& GetTo( ) const
            {
                return to;
            }
    };


    extern template class Interval<float>;
    extern template class Interval<double>;

    using IntervalF = Interval<float>;
    using IntervalD = Interval<double>;


} // namespace RayTracer