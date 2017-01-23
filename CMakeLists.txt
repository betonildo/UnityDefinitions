cmake_minimum_required (VERSION 2.6)

project(UnityDefinitions)

file(GLOB INCLUDE_UNITS include/*.h)

include_directories(${INCLUDE_UNITS})

# expose transitiantly the include folder
set(${PROJECT_NAME}_INCLUDE_DIRS 
    ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(${PROJECT_NAME}_INCLUDE_UNITS
    ${INCLUDE_UNITS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)