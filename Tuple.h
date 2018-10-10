#pragma once
#include <type_traits>
#include <utility>

template<typename... T>
struct Tuple
{
    explicit Tuple(T&&... t)
    {
        construct(std::make_index_sequence<sizeof...(T)>{}, std::forward<T>(t)...);
    }

    template<size_t Idx>
    decltype(auto) get()
    {
        return getRef<0, Idx, T...>();
    }

private:
    template<size_t Idx, size_t Target, typename Head, typename... Tail>
    decltype(auto) getRef()
    {
        if constexpr (Idx == Target) {
            return *reinterpret_cast<Head*>(&buffer[offsetAt(Idx)]);
        }
        else {
            return getRef<Idx+1, Target, Tail...>();
        }
    }

    template<size_t... I, typename... U>
    void construct(std::index_sequence<I...>, U&&...u)
    {
        int dummy[] = { (new (&buffer[offsetAt(I)]) T(std::forward<U>(u)), 0)...  };
        (void)dummy;
    }

    static constexpr size_t offsetAt(size_t idx)
    {
        constexpr size_t sizes[] = {
            sizeof(std::aligned_storage_t<sizeof(T)>)...
        };
        size_t offset = 0;
        for (size_t i = 0; i != idx; ++i) {
            offset += sizes[i];
        }
        return offset;
    }

    char buffer[offsetAt(sizeof...(T))];
};
