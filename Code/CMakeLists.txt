set( SDL_SHARED_DEFAULT OFF)
set( SDL_STATIC_DEFAULT ON)
set( SDL_SHARED OFF)
set( SDL_STATIC ON)

add_subdirectory( "ThirdParty/SDL-preview-3.1.6" EXCLUDE_FROM_ALL)

add_subdirectory(RayTracer)
add_subdirectory(Gui)
add_subdirectory(Test)



