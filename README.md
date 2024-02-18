# Predicate Logic Compiler
This is a predicate logic compiler, which has been built for the lecture Compilerbau at the DHBW. It parses a file containing a predicate logic formula, optimizes it into negation normal form (NNF) and returns it in a file.

## Compile using make
You will need `make`, `flex`, `bison` and `gcc` to be able to compile. Run the following command to compile: 
```shell
make all
```

## Usage
First compile using the command above, then use the following command to compile a .pl1 file:
```shell
./pl1c <input_file> <output_file>
```
Note that `<output_file>` is optional, if it is not defined the default `output.pl1` will be used.

Example .pl1 files can be found in the `examples` folder.

For further make commands run: 
```shell
make help
```