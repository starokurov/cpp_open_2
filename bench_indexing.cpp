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
Container generate_container(size_t size) {
	Container container;
	for (size_t i = 0; i < size; ++i) {
		container.push_back(value_to_test);
	}
	return container;
}

template<typename Container>
void indexing(const Container& c) {
	// Just go through the container and take every second element
	for (size_t i = 0; i < c.size()-2; i+=2) {
		auto citer = c.cbegin();
		std::advance(citer, i);
		TypeToTest value = *citer;
		benchmark::DoNotOptimize(value);
	}
}


void list_indexing(benchmark::State& state) {
	auto container = generate_container<std::list<TypeToTest>>(state.range(0));
	for (auto _ : state)
		indexing(container);
}

void vector_indexing(benchmark::State& state) {
	auto container = generate_container<std::vector<TypeToTest>>(state.range(0));
	for (auto _ : state)
		indexing(container);
}

void deque_indexing(benchmark::State& state) {
	auto container = generate_container<std::deque<TypeToTest>>(state.range(0));
	for (auto _ : state)
		indexing(container);
}


BENCHMARK(list_indexing)->Arg(100)->Unit(benchmark::kMicrosecond);
BENCHMARK(vector_indexing)->Arg(100)->Unit(benchmark::kMicrosecond);
BENCHMARK(deque_indexing)->Arg(100)->Unit(benchmark::kMicrosecond);

BENCHMARK(list_indexing)->Arg(2000)->Unit(benchmark::kMicrosecond);
BENCHMARK(vector_indexing)->Arg(2000)->Unit(benchmark::kMicrosecond);
BENCHMARK(deque_indexing)->Arg(2000)->Unit(benchmark::kMicrosecond);

BENCHMARK(list_indexing)->Arg(30000)->Unit(benchmark::kMicrosecond);
BENCHMARK(vector_indexing)->Arg(30000)->Unit(benchmark::kMicrosecond);
BENCHMARK(deque_indexing)->Arg(30000)->Unit(benchmark::kMicrosecond);


BENCHMARK_MAIN();


// Running C:\my\source\CMakeFiles\Release\bench_indexing.exe
// Run on (8 X 1800 MHz CPU s)
// CPU Caches:
//   L1 Data 32K (x4)
//   L1 Instruction 32K (x4)
//   L2 Unified 262K (x4)
//   L3 Unified 6291K (x1)
// -------------------------------------------------------------
// Benchmark                      Time           CPU Iterations
// -------------------------------------------------------------
// list_indexing/100              6 us          6 us     112000
// vector_indexing/100            4 us          4 us     213333
// deque_indexing/100             3 us          3 us     203636
// list_indexing/2000          3408 us       3370 us        204
// vector_indexing/2000          83 us         78 us      11200
// deque_indexing/2000           70 us         69 us       9249
// list_indexing/30000      1602280 us    1609375 us          1
// vector_indexing/30000       1007 us       1001 us        640
// deque_indexing/30000        1124 us       1088 us        560

