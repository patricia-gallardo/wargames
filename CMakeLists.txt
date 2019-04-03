cmake_minimum_required(VERSION 3.10)
project(wargames)

# -----------------------------------------------------------------
#
# WARGAMES
#
# -----------------------------------------------------------------

# Wargames C
# -------------------------
add_executable(launch src/launch.c)
# Get gets
set_property(TARGET launch PROPERTY C_STANDARD 99)
# Allow gets
target_compile_options(launch PRIVATE -Wno-deprecated-declarations)
# Remove Fortify protection in libc
# *** buffer overflow detected ***: ./launch terminated
# Aborted (core dumped)
target_compile_options(launch PRIVATE -D_FORTIFY_SOURCE=0)
# remove the stack protector
# *** stack smashing detected ***: <unknown> terminated
# Aborted (core dumped)
target_compile_options(launch PRIVATE -fno-stack-protector)
# Make the stack executable - otherwise Segmentation fault (core dumped)
set_target_properties(launch PROPERTIES LINK_FLAGS "-z execstack")

# Wargames C++
# -------------------------
add_executable(launch_cpp src/launch.cpp)
# remove the stack protector
# *** stack smashing detected ***: <unknown> terminated
# Aborted (core dumped)
target_compile_options(launch_cpp PRIVATE -fno-stack-protector)

# Wargames Fixed C++
# -------------------------
add_executable(launch_fixed_cpp src/launch_fixed.cpp)

# Simple Exploit
# -------------------------
add_executable(simple_exploit src/simple_exploit.c)

# Wargames C++
# -------------------------
add_executable(launch_bigger src/launch_bigger.cpp)
# remove the stack protector
# *** stack smashing detected ***: <unknown> terminated
# Aborted (core dumped)
target_compile_options(launch_bigger PRIVATE -fno-stack-protector)

# Attempt 1: Simple Stack Buffer Shellcode test
# -------------------------
add_executable(simple_stack_overflow_test src/simple_stack_overflow_test.c)

# Attempt 1: Simple Stack Buffer Exploit
# -------------------------
add_executable(simple_stack_overflow_exploit src/simple_stack_overflow_exploit.c)

# Attempt 2: Simple Stack Buffer Shellcode test
# -------------------------
add_executable(simple_stack_overflow_test2 src/simple_stack_overflow_test2.c)

# Attempt 2: Simple Stack Buffer Exploit
# -------------------------
add_executable(simple_stack_overflow_exploit2 src/simple_stack_overflow_exploit2.c)

# Attempt 3: Stack Buffer Shellcode in C
# -------------------------
add_executable(shellcode src/shellcode.c)

# Attempt 3: Stack Buffer Shellcode in asm
# -------------------------
add_executable(shellcode_asm src/shellcode_asm.c)

# Attempt 3: Stack Buffer Shellcode test
# -------------------------
add_executable(shellcode_test src/shellcode_test.c)

# Attempt 3: Stack Buffer Shellcode exploit
# -------------------------
add_executable(shellcode_exploit src/shellcode_exploit.c)