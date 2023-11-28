//
// Created by Adnan Vatric on 18.02.23.
//

#include "program_options.h"

#include <vector>
#include <iostream>

/**
 * Get options passed to the program
 *
 * @param args
 * @param option_name
 * @return
 */
std::string_view program_options::get(
        const std::vector<std::string_view> &args,
        const std::string_view &option_name) {
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == option_name)
            if (it + 1 != end)
                return *(it + 1);
    }

    return "";
}

/**
 * Check if option exists
 *
 * @param args
 * @param option_name
 * @return
 */
bool program_options::has(
        const std::vector<std::string_view> &args,
        const std::string_view &option_name) {
    for (auto arg: args) {
        if (arg == option_name)
            return true;
    }

    return false;
}

/**
 * Output description
 */
void program_options::description() {
    std::cout.setf(std::ios::right, std::ios::adjustfield);
    std::cout.width(50);
    std::cout << "Usage of the convex hull calculator" << std::endl << std::endl;
    std::cout.setf(std::ios::right, std::ios::adjustfield);
    std::cout.width(39);
    std::cout << "-d <number>: Hull dimension (10 - 10 000)" << std::endl;
    std::cout.width(45);
    std::cout << "-v: Verbose mode" << std::endl;
    std::cout.width(19);
    std::cout << "-h: Help" << std::endl << std::endl;
}
