###################################################################

# Created by write_sdc on Thu Mar 24 08:56:02 2016

###################################################################
set sdc_version 1.8

set_units -time ns -resistance kOhm -capacitance pF -voltage V -current mA
set_max_delay 31  -from [list [get_ports a] [get_ports b] [get_ports c] [get_ports d]           \
[get_ports e] [get_ports f] [get_ports g] [get_ports h]]  -to [list [get_ports i] [get_ports j] [get_ports k] [get_ports p] [get_ports  \
q] [get_ports r] [get_ports s] [get_ports t] [get_ports y]]
