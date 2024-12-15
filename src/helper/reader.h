//
// Created by rico on 12/1/24.
//

#ifndef READER_H
#define READER_H
#include <fstream>
#include <string_view>


inline auto read(const std::string_view path_to_file) {

    std::ifstream file((path_to_file.data()));

    std::vector<std::string> result;
    std::string str;

    while ( !file.eof() ) {
        std::getline (file, str);
        result.push_back(str);
    }
    return result;
}


#endif //READER_H
