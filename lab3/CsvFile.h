#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Point.h"
#include "IFile.h"

class CsvFile : public IFile{
private:
	void WriteLine(const Point&);
	std::vector<std::string> Split(std::string, char);
public:
	using IFile::IFile;

	virtual FileError Write (const std::vector<Point>&) override;
	virtual FileError Read(std::vector<Point>&) override;
	virtual FileError Read(Point&, unsigned long) override;
};