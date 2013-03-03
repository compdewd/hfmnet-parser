
#include "globals.hpp"

using namespace std;

void request_core_type(CHARSTR &user_selection)
{
    cout << "Which core would you like to have output? ";
    
    string user_input;
    getline(cin, user_input);
    
    LENGTH len_user_input = user_input.length();
    user_selection = new char [len_user_input + 1];
    for (POSITION i = 0; i < len_user_input; ++i)
    {
        user_selection[i] = user_input[i];
    }
    user_selection[len_user_input] = 0x00;
}
