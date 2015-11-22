#pragma once

#include <string>
#include <vector>
#include <locale>
#include <sstream>

std::string toUpper(const std::string& s);
std::string toLower(const std::string& s);

std::vector<std::string> explode(const std::string& str, const char delimiter);
std::string implode(std::vector<std::string> & elements, char delimiter);
