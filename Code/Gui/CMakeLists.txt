set( GuiHeaderFiles 
	Gui.hpp

)

set( GuiSourceFiles 
	Gui.cpp
)

add_library( Gui STATIC ${GuiHeaderFiles} ${GuiSourceFiles} )
add_library( RayTracer::Gui ALIAS Gui )

target_include_directories(Gui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Gui PRIVATE SDL3::SDL3 RayTracer::RayTracer)
set_property(TARGET Gui PROPERTY CXX_STANDARD 20)

if ( MSVC )

	target_compile_options(Gui PUBLIC "/fp:fast")

endif( )
