#include "CsvFile.h"

IFile::FileError CsvFile::Write(const std::vector<Point>& v)
{
	FileError result = FileError(ACCESS_DENIED);

	if (!file.is_open()) {
		result = FileError(FILE_INVALID);
	}
	else if (openMode & std::fstream::out) {
		for (unsigned int i = 0; i < v.size(); i++) {
			WriteLine(v[i]);
		}

		//change the length
		file.seekg(0, std::fstream::end);
		length = file.tellg();
		file.seekg(0, std::fstream::beg);

		result = FileError(SUCCESS);
	}
	return result;
}

IFile::FileError CsvFile::Read(std::vector<Point>& readout)
{
	FileError error = FileError(ACCESS_DENIED);

	if (!file.is_open())
	{
		error = FileError(FILE_INVALID);
	}
	else if (openMode & std::fstream::in)
	{
		// clear flags to enable using Read method many times
		file.clear();
		file.seekg(0, std::fstream::beg);
		readout.clear();
		std::string line;
		std::vector<std::string> temp;
		Point point;

		while (std::getline(file, line)) {
			temp = Split(line, ',');
			// sizeof(Point) instead of 3
			if(temp.size() == 3) {
				point.x = std::stod(temp[0]);
				point.y = std::stod(temp[1]);
				point.z = std::stod(temp[2]);
				readout.push_back(point);
			}
		temp.clear();
		}
		error = FileError(SUCCESS);
	}
	return error;
}

IFile::FileError CsvFile::Read(Point& p, const unsigned long index)
{
	FileError error = FileError(ACCESS_DENIED);

	if (!file.is_open())
	{
		error = FileError(FILE_INVALID);
	}

	else if (openMode & std::fstream::in)
	{
		// clear flags to enable using Read method many times
		file.clear();
		file.seekg(0, std::fstream::beg);
		unsigned long lineNum = 0;
		bool found = false;
		std::string line;

		while (getline(file, line) ) {
			if (index == lineNum) {
				std::vector<std::string>temp = Split(line, ',');
				if (temp.size() == 3) {
					p.x = std::stod(temp[0]);
					p.y = std::stod(temp[1]);
					p.z = std::stod(temp[2]);
				}
				found = true;
				break;
			}
			lineNum++;
		}
		found ? error = FileError(SUCCESS) : error = FileError(OUT_OF_BOUNDS);
	}
	return error;
}


void CsvFile::WriteLine(const Point& p)
{
	file << p.x << "," << p.y << "," << p.z << "\n";
}


std::vector<std::string> CsvFile::Split(const std::string str, const char sep)
{
	std::vector<std::string> result;

	std::stringstream ss(str);
	std::string item;
	
	while (std::getline(ss, item, sep)) {
		result.push_back(item);
	}

	return result;
}
