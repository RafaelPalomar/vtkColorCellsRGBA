cmake_minimum_required(VERSION 3.0)

project(vtkColorCellsRGBA)

find_package(VTK REQUIRED)

include(${VTK_USE_FILE})

add_executable(vtkColorCellsRGBA
  main.cxx
  )

target_link_libraries(vtkColorCellsRGBA
  ${VTK_LIBRARIES}
  )
