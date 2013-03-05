
#include "globals.hpp"

using namespace std;

POSITION algorithms::find(CONST_CHARSTR haystack
                         ,POSITION pos_start
                         ,POSITION pos_end
                         ,CONST_CHARSTR needle)
{
    POSITION pos_needle = 0;
    POSITION pos_haystack = pos_start;
    POSITION pos_found_string = NOT_FOUND;
    LENGTH len_needle = strlen(needle);

    while (pos_haystack <= pos_end)
    {
        if (pos_needle < len_needle)
        {
            if (needle[pos_needle] == haystack[pos_haystack])
            {
                if (pos_found_string == NOT_FOUND)
                {
                    pos_found_string = pos_haystack;
                }
                ++pos_needle;
            }
            else
            {
                pos_found_string = NOT_FOUND;
                pos_needle = 0;
            }
        }
        else
        {
            break;
        }
        ++pos_haystack;
    }

    return pos_found_string;
}

POSITION algorithms::find(CORE_TYPES *haystack
                         ,POSITION pos_start
                         ,POSITION pos_end
                         ,CONST_CHARSTR needle)
{
    POSITION pos_haystack = pos_start;
    POSITION pos_found_string = NOT_FOUND;
    LENGTH len_needle = strlen(needle);

    while (pos_haystack <= pos_end)
    {
        if (strncmp(haystack->at(pos_haystack), needle, len_needle) == 0)
        {
            if (strlen(haystack->at(pos_haystack)) == len_needle)
            {
                pos_found_string = pos_haystack;
                break;
            }
        }
        else
        {
            ++pos_haystack;
        }
    }

    return pos_found_string;
}

POSITION algorithms::find
(
     char ***haystack
    ,ARRAY_INDEX pos_start
    ,ARRAY_INDEX pos_end
    ,ARRAY_INDEX column
    ,CONST_CHARSTR needle
)
{
    POSITION pos_haystack = pos_start;
    POSITION row_found = NOT_FOUND;
    LENGTH len_needle = strlen(needle);

    while (pos_haystack <= pos_end)
    {
        if (strncmp(haystack[pos_haystack][column], needle, len_needle) == 0)
        {
            if (strlen(haystack[pos_haystack][column]) == len_needle)
            {
                row_found = pos_haystack;
                break;
            }
        }
        else
        {
            ++pos_haystack;
        }
    }

    return row_found;
}

POSITION algorithms::find_first_alphanumeric
(
     CONST_CHARSTR haystack
    ,POSITION pos_start
    ,POSITION pos_end
)
{
    POSITION pos_found = NOT_FOUND;
    for (POSITION i = pos_start; i < pos_end; ++i)
    {
        if
        (
            (
                (haystack[i] >= 'A' && haystack[i] <= 'Z')
                ||
                (haystack[i] >= 'a' && haystack[i] <= 'z')
            )
            ||
            (
                (haystack[i] >= '0' && haystack[i] <= '9')
            )
            ==
            true
        )
        {
            pos_found = i;
            break;
        }
    }
    return pos_found;
}

bool algorithms::compare(CONST_CHARSTR input_1, CONST_CHARSTR input_2)
{
    LENGTH len_input_1 = strlen(input_1);
    LENGTH len_input_2 = strlen(input_2);
    if (strncmp(input_1, input_2, len_input_1) == 0)
    {
        if (len_input_1 == len_input_2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else return false;
}

bool algorithms::compare(const char input_1, const char input_2)
{
    LENGTH len_input_1 = strlen(&input_1);
    LENGTH len_input_2 = strlen(&input_2);
    if (strncmp(&input_1, &input_2, len_input_1) == 0)
    {
        if (len_input_1 == len_input_2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else return false;
}

bool algorithms::compare(float input_1, float input_2)
{
    if (input_1 == input_2)
        return true;
    else
        return false;
}

bool algorithms::isdigit(char input)
{
    if (input >= '0' && input <= '9')
        return true;
    else
        return false;
}

float algorithms::round(float input, int decimal_places)
{
    int power_of_ten = 1;
	for (int i = 0; i < decimal_places; ++i)
	{
		power_of_ten *= 10;
	}
	int integer = static_cast<int>(floor(input * power_of_ten + 0.5));
	float new_float = static_cast<float>(integer) / power_of_ten;

	return new_float;
}
