###################################################################

# Created by write_sdc on Thu Mar 24 08:53:52 2016

###################################################################
set sdc_version 1.8

set_units -time ns -resistance kOhm -capacitance pF -voltage V -current mA
set_max_delay 43  -from [list [get_ports N1] [get_ports N8] [get_ports N13] [get_ports N17]     \
[get_ports N26] [get_ports N29] [get_ports N36] [get_ports N42] [get_ports     \
N51] [get_ports N55] [get_ports N59] [get_ports N68] [get_ports N72]           \
[get_ports N73] [get_ports N74] [get_ports N75] [get_ports N80] [get_ports     \
N85] [get_ports N86] [get_ports N87] [get_ports N88] [get_ports N89]           \
[get_ports N90] [get_ports N91] [get_ports N96] [get_ports N101] [get_ports    \
N106] [get_ports N111] [get_ports N116] [get_ports N121] [get_ports N126]      \
[get_ports N130] [get_ports N135] [get_ports N138] [get_ports N143] [get_ports \
N146] [get_ports N149] [get_ports N152] [get_ports N153] [get_ports N156]      \
[get_ports N159] [get_ports N165] [get_ports N171] [get_ports N177] [get_ports \
N183] [get_ports N189] [get_ports N195] [get_ports N201] [get_ports N207]      \
[get_ports N210] [get_ports N219] [get_ports N228] [get_ports N237] [get_ports \
N246] [get_ports N255] [get_ports N259] [get_ports N260] [get_ports N261]      \
[get_ports N267] [get_ports N268]]  -to [list [get_ports N388] [get_ports N389] [get_ports N390] [get_ports N391] \
[get_ports N418] [get_ports N419] [get_ports N420] [get_ports N421] [get_ports \
N422] [get_ports N423] [get_ports N446] [get_ports N447] [get_ports N448]      \
[get_ports N449] [get_ports N450] [get_ports N767] [get_ports N768] [get_ports \
N850] [get_ports N863] [get_ports N864] [get_ports N865] [get_ports N866]      \
[get_ports N874] [get_ports N878] [get_ports N879] [get_ports N880]]
