###################################################################

# Created by write_sdc on Thu Mar 24 08:57:51 2016

###################################################################
set sdc_version 1.8

set_units -time ns -resistance kOhm -capacitance pF -voltage V -current mA
set_max_delay 45  -from [list [get_ports A0] [get_ports A1] [get_ports A2] [get_ports A3]       \
[get_ports A4] [get_ports A5] [get_ports A6] [get_ports A7] [get_ports A8]     \
[get_ports A9] [get_ports A10] [get_ports A11] [get_ports A12] [get_ports A13] \
[get_ports A14] [get_ports A15] [get_ports A16] [get_ports A17] [get_ports     \
A18] [get_ports A19] [get_ports B0] [get_ports B1] [get_ports B2] [get_ports   \
B3] [get_ports B4] [get_ports B5] [get_ports B6] [get_ports B7] [get_ports B8] \
[get_ports B9] [get_ports B10] [get_ports B11] [get_ports B12] [get_ports B13] \
[get_ports B14] [get_ports B15] [get_ports B16] [get_ports B17] [get_ports     \
B18] [get_ports B19] [get_ports F]]  -to [list [get_ports E0] [get_ports E1] [get_ports E2] [get_ports E3]         \
[get_ports E4] [get_ports E5] [get_ports E6] [get_ports E7] [get_ports E8]     \
[get_ports E9] [get_ports E10] [get_ports E11] [get_ports E12] [get_ports E13] \
[get_ports E14] [get_ports E15] [get_ports E16] [get_ports E17] [get_ports     \
E18] [get_ports E19] [get_ports G]]
