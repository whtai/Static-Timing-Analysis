# Static Timing Analysis
## Descriptions
This program, being the Second Prize solution to the 2016 ICCAD (Integrated Circuits Computer Aided Design) Contest Problem D, aims to efficiently identify true paths with delay larger than a predefined constraint in a combinational logic circuit. A true path is defined as a path where a change of value at the input (e.g., from  0 to 1) could propagate to the output. Those overly long true paths are the paths that could compromise the timing performance of a circuit. Evaluation in the contest was based on both correctness and runtime.

## Compilation
The program can be built with ```make```. There is also a pre-compiled executable named ```cadb105``` in the repository.

## Usage
```
./cadb105 [case_name] [timing_constraint] [slack_constraint]
```
