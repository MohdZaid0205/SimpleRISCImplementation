#ifndef ASSEMBLER_ARGPARSE_H
#define ASSEMBLER_ARGPARSE_H

#include "pch.h"

// [ INFO ] --------------------------------------------------------------------+
// Argument parser for the assembler. This module is responsible for abstracting|
// the command line arguments (argv/argc) into a structured format that the     |
// main assembler loop can consume easily.                                      |
//                                                                              |
// It handles identifying flags (short `-o` or long `--output`), mapping them   |
// to their enumerated types, and associating them with their raw string values.|
// -----------------------------------------------------------------------------+

// [ IDEA ] --------------------------------------------------------------------+
// The main loop shouldn't care about string comparison for flags. It should    |
// operate on a stream of "Argument Objects". We define a structure that holds  |
// both the type of the argument (what it is) and the value (the data).         |
//                                                                              |
// We use a Factory Pattern approach here:                                      |
//      argparse_argument_input("file.s")   -> returns{ ARGUMENT_INP, "file.s" }|
//      argparse_argument_output("out.bin") -> returns{ ARGUMENT_OUT, "out.bin"}|
// -----------------------------------------------------------------------------+

// [ CHANGE_LOG ] --------------------------------------------------------------+
// ---------------------------(26-12-2025 08:30)--------------------------------+
// -> Initial definition of argument types and structures.                      |
// -> Added constructors for specific argument types to ensure type safety      |
//    when creating argument structs manually.                                  |
// -----------------------------------------------------------------------------+

// enum ASSEMBLER_ARGUMENT_TYPE aka ArgumentType & FlagType
// Defines the specific role of a command line argument.
//
// -----------------+-----------------------------------------------------------+
// ARGUMENT_INP     | The input source file (.asm, .s). If no flag is provided  |
//                  | before a string, it is usually assumed to be this.        |
// ARGUMENT_OUT     | Destination file. Corresponds to -o or --output.          |
// ARGUMENT_FMT     | Output format (binary, executable, object). -f or --fmt.  |
// ARGUMENT_MAP     | Architecture mapping/layout file. -m or --map.            |
// ARGUMENT_HLP     | Request for help/usage text. -h or --help.                |
// -----------------+-----------------------------------------------------------+
typedef enum ASSEMBLER_ARGUMENT_TYPE{
    ARGUMENT_INP,                   // Input file path (source)
    ARGUMENT_OUT,                   // Output file path (destination)
    ARGUMENT_FMT,                   // Format specifier (bin/exe/obj)
    ARGUMENT_MAP,                   // Memory mapping/Arch specifier
    ARGUMENT_HLP,                   // Help / Usage info
    ARGUMENT_NONE,                  // no type matched with argument
} ArgumentType, FlagType;

// struct ASSEMBLER_ARGUMENT aka AssemblerArgument & Arg
// Represents a single parsed command line entity. 
//
// [ NOTE ] --------------------------------------------------------------------+
// The `value` pointer usually points to the actual memory inside `argv[]`.     |
// We do not copy the string, so we do not own the memory. Do not free `value`. |
// -----------------------------------------------------------------------------+
typedef struct ASSEMBLER_ARGUMENT{
    enum ASSEMBLER_ARGUMENT_TYPE type;  // The category of this argument
    const char* value;                  // The string data associated (if any)
} AssemblerArgument, Arg;

// argparse_get_type_for
// Takes a raw string (like "-o", "--help", or "filename.s") and determines
// which enum type it corresponds to.
//
// [ NOTE ] --------------------------------------------------------------------+
// This function needs to be robust. It should handle both short flags (-) and  |
// long flags (--). If the string doesn't look like a flag (doesn't start with  |
// hyphen), it might default to ARGUMENT_INP or return an error/unknown state   |
// depending on how strict we want the parser to be.                            |
// -----------------------------------------------------------------------------+
enum ASSEMBLER_ARGUMENT_TYPE argparse_get_type_for(const char* flag);

// argparse_argument_input
// Constructor for an Input Argument. Creates a struct configured as a source file 
// input. By default it is assumed that file extension contains .s or .asm in it.
struct ASSEMBLER_ARGUMENT argparse_argument_input(const char* value);

// argparse_argument_output
// Constructor for an Output Argument.
// Creates a struct configured as a destination file output.
//
// [ INFO ] --------------------------------------------------------------------+
// Used when the parser encounters a -o flag and grabs the next token.          |
// -----------------------------------------------------------------------------+
struct ASSEMBLER_ARGUMENT argparse_argument_output(const char* value);

// argparse_argument_format
// Constructor for a Format Argument. Specifies the output binary format (flat 
// binary, elf, etc).
//
// [ TODO ] --------------------------------------------------------------------+
// We might need to validate if 'value' is actually a supported format here,    |
// or leave that validation for the main logic? For now, we just store it.      |
// -----------------------------------------------------------------------------+
struct ASSEMBLER_ARGUMENT argparse_argument_format(const char* value);

// argparse_argument_mapping
// Constructor for a Mapping Argument. Used for passing custom architecture 
// definitions json maps. or any supported maps.
struct ASSEMBLER_ARGUMENT argparse_argument_mapping(const char* value);

// argparse_argument_help
// Constructor for a Help Argument.The 'value' here is typically NULL or empty, 
// as the flag itself is the msg, but kept as const char* for structural 
// consistency with other constructors.
//
// [ INFO ] --------------------------------------------------------------------+
// If -h or --help flag is present, no other falg is allowed to run             |
// -----------------------------------------------------------------------------+
struct ASSEMBLER_ARGUMENT argparse_argument_help(const char* value);

#endif
