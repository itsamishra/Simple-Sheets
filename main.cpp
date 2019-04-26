#include <fstream>
#include <iostream>
#include <string>

//#define CSV_FILE_NAME   "MOCK_DATA.csv"
#define NUM_COLUMNS     5
#define NUM_DATA_ROWS   100

class Spreadsheet {
private:
    // Converts csv contents into string
    std::string getCsvFileString() {
        // Opens file in read mode
        std::ifstream csv_file;
        csv_file.open(this->csvFileName, std::ios::in);

        // Makes sure file is open
        if (csv_file.is_open() == false) {
            std::cout << "ERROR: Could not open file\n";
        }

        // Feeds csv file into string line by line
        std::string line;
        std::string csvString = "";
        while (getline(csv_file, line)) {
            csvString += line + ",";
        }

        // Closes file
        csv_file.close();

        return csvString;
    }

    // Sets value of headerArray[]
    void setHeaderArray() {
        // int dataStartIndex = 0;  // Keeps track of string index at which the data starts
        int headerLength = 0;    // Keeps track of header length
        int numHeadersFound = 0; // Keeps track of # of headers found
        int numHeaders = NUM_COLUMNS; // Keeps track of # of headers that exist
        for (uint i = 0; i < this->csvFileString.length(); i++) {
            // If the next character is a comma, then we must be at the end of a header
            if (this->csvFileString[i] == ',') {
                // Extracts header from string
                std::string header = this->csvFileString.substr(i - headerLength, headerLength);

                // Resets header length to zero
                headerLength = 0;

                // Adds new header to Spreadsheet object and checks to see if there are any more headers to find
                numHeadersFound++;
                int headerIndex = numHeadersFound - 1;
                this->headerArray[headerIndex] = header;

                // If all headers have been found, records index at which headers end and exits loop
                if (numHeadersFound == numHeaders) {
                    this->dataStartIndex = i + 1; // Adds 1 so that index points to first character of data
                    break;
                }
            }
                // Else if the next character isn't a comma, increments length (i.e. size) of current header
            else {
                headerLength += 1;
            }
        }
    }

    // Sets value of dataArray[][]
    void setDataArray() {
        int dataLength = 0;   // Keeps track of the size of the data string
        int numDataFound = 0; // Keeps track of # of data found

        // Iterates over csv string, starting at index at which data begins
        for (uint i = this->dataStartIndex; i < this->csvFileString.length(); i++) {
            // If the next character is a comma, adds the 'data' to dataArray
            if (this->csvFileString[i] == ',') {
                // Extracts data string from csv string
                std::string dataString = this->csvFileString.substr(i - dataLength, dataLength);

                // Resets size of data to zero
                dataLength = 0;

                // Adds data string to dataArray
                numDataFound++;
                int dataIndex1 = (numDataFound - 1) / NUM_COLUMNS;
                int dataIndex2 = (numDataFound - 1) % NUM_COLUMNS;
                this->dataArray[dataIndex1][dataIndex2] = dataString;
            }
                // Else if the next character isn't a comma, increments length (i.e. size) of data
            else {
                dataLength += 1;
            }
        }
    }

    // Converts Spreadsheet object to string and returns it
    std::string getSpreadsheetString(){
        std::string spreadsheetCsvString = "";

        // Adds header to spreadsheetCsvString
        for (int i=0; i<NUM_COLUMNS; i++){
            spreadsheetCsvString += this->headerArray[i] + ",";
        }
        // Replaces last comma on line with newline character
        spreadsheetCsvString.replace(spreadsheetCsvString.length()-1, 1, "\n");

        // Adds data to spreadsheetCsvString
        for (int i=0; i<NUM_DATA_ROWS; i++){
            for (int j=0; j<NUM_COLUMNS; j++){
                spreadsheetCsvString += this->dataArray[i][j] + ",";
            }
            // Replaces last comma on line with newline character
            spreadsheetCsvString.replace(spreadsheetCsvString.length()-1, 1, "\n");
        }

        return spreadsheetCsvString;
    }

public:
    // Object attributes
    std::string csvFileName;
    std::string csvFileString = "";       // String containing entire csv file
    std::string headerArray[NUM_COLUMNS]; // Array of header items
    std::string dataArray[NUM_DATA_ROWS][NUM_COLUMNS]; // Array of data items
    int dataStartIndex = 0;  // Keeps track of string index at which the data starts

    // Constructor
    Spreadsheet(std::string *csvFileName) {
        // Initializes object attributes
        this->csvFileName = *csvFileName;
        this->csvFileString = getCsvFileString();
        // TODO: Handle possible error from getCsvString
        setHeaderArray();
        setDataArray();
    }

    // Saves Spreadsheet object to disk
    void saveSpreadsheetAsCsv(std::string newCsvFileName) {
        // Gets string representation of Spreadsheet object
        std::string spreadsheetCsvString = this->getSpreadsheetString();
        std::cout << spreadsheetCsvString;

        // Saves spreadsheetCsvString to csv file
        std::ofstream newCsvFile;
        newCsvFile.open(newCsvFileName);
        newCsvFile << spreadsheetCsvString;
        newCsvFile.close();
    }
};

int main(int argc, char *argv[]) {
    // Temp values
    std::string CSV_FILE_NAME = "MOCK_DATA.csv";

    // Creates Spreadsheet object, which loads specified csv file into memory
    Spreadsheet spreadsheet(&CSV_FILE_NAME);

    // Saves Spreadsheet object to disk as csv
    spreadsheet.saveSpreadsheetAsCsv("MOCK_DATA_NEW.csv");

    std::cout << "=====DONE=====\n";

    // STEP 2: Save csv data from memory to disk
    // - figure out how to write to file

    // STEP 3: Use Qt to make spreadsheet GUI
    // - figure out how to use Qt
    // - implement cells in Qt GUI to view CSV data as spreadsheet
    // - implement editing cells of spreadsheet
    // - implement "Save" button

    return 0;
}