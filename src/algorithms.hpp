#ifndef COMPDEWD_ALGORITHMS
#define COMPDEWD_ALGORITHMS

#include "globals.hpp"

namespace algorithms
{
    POSITION find(CONST_CHARSTR, POSITION, POSITION, CONST_CHARSTR);
    POSITION find(CORE_TYPES *
                 ,POSITION
                 ,POSITION
                 ,CONST_CHARSTR);
    POSITION find
    (
         char ***
        ,ARRAY_INDEX
        ,ARRAY_INDEX
        ,ARRAY_INDEX
        ,CONST_CHARSTR
    );
    POSITION find_first_alphanumeric
    (
         CONST_CHARSTR
        ,POSITION
        ,POSITION
    );
    bool compare(CONST_CHARSTR, CONST_CHARSTR);
    bool compare(const char, const char);
    bool compare(float, float);
    bool isdigit(char);
    float round(float, int);
}

#endif
