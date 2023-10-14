#include "instructions.h"
#include "../../src/core/cpu.h"
#include "../../src/core/executionengine.h"
#include "../../src/api/constants.h"
#include "../../src/api/numbers.h"

bool lda_shouldloadaccum() {
	auto cpu = std::make_unique<Cpu>();
	auto fname = Paths::get_path(C64_BASIC_KERNAL_FILENAME);
	auto mem = cpu->get_memory();
	auto engine = cpu->get_engine();
	mem->load(fname, 0xc000);
	auto val = mem->read_word(0xfffc);

	ASSERT(val == 64738, "rom was not loaded");
	cpu->set_register_word("pc", val);
	// lda is 0xad and has 3 steps
	Byte instr = 0xad;
	mem->write(val, instr);
	ASSERT_EQUAL(engine->currentstep, 0, "cpu did not step");
	cpu->step();
	//LRemove try..finallyengine->
	ASSERT_EQUAL(engine->currentstep, 1, "cpu did not step");
	ASSERT_EQUAL(engine->is_executing_instuction, true, "stepcount did not reset");
	
	cpu->step();

	return true;
}

void InstructionTests::register_tests() {
	UNIT_TEST(lda_shouldloadaccum);
}