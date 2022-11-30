#include "MyVector.hpp"

#include <benchmark/benchmark.h>

#include <deque>
#include <list>
#include <vector>

using TypeToTest = MyVector<int>;

TypeToTest generate_value_to_test() {
	TypeToTest value{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	return value;
}

TypeToTest value_to_test = generate_value_to_test();

template<typename Container>
void test_push_back(size_t size) {
	Container container;
	for (size_t i = 0; i < size; ++i) {
		container.push_back(value_to_test);
	}
}



void list_push_back(benchmark::State& state) {
	for (auto _ : state)
		test_push_back<std::list<TypeToTest>>(state.range(0));
}

void vector_push_back(benchmark::State& state) {
	for (auto _ : state)
		test_push_back<std::vector<TypeToTest>>(state.range(0));
}

void deque_push_back(benchmark::State& state) {
	for (auto _ : state)
		test_push_back<std::deque<TypeToTest>>(state.range(0));
}


BENCHMARK(list_push_back)->Arg(100)->Unit(benchmark::kMicrosecond);
BENCHMARK(deque_push_back)->Arg(100)->Unit(benchmark::kMicrosecond);
BENCHMARK(vector_push_back)->Arg(100)->Unit(benchmark::kMicrosecond);

BENCHMARK(list_push_back)->Arg(2000)->Unit(benchmark::kMicrosecond);
BENCHMARK(deque_push_back)->Arg(2000)->Unit(benchmark::kMicrosecond);
BENCHMARK(vector_push_back)->Arg(2000)->Unit(benchmark::kMicrosecond);

BENCHMARK(list_push_back)->Arg(30000)->Unit(benchmark::kMicrosecond);
BENCHMARK(deque_push_back)->Arg(30000)->Unit(benchmark::kMicrosecond);
BENCHMARK(vector_push_back)->Arg(30000)->Unit(benchmark::kMicrosecond);


BENCHMARK_MAIN();


// Running C:\my\source\CMakeFiles\Release\bench_push_back.exe
// Run on (8 X 1800 MHz CPU s)
// CPU Caches:
//   L1 Data 32K (x4)
//   L1 Instruction 32K (x4)
//   L2 Unified 262K (x4)
//   L3 Unified 6291K (x1)
// --------------------------------------------------------------
// Benchmark                       Time           CPU Iterations
// --------------------------------------------------------------
// list_push_back/100             20 us         20 us      37333
// deque_push_back/100            21 us         21 us      34462
// vector_push_back/100           16 us         16 us      40727
// list_push_back/2000           309 us        310 us       1867
// deque_push_back/2000          332 us        330 us       2036
// vector_push_back/2000         216 us        215 us       3200
// list_push_back/30000         5430 us       5469 us        100
// deque_push_back/30000        6583 us       6076 us         90
// vector_push_back/30000       3733 us       3765 us        166