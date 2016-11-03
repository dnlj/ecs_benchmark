#include <string>
#include <vector>
#include <thread>
#include <memory>

#include "benchpress/benchpress.hpp"

#include "entityx/entityx.hh"

#include "EntityX2Benchmark.h"

inline void init_entities(EntityX2Benchmark::EntityManager& entities, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
		auto entity = entities.create();

		entity.assign<EntityX2Benchmark::PositionComponent>();
		entity.assign<EntityX2Benchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityX2Benchmark::ComflabulationComponent>();
		}
	}
}

inline void runEntitiesSystemsBenchmark(benchpress::context* ctx, size_t nentities) {
    EntityX2Benchmark::Application app;
    auto& entities = app.getEntityManager();

    init_entities(entities, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityX2Benchmark::fakeDeltaTime);
    }
}




BENCHMARK("entityx create destroy entity with components", [](benchpress::context* ctx) {
    EntityX2Benchmark::EntityManager entities;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto entity = entities.create();

        entity.assign<EntityX2Benchmark::PositionComponent>();
		entity.assign<EntityX2Benchmark::DirectionComponent>();
		entity.assign<EntityX2Benchmark::ComflabulationComponent>();

        entities.destroy(entity.id());
    }
})




BENCHMARK("entityx    25 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsBenchmark(ctx, 25);
})

BENCHMARK("entityx    50 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsBenchmark(ctx, 50);
})

BENCHMARK("entityx   100 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsBenchmark(ctx, 100);
})

BENCHMARK("entityx   200 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsBenchmark(ctx, 200);
})


BENCHMARK("entityx   400 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsBenchmark(ctx, 400);
})


BENCHMARK("entityx   800 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsBenchmark(ctx, 800);
})


BENCHMARK("entityx  1600 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsBenchmark(ctx, 1600);
})



BENCHMARK("entityx  3200 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsBenchmark(ctx, 3200);
})


BENCHMARK("entityx  5000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsBenchmark(ctx, 5000);
})


BENCHMARK("entityx 10000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsBenchmark(ctx, 10000);
})