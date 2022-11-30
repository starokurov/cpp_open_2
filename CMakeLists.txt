cmake_minimum_required(VERSION 3.15)
project(stl_containers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(benchmark CONFIG REQUIRED)

add_executable(
	bench_push_front
	bench_push_front.cpp
)

target_link_libraries(
	bench_push_front 
	PRIVATE 
	benchmark::benchmark benchmark::benchmark_main
)

add_executable(
	bench_push_back
	bench_push_back.cpp
)

target_link_libraries(
	bench_push_back 
	PRIVATE 
	benchmark::benchmark benchmark::benchmark_main
)

add_executable(
	bench_indexing
	bench_indexing.cpp
)

target_link_libraries(
	bench_indexing 
	PRIVATE 
	benchmark::benchmark benchmark::benchmark_main
)

add_executable(
	bench_pass_through
	bench_pass_through.cpp
)

target_link_libraries(
	bench_pass_through 
	PRIVATE 
	benchmark::benchmark benchmark::benchmark_main
)
