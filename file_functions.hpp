#ifndef COMPDEWD_FILE_FUNCTIONS
#define COMPDEWD_FILE_FUNCTIONS

#include "globals.hpp"

namespace file_functions
{
	RETURN_CODE get_file_size(FILENAME, FILE_SIZE);
    RETURN_CODE get_file_content(FILENAME, FILE_CONTENT &);
    RETURN_CODE write_array(FILENAME, lines *);
    RETURN_CODE write_averaged_new_records
    (
         FILENAME
        ,std::vector<averaged_new_record *> *
    );
}

#endif
