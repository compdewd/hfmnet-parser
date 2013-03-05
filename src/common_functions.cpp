
#include "globals.hpp"

using namespace std;

int common_functions::get_num_lines(FILE_CONTENT content)
{
    AMOUNT num_lines = 0;
    LENGTH len_content = strlen(content);
    LENGTH len_end_of_line = strlen(end_of_line);

    for (POSITION i = 0; i < len_content; ++i)
    {
        char *buffer = new char [len_end_of_line + 1];
        strncpy(buffer, &(content[i]), len_end_of_line);
        buffer[len_end_of_line] = 0x00;
        if (algorithms::compare(buffer, end_of_line) == true)
        {
            ++num_lines;
        }
        delete [] buffer;
    }

    return num_lines;
}

int common_functions::get_length_longest_field(FILE_CONTENT content)
{
    LENGTH len_content = strlen(content);

    POSITION pos_end_of_line_1 = algorithms::find
                                             (
                                                  content
                                                 ,0
                                                 ,len_content
                                                 ,end_of_line
                                             );
    POSITION pos_delimiter_1 = algorithms::find
                                           (
                                                content
                                               ,0
                                               ,len_content
                                               ,field_delimiter
                                           );
    LENGTH len_longest_field = pos_delimiter_1 - 0;
    POSITION pos_delimiter_2 = algorithms::find
                                           (
                                                content
                                               ,pos_delimiter_1 + 1
                                               ,len_content
                                               ,field_delimiter
                                           );
    if (pos_delimiter_2 > pos_end_of_line_1)
    {
        LENGTH len_current_field = pos_end_of_line_1 - pos_delimiter_1 + 1;
        if (len_current_field > len_longest_field)
        {
            len_longest_field = len_current_field;
        }
    }
    else
    {
        LENGTH len_current_field = pos_delimiter_2 - pos_delimiter_1 + 1;
        if (len_current_field > len_longest_field)
        {
            len_longest_field = len_current_field;
        }
    }

    while (pos_delimiter_2 != -1)
    {
        pos_delimiter_1 = pos_delimiter_2;
        pos_delimiter_2 = algorithms::find
                                      (
                                           content
                                          ,pos_delimiter_1 + 1
                                          ,len_content
                                          ,field_delimiter
                                      );
        if (pos_delimiter_2 > pos_end_of_line_1)
        {
            LENGTH len_current_field = pos_end_of_line_1 - pos_delimiter_1 + 1;
            if (len_current_field > len_longest_field)
            {
                len_longest_field = len_current_field;
            }
        }
        else
        {
            LENGTH len_current_field = pos_delimiter_2 - pos_delimiter_1 + 1;
            if (len_current_field > len_longest_field)
            {
                len_longest_field = len_current_field;
            }
        }
    }

    LENGTH len_current_field = len_content - pos_delimiter_1 + 1;
    if (len_current_field > len_longest_field)
    {
        len_longest_field = len_current_field;
    }

    return len_longest_field;
}

int common_functions::convert_to_int(CHARSTR input)
{
    return atoi(input);
}

float common_functions::convert_to_float(CHARSTR input)
{
    return static_cast<float>(atof(input));
}

CHARSTR common_functions::convert_to_charstr(float input)
{
    stringstream strstream;
    strstream << input;
    string str = strstream.str();
    LENGTH len_str = str.length();
    char *charstr = new char [len_str + 1];
    for (POSITION i = 0; i < len_str; ++i)
    {
        charstr[i] = str[i];
    }
    charstr[len_str] = '\0';
    return charstr;
}

CHARSTR common_functions::convert_to_charstr(unsigned int input)
{
    stringstream strstream;
    strstream << input;
    string str = strstream.str();
    LENGTH len_str = str.length();
    char *charstr = new char [len_str + 1];
    for (POSITION i = 0; i < len_str; ++i)
    {
        charstr[i] = str[i];
    }
    charstr[len_str] = '\0';
    return charstr;
}

void common_functions::fill(CHARSTR &destination, LENGTH length, char filler)
{
    for (POSITION i = 0; i < length; ++i)
    {
        destination[i] = filler;
    }
}

void common_functions::wait_for_user()
{
    cin.get();
}
