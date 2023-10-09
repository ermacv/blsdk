###############################################################################
# Setup Compile options
add_compile_options(-march=rv64imafdcv0p7_zfh_xtheadc)
add_compile_options(-mtune=c906)
add_compile_options(-mabi=lp64d)
###############################################################################
# Setup Linker options
add_link_options(-march=rv64imafdcv0p7_zfh_xtheadc)
add_link_options(-mtune=c906)
add_link_options(-mabi=lp64d)
###############################################################################
