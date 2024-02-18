set(target glad)

set(GLAD_SOURCES src/glad.c)

add_library(${target} STATIC ${GLAD_SOURCES})

