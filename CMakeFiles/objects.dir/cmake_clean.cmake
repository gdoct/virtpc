file(REMOVE_RECURSE
  "CMakeFiles/objects"
  "obj/core/core/bus.o"
  "obj/core/core/clock.o"
  "obj/core/core/cpu.o"
  "obj/core/core/machine.o"
  "obj/core/core/mem.o"
  "obj/main/main/main.o"
  "obj/microcode/microcode/microcode.o"
  "obj/microcode/microcode/microinstruction.o"
  "obj/util/util/logger.o"
  "obj/util/util/options.o"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/objects.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
