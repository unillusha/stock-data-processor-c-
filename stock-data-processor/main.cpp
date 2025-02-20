#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <limits>

using namespace std;

map<string, int> totalVolume;
map<string, float> High;
map<string, float> Low;

int main(int argc, char* argv[]) {

    string stock;
    int interval;
    int volume;
    float high;
    float low;

    // Verify if file name is provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Open the file
    ifstream file(argv[1]);  // argv[1] contains the input file name
    if (!file) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 2;  // Exit if file failed to open
    }

    while(!file.eof()){
        file >> stock >> interval >> volume >> high >> low;
        //cout << stock << interval << volume << high << low << endl;

        totalVolume[stock] += volume;
        //cout << totalVolume[stock] << endl;

        if(High[stock] == 0){
            High[stock] = high;

        } else if(high > High[stock]){
            High[stock] = high;
        }
        //cout << High[stock] << endl;

        if(Low[stock] == 0){
            Low[stock] = low;

        } else if(low < Low[stock]){
            Low[stock] = low;
        }
        //cout << Low[stock] << endl;
    }

    cout << "File opened successfully: " << argv[1] << endl;

    map<string, float>::iterator it = High.begin();

    // Iterate through the map and print the elements
    while (it != High.end()) {

        string s = it->first;
        cout << s << totalVolume[s] << High[s] << Low[s] << endl;
        ++it;
    }

    file.close();  // Close the file after use
    return 0;
}
