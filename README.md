## Predicate Logic Compiler
This is a predicate logic compiler, which has been built for the lecture Compilerbau at the DHBW.

## Compile using make
You will need `make`, `flex`, `bison` and `gcc` to be able to compile. Run the following command to compile: 
```shell
make all
```

## Usage
First compile using the command above, then use the following command to compile a .pl1 file:
```shell
./pl1c <input_file> > <output_file>
```
Example .pl1 files can be found in the `examples` folder.
