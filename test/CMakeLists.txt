# tests

# 为每个测试文件创建一个单独的可执行文件和测试
add_executable(test3 test3.cpp)
target_link_libraries(test3 ${PROJECT_NAME})

add_executable(test1_2 test1_2.cpp)
target_link_libraries(test1_2 PRIVATE ${PROJECT_NAME})

add_executable(test1_3 test1_3.cpp)
target_link_libraries(test1_3 ${PROJECT_NAME})

add_executable(test1_4 test1_4.cpp)
target_link_libraries(test1_4 ${PROJECT_NAME})

add_executable(test2_1 test2_1.cpp)
target_link_libraries(test2_1 ${PROJECT_NAME})

add_executable(test2_2 test2_2.cpp)
target_link_libraries(test2_2 ${PROJECT_NAME})
