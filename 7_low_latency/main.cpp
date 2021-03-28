#include <iostream>
#include <string>
#include <sstream>
#include <locale>
#include <vector>

// This ctype facet classifies commas and endlines as whitespace
struct csv_whitespace : std::ctype<char> {
    static const mask* make_table()
    {
        // make a copy of the "C" locale table
        static std::vector<mask> v(classic_table(), classic_table() + table_size);
        v[','] |=  space;  // comma will be classified as whitespace
        v[' '] &= ~space;      // space will not be classified as whitespace
        return &v[0];
    }
    csv_whitespace(std::size_t refs = 0) : ctype(make_table(), false, refs) {}
};

int main()
{
    std::string s;
    float logReturns[10];
    int momentum[9];
    int momentumSum = 0;
    int count = 0;
    int flag = 1;

    while (std::cin >> s) {
        // Receive data
        std::string token;
        std::istringstream buf1(s);
        buf1.imbue(std::locale(buf1.getloc(), new csv_whitespace));
        do {
            buf1 >> token;
            // std::cout << " " << token << std::endl;
            logReturns[count] = std::stof(token);
            // std::cout << " " << logReturns[count] << std::endl;
            
            // Intake first 10 previous values
            switch (count)
            {
            case 0:
                // std::cout << " " << logReturns[count] << std::endl;
                break;
            case 9:
                if (logReturns[count] > logReturns[count-1]) {
                    momentum[count-1] = 1; // decreasing
                    momentumSum++;
                }
                else momentum[count-1] = 0; // increasing
                flag = 0;
                break;
            default:
                if (logReturns[count] > logReturns[count-1]) {
                    momentum[count-1] = 1; // decreasing
                    momentumSum++;
                }
                else momentum[count-1] = 0; // increasing
                // std::cout << " " << logReturns[count] << "    " << momentum[count-1] << std::endl;
                break;
            }
            count++;
        } while (flag);

        // Print prediction
        if (momentum[0]) std::cout << 0 << std::endl;
        else std::cout << 1 << std::endl;
        // std::cout << momentumSum << std::endl;
        for (int i = 0; i < 9; i++) {
            // std::cout << momentum[i];
        }
    }
    return 0;
}