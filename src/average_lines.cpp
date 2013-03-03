
#include "globals.hpp"

using namespace std;

void average_lines
(
     lines *assembled_lines
    ,file *ProjectInfo
    ,file *SlotNames
    ,PROJECT_TO_CORE_TYPE *project_to_core_type
    ,vector<averaged_new_record *> *averaged_new_records
)
{
    vector<distinct_new_record *> distinct_new_records;
    distinct_new_records.insert
    (
         distinct_new_records.end()
        ,new distinct_new_record
    );

    distinct_new_records.at(0)->project =
        common_functions::convert_to_int
        (
            assembled_lines->lines[0][columns::WuHistory::ProjectId]
        );
    distinct_new_records.at(0)->slot_name =
        assembled_lines->lines[0][columns::WuHistory::SlotName];
    /*strncpy
    (
         distinct_new_records.at(0)->core_type
        ,project_to_core_type->at(distinct_new_records.at(0)->project)
        ,strlen
         (
             project_to_core_type->at(distinct_new_records.at(0)->project)
         )
    );*/
    distinct_new_records.at(0)->core_version =
        algorithms::round
        (
             common_functions::convert_to_float
             (
                 assembled_lines->lines[0][columns::WuHistory::CoreVersion]
             )
            ,2
        );
    distinct_new_records.at(0)->username =
        assembled_lines->lines[0][columns::WuHistory::Username];
    distinct_new_records.at(0)->project_performance_values.time_per_frame.insert
    (
         distinct_new_records.at(0)->project_performance_values.time_per_frame
             .end()
        ,common_functions::convert_to_int
         (
             assembled_lines->lines[0][columns::WuHistory::FrameTime]
         )
    );
    CHARSTR charstr_project =
        common_functions::convert_to_charstr
        (
             distinct_new_records.at(0)->project
        );
    ARRAY_INDEX row_ProjectInfo =
        algorithms::find
        (
             ProjectInfo->fca.content_array
            ,0
            ,ProjectInfo->fci.rows
            ,columns::ProjectInfo::ProjectId
            ,charstr_project
        );
    distinct_new_records.at(0)->project_performance_values.points_per_day.insert
    (
         distinct_new_records.at(0)->
             project_performance_values.points_per_day.end()
        ,calculate_points_per_day
         (
              common_functions::convert_to_float
              (
                  ProjectInfo->fca.content_array
                  [row_ProjectInfo]
                  [columns::ProjectInfo::BasePoints]
              )
             ,common_functions::convert_to_float
              (
                  ProjectInfo->fca.content_array
                  [row_ProjectInfo]
                  [columns::ProjectInfo::FinalDeadline]
              )
             ,common_functions::convert_to_float
              (
                  ProjectInfo->fca.content_array
                  [row_ProjectInfo]
                  [columns::ProjectInfo::KFactor]
              )
             ,distinct_new_records.at(0)->
                  project_performance_values.time_per_frame.at(0)
         )
    );
    distinct_new_records.at(0)->date =
        string(assembled_lines->lines[0][columns::WuHistory::DateDownloaded]);


/*
    for (ARRAY_INDEX row = 1;
         row < assembled_lines->rows;
         ++row)
    {
        for (ARRAY_INDEX pos_record = 0;
             pos_record < distinct_new_records.size();
             ++pos_record)
        {
            bool record_line_match =
                algorithms::compare
                (
                     distinct_new_records[pos_record]->project
                    ,assembled_lines->lines[row][columns::WuHistory::ProjectId]
                )
                &
                algorithms::compare
                (
                     distinct_new_records[pos_record]->slot_name
                    ,assembled_lines->lines[row][columns::WuHistory::SlotName]
                )
                &
                algorithms::compare
                (
                     distinct_new_records[pos_record]->core_type
                    ,project_to_core_type->
                        at
                        (
                            common_functions::convert_to_int
                            (
                                assembled_lines->lines
                                    [row]
                                    [columns::WuHistory::ProjectId]
                            )
                        )
                )
                &
                algorithms::compare
                (
                     distinct_new_records[pos_record]->core_version
                    ,common_functions::convert_to_float
                     (
                         assembled_lines->lines
                         [row]
                         [columns::WuHistory::CoreVersion]
                     )
                )
                &
                algorithms::compare
                (
                     distinct_new_records[pos_record]->username
                    ,assembled_lines->lines
                     [row]
                     [columns::WuHistory::Username]
                );
            if (record_line_match == false)
            {
                distinct_new_records.insert
                (
                     distinct_new_records.end()
                    ,new distinct_new_record
                );

            }
        }
    }
    */

    averaged_new_records = new vector<averaged_new_record *>;
    for (POSITION record = 0; record < distinct_new_records.size(); ++record)
    {
        averaged_new_records->insert
        (
             averaged_new_records->end()
            ,new averaged_new_record
        );
        averaged_new_records->at(record)->project =
            distinct_new_records.at(record)->project;
        strncpy
        (
             averaged_new_records->at(record)->slot_name
            ,distinct_new_records.at(record)->slot_name
            ,strlen(distinct_new_records.at(record)->slot_name)
        );/*
        strncpy
        (
             averaged_new_records->at(record)->core_type
            ,distinct_new_records.at(record)->core_type
            ,strlen(distinct_new_records.at(record)->core_type)
        );
        averaged_new_records->at(record)->core_version =
            distinct_new_records.at(record)->core_version;
        strncpy
        (
             averaged_new_records->at(record)->username
            ,distinct_new_records.at(record)->username
            ,strlen(distinct_new_records.at(record)->username)
        );
        averaged_new_records->at(record)->averaged_points_per_day = 0;
        averaged_new_records->at(record)->averaged_time_per_frame = 0;
        for (POSITION pos_value = 0;
             pos_value < distinct_new_records.at(record)->
                 project_performance_values.points_per_day.size();
             ++pos_value)
        {
            averaged_new_records->at(record)->averaged_points_per_day +=
                distinct_new_records.at(record)->project_performance_values.
                points_per_day.at(pos_value);
            averaged_new_records->at(record)->averaged_time_per_frame +=
                distinct_new_records.at(record)->project_performance_values.
                time_per_frame.at(pos_value);
        }
        averaged_new_records->at(record)->averaged_points_per_day =
            static_cast<AMOUNT>
            (
                averaged_new_records->at(record)->averaged_points_per_day /
                distinct_new_records.at(record)->
                    project_performance_values.points_per_day.size()
            );
        averaged_new_records->at(record)->averaged_time_per_frame =
            static_cast<AMOUNT>
            (
                averaged_new_records->at(record)->averaged_time_per_frame /
                distinct_new_records.at(record)->
                    project_performance_values.time_per_frame.size()
            );
        averaged_new_records->at(record)->date =
            distinct_new_records.at(0)->date;*/
    }
}
