# Create Library
add_library(UpsilonBase STATIC
    Ref.cpp
)

# Add Library Include
target_include_directories(UpsilonBase PUBLIC "${INCLUDE_DIR}/Base")
target_include_directories(UpsilonBase PUBLIC "${INCLUDE_DIR}/Render")

# Add 3rd Party Includes
# target_include_directories(UpsilonBase PUBLIC rttr)

# Link 3rd Party Librarys
target_link_libraries(UpsilonBase rttr_core_lib)