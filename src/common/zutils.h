#pragma once

#include "zvalue.h"

class ZUtils {
public:
    // Php Value Utils

    static zmsg_t *phpvalue_to_zmsg(const Php::Value &value) {
        ZValue *val = (ZValue *) &value;
        return val->to_zmsg();
    }

    static zmq_pollitem_t phpvalue_to_pollitem(const Php::Value &value, short event = 0) {
        ZValue *val = (ZValue *) &value;
        return val->to_pollitem(event);
    }

    // String Utils

    static std::string toUpper(const std::string& s) {
        std::string result;

        std::locale loc;
        for (unsigned int i = 0; i < s.length(); ++i)
        {
            result += std::toupper(s.at(i), loc);
        }

        return result;
    }

    static std::string toLower(const std::string& s) {
        std::string result;

        std::locale loc;
        for (unsigned int i = 0; i < s.length(); ++i)
        {
            result += std::tolower(s.at(i), loc);
        }

        return result;
    }

    static std::vector<std::string> explode(const std::string& str, const char delimiter) {
      std::vector<std::string> elements;
      std::stringstream stream(str);
      std::string item;
      while (std::getline(stream, item, delimiter))
        elements.push_back(item);

      return elements;
    }

    static std::string implode(std::vector<std::string> & elements, char delimiter) {
      std::string full;
      for (std::vector<std::string>::iterator it = elements.begin(); it != elements.end(); ++it)
      {
        full += (*it);
        if (it != elements.end()-1)
          full += delimiter;

      }
      return full;
    }

};