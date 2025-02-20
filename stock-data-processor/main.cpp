#include <iostream>
#include <fstream>
#include <map>
#include <limits>

using namespace std;

// Define StockData as a Class
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

    string stock;
    int interval, volume;
    float high, low;

    // Read file line by line and update stock summary
    while (file >> stock >> interval >> volume >> high >> low) {
        stockSummary[stock].update(volume, high, low);
    }

    cout << "File opened successfully: " << argv[1] << endl;

    // Print summary: [Stock], [Total Volume Traded], [High], [Low]
    for (const auto& entry : stockSummary) {
        cout << entry.first << " " << entry.second.getTotalVolume() << " "
             << entry.second.getHigh() << " " << entry.second.getLow() << endl;
    }

    file.close(); // Close the file after use
    return 0;
}
