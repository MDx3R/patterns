add_library(core
    application/usecases/create_milk_use_case_impl.cpp
    application/usecases/create_toy_use_case_impl.cpp
    application/usecases/create_tv_use_case_impl.cpp
    application/usecases/get_product_use_case_impl.cpp
    domain/entities/milk.cpp
    domain/entities/tv.cpp
    domain/entities/toy.cpp
    domain/entities/product.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)
