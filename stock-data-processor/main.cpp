#include <iostream>
#include <fstream>
#include <map>
#include <limits>

using namespace std;


class StockData {
private:
    int totalVolume;
    float High;
    float Low;

public:
    // Constructor initializes values
    StockData() : totalVolume(0), High(numeric_limits<float>::lowest()), Low(numeric_limits<float>::max()) {}

    // Method to update stock data
    void update(int volume, float high, float low) {
        totalVolume += volume;
        High = max(High, high);
        Low = min(Low, low);
    }

    // Getters
    int getTotalVolume() const { return totalVolume; }
    float getHigh() const { return High; }
    float getLow() const { return Low; }
};

int main(int argc, char* argv[]) {

    string stock;
    int interval, volume;
    float high, low;

    // Verify if file name is provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Open the file
    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 2;
    }

    map<string, StockData> stockSummary; // Map storing StockData objects for each stock

    // Read file line by line and update stock summary
    while (file >> stock >> interval >> volume >> high >> low) {
        stockSummary[stock].update(volume, high, low);
    }

    cout << "File opened successfully: " << argv[1] << endl;


    file.close(); // Close the file after use

    // Open the file again for the second pass
    file.open(argv[1]);
    if (!file) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 2;
    }

    // Print output 1: [Stock], [Interval], [% Volume Traded]
    while (file >> stock >> interval >> volume >> high >> low) {
        float percentageVolumeTraded = (static_cast<float>(volume) / stockSummary[stock].getTotalVolume()) * 100;
        cout << stock << " " << interval << " " << percentageVolumeTraded  << endl;
    }

    // Print delimiter
    cout << "#" << endl;

    // Print output 2: [Stock], [Day High], [Day Low]
    for (const auto& entry : stockSummary) {
        cout << entry.first << " " << entry.second.getHigh() << " " << entry.second.getLow() << endl;
    }

    file.close(); // Close the file after second pass

    return 0;
}
