###################################################################

# Created by write_sdc on Thu Mar 24 09:02:14 2016

###################################################################
set sdc_version 1.8

set_units -time ns -resistance kOhm -capacitance pF -voltage V -current mA
set_max_delay 47  -from [list [get_ports I0] [get_ports I1] [get_ports I2] [get_ports I3]       \
[get_ports I4] [get_ports I5] [get_ports I6] [get_ports I7] [get_ports I8]     \
[get_ports I9] [get_ports I10] [get_ports I11] [get_ports I12] [get_ports I13] \
[get_ports I14] [get_ports I15] [get_ports I16] [get_ports I17] [get_ports     \
I18] [get_ports I19] [get_ports I20] [get_ports I21] [get_ports I22]           \
[get_ports I23] [get_ports I24] [get_ports I25] [get_ports I26] [get_ports     \
I27] [get_ports I28] [get_ports I29] [get_ports I30] [get_ports I31]           \
[get_ports I32] [get_ports I33] [get_ports I34] [get_ports I35] [get_ports     \
I36] [get_ports I37] [get_ports I38] [get_ports I39] [get_ports I40]           \
[get_ports I41] [get_ports I42] [get_ports I43] [get_ports I44] [get_ports     \
I45] [get_ports I46] [get_ports I47] [get_ports I48] [get_ports I49]           \
[get_ports I50] [get_ports I51] [get_ports I52] [get_ports I53] [get_ports     \
I54] [get_ports I55] [get_ports I56] [get_ports I57] [get_ports I58]           \
[get_ports I59] [get_ports I60] [get_ports I61] [get_ports I62] [get_ports     \
I63]]  -to [list [get_ports O0] [get_ports O1] [get_ports O2] [get_ports O3]         \
[get_ports O4] [get_ports O5] [get_ports O6] [get_ports O7] [get_ports O8]     \
[get_ports O9] [get_ports O10] [get_ports O11] [get_ports O12] [get_ports O13] \
[get_ports O14] [get_ports O15] [get_ports O16] [get_ports O17] [get_ports     \
O18] [get_ports O19] [get_ports O20] [get_ports O21] [get_ports O22]           \
[get_ports O23] [get_ports O24] [get_ports O25] [get_ports O26] [get_ports     \
O27] [get_ports O28] [get_ports O29] [get_ports O30] [get_ports O31]]
