// 
// Copyright 2022 Clemens Cords
// Created on 13.02.22 by clem (mail@clemens-cords.com)
//

namespace jluna
{
    /// @brief unbox to type
    template<Is<Type> T>
    inline T unbox(Any* value)
    {
        jl_assert_type(value, "Type");
        return Type((jl_datatype_t*) value);
    }

    /// @brief box jluna::Type to Base.Type
    template<Is<Type> T>
    inline Any* box(T value)
    {
        return value.operator Any*();
    }

    /// @brief type deduction
    template<>
    struct detail::to_julia_type_aux<Type>
    {
        static inline const std::string type_name = "Type";
    };

    template<ToJuliaTypeConvertable T>
    Type Type::construct_from()
    {
        auto* type = jl_eval_string(("return " + to_julia_type<T>::type_name).c_str());
        return Type((jl_datatype_t*) type);
    }
}