#include <iostream>
#include <fstream>
#include <string>

#define CSV_FILE_NAME	"MOCK_DATA.csv"
#define NUM_COLUMNS	5
#define NUM_DATA_ROWS	100


class Spreadsheet {
	public:
		std::string headerArray[NUM_COLUMNS];
		std::string dataArray[NUM_DATA_ROWS][NUM_COLUMNS];
};


int main(int argc, char *argv[]){
	// Opens file in read mode
	std::ifstream csv_file;
	csv_file.open(CSV_FILE_NAME, std::ios::in);

	// Makes sure file is open
	if (csv_file.is_open() == false){
		std::cout << "ERROR: Could not open file\n";
		return 1;
	}

	// Feeds csv file into string line by line
	std::string line;
	std::string csvString = "";
	while(getline(csv_file, line)){
		csvString += line + ",";
	}
	//std::cout << csvString << "\n";

	// Closes file
	csv_file.close();

	// Reads header into Spreadsheet object
	Spreadsheet sheet;		// Contains all spreadsheet data
	int headerEndIndex = 0;		// Keeps track of string index at which the header ends and the data starts
	int headerLength = 0;		// Keeps track of header length
	int numHeadersFound = 0;	// Keeps track of # of headers found
	int numHeaders = NUM_COLUMNS;	// Keeps track of # of headers that exist
	for (uint i=0; i<csvString.length(); i++){
		// If the next character is a comma, then we must be at the end of a header
		if (csvString[i]==','){
			// Extracts header from string
			std::string header = csvString.substr(i-headerLength, headerLength);
			//std::cout << header << "\n";
			
			// Resets header length
			headerLength = 0;
		
			// Adds new header to Spreadsheet object and checks to see if there are any more headers to find
			numHeadersFound ++;
			int headerIndex = numHeadersFound - 1;
			sheet.headerArray[headerIndex] = header;
			// If all headers have been found, records index at which headers end and exits loop
			if (numHeadersFound == numHeaders){
				headerEndIndex = i + 1; // Adds 1 so that index points to first character of data
				break;
			}
		}
		else {
			headerLength += 1;
		}
	}

	// Loads data into Spreadsheet object
	int dataLength = 0;	// Keeps track of the size of the data string
	for (uint i=headerEndIndex; i<csvString.length(); i++){
		std::cout << csvString[i];

		if (csvString[i]==','){

			dataLength = 0;
		}
		else {
			dataLength += 1;
		}
	}

	// STEP 2: Save csv data from memory to disk
	// - figure out how to write to file
	
	// STEP 3: Use Qt to make spreadsheet GUI
	// - figure out how to use Qt
	// - implement cells in Qt GUI to view CSV data as spreadsheet
	// - implement editing cells of spreadsheet
	// - implement "Save" button

	return 0;
}
