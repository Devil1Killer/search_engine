if(EXISTS "C:/CLion/search_engine/cmake-build-debug/project[1]_tests.cmake")
  include("C:/CLion/search_engine/cmake-build-debug/project[1]_tests.cmake")
else()
  add_test(project_NOT_BUILT project_NOT_BUILT)
endif()