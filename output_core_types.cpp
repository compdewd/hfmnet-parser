
#include "globals.hpp"

using namespace std;

void output_core_types(CORE_TYPES *core_types)
{
    LENGTH size_core_types = core_types->size();
    for (POSITION pos_core_types = 0;
         pos_core_types < size_core_types;
         ++pos_core_types)
    {
        cout << "(" << pos_core_types + 1 << ") ";
        cout << core_types->at(pos_core_types) << endl;
    }
}
