#include "cpu.h"
#include "../tests.h"
#include "../../src/core/cpu.h"
/*
class Cpu {
    public:
        Cpu();
        Cpu(Cpu& other);
        Cpu(Bus* cpubus, Clock* clock, Memory* memory);

        Memory* get_Memory() const { return memory.get(); }

        Byte get_x() const;
        void set_x(Byte x);

        Byte get_y() const;
        void set_y(Byte y);

        Byte get_acc() const;
        void set_acc(Byte acc);

        Word get_pc() const;
        void set_pc(Word pc);

        Word get_mc() const;
        void set_mc(Word mc);

        Byte get_status() const;
        void set_status(Byte status);

        void step();
*/
bool cpu_shouldcreate() {
    auto cpu = new Cpu();
    ASSERT_FALSE(cpu == nullptr, "constructor fail");
    return true;
}

bool cpu_should_initialize_properly() {
    auto cpu = new Cpu();
    ASSERT_EQUAL(cpu->get_acc(), 0, "acc");
    ASSERT_EQUAL(cpu->get_mc(), 0, "mc");
    ASSERT_EQUAL(cpu->get_pc(), 0, "pc");
    ASSERT_EQUAL(cpu->get_status(), 0, "status");
    ASSERT_EQUAL(cpu->get_x(), 0, "x");
    ASSERT_EQUAL(cpu->get_y(), 0, "y");
    
    return true;
}

bool cpu_step_nop_increases_pc_only() {
    auto cpu = new Cpu();
    ASSERT_EQUAL(cpu->get_pc(), 0, "pc");

    cpu -> step();

    ASSERT_EQUAL(cpu->get_acc(), 0, "acc");
    ASSERT_EQUAL(cpu->get_mc(), 0, "mc");
    ASSERT_EQUAL(cpu->get_pc(), 1, "pc");
    ASSERT_EQUAL(cpu->get_status(), 0, "status");
    ASSERT_EQUAL(cpu->get_x(), 0, "x");
    ASSERT_EQUAL(cpu->get_y(), 0, "y");

    return true;
}

bool cpu_setters() {
    auto cpu = new Cpu();
    cpu->set_acc(123);
    ASSERT_EQUAL(cpu->get_acc(), 123, "acc");
    cpu->set_acc(static_cast<Byte>(257));
    ASSERT_NOTEQUAL(cpu->get_acc(), 257, "acc overflow");
    cpu->set_acc(-1);
    ASSERT_NOTEQUAL(cpu->get_acc(), -1, "acc negative");

    cpu->set_mc(456);
    ASSERT_EQUAL(cpu->get_mc(), 456, "mc");
    cpu->set_mc(static_cast<Word>(1234567));
    ASSERT_NOTEQUAL(cpu->get_mc(), 1234567, "mc overflow");
    cpu->set_mc(-1);
    ASSERT_NOTEQUAL(cpu->get_mc(), -1, "mc negative");

    cpu->set_pc(789);
    ASSERT_EQUAL(cpu->get_pc(), 789, "pc");
    cpu->set_pc(65534);
    ASSERT_EQUAL(cpu->get_pc(), 65534, "pc");
    cpu->set_pc(static_cast<Word>(65537));
    ASSERT_NOTEQUAL(cpu->get_pc(), 65537, "pc overflow");
    cpu->set_pc(-1);
    ASSERT_NOTEQUAL(cpu->get_pc(), -1, "pc negative");

    cpu->set_status(222);
    ASSERT_EQUAL(cpu->get_status(), 222, "status");
    cpu->set_status(static_cast<Byte>(256));
    ASSERT_NOTEQUAL(cpu->get_status(), 256, "status overflow");
    cpu->set_status(-1);
    ASSERT_NOTEQUAL(cpu->get_status(), -1, "status negative");

    cpu->set_x(42);
    ASSERT_EQUAL(cpu->get_x(), 42, "x");
    cpu->set_x(static_cast<Byte>(420));
    ASSERT_NOTEQUAL(cpu->get_x(), 420, "x overflow");

    cpu->set_y(128);
    ASSERT_EQUAL(cpu->get_y(), 128, "y");
    cpu->set_y(-5);
    ASSERT_NOTEQUAL(cpu->get_y(), -5, "y negative");

    return true;
}


void CpuTests::register_tests() {
    UNIT_TEST(cpu_shouldcreate);
    UNIT_TEST(cpu_should_initialize_properly);
    UNIT_TEST(cpu_step_nop_increases_pc_only);
    UNIT_TEST(cpu_setters);
}