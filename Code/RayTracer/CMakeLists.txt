find_package(OpenMP REQUIRED)


set( RtHeaderFiles 
	Algebra.hpp
	Array.hpp
	Camera.hpp
	Color.hpp
	Common.hpp
	Hittable.hpp
	Image.hpp
	Interval.hpp
	Material.hpp
	Octree.hpp
	Ray.hpp
	ThreadPool.hpp
	Triangle.hpp
	TriangleMesh.hpp

)

set( RtSourceFiles 
Aabb.cpp
	Algebra.cpp
	Array.cpp
	Camera.cpp
	Common.cpp
	Hittable.cpp
	Color.cpp
	Image.cpp
	Interval.cpp
	Material.cpp
	Octree.cpp
	Ray.cpp
	ThreadPool.cpp
	Triangle.cpp
	TriangleMesh.cpp
)

add_library( RayTracer STATIC ${RtSourceFiles} ${RtHeaderFiles}  )
add_library( RayTracer::RayTracer ALIAS RayTracer )

target_include_directories(RayTracer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries( RayTracer PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries( RayTracer PRIVATE ObjLoader::ObjLoader )

set_property(TARGET RayTracer PROPERTY CXX_STANDARD 20)

if ( MSVC )

	target_compile_options(RayTracer PUBLIC "/fp:fast")

endif( )