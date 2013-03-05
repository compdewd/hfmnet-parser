
#include "globals.hpp"

using namespace std;

RETURN_CODE file_functions::get_file_size(FILENAME filename
                                        ,FILE_SIZE file_size)
{
    ifstream file;

    file.open(filename, ios_base::in);
    if (file.is_open())
    {
        file.seekg(0, ios::beg);
        streampos beg = file.tellg();
        file.seekg(0, ios::end);
        streampos end = file.tellg();
        (*file_size) = static_cast<int>(end - beg);
        file.close();

        return OPERATION_SUCCESSFUL;
    }
    else
    {
        return FILE_UNOPENED;
    }
}

RETURN_CODE file_functions::get_file_content(FILENAME filename
                            ,FILE_CONTENT &content)
{
    ifstream file;
    int file_size = 0;

    handle_return_code
    (
        file_functions::get_file_size(filename, &file_size)
    );

    file.open(filename, ios_base::in);
    if (file.is_open())
    {
        file.seekg(0, ios::beg);
        file.read(content, file_size);
        file.close();

        return OPERATION_SUCCESSFUL;
    }
    else
    {
        return FILE_UNOPENED;
    }
}

RETURN_CODE file_functions::write_array
(
     FILENAME filename
    ,lines *assembled_lines
)
{
    vector<char> single_line_assembly;

    for (ARRAY_INDEX row = 0; row < assembled_lines->rows; ++row)
    {
        for (ARRAY_INDEX column = 0;
             column < assembled_lines->columns;
             ++column)
        {
            for (ARRAY_INDEX character = 0;
                 character < strlen(assembled_lines->lines[row][column]);
                 ++character)
            {
                int integer_value =
                    static_cast<int>
                    (
                        assembled_lines->lines
                        [row]
                        [column]
                        [character]
                    );
                if
                (
                    (integer_value > 32 && integer_value < 127)
                    ||
                    (integer_value == 10 || integer_value == 13)
                )
                {
                    single_line_assembly.insert
                    (
                         single_line_assembly.end()
                        ,assembled_lines->lines[row][column][character]
                    );
                }
            }
            if (column != assembled_lines->columns - 1)
            {
                single_line_assembly.insert
                (
                     single_line_assembly.end()
                    ,(*field_delimiter)
                );
            }
        }
        single_line_assembly.insert
        (
             single_line_assembly.end()
            ,(*end_of_line)
        );
    }
    LENGTH len_single_line_assembly = single_line_assembly.size();
    CHARSTR single_line = new char [len_single_line_assembly + 1];
    for (POSITION i = 0;
         i < len_single_line_assembly;
         ++i)
    {
        single_line[i] = single_line_assembly[i];
    }
    single_line[len_single_line_assembly] = 0x00;

    ofstream file;
    file.open(filename, ios_base::out);
    if (file.is_open())
    {
        file.write(single_line, len_single_line_assembly);
        file.close();
        delete [] single_line;

        return OPERATION_SUCCESSFUL;
    }
    else
    {
        delete [] single_line;
        return FILE_UNOPENED;
    }
}

