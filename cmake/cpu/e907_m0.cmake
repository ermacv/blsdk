###############################################################################
# Setup Compile options
add_compile_options(-march=rv32imafcpzpsfoperand_xtheade)
add_compile_options(-mtune=e907)
add_compile_options(-mabi=ilp32f)
###############################################################################
# Setup Linker options
add_link_options(-march=rv32imafcpzpsfoperand_xtheade)
add_link_options(-mtune=e907)
add_link_options(-mabi=ilp32f)
###############################################################################