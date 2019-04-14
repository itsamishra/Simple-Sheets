#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define CSV_FILE_NAME "MOCK_DATA.csv"

class CsvData {
	std::vector<std::string> headers;
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

	// Reads csv file, line by line
	std::string line;
	std::vector<std::string> csvLines;
	while(getline(csv_file, line)){
		csvLines.push_back(line);
	}

	// Prints out contents of file
	for (uint i=0; i<csvLines.size(); i++){
		std::cout << csvLines[i] << "\n";
	}

	// Closes file
	csv_file.close();

	// STEP 2: Save csv data from memory to disk
	// - figure out how to write to file
	
	// STEP 3: Use Qt to make spreadsheet GUI
	// - figure out how to use Qt
	// - implement cells in Qt GUI to view CSV data as spreadsheet
	// - implement editing cells of spreadsheet
	// - implement "Save" button

	return 0;
}