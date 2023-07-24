set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

set(INCLUDE_DIRS "${EXTERNAL_DIR}/glad/include" "${EXTERNAL_DIR}/glfw/include" "${EXTERNAL_DIR}/imgui" "${EXTERNAL_DIR}/imgui/backends")
set(LINK_DIRS "${EXTERNAL_DIR}/glfw/build/src")
set(SUB_DIRS "dataset")

include_directories(${INCLUDE_DIRS} ${SUB_DIRS})
link_directories(${LINK_DIRS})

set(LIBS "glfw3" "opengl32")
set(SUB_SRCS "dataset")

add_subdirectory(${SUB_DIRS})
add_executable(ConvNet "ConvNet.cpp")

set(TARGET_SRCS "imgui.cpp" "imgui_demo.cpp" "imgui_draw.cpp" "imgui_tables.cpp" "imgui_widgets.cpp")
list(TRANSFORM TARGET_SRCS PREPEND "${EXTERNAL_DIR}/imgui/")
target_sources(ConvNet PRIVATE ${TARGET_SRCS})

set(TARGET_SRCS "imgui_impl_glfw.cpp" "imgui_impl_opengl3.cpp")
list(TRANSFORM TARGET_SRCS PREPEND "${EXTERNAL_DIR}/imgui/backends/")
target_sources(ConvNet PRIVATE ${TARGET_SRCS})

set(TARGET_SRCS "glad.c")
list(TRANSFORM TARGET_SRCS PREPEND "${EXTERNAL_DIR}/glad/src/")
target_sources(ConvNet PRIVATE ${TARGET_SRCS})

target_link_libraries(ConvNet ${LIBS} ${SUB_SRCS})