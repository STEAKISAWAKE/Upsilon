# Create Executable
add_executable(BaseTests
    main.cpp
)

# Add Library Includes
target_include_directories(BaseTests PUBLIC "${INCLUDE_DIR}/Base")

# Link Library to Executable
target_link_libraries(BaseTests UpsilonBase)