#include "instructions.h"
#include "../../src/core/cpu.h"
#include "../../src/core/executionengine.h"
#include "../../src/api/constants.h"
#include "../../src/api/numbers.h"

bool lda_shouldloadaccum() {
	auto cpu = std::make_unique<Cpu>();
	auto fname = Paths::get_path(C64_BASIC_KERNAL_FILENAME);
	auto mem = cpu->get_Memory();
	auto engine = cpu->get_Engine();
	mem->load(fname, 0xc000);
	auto val = mem->read_word(0xfffc);

	ASSERT(val == 64738, "rom was not loaded");
	cpu->set_pc(val);
	// lda is 0xad and has 3 steps
	Byte instr = 0xad;
	mem->write(val, instr);
	ASSERT_EQUAL(engine->currentstep, 0, "xcpu did not step");
	cpu->step();
	//LRemove try..finallyengine->
	ASSERT_EQUAL(engine->currentstep, 1, "cpu did not step");
	ASSERT_EQUAL(engine->stepcount, 0, "stepcount did not reset");
	
	cpu->step();

	//LRemove try..finallyengine->
	ASSERT_EQUAL(engine->currentstep, 1, "cpu did not step to 1");
	ASSERT_EQUAL(engine->stepcount, 0, "stepcount changed unexpectedly");
	ASSERT_EQUAL(engine->currentinstruction, 0xad, "instruction was not loaded");

	cpu->step();

	ASSERT_EQUAL(engine->currentstep, 2, "cpu did not step to 2");
	ASSERT_EQUAL(engine->currentinstruction, 0xad, "instruction was unloaded");
	ASSERT_EQUAL(engine->stepcount, 5, "steps were not loaded");
	return true;
}

void InstructionTests::register_tests() {
	UNIT_TEST(lda_shouldloadaccum);
}