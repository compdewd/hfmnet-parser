
#include "globals.hpp"

using namespace std;

AMOUNT calculate_points_per_day
(
     float base_points
    ,float final_deadline
    ,float k_factor
    ,AMOUNT time_per_frame
)
{
    float completion_time = time_per_frame / 864;
    float bonus_factor = k_factor * final_deadline / completion_time;
    bonus_factor < 1 ? 1 : bonus_factor;
    return static_cast<unsigned int>
        (bonus_factor * base_points / completion_time);
}
