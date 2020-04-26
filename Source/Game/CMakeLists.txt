
# Create Library
add_library(UpsilonGame STATIC
    Game.cpp
    World.cpp
)

# Include Directories
target_include_directories(UpsilonGame PUBLIC "${INCLUDE_DIR}/Base")
target_include_directories(UpsilonGame PUBLIC "${INCLUDE_DIR}/Math")
target_include_directories(UpsilonGame PUBLIC "${INCLUDE_DIR}/Game")

# Link Libraries
target_link_libraries(UpsilonGame UpsilonBase)
target_link_libraries(UpsilonGame UpsilonMath)