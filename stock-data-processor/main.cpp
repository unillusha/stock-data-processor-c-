#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <limits>

using namespace std;

int main(int argc, char* argv[]) {
    // Verify if file name is provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Open the file
    ifstream file(argv[1]);  // argv[1] contains the input file name
    if (!file) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;  // Exit if file failed to open
    }

    cout << "File opened successfully: " << argv[1] << endl;

    file.close();  // Close the file after use
    return 0;
}
