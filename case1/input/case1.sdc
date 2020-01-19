###################################################################

# Created by write_sdc on Thu Mar 24 08:36:57 2016

###################################################################
set sdc_version 1.8

set_units -time ns -resistance kOhm -capacitance pF -voltage V -current mA
set_max_area 0
set_max_delay 45  -from [list [get_ports a1] [get_ports a2] [get_ports a3] [get_ports a4]       \
[get_ports a5] [get_ports a6] [get_ports a7] [get_ports a8] [get_ports a9]     \
[get_ports a10] [get_ports b1] [get_ports b2] [get_ports b3] [get_ports b4]    \
[get_ports b5] [get_ports b6] [get_ports b7] [get_ports b8] [get_ports b9]     \
[get_ports b10]]  -to [list [get_ports product0] [get_ports product1] [get_ports product2]      \
[get_ports product3] [get_ports product4] [get_ports product5] [get_ports      \
product6] [get_ports product7] [get_ports product8] [get_ports product9]       \
[get_ports product10] [get_ports product11] [get_ports product12] [get_ports   \
product13] [get_ports product14] [get_ports product15] [get_ports product16]   \
[get_ports product17] [get_ports product18] [get_ports product19]]
