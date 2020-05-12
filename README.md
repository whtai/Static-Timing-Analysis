# Static Timing Analysis
## Descriptions
This program aims to efficiently identify true paths in a combinational logic circuit whose path delays exceed a predefined constraint. A true path is defined as a path where a change of value at the input (e.g., from  0 to 1) could propagate to the output. Our approach is based on the exact criterion as defined in [[1]](#1), which guarantees exactness, meaning that it will claim every true path to be true, and every false path to be false.

Identifying true paths in a circuit is critical and central to static timing analysis. The longest true path contributes to the critical path delay and thus determines whether the timing constraints are met for a design. For a more complete description of the problem, visit the [contest website](https://cad-contest-2016.el.cycu.edu.tw/Problem_D/default.html).

## Compilation
The program can be built using ```make```. There is also a pre-compiled executable named ```cadb105``` in the repository.

## Usage
```./cadb105 <case_name> <timing_constraint> <slack_constraint>```
- ```case_name``` is the name of the directory containing the input files (a Verilog gate-level netlist and its associated Verilog model).
- ```timing_constraint``` and ```slack_constraint``` are the predefined constraints for that specific testcase given by the contest. 

We can generate true path sets for the five public benchmarks with the following commands:
```
./cadb105 case1 45 4
./cadb105 case2 43 10
./cadb105 case3 31 6
./cadb105 case4 45 6
./cadb105 case5 47 10
```
Example output files for the five public benchmarks are provided in the ```./outputs``` directory.

## References
<a id="1">[1]</a> 
R. Peset Llopis. 1994. Exact path sensitization in timing analysis. In Proceedings of the conference on European design automation (EURO-DAC ’94). IEEE Computer Society Press, Washington, DC, USA, 380–385.