RETURN_CODE file_functions::write_averaged_new_records
(
     FILENAME filename
    ,vector<averaged_new_record *> *averaged_new_records
    ,SLOT_NAME_TO_CHIPSET_AND_MODEL *slot_name_to_chipset_and_model
    ,file *SlotNames
)
{
    vector<char> single_line_assembly;

    for (ARRAY_INDEX row = 0; row < averaged_new_records->size(); ++row)
    {
        // Chipset and Model
        char *slot_name =
            SlotNames->fca.content_array
                [
                    algorithms::find
                    (
                         SlotNames->fca.content_array
                        ,0
                        ,SlotNames->fci.rows - 1
                        ,columns::SlotNames::SlotName
                        ,averaged_new_records->at(row)->slot_name
                    )
                ]
                [columns::SlotNames::SlotName];
        for (ARRAY_INDEX character = 0;
             character <
                 strlen
                 (
                     slot_name_to_chipset_and_model->at(slot_name)
                 );
             ++character)
        {
            single_line_assembly.insert
            (
                 single_line_assembly.end()
                ,slot_name_to_chipset_and_model->at(slot_name)[character]
            );
        }
        single_line_assembly.insert
        (
             single_line_assembly.end()
            ,(*field_delimiter)
        );

        // Project
        CHARSTR project =
            common_functions::convert_to_charstr
            (
                 averaged_new_records->at(row)->project
            );
        for (ARRAY_INDEX character = 0;
             character < strlen(project);
             ++character)
        {
            single_line_assembly.insert
            (
                 single_line_assembly.end()
                ,project[character]
            );
        }
        delete [] project;
        single_line_assembly.insert
        (
             single_line_assembly.end()
            ,(*field_delimiter)
        );

        // Time per frame
        char *averaged_time_per_frame =
            common_functions::convert_to_charstr
            (
                averaged_new_records->at(row)->averaged_time_per_frame
            );
        for (ARRAY_INDEX character = 0;
             character < strlen(averaged_time_per_frame);
             ++character)
        {
            single_line_assembly.insert
            (
                 single_line_assembly.end()
                ,averaged_time_per_frame[character]
            );
        }
        delete [] averaged_time_per_frame;
        single_line_assembly.insert
        (
             single_line_assembly.end()
            ,(*field_delimiter)
        );

        // Points per day
        char *averaged_points_per_day =
            common_functions::convert_to_charstr
            (
                 averaged_new_records->at(row)->averaged_points_per_day
            );
        for (ARRAY_INDEX character = 0;
             character < strlen(averaged_points_per_day);
             ++character)
        {
            single_line_assembly.insert
            (
                 single_line_assembly.end()
                ,averaged_points_per_day[character]
            );
        }
        delete [] averaged_points_per_day;
        single_line_assembly.insert
        (
             single_line_assembly.end()
            ,(*field_delimiter)
        );

        // Core type
        for (ARRAY_INDEX character = 0;
             character < strlen(averaged_new_records->at(row)->core_type);
             ++character)
        {
            single_line_assembly.insert
            (
                 single_line_assembly.end()
                ,averaged_new_records->at(row)->core_type[character]
            );
        }
        single_line_assembly.insert
        (
             single_line_assembly.end()
            ,(*field_delimiter)
        );

        // Core version
        char *core_version =
            common_functions::convert_to_charstr
            (
                 averaged_new_records->at(row)->core_version
            );
        for (ARRAY_INDEX character = 0;
             character < strlen(core_version);
             ++character)
        {
            single_line_assembly.insert
            (
                 single_line_assembly.end()
                ,core_version[character]
            );
        }
        delete [] core_version;
        single_line_assembly.insert
        (
             single_line_assembly.end()
            ,(*field_delimiter)
        );

        // Username
        for (ARRAY_INDEX character = 0;
             character < strlen(averaged_new_records->at(row)->username);
             ++character)
        {
            single_line_assembly.insert
            (
                 single_line_assembly.end()
                ,averaged_new_records->at(row)->username[character]
            );
        }
        single_line_assembly.insert
        (
             single_line_assembly.end()
            ,(*field_delimiter)
        );



        // Date
        for (ARRAY_INDEX character = 0;
             character < DATE_LENGTH;
             ++character)
        {
            single_line_assembly.insert
            (
                 single_line_assembly.end()
                ,averaged_new_records->at(row)->date[character]
            );
        }
        single_line_assembly.insert
        (
             single_line_assembly.end()
            ,(*end_of_line)
        );
    }
    LENGTH len_single_line_assembly = single_line_assembly.size();
    CHARSTR single_line = new char [len_single_line_assembly + 1];
    for (POSITION i = 0;
         i < len_single_line_assembly;
         ++i)
    {
        single_line[i] = single_line_assembly[i];
        cout << single_line_assembly[i];
    }
    single_line[len_single_line_assembly] = 0x00;

    ofstream file;
    file.open(filename, ios_base::out);
    if (file.is_open())
    {
        file.write(single_line, len_single_line_assembly);
        delete [] single_line;
        file.close();

        return OPERATION_SUCCESSFUL;
    }
    else
    {
        delete [] single_line;
        return FILE_UNOPENED;
    }
}
