#include "messenger.h"
#include <stdio.h>
#include <stdarg.h>

// debug.h implementation
#define BUFFER_LENGTH 2048
#define BUFFER_LENGTH_FINAL BUFFER_LENGTH + 128


// debug_log function
int debug_log (DebugSeverity severity, const char *file, const char *func, const int line, const char *format, ...) {

    static char bufferString1[BUFFER_LENGTH]; // bufferstring preallocated for stack storage
    static char bufferString2[BUFFER_LENGTH_FINAL]; // add extra room for prefix
    va_list args;
    va_start (args, format);

    // messege severity prefixes
    const char *messegeSeverity[DEBUG_TYPE_MAX] = {
        "\033[1;31m[FATAL]: \033[0m",      // fatal
        "\033[1;33m[ERROR]: \033[0m",      // error
        "\033[1,56m[WARNING]: \033[0m",    // warning
	    "\033[1;96m[VALIDATION]: \033[0m", // validation
        "\033[1;32m[INFO]: \033[0m",       // info
        "\033[1;35m[DEBUG]: \033[0m"       // debug
    };

    // print error messege
    vsnprintf (bufferString1, BUFFER_LENGTH, format, args);

    uint16_t strlen = snprintf (
        bufferString2,              // output
        BUFFER_LENGTH,              // max length
        ">>> %s:%s->%i\n\t%s%s\n",  // format string
        file,                       // filename
        func,                       // function name
        line,                       // line number
        messegeSeverity[severity],  // messege severity prefix
        bufferString1               // error messege
    );

    if (strlen >= BUFFER_LENGTH_FINAL) {
        log_warning ("Debug called on line %i:%s overflowed buffer.", line, file);
    }

    // TODO log to file
    printf ("%s", bufferString2);
    va_end (args);

    return 0;
    
}
