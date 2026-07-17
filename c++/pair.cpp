#include <iostream>
#include <string>

using namespace std;

bool isPair(int n)
{
    string num_string = to_string(n);
    char num_char = num_string.back();
    
    cout << num_char << endl;
    
    if (num_char == '2' || num_char == '4' || num_char == '6' || num_char == '8' || num_char == '0')
        return true;
    else
        return false;

}

int main()
{
    cout << isPair(10) << endl;
    return 0;
}
