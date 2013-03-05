#ifndef COMPDEWD_STRUCTURES
#define COMPDEWD_STRUCTURES

#include "globals.hpp"

// file_content
struct file_content
{
public:
	FILE_CONTENT content;

	void cleanUp()
	{
        delete [] content;
        content = 0;
    }
};

// file_content_info
struct file_content_info
{
public:
	LENGTH length;
	AMOUNT rows;
	AMOUNT columns;
	LENGTH longest_field;
};

// file_content_array
struct file_content_array
{
public:
	FILE_CONTENT_ARRAY content_array;

	void cleanUp(int rows, int columns)
	{
        for (int row = 0; row < rows; ++row)
        {
            for (int column = 0; column < columns; ++column)
            {
                delete [] content_array[column];
                content_array[column] = 0;
            }
            delete [] content_array[row];
            content_array[row] = 0;
        }
    }
};

// file
struct file
{
public:
	file_content_info fci;
	file_content fc;
	file_content_array fca;
	CHARSTR filename;

	void cleanUp()
	{
	    fc.cleanUp();
        delete [] filename;
        filename = 0;
    }
};

// lines
struct lines
{
public:
	ASSEMBLED_LINES lines;
	AMOUNT rows;
	AMOUNT columns;

	void cleanUp()
	{
        for (ARRAY_INDEX row = 0; row < rows; ++row)
        {
            for (ARRAY_INDEX column = 0; column < columns; ++column)
            {
                delete [] lines[column];
                lines[column] = 0;
            }
            delete [] lines[row];
            lines[row] = 0;
        }
    }
};

// performance_values
struct performance_values
{
    std::vector<AMOUNT> points_per_day;
    std::vector<AMOUNT> time_per_frame;
};

// distinct_new_record
struct distinct_new_record
{
    PROJECT project;
    SLOT_NAME slot_name;
    CORE_TYPE core_type;
    CORE_VERSION core_version;
    USERNAME username;
    performance_values project_performance_values;
    std::string date;
};

// averaged_new_record
struct averaged_new_record
{
    PROJECT project;
    SLOT_NAME slot_name;
    CORE_TYPE core_type;
    CORE_VERSION core_version;
    USERNAME username;
    AMOUNT averaged_points_per_day;
    AMOUNT averaged_time_per_frame;
    std::string date;
};

#endif
