find_package(OpenMP REQUIRED)

add_executable( Test003 main.cpp )

target_link_libraries( Test003 PRIVATE RayTracer::RayTracer SDL3::SDL3)

target_link_libraries(Test003 PRIVATE RayTracer::Gui OpenMP::OpenMP_CXX)

set_property(TARGET Test003 PROPERTY CXX_STANDARD 20)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT test003)

if ( MSVC )

	target_compile_options(Test003 PUBLIC "/fp:fast")

endif( )