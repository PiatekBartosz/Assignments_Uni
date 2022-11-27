#include "FileFactory.h"
#include "RNG.h"
#include <vector>
#include <iostream>

int main(void) {
	IFile *FileCSV = FileFactory::Open("Point.csv", "w");
	Point point;
	std::vector<Point> vectorcsv;
	for (int i = 0; i < 1000; i++) {
		vectorcsv.push_back(Point(rand(), rand(), rand()));
	}
	FileCSV->Write(vectorcsv);
	 
	IFile* FileBIN = FileFactory::Open("test.bin", "r");
	std::vector<Point> vectorbin;
	FileBIN->Read(vectorbin);

	for (size_t i = 0; i < vectorbin.size(); i++) {
		std::cout << vectorbin[i].x << vectorbin[i].y << vectorbin[i].z << "\n";
	}
}