#pragma once
#include <string>
#include "BinaryFile.h"
#include "CsvFile.h"

static class FileFactory
{
public:
	static IFile* Open(const std::string, const std::string);
};

