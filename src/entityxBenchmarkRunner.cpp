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




BENCHMARK("entityx    25 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 25);
})

BENCHMARK("entityx    50 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 50);
})

BENCHMARK("entityx   100 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 100);
})

BENCHMARK("entityx   200 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 200);
})


BENCHMARK("entityx   400 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 400);
})


BENCHMARK("entityx   800 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 800);
})


BENCHMARK("entityx  1600 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 1600);
})



BENCHMARK("entityx  3200 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 3200);
})


BENCHMARK("entityx  5000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 5000);
})


BENCHMARK("entityx 10000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 10'000);
})

BENCHMARK("entityx 30000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 30'000);
})


BENCHMARK("entityx 100000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 100'000L);
})


BENCHMARK("entityx 500000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 500'000L);
})

BENCHMARK("entityx 1M entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 1'000'000L);
})

BENCHMARK("entityx 2M entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 2'000'000L);
})