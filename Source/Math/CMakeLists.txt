# Create Library
add_library(UpsilonMath STATIC
    Mesh.cpp
)

# Library Includes
target_include_directories(UpsilonMath PUBLIC "${INCLUDE_DIR}/Math")

# 3rd Party Includes
target_include_directories(UpsilonMath PUBLIC ${GLM_INCLUDE_DIRS})

# Link 3rd Party Libraries
target_link_libraries(UpsilonMath glm)