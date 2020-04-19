set(GLM_TEST_ENABLE OFF CACHE BOOL "GLM test" FORCE)
set(GLM_TEST_ENABLE_LANG_EXTENSIONS OFF CACHE BOOL "Enable language extensions" FORCE)
set(GLM_DISABLE_AUTO_DETECTION ON CACHE BOOL "Force 'pure' instructions" FORCE)

add_definitions(-DGLM_FORCE_LEFT_HANDED)

add_subdirectory(glm)