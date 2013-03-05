
/*
    By:         Patrick Joseph Sauber Rebsch
    Purpose:    Parses ".csv" file versions of the "WuHistory.db3" and
                "ProjectInfo.tab" files originating from "HFM.NET" and
                creates a ".csv" file of a list of the specified core type
*/

#include "globals.hpp"

using namespace std;

namespace columns
{
    namespace ProjectInfo
    {
        const unsigned int ProjectId = 0;
        const unsigned int FinalDeadline = 5;
        const unsigned int BasePoints = 6;
        const unsigned int CoreType = 8;
        const unsigned int KFactor = 11;
        const unsigned int total = 12;
    }
    namespace WuHistory
    {
        const unsigned int ProjectId = 1;
        const unsigned int SlotName = 5;
        const unsigned int Username = 7;
        const unsigned int CoreVersion = 9;
        const unsigned int FrameTime = 11;
        const unsigned int DateDownloaded = 13;
        const unsigned int DateFinished = 14;
        const unsigned int total = 15;
    }
    namespace SlotNames
    {
        const unsigned int SlotName = 0;
        const unsigned int Chipset_and_Model = 1;
        const unsigned int total = 2;
    }
}

const CHARSTR field_delimiter = ",";
const CHARSTR end_of_line = "\n"; //0x0a; // 0x0d on Unix

int main(int argc, char **argv)
{
    // Variables
    file file_array[NUM_FILES];
    file_array[PROJECTINFO].filename = "ProjectInfo.csv";
    file_array[PROJECTINFO].fci.columns = columns::ProjectInfo::total;
    file_array[WUHISTORY].filename = "WuHistory.csv";
    file_array[WUHISTORY].fci.columns = columns::WuHistory::total;
    file_array[SLOTNAMES].filename = "SlotNames.csv";
    file_array[SLOTNAMES].fci.columns = columns::SlotNames::total;
    CHARSTR filename_new_WuHistory = "C:\\Hello.csv";
    CHARSTR filename_finished_product = "C:\\World.csv";

    // Get lengths of files
    for (int i = 0; i < NUM_FILES; ++i)
    {
        handle_return_code
        (
            file_functions::get_file_size
            (
                 file_array[i].filename
                ,&(file_array[i].fci.length)
            )
        );
    }

    // Allocate space for importing the files
    for (int i = 0; i < NUM_FILES; ++i)
    {
        file_array[i].fc.content = new char [file_array[i].fci.length + 1];
    }

    // Get the file into the program
    for (int i = 0; i < NUM_FILES; ++i)
    {
        handle_return_code
        (
            file_functions::get_file_content
            (
                 file_array[i].filename
                ,file_array[i].fc.content
            )
        );
    }

    // Fill in the number of rows and the longest field
    for (int i = 0; i < NUM_FILES; ++i)
    {
        file_array[i].fci.rows = common_functions::get_num_lines
                                 (
                                     file_array[i].fc.content
                                 );
        file_array[i].fci.longest_field =
            common_functions::get_length_longest_field
            (
                file_array[i].fc.content
            );
    }

    // Allocate memory for the content array
    for (int i = 0; i < NUM_FILES; ++i)
    {
        file_array[i].fca.content_array = new char ** [file_array[i].fci.rows];
        for (ARRAY_INDEX row = 0; row < file_array[i].fci.rows; ++row)
        {
            file_array[i].fca.content_array[row] =
                new char * [file_array[i].fci.columns];
            for (ARRAY_INDEX column = 0;
                 column < file_array[i].fci.columns;
                 ++column)
            {
                file_array[i].fca.content_array[row][column] =
                    new char [file_array[i].fci.longest_field + 1];
                common_functions::fill
                (
                     file_array[i].fca.content_array[row][column]
                    ,file_array[i].fci.longest_field + 1
                    ,'\0'
                );
            }
        }
    }
    // Get the file content into an array
    for (int i = 0; i < NUM_FILES; ++i)
    {
        arrayitize
        (
            file_array[i].fc.content
           ,&(file_array[i].fci)
           ,file_array[i].fca.content_array
        );
        file_array[i].fc.cleanUp();
    }

    // Map core types to projects
    PROJECT_TO_CORE_TYPE project_to_core_type;
    map_core_types_to_projects
    (
         &project_to_core_type
        ,&(file_array[PROJECTINFO])
    );

    // Map chipset and model to slot names
    SLOT_NAME_TO_CHIPSET_AND_MODEL slot_name_to_chipset_and_model;
    map_slot_name_to_chipset_and_models
    (
         &slot_name_to_chipset_and_model
        ,&(file_array[SLOTNAMES])
    );

    // Get core types used in the WU history
    CORE_TYPES core_types;
    get_core_types
    (
         &project_to_core_type
        ,&core_types
        ,&(file_array[PROJECTINFO])
        ,&(file_array[WUHISTORY])
    );

    // Give the user the cores from which to select and request a selection
    output_core_types(&core_types);
    CHARSTR user_selected_core_type;
    request_core_type(user_selected_core_type);

    // Assemble the lines to write
    /*
        These lines are the WuHistory lines of the core type the user selected.

        If a WU, X, had a project, Y, that corresponds to the specific core
        type, Z, then that WU, X, is added to a list of lines to write to a
        file.
    */
    lines *assembled_lines =
        assemble_lines
        (
             &(file_array[WUHISTORY])
            ,&core_types
            ,user_selected_core_type
            ,&project_to_core_type
        );

    // We no longer need to know the user's selection
    delete [] user_selected_core_type;

    // Write the aforementioned assembled lines to a file
    handle_return_code
    (
        file_functions::write_array(filename_new_WuHistory, assembled_lines)
    );

    // Average the values of the aforementioned assembled lines
    vector<averaged_new_record *> *averaged_new_records;
    average_lines
    (
         assembled_lines
        ,&(file_array[PROJECTINFO])
        ,&(file_array[SLOTNAMES])
        ,&project_to_core_type
        ,averaged_new_records
    );

    // Write the averaged lines to a file
    handle_return_code
    (
        file_functions::write_averaged_new_records
        (
             filename_finished_product
            ,averaged_new_records
            ,&slot_name_to_chipset_and_model
            ,&(file_array[SLOTNAMES])
        )
    );

    // Cleanup
    for (unsigned int i = 0; i < NUM_FILES; ++i)
    {
        file_array[i].fca.cleanUp
        (
             file_array[i].fci.rows
            ,file_array[i].fci.columns
        );
        file_array[i].cleanUp();
    }
    assembled_lines->cleanUp();
    for (unsigned int i = 0; i < averaged_new_records->size(); ++i)
    {
        delete [] averaged_new_records->at(i)->slot_name;
        delete [] averaged_new_records->at(i)->core_type;
        delete [] averaged_new_records->at(i)->username;
        delete averaged_new_records->at(i);
    }

    // Tell the user that we're finished
    cout << endl << endl << "All done!";

    // Wait for user to confirm exit
    atexit(common_functions::wait_for_user);

    // Return success!
    return 0;
}
