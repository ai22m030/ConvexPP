########################################################################################################################
### CONVEX HULL TESTS
########################################################################################################################

add_executable(${CONVEX_HULL_PROJECT_NAME}Hull10
        ${CONVEX_HULL_TESTS_DIR}/convex_hull_10_test.cpp)

find_package(OpenMP REQUIRED)

if (OpenMP_CXX_FOUND)
    target_include_directories(${CONVEX_HULL_PROJECT_NAME}Hull10 PUBLIC OpenMP::OpenMP_CXX_INCLUDE_DIRS)
    target_link_libraries(${CONVEX_HULL_PROJECT_NAME}Hull10 PUBLIC OpenMP::OpenMP_CXX)
endif ()

target_include_directories(${CONVEX_HULL_PROJECT_NAME}Hull10 PUBLIC
        ${CONVEX_HULL_INC_DIR})

target_include_directories(${CONVEX_HULL_PROJECT_NAME}Hull10 PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${CONVEX_HULL_PROJECT_NAME}Hull10 PRIVATE ${SDL2_LIBRARIES} imgui)

add_test(NAME hull_10_test COMMAND $<TARGET_FILE:${CONVEX_HULL_PROJECT_NAME}Hull10>)