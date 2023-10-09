###############################################################################
# Setup Compile options
add_compile_options(-march=rv32emcxtheadse)
add_compile_options(-mtune=e902)
add_compile_options(-mabi=ilp32e)
###############################################################################
# Setup Linker options
add_link_options(-march=rv32emcxtheadse)
add_link_options(-mtune=e902)
add_link_options(-mabi=ilp32e)
###############################################################################
