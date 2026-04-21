#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "httplib::httplib" for configuration "RelWithDebInfo"
set_property(TARGET httplib::httplib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(httplib::httplib PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/httplib.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/httplib.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS httplib::httplib )
list(APPEND _IMPORT_CHECK_FILES_FOR_httplib::httplib "${_IMPORT_PREFIX}/lib/httplib.lib" "${_IMPORT_PREFIX}/bin/httplib.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
