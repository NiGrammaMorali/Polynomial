set(target a${CUSTOM})

file(GLOB hdrs "*.h*" "${INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_include_directories(${target} PRIVATE ${INCLUDE})