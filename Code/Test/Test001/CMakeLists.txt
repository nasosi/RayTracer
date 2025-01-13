add_executable( Test001 main.cpp )

target_link_libraries( Test001 PRIVATE RayTracer::RayTracer)

set_property(TARGET Test001 PROPERTY CXX_STANDARD 20)