#include "header.h"

/**
 * Purpose: Calculates the Euclidean distance between two DataPoint objects.
 * Pre-condition: Both DataPoint objects must have valid attributes.
 * Post-condition: Returns the computed Euclidean distance.
 */
double calculateEuclideanDistance(const DataPoint& dp1, const DataPoint& dp2)
{
    double sumOfSquares = 0.0;
    
    // Loop over all 22 attributes
    for (int i = 0; i < 22; ++i)
    {
        // Calculate squared difference between attributes
        double diff = dp1.getAttribute(i) - dp2.getAttribute(i);
        sumOfSquares += diff * diff;
    }

    // Return the square root of the sum of squared differences
    return sqrt(sumOfSquares);
}

/**
 * Purpose: Classifies test mushrooms using k-NN and outputs results.
 * Pre-condition: The dataset must contain reference data, and test data must be loaded.
 * Post-condition: Outputs results to console and "predictions.txt".
 */
void classifyMushrooms(DataSet* dataset, DataSet& testData, int k)
{
    ofstream outFile("predictions.txt");
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open predictions.txt for writing." << endl;
        return;
    }

    DataSet::Node* testNode = testData.getHead();
    int testIndex = 1;

    while (testNode != nullptr)
    {
        // Get k nearest neighbors for the current test mushroom
        Neighbor* neighbors = getKNearestNeighbors(dataset, testNode->mData, k);

        //// Print the closest neighbors
        //cout << "Test Mushroom[" << testIndex << "] - 3 Closest Neighbors:" << endl;
        //outFile << "Test Mushroom[" << testIndex << "] - 3 Closest Neighbors:" << endl;

        //// Print the 3 closest neighbors with their distance and class
        //for (int i = 0; i < 3 && i < k; ++i)
        //{
        //    //cout << "Neighbor " << i + 1 << " - Distance: " << neighbors[i].distance << ", Class: ";
        //    //outFile << "Neighbor " << i + 1 << " - Distance: " << neighbors[i].distance << ", Class: ";

        //    if (neighbors[i].dp.getClassification() == 'e') {
        //        //cout << "edible" << endl;
        //        outFile << "edible" << endl;
        //    }
        //    else {
        //        //cout << "poisonous" << endl;
        //        outFile << "poisonous" << endl;
        //    }
        //}

        // Count occurrences of 'e' (edible) and 'p' (poisonous) to determine prediction
        int edibleCount = 0;
        int poisonousCount = 0;

        for (int i = 0; i < k; ++i)
        {
            if (neighbors[i].dp.getClassification() == 'e')
            {
                edibleCount++;
            }
            else
            {
                poisonousCount++;
            }
        }

        // Determine the classification based on the majority vote
        char predictedClass;
        if (edibleCount > poisonousCount)
        {
            predictedClass = 'e';
        }
        else
        {
            predictedClass = 'p';
        }

        //// Output the prediction for the test mushroom
        //cout << "Predicted Class for Test Mushroom[" << testIndex << "]: ";
        //outFile << "Predicted Class for Test Mushroom[" << testIndex << "]: ";

        if (predictedClass == 'e') {
            cout << "edible" << endl;
            outFile << "edible" << endl;
        }
        else {
            cout << "poisonous" << endl;
            outFile << "poisonous" << endl;
        }

        testNode = testNode->mNext;
        testIndex++;
    }

    outFile.close();
}

/**
 * Purpose: Finds the k-nearest neighbors to the test mushroom using Euclidean distance.
 * Pre-condition: The dataset must not be empty, and k must be valid.
 * Post-condition: Returns a dynamically allocated array of k nearest neighbors.
 */
Neighbor* getKNearestNeighbors(DataSet* dataset, const DataPoint& testMushroom, int k)
{
    // Create an array to store the closest k neighbors
    Neighbor* neighbors = new Neighbor[k];

    // Initialize the neighbors array with invalid distances
    for (int i = 0; i < k; ++i)
    {
        neighbors[i].distance = -1.0; // Invalid distance initially (since distance can't be negative)
    }

    // Iterate through the dataset to calculate distances
    DataSet::Node* current = dataset->getHead();
    while (current != nullptr)
    {
        double distance = calculateEuclideanDistance(testMushroom, current->mData);

        // Find the position to insert the current neighbor
        for (int i = 0; i < k; ++i)
        {
            // If the neighbor at index i has an invalid distance or the current distance is smaller
            if (neighbors[i].distance == -1.0 || distance < neighbors[i].distance)
            {
                // Shift the neighbors that are farther away down by one slot
                for (int j = k - 1; j > i; --j)
                {
                    neighbors[j] = neighbors[j - 1];
                }

                // Insert the current neighbor at the correct position
                neighbors[i].dp = current->mData;
                neighbors[i].distance = distance;
                break;
            }
        }

        current = current->mNext;
    }

    // Print the details of the neighbors including their distance and attributes
    //cout << "The " << k << " nearest neighbors are:\n";
    //for (int i = 0; i < k; ++i)
    //{
    //    // Print the distance of the neighbor
    //    cout << "Neighbor " << (i + 1) << " (Distance: " << neighbors[i].distance << "): ";

    //    // Print the attributes of the neighbor
    //    for (int j = 0; j < 22; ++j)  // Assuming there are 22 attributes
    //    {
    //        cout << neighbors[i].dp.getAttribute(j) << " ";
    //    }

    //    // Print a newline for better readability
    //    cout << endl;
    //}

    return neighbors;
}

/**
 * Purpose: Prompts user for test data file name and loads test mushrooms into a dataset.
 * Pre-condition: A valid filename must be entered.
 * Post-condition: Returns true if file is successfully loaded, false otherwise.
 */
bool loadTestData(DataSet& testData, int& k)
{
    string filename;
    cout << "Enter the test data file name: ";
    cin >> filename;

    ifstream testFile(filename);
    if (!testFile.is_open())
    {
        cerr << "Error: Could not open test data file: " << filename << endl;
        return false;
    }

    testFile >> k;  // Read the k value from the first line
    //cout << "k value: " << k << endl;  // Debugging output

    testFile.ignore();  // To ignore the newline character after reading the k value

    DataPoint mushroom;
    int mushroomCount = 0;
    while (testFile >> mushroom)  // Read each test sample
    {
        testData.insert(mushroom);
        mushroomCount++;
        //cout << "Loaded Mushroom #" << mushroomCount << endl;  // Debugging output
    }

    if (mushroomCount == 0)
    {
        cerr << "No mushrooms loaded. Please check the format of your testdata.txt file." << endl;
    }

    testFile.close();
    return true;
}


/**
 * Purpose: Sorts the neighbors array by distance in ascending order.
 * Pre-condition: The array must be initialized and populated.
 * Post-condition: The array is sorted in place.
 */
void sortNeighborsByDistance(Neighbor* neighbors, int k)
{
    for (int i = 0; i < k - 1; ++i)
    {
        for (int j = i + 1; j < k; ++j)
        {
            if (neighbors[i].distance > neighbors[j].distance)
            {
                // Swap the neighbors if they are out of order
                Neighbor temp = neighbors[i];
                neighbors[i] = neighbors[j];
                neighbors[j] = temp;
            }
        }
    }
}
