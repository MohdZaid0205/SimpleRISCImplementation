#ifndef ASSEMBLER_LOGGING_H
#define ASSEMBLER_LOGGING_H

#include "pch.h"

// [ SCOPE ] -------------------------------------------------------------------+
// This file contains ways for showing elaborate exceptions and its trace in	|
// order to provide with better and more workable exceptions for assembler.		|
// -----------------------------------------------------------------------------+

// Logger Level Option(s) contains all supported options that that can be used
// selectively to create custom logging level as per your requirement by using
// bitwise OR operations such as (LEVEL_LOG | LEVEL_INF) shows LOGs and INFOs
typedef enum LOGGER_LEVEL_OPTION {
	LEVEL_NO  = 0b000000,		// NONE or NO		are allowed to pass.
	LEVEL_LOG = 0b000001,		// LOGs				are allowed to pass.
	LEVEL_INF = 0b000010,		// INFORMATIONs		are allowed to pass.
	LEVEL_DBG = 0b000100,		// DEBUGs			are allowed to pass.
	LEVEL_WRN = 0b001000,		// WARNINGs			are allowed to pass.
	LEVEL_ERR = 0b010000,		// ERRORs			are allowed to pass.
	LEVEL_FAT = 0b100000,		// FATALs			are allowed to pass.
	LEVEL_ALL = 0b111111,		// ALL				are allowed to pass.
} LogLevel, TraceLevel;

// [ INFO ] --------------------------------------------------------------------+
// In order to default to some output level if level has not been defined		|
// if build into DEBUG mode then set debug to ALL levels otherwise ERRORs		|
// -----------------------------------------------------------------------------+

#ifndef LOGGING_LEVEL
	#ifdef DEBUG
		#define LOGGING_LEVEL LEVEL_ALL
	#else
		#define LOGGING_LEVEL LEVEL_WRN | LEVEL_ERR | LEVEL_FAT
	#endif
#endif

// [ INFO ] --------------------------------------------------------------------+
// helper macro definitions for dealing with ANSI escape sequence for colors if	|
// no color mode is selected. in order to disable this coloring mechanism pass	|
// flag -DLOGGING_DISABLE_COLORING to compiler									|
// -----------------------------------------------------------------------------+

#ifndef LOGGING_DISABLE_COLORING
	// define macros to create string that contains ansi sequence for colors
	#define COLORED_FOREGROUND(r, g, b) "\033[38;2;"#r";"#g";"#b"m"
	#define COLORED_BACKGROUND(r, g, b) "\033[48;2;"#r";"#g";"#b"m"
	#define DEFAULT_FOREGROUND "\033[39m"
	#define DEFAULT_BACKGROUND "\033[49m"
#else
	// define colors macros as empty so that no ansi is used at runtime
	#define COLORED_FOREGROUND(r, g, b) ""
	#define COLORED_BACKGROUND(r, g, b) ""
	#define DEFAULT_FOREGROUND ""
	#define DEFAULT_BACKGROUND ""
#endif

#ifndef CLIENT_COLORS
	// define all foreground colors that is to be used for corresponding level
	#define LOGGER_COLOR_LOG_F COLORED_FOREGROUND(127, 127, 127)
	#define LOGGER_COLOR_INF_F COLORED_FOREGROUND(127, 127, 255)
	#define LOGGER_COLOR_DBG_F COLORED_FOREGROUND(127, 255, 127)
	#define LOGGER_COLOR_WRN_F COLORED_FOREGROUND(255, 255, 127)
	#define LOGGER_COLOR_ERR_F COLORED_FOREGROUND(255, 127, 127)
	#define LOGGER_COLOR_FAT_F COLORED_FOREGROUND(255, 127, 000)

	// define all background colors that is to be used for corresponding level
	#define LOGGER_COLOR_LOG_B COLORED_BACKGROUND(127, 127, 127)
	#define LOGGER_COLOR_INF_B COLORED_BACKGROUND(127, 127, 255)
	#define LOGGER_COLOR_DBG_B COLORED_BACKGROUND(127, 255, 127)
	#define LOGGER_COLOR_WRN_B COLORED_BACKGROUND(255, 255, 127)
	#define LOGGER_COLOR_ERR_B COLORED_BACKGROUND(255, 127, 127)
	#define LOGGER_COLOR_FAT_B COLORED_BACKGROUND(255, 127, 000)
#endif

// A helper method to get foreground color associated with LOGGER_LEVEL_OPTION
// in order to get LEVEL_XXX's color as defined by default ot as defined by usr
const char* __get_associated_foreground_for(enum LOGGER_LEVEL_OPTION level);

// A helper method to get background color associated with LOGGER_LEVEL_OPTION
// in order to get LEVEL_XXX's color as defined by default ot as defined by usr
const char* __get_associated_background_for(enum LOGGER_LEVEL_OPTION level);

// Underlying method to display onto selected stream based on log level that
// has been selected at compile time in order to deal with size and instruction
// limitations, this is supposed to work with output files as it writes to
// any specified stream.
// 
// lfprintf defines:
//		- %[ : start background highlight
//		- %] : stops nackground highlight
//		- %( : start foreground highlight
//		- %) : stops foreground highlight
// 
// NOTE: opening and closing stream is not job of this method, if user passes
//       any file as an input, they are required to make sure that it is open
int lfprintf(LogLevel level, FILE* stream, const char* format, ...);

#endif