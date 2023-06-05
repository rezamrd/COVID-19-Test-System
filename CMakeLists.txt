# CMakeList.txt : CMake project for FinalProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("FinalProject")

# Add source to this project's executable.
add_executable (FinalProject "FinalProject.cpp" "FinalProject.h")

# TODO: Add tests and install targets if needed.
target_include_directories(FinalProject PUBLIC "F:\\nanaLibrary\\nana\\include")


#Compiler variable
add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)

#Target library

target_link_libraries(FinalProject "nana_v142_Debug_x64" )



target_link_directories(FinalProject PUBLIC "F:\\nanaLibrary\\nana\\build\\bin")
