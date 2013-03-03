
#include "globals.hpp"

using namespace std;

void get_core_types(PROJECT_TO_CORE_TYPE *project_to_core_type
                   ,CORE_TYPES *core_types
                   ,file *ProjectInfo
                   ,file *WuHistory)
{
    for (ARRAY_INDEX row = 0; row < WuHistory->fci.rows; ++row)
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
            POSITION pos_found =
                algorithms::find
                (
                     core_types
                    ,0
                    ,core_types->size() - 1
                    ,(it_project_to_core_type->second)
                );
            if (pos_found == NOT_FOUND)
            {
                core_types->
                    insert(core_types->end(), it_project_to_core_type->second);
            }
        }
    }
}
