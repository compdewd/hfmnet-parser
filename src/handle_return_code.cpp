
#include "globals.hpp"

using namespace std;

void handle_return_code(RETURN_CODE return_code)
{
    switch (return_code)
    {
        case FILE_UNOPENED:
        {
            cout << endl << "One or more files could not be opened." << endl;
            break;
        }
        case FILE_CORRUPT:
        {
            cout << endl << "One or more files were corrupt." << endl;
            break;
        }
        case FILE_EMPTY:
        {
            cout << endl << "One or more files were empty." << endl;
            break;
        }
        case NOT_FOUND:
        {
            cout
                << endl
                << "One or more critical elements were not found."
                << endl;
            break;
        }
        default:
        {
            break;
        }
    }
}
