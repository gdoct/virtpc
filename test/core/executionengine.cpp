#include "executionengine.h"
#include "../../src/api/constants.h"
#include "../../src/core/executionengine.h"

bool executionEngine_factory_creates() {
    auto engine = ExecutionEngine::create_execution_engine(Paths::get_path(MICROCODE_FILENAME));
    ASSERT_NOTNULL(engine, "engine is null");
    return true;
}

bool executionEngine_factory_creates_ptr() {
    auto engine = ExecutionEngine::create_execution_engine_ptr(Paths::get_path(MICROCODE_FILENAME));
    ASSERT_NOTNULL(engine, "engine is null");
    return true;
}

bool executionEngine_canstep() {
    auto engine = ExecutionEngine::create_execution_engine(Paths::get_path(MICROCODE_FILENAME));
    Cpu* cpu = new Cpu();
    engine->step(cpu);
    delete cpu;
    delete engine;
    return true;
}

void ExecutionEngineTests::register_tests() {
    UNIT_TEST(executionEngine_factory_creates);
    UNIT_TEST(executionEngine_factory_creates_ptr);
    UNIT_TEST(executionEngine_canstep);
   // UNIT_TEST(mini_test);
}

