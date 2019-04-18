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
	// STEP 1: Load csv data from disk to memory
	// - figure out how to read from file
	// - figure out which data structure I want to use to store the data
	// - load file line-by-line (first line is headers) and pass it into data structure

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

	
	// Extracts header and data from string	and loads it into Spreadsheet object
	Spreadsheet spreadsheet;
	int cellCount = 0;		// Keeps track of # of spreadsheet cells which have been parsed
	int cellSize = 0;		// Keep track of string in cell's size in for loop below
	bool headerParsed = false;	// Keeps track of whether the header has been parsed yet
	for (int i=0; i<csvString.length(); i++){
		// If comma is encountered, then current cell must have ended
		if (csvString[i]==','){
			// Extracts current cell
			std::string currentCell = csvString.substr(i-cellSize, cellSize);
			std::cout << currentCell << ",";

			cellCount += 1;
			if (cellCount % 5 == 0){
				std::cout << "\n";
			}
			
			// If header hasn't yet been parsed, parses header
			if (headerParsed == false){
				int arrayIndex = (cellCount%5)-1;
				spreadsheet.headerArray[arrayIndex] = currentCell;
				headerParsed = true;
			}


			// Resets cell size
			cellSize = 0;
		}
		else {
			cellSize += 1;
		}
	}
	std::cout << cellCount << "\n";

	// STEP 2: Save csv data from memory to disk
	// - figure out how to write to file
	
	// STEP 3: Use Qt to make spreadsheet GUI
	// - figure out how to use Qt
	// - implement cells in Qt GUI to view CSV data as spreadsheet
	// - implement editing cells of spreadsheet
	// - implement "Save" button

	return 0;
}
