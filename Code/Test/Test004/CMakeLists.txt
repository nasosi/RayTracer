find_package( OpenMP REQUIRED )

set( RayTracer_Current_Target_Name Test004 )

add_executable( ${RayTracer_Current_Target_Name} main.cpp )

target_link_libraries( ${RayTracer_Current_Target_Name} PRIVATE RayTracer::RayTracer SDL3::SDL3 )

target_link_libraries( ${RayTracer_Current_Target_Name} PRIVATE RayTracer::Gui OpenMP::OpenMP_CXX )

set_property( TARGET ${RayTracer_Current_Target_Name} PROPERTY CXX_STANDARD 20 )

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT test003)

if ( MSVC )

	target_compile_options( ${RayTracer_Current_Target_Name} PUBLIC "/fp:fast" )

endif( )

configure_file( ${RayTracer_DataDir}/Sponza/sponza.obj     ${CMAKE_CURRENT_BINARY_DIR} COPYONLY )
configure_file( ${RayTracer_DataDir}/TestData/TwoCubes.obj ${CMAKE_CURRENT_BINARY_DIR} COPYONLY )
