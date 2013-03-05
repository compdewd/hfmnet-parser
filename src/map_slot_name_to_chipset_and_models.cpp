
#include "globals.hpp"

using namespace std;

void map_slot_name_to_chipset_and_models
(
     SLOT_NAME_TO_CHIPSET_AND_MODEL *slot_name_to_chipset_and_model
    ,file *SlotNames
)
{
    for (ARRAY_INDEX row = 0; row < SlotNames->fci.rows; ++row)
    {
        slot_name_to_chipset_and_model->
            insert
            (
                make_pair
                (
                     SlotNames->fca.content_array
                        [row]
                        [columns::SlotNames::SlotName]
                    ,SlotNames->fca.content_array
                        [row]
                        [columns::SlotNames::Chipset_and_Model]
                )
            );
    }
}
