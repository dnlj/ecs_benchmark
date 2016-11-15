#include <string>
#include <vector>
#include <thread>
#include <memory>

#include "benchpress/benchpress.hpp"

#include "entityx/entityx.h"

#include "EntityXBenchmark.h"

inline void init_entities(entityx::EntityManager& entities, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}
}

inline void runEntitiesSystemsEntityXBenchmark(benchpress::context* ctx, size_t nentities) {
    EntityXBenchmark::Application app;
    auto& entities = app.entities;

    init_entities(entities, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
}








BENCHMARK("entityx create destroy entity with components", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto entity = entities.create();

        entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();
		entity.assign<EntityXBenchmark::ComflabulationComponent>();

        entity.destroy();
    }
})





class BenchmarksEntityX {
    public:
    static const std::vector<int> ENTITIES;

    static inline void makeBenchmarks(std::string name) {
        makeBenchmarks(name, ENTITIES);
    }
    
    static void makeBenchmarks(std::string name, const std::vector<int>& entities) {
        for(int nentities : entities) {
            std::string tag = "[" + std::to_string(nentities) + "]";

            std::stringstream ss;
            ss << std::right << std::setw(10) << tag << ' ';
            ss << name << ' ';
            ss << std::right << std::setw(8) << nentities;
            ss << " entities component systems update";

            std::string benchmark_name = ss.str();
            BENCHMARK(benchmark_name, [nentities](benchpress::context* ctx) {
                runEntitiesSystemsEntityXBenchmark(ctx, nentities);
            })
        }
    }

    BenchmarksEntityX(std::string name){
        makeBenchmarks(name);
    }
};
const std::vector<int> BenchmarksEntityX::ENTITIES = {
    25, 50, 
    100, 200, 400, 800, 
    1600, 3200, 5000, 
    10'000, 30'000, 
    100'000, 500'000, 
    1'000'000, 2'000'000
};

BenchmarksEntityX entityxbenchmarks ("entityx");

