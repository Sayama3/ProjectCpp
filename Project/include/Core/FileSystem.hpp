//
// Created by ianpo on 18/07/2024.
//

#pragma once

#include <filesystem>
#include <string>
#include <ostream>
#include <fstream>

namespace PC {
	namespace FS {
		inline bool WriteTextInFile(const std::filesystem::path& path, const std::string& text)
		{
			std::ofstream ofile(path);
			if (!ofile.is_open()) {
				return false;
			}
			ofile << text;
			ofile.close();
			return true;
		}

		inline bool ReadTextInFile(const std::filesystem::path& path, std::string& text)
		{
			std::ifstream ifile(path);
			if (!ifile.is_open()) {
				return false;
			}
			std::stringstream buffer;
			buffer << ifile.rdbuf();
			text = buffer.str();
			ifile.close();
			return true;
		}

		inline std::string ReadTextInFile(const std::filesystem::path& path)
		{
			std::string str;
			ReadTextInFile(path, str);
			return std::move(str);
		}
	}
}