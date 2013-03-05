
#include "globals.hpp"

using namespace std;

void map_core_types_to_projects
(
     PROJECT_TO_CORE_TYPE *project_to_core_type
    ,file *ProjectInfo
)
{
    for (ARRAY_INDEX row = 0; row < ProjectInfo->fci.rows; ++row)
    {
        project_to_core_type->
            insert
            (
                make_pair
                (
                     common_functions::convert_to_int
                     (
                         ProjectInfo->fca.content_array
                         [row]
                         [columns::ProjectInfo::ProjectId]
                     )
                    ,ProjectInfo->fca.content_array
                     [row]
                     [columns::ProjectInfo::CoreType]
                )
            );
    }
}
