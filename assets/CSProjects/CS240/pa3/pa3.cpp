#include "header.h"

using namespace std;

int main()
{
    // Create DataSet objects for training data and test data
    DataSet dataSet;
    DataSet testData;

    // File path for the dataset
    string datasetFile = "data.txt";
    ifstream dataFile(datasetFile);

    // Check if dataset file opened successfully
    if (!dataFile)
    {
        cerr << "Error: Could not open dataset file: " << datasetFile << endl;
        return 1; // Return error code
    }
    else
        cout << "data.txt loaded" << endl;

    // Read dataset and insert DataPoints into dataSet
    DataPoint dp;
    int count = 0;
    while (dataFile >> dp)
    {
        dataSet.insert(dp);
        count++;
    }
    dataFile.close();
    cout << count << endl;



    // Variable to hold k for k-NN
    int k;

    // Load test data from a file
    if (!loadTestData(testData, k))
    {
        cerr << "Error loading test data." << endl;
        return 1; // Return error code if test data fails to load
    }

    // Perform classification and output the results
    classifyMushrooms(&dataSet, testData, k);

    // Output completion message
    cout << "Classification completed. Results saved to predictions.txt." << endl;

    return 0;
}
