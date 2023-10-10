###############################################################################
# Setup common Linker options
###############################################################################
add_link_options(-Wl,--gc-sections)
add_link_options(-Wl,--print-memory-usage)
add_link_options(-Wl,--traditional-format)
add_link_options(-Wl,--cref)
add_link_options(-nostartfiles)
add_link_options(-fms-extensions)
add_link_options(-ffunction-sections)
add_link_options(-fdata-sections)
# Newlib specific --specs.*
# add_link_options(--specs=nano.specs)
# add_link_options(--specs=nosys.specs)
###############################################################################
