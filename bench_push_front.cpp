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
void test_push_front(size_t size) {
	Container container;
	for (size_t i = 0; i < size; ++i) {
		// Could not be used for std::vector
		// container.push_front(value_to_test);

		// Emulate push_front through the insert(0)
		container.insert(container.begin(), value_to_test);
	}
}



void list_push_front(benchmark::State& state) {
	for (auto _ : state)
		test_push_front<std::list<TypeToTest>>(state.range(0));
}

void vector_push_front(benchmark::State& state) {
	for (auto _ : state)
		test_push_front<std::vector<TypeToTest>>(state.range(0));
}

void deque_push_front(benchmark::State& state) {
	for (auto _ : state)
		test_push_front<std::deque<TypeToTest>>(state.range(0));
}


BENCHMARK(list_push_front)->Arg(100)->Unit(benchmark::kMicrosecond);
BENCHMARK(deque_push_front)->Arg(100)->Unit(benchmark::kMicrosecond);
BENCHMARK(vector_push_front)->Arg(100)->Unit(benchmark::kMicrosecond);

BENCHMARK(list_push_front)->Arg(2000)->Unit(benchmark::kMicrosecond);
BENCHMARK(deque_push_front)->Arg(2000)->Unit(benchmark::kMicrosecond);
BENCHMARK(vector_push_front)->Arg(2000)->Unit(benchmark::kMicrosecond);

BENCHMARK(list_push_front)->Arg(30000)->Unit(benchmark::kMicrosecond);
BENCHMARK(deque_push_front)->Arg(30000)->Unit(benchmark::kMicrosecond);
BENCHMARK(vector_push_front)->Arg(30000)->Unit(benchmark::kMicrosecond);


BENCHMARK_MAIN();






// 11/30/22 19:27:53
// Running C:\my\source\CMakeFiles\Release\bench_push_front.exe
// Run on (8 X 1800 MHz CPU s)
// CPU Caches:
//   L1 Data 32K (x4)
//   L1 Instruction 32K (x4)
//   L2 Unified 262K (x4)
//   L3 Unified 6291K (x1)
// ---------------------------------------------------------------
// Benchmark                        Time           CPU Iterations
// ---------------------------------------------------------------
// list_push_front/100             17 us         17 us      40727
// deque_push_front/100            18 us         18 us      37333
// vector_push_front/100           27 us         25 us      29867
// list_push_front/2000           308 us        305 us       1792
// deque_push_front/2000          335 us        338 us       2036
// vector_push_front/2000        4171 us       4179 us        172
// list_push_front/30000         5620 us       5625 us        100
// deque_push_front/30000        5374 us       5301 us        112
// vector_push_front/30000     980966 us     968750 us          1