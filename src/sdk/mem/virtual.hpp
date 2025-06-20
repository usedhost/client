#pragma once

namespace selaura {
    namespace details {
        template<typename>
        struct resolve_func;

        template<typename R, typename... Args>
        struct resolve_func<R(Args...)> {

            template<typename T>
            struct memfn : std::type_identity<R(T::*)(Args...)> {};

            template<typename T>
            struct memfn<const T> : std::type_identity<R(T::*)(Args...) const> {};

            template<typename T>
            using memfn_t = typename memfn<T>::type;
        };

        template<typename R, typename T, typename... Args>
        struct resolve_func<R(T::*)(Args...)> {
            template<typename>
            using memfn_t = R(T::*)(Args...);
        };

        template<typename R, typename T, typename... Args>
        struct resolve_func<R(T::*)(Args...) const> {
            template<typename>
            using memfn_t = R(T::*)(Args...) const;
        };
    }

    template <typename Ret, typename Inst, typename... Args>
    Ret call_virtual(Inst* instance, size_t index, Args&&... args) {
        const auto vtable = *reinterpret_cast<const uintptr_t* const*>(instance);
        const uintptr_t addr = vtable[index];

        using Fn = Ret(Args...);
        using memfn_t = typename details::resolve_func<Fn>::template memfn_t<Inst>;

        const auto memfn = std::bit_cast<memfn_t>(addr);
        return (instance->*memfn)(std::forward<Args>(args)...);
    }

    template <typename TRet, typename... TArgs>
        TRet call_virtual_raw(void* thisptr, size_t index, TArgs... argList) {
        using TFunc = TRet(__fastcall*)(void*, TArgs...);
        TFunc* vtable = *reinterpret_cast<TFunc**>(thisptr);
        return vtable[index](thisptr, argList...);
    }
};