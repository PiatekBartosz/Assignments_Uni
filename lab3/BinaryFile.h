#pragma once
#include <fstream>
#include <vector>
#include "Point.h"
#include "IFile.h"

class BinaryFile : public IFile {
public:
	using IFile::IFile;

	virtual FileError Write(const std::vector<Point>&) override;
	virtual FileError Read(std::vector<Point>&) override;
	virtual FileError Read(Point&, const unsigned long) override;
};

