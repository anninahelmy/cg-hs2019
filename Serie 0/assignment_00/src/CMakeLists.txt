# add as object library as not to compile all of these twice:
add_library(common OBJECT Cylinder.cpp Mesh.cpp Plane.cpp Scene.cpp Sphere.cpp vec3.cpp)

add_executable(raytrace raytrace.cpp)
add_executable(debug_aabb debug_aabb.cpp)


find_package(OpenMP)

SET(TARGETS raytrace debug_aabb)

foreach(TARGET common ${TARGETS})
    set_target_properties(${TARGET}
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
    )
    target_compile_definitions(${TARGET} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:_USE_MATH_DEFINES>
        $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
        )
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${TARGET} PUBLIC OpenMP::OpenMP_CXX)
    endif()
endforeach()

foreach(TARGET ${TARGETS})
    target_link_libraries(${TARGET} PRIVATE common)
endforeach()
