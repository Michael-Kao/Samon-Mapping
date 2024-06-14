cmake_minimum_required(VERSION 3.26.0)

project(homework)

if(UNIX)
    set(CMAKE_TOOLCHAIN_FILE ~/builds/vcpkg/scripts/buildsystems/vcpkg.cmake)
    include(~/builds/vcpkg/scripts/buildsystems/vcpkg.cmake)
endif (UNIX)

add_executable(${PROJECT_NAME})

# 顯示相關資訊
message(STATUS)
message(STATUS "========== Build Information ==========")
message(STATUS "\tHost System Name:         ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "\tHost System Version:      ${CMAKE_HOST_SYSTEM_VERSION}")
message(STATUS "\tHost System Processor:    ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS)
message(STATUS "\tC++ Compiler:             ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "\tC++ Compiler Path:        ${CMAKE_CXX_COMPILER}")
message(STATUS)
message(STATUS "\tVCPKG Path:               ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS)

find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# 指定標頭檔資料夾、找尋所有原始檔、並將【原始碼】加入到【執行檔目標】中
target_include_directories(${PROJECT_NAME} PRIVATE "include")
file(GLOB MY_SOURCE CONFIGURE_DEPENDS "src/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${MY_SOURCE})

target_link_libraries(${PROJECT_NAME} 
    PRIVATE OpenGL::GL
    PRIVATE glad::glad
    PRIVATE glfw
    PRIVATE imgui::imgui
    PRIVATE glm::glm
)

# 建立 Symlink 到 assets 資料夾
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    COMMENT
        "Creating symlinks to project resources..."
    VERBATIM
)
