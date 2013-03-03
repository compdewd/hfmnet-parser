
#include "globals.hpp"

using namespace std;

void arrayitize
(
     CONST_CHARSTR input
    ,file_content_info *info
    ,char ***&input_array
)
{
    ARRAY_INDEX row = 0;
    ARRAY_INDEX column = 0;
    LENGTH len_field = 0;
    POSITION pos_delimiter_1 = 0;
    POSITION pos_delimiter_2 = 0;
    POSITION pos_end_of_line_1 = 0;

    for (; column < info->columns; ++column)
    {
        if (column != info->columns - 1)
        {
            pos_delimiter_2 =
                algorithms::find
                (
                     input
                    ,pos_delimiter_1
                    ,info->length
                    ,field_delimiter
                );
        }
        else
        {
            pos_delimiter_2 =
                algorithms::find
                (
                     input
                    ,pos_delimiter_1
                    ,info->length
                    ,end_of_line
                );
        }
        len_field = pos_delimiter_2 - pos_delimiter_1;
        strncpy
        (
             input_array[row][column]
            ,&(input[pos_delimiter_1])
            ,len_field
        );
        input_array[row][column][len_field] = '\0';
        pos_delimiter_1 = pos_delimiter_2 + 1;
    }

    for (row = 1; row < info->rows; ++row)
    {
        for (column = 0; column < info->columns; ++column)
        {
            if (column == 0)
            {
                pos_delimiter_1 =
                    algorithms::find_first_alphanumeric
                    (
                         input
                        ,pos_delimiter_2
                        ,info->length
                    );
                pos_delimiter_2 =
                    algorithms::find
                    (
                         input
                        ,pos_delimiter_1
                        ,info->length
                        ,field_delimiter
                    );
            }
            else if (column == info->columns - 1)
            {
                pos_delimiter_1 = pos_delimiter_2 + 1;
                pos_delimiter_2 =
                    algorithms::find
                    (
                         input
                        ,pos_delimiter_1
                        ,info->length
                        ,end_of_line
                    );
            }
            else
            {
                pos_delimiter_1 = pos_delimiter_2 + 1;
                pos_delimiter_2 =
                    algorithms::find
                    (
                         input
                        ,pos_delimiter_1
                        ,info->length
                        ,field_delimiter
                    );
            }
            len_field = pos_delimiter_2 - pos_delimiter_1;
            input_array[row][column] = new char [len_field + 1];
            strncpy
            (
                 input_array[row][column]
                ,&(input[pos_delimiter_1])
                ,len_field
            );
            input_array[row][column][len_field] = '\0';
        }
    }
}
