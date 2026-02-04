#ifndef ARGUMENT_HANDLERS_H
#define ARGUMENT_HANDLERS_H

typedef enum {
    PARSE_OK            = 0,
    PARSE_UNKNOWN_FLAG  = 1,
    PARSE_MISSING_VALUE = 2,
    PARSE_BAD_VALUE     = 3,
    PARSE_HELP_REQEST   = 4,
    PARSE_DOUBLE_VALUE  = 5,
    PARSE_FILE_ERROR    = 6
} parse_return_e;

parse_return_e help_handler(params_t *param, const char *value);
parse_return_e port_handler(params_t *param, const char *value);
parse_return_e address_handler(params_t *param, const char *value);
parse_return_e file_handler(params_t *param, const char *value);
parse_return_e scan_handler(params_t *param, const char *value);
parse_return_e speedup_handler(params_t *param, const char *value);

#endif /* ARGUMENT_HANDLERS_H */