# Project setup
project('vulnerable_credentials_manager', 'c')

# Project 'source' and 'include' directories
project_sources = []
project_includes = []

# Declare dependencies
add_project_dependencies(dependency('sqlite3', required: true), language: 'c')

# Call subdirectories
subdir('src')

# Create executable
executable(
    'credentials_manager',
    sources: project_sources,
    include_directories: project_includes,

)
