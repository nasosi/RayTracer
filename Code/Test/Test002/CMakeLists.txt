add_executable( Test002 main.cpp )

target_link_libraries( Test002 PRIVATE RayTracer::RayTracer)

set_property(TARGET Test002 PROPERTY CXX_STANDARD 20)