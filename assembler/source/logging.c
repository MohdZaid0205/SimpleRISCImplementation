#include "logging.h"

const char* __get_associated_foreground_for(enum LOGGER_LEVEL_OPTION level) {
	switch (level) {
		case LEVEL_LOG: return LOGGER_COLOR_LOG_F;
		case LEVEL_INF: return LOGGER_COLOR_INF_F;
		case LEVEL_DBG: return LOGGER_COLOR_DBG_F;
		case LEVEL_WRN: return LOGGER_COLOR_WRN_F;
		case LEVEL_ERR: return LOGGER_COLOR_ERR_F;
		case LEVEL_FAT: return LOGGER_COLOR_FAT_F;
		default:		return DEFAULT_FOREGROUND;
	}
}

const char* __get_associated_background_for(enum LOGGER_LEVEL_OPTION level) {
	switch (level) {
		case LEVEL_LOG: return LOGGER_COLOR_LOG_B;
		case LEVEL_INF: return LOGGER_COLOR_INF_B;
		case LEVEL_DBG: return LOGGER_COLOR_DBG_B;
		case LEVEL_WRN: return LOGGER_COLOR_WRN_B;
		case LEVEL_ERR: return LOGGER_COLOR_ERR_B;
		case LEVEL_FAT: return LOGGER_COLOR_FAT_B;
		default:		return DEFAULT_BACKGROUND;
	}
}


int lfprintf(LogLevel level, FILE* stream, const char* format, ...) {

    if (!(level & LOGGING_LEVEL)) return 0;

    size_t final_len = 0;
    const char* ptr = format;

    while (*ptr) {
        
        if (*ptr == '%' && *(ptr + 1)) {
            const char* replacement = NULL;

            switch (*(ptr + 1)) {
                case '[': replacement = __get_associated_background_for(level); break;
                case ']': replacement = DEFAULT_BACKGROUND; break;
                case '(': replacement = __get_associated_foreground_for(level); break;
                case ')': replacement = DEFAULT_FOREGROUND; break;
            }

            if (replacement) {
                final_len += strlen(replacement);
                ptr += 2; continue;
            }
        }

        final_len++;
        ptr++;
    }

    char* updated = (char*) malloc(final_len + 1);    
    if (!updated) return -1;
    
    char* dest = updated;
    ptr = format;

    while (*ptr) {
        if (*ptr == '%' && *(ptr + 1)) {
            const char* replacement = NULL;

            switch (*(ptr + 1)) {
                case '[': replacement = __get_associated_background_for(level); break;
                case ']': replacement = DEFAULT_BACKGROUND; break;
                case '(': replacement = __get_associated_foreground_for(level); break;
                case ')': replacement = DEFAULT_FOREGROUND; break;
            }

            if (replacement) {
                int len = strlen(replacement);
                memcpy(dest, replacement, len);
                dest += len; ptr += 2;
                continue;
            }
        }

        *dest++ = *ptr++;
    }
    *dest = '\0';

    va_list args;
    va_start(args, format);
    int result = vfprintf(stream, updated, args);
    va_end(args);

    free(updated);

    return result;
}