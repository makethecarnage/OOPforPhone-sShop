#ifndef TRYPROJECT_LIBRARY_HPP
#define TRYPROJECT_LIBRARY_HPP

#include <string>
#include <vector>


std::vector<std::string> split(const std::string &s, char delim) {

    std::vector<std::string> elems;
    size_t pos = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == delim) {
            elems.push_back(s.substr(pos, i - pos));
            pos = i + 1;
        }
    }
    elems.push_back(s.substr(pos, s.size()));
    return elems;

}

std::string& trim(std::string& str, const std::string& whitespace = " ") {

    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return str; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.assign(str, strBegin, strRange);
}


#endif //TRYPROJECT_LIBRARY_HPP
