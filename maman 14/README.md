# C-Final-Project

## Project directory tree Structure :

-
    ```
    .
    ├── include                 # Header files
    ├── src                     # C Source files
    │   ├── macro.c             # File that spread all the macros into a new file
    │   ├── input.c             # File to handle the given input
    │   ├── data.c              # File with API to all data types
    │   ├── operands.c          # File that identify different operands in commands word
    │   ├── symbol.c            # File that store all the symbols of sourcefile
    │   ├── commands.c          # File that identify the memory_word structure
    │   ├── handleFiles.c       # File that write the lists content into the output files
    │   └── main.c              # The program main file
    ├── bin                     # Program binaries
    ├── tests                   # Example tests with output
    │   ├── test1               # Example program from project instruction
    │   └── test2               # Test with macro definitions
    └── README.md
    ```
- Note: Remove ```clean``` command from Makefile to keep\
    The Binary files inside 'bin' directory\
    incase you need it for debug purposes.
