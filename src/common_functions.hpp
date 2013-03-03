#ifndef COMPDEWD_COMMON_FUNCTIONS
#define COMPDEWD_COMMON_FUNCTIONS

#include "globals.hpp"

namespace common_functions
{
    int get_num_lines(FILE_CONTENT);
    int get_length_longest_field(FILE_CONTENT);
    int convert_to_int(CHARSTR);
    float convert_to_float(CHARSTR);
    CHARSTR convert_to_charstr(float);
    void fill(CHARSTR &, LENGTH, char);
    void wait_for_user();
}

#endif
