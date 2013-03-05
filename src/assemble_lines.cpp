
#include "globals.hpp"

using namespace std;

lines *assemble_lines(file *WuHistory
                     ,CORE_TYPES *core_types
                     ,CHARSTR &user_selected_core_type
                     ,PROJECT_TO_CORE_TYPE *project_to_core_type)
{
    lines *assembled_lines = new lines;
    LINES_TO_ASSEMBLE lines_to_assemble;
    CHARSTR selected_core_type;

    if (algorithms::isdigit(user_selected_core_type[0]) == true)
    {
        NUMBER user_selected_core_number =
            common_functions::convert_to_int(user_selected_core_type) - 1;
        if
        (
            user_selected_core_number < static_cast<NUMBER>(core_types->size())
            &&
            user_selected_core_number > 0
        )
        {
            selected_core_type = new char
                [
                    strlen(core_types->at(user_selected_core_number)) + 1
                ];
            for (LENGTH i = 0;
                 i < strlen(core_types->at(user_selected_core_number)) + 1;
                 ++i)
            {
                selected_core_type[i] =
                    core_types->at(user_selected_core_number)[i];
            }

            for (ARRAY_INDEX row = 0, row_lines_to_assemble = 0;
                 row < WuHistory->fci.rows;
                 ++row)
            {
                PROJECT_TO_CORE_TYPE::iterator it_project_to_core_type =
                    project_to_core_type->
                        find
                        (
                            common_functions::convert_to_int
                            (
                                WuHistory->fca.content_array
                                [row]
                                [columns::WuHistory::ProjectId]
                            )
                        );
                if (it_project_to_core_type != project_to_core_type->end())
                {
                    if
                    (
                        algorithms::compare
                        (
                             selected_core_type
                            ,it_project_to_core_type->second
                        )
                        ==
                        true
                    )
                    {
                        lines_to_assemble.insert
                        (
                             lines_to_assemble.end()
                            ,new SUB_LINES_TO_ASSEMBLE
                        );

                        for (ARRAY_INDEX column = 0;
                             column < WuHistory->fci.columns;
                             ++column)
                        {
                            lines_to_assemble[row_lines_to_assemble]->insert
                            (
                                 lines_to_assemble[row_lines_to_assemble]->end()
                                ,WuHistory->fca.content_array[row][column]
                            );
                        }
                        ++row_lines_to_assemble;
                    }
                }
            }

            assembled_lines->lines = new char ** [lines_to_assemble.size()];
            for (ARRAY_INDEX row = 0; row < lines_to_assemble.size(); ++row)
            {
                assembled_lines->lines[row] =
                    new char * [WuHistory->fci.columns];
                for (ARRAY_INDEX column = 0;
                     column < WuHistory->fci.columns;
                     ++column)
                {
                    LENGTH len_lines_to_assemble_current_field =
                        strlen(lines_to_assemble[row]->at(column));
                    assembled_lines->lines[row][column] =
                        new char [len_lines_to_assemble_current_field + 1];
                    strncpy
                    (
                         assembled_lines->lines[row][column]
                        ,lines_to_assemble[row]->at(column)
                        ,len_lines_to_assemble_current_field
                    );
                    assembled_lines->lines
                        [row]
                        [column]
                        [len_lines_to_assemble_current_field]
                    = 0x00;
                }
            }
            assembled_lines->rows = lines_to_assemble.size();
            assembled_lines->columns = WuHistory->fci.columns;

            for (ARRAY_INDEX i = 0; i < lines_to_assemble.size(); ++i)
            {
                delete lines_to_assemble[i];
            }
            delete [] selected_core_type;

            return assembled_lines;
        }
        else
        {
            cout << endl << "Next time, please specify a number that "
                << "corresponds to a core type rather than one that does not."
                << endl;
        }
    }
    else
    {
        cout << endl << "Next time, please specify the number corresponding to "
            << "the desired core type." << endl;
    }
}
