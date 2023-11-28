########################################################################################################################
### CONVEX HULL APPLICATION
########################################################################################################################

add_executable(${CONVEX_HULL_PROJECT_NAME}
        ${CONVEX_HULL_SRC_DIR}/main.cpp
        ${CONVEX_HULL_SRC_DIR}/program_options.cpp)
        ##${CONVEX_HULL_SRC_DIR}/magic_square.cpp)

find_package(OpenMP REQUIRED)

if (OpenMP_CXX_FOUND)
    target_include_directories(${CONVEX_HULL_PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX_INCLUDE_DIRS)
    target_link_libraries(${CONVEX_HULL_PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif ()

target_include_directories(${CONVEX_HULL_PROJECT_NAME} PUBLIC
        ${CONVEX_HULL_INC_DIR})

target_include_directories(${CONVEX_HULL_PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${CONVEX_HULL_PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} imgui)