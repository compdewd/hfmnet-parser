#ifndef COMPDEWD_PARSER_GLOBALS
#define COMPDEWD_PARSER_GLOBALS

// Includes
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

// Defines
#define PROJECTINFO 0
#define WUHISTORY 1
#define SLOTNAMES 2
#define NUM_FILES 3
#define DATE_LENGTH 10

// Typedefs
typedef unsigned int AMOUNT;
typedef unsigned int PROJECT;
typedef unsigned int AVERAGE_TPF;
typedef unsigned int AVERAGE_PPD;
typedef unsigned int ARRAY_INDEX;
typedef signed int NUMBER;
typedef signed int LENGTH;
typedef signed int POSITION;
typedef signed int * FILE_SIZE;
typedef float CORE_VERSION;
typedef char * FILE_CONTENT;
typedef char * CHARSTR;
typedef char * CORE_TYPE;
typedef char * SLOT_NAME;
typedef char * USERNAME;
typedef char * CHIPSET_AND_MODEL;
typedef char *** FILE_CONTENT_ARRAY;
typedef char *** ASSEMBLED_LINES;
typedef const char * FILENAME;
typedef const char * CONST_CHARSTR;
typedef std::pair<AVERAGE_TPF,AVERAGE_PPD> AVERAGED_TPF_AND_PPD;
typedef std::pair<SLOT_NAME,CORE_VERSION> SLOT_NAME_AND_CORE_VERSION;
typedef std::vector<CHARSTR> SUB_LINES_TO_ASSEMBLE;
typedef std::vector<SUB_LINES_TO_ASSEMBLE *> LINES_TO_ASSEMBLE;
typedef std::vector<CORE_TYPE> CORE_TYPES;
typedef std::vector<AVERAGED_TPF_AND_PPD> PROJECT_AVERAGED_VALUES;
typedef std::map<PROJECT,CORE_TYPE> PROJECT_TO_CORE_TYPE;
typedef std::map<SLOT_NAME,CHIPSET_AND_MODEL> SLOT_NAME_TO_CHIPSET_AND_MODEL;
typedef std::map<PROJECT,PROJECT_AVERAGED_VALUES>
    PROJECT_TO_PROJECT_AVERAGED_VALUES;

typedef struct lines LINES;

enum RETURN_CODE
{
    NOT_FOUND               = -1,    /* element/string was not found */
    FILE_EMPTY                  ,    /* file was empty */
	OPERATION_SUCCESSFUL        ,    /* operation completed successfully */
	FILE_CORRUPT                ,    /* file was corrupt */
	FILE_UNOPENED                    /* file could not be opened */
};

// Project file includes
#include "structures.hpp"                   // should be first to be included
#include "algorithms.hpp"
#include "arrayitize.hpp"
#include "assemble_lines.hpp"
#include "average_lines.hpp"
#include "calculate_points_per_day.hpp"
#include "common_functions.hpp"
#include "file_functions.hpp"
#include "get_core_types.hpp"
#include "handle_return_code.hpp"
#include "map_core_types_to_projects.hpp"
#include "map_slot_name_to_chipset_and_models.hpp"
#include "output_core_types.hpp"
#include "request_core_type.hpp"

// Constants
extern const CHARSTR field_delimiter;
extern const CHARSTR end_of_line;

// Namespaces
namespace columns
{
	namespace ProjectInfo
	{
		extern const unsigned int ProjectId;
		extern const unsigned int FinalDeadline;
		extern const unsigned int BasePoints;
		extern const unsigned int CoreType;
		extern const unsigned int KFactor;
	}
	namespace WuHistory
	{
		extern const unsigned int ProjectId;
		extern const unsigned int SlotName;
		extern const unsigned int Username;
		extern const unsigned int CoreVersion;
		extern const unsigned int FrameTime;
		extern const unsigned int DateDownloaded;
	}
	namespace SlotNames
	{
		extern const unsigned int SlotName;
		extern const unsigned int Chipset_and_Model;
	}
}

#endif
