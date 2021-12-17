/**
 * @file parser.h
 * @brief CSV parsing tools.
 * @version 0.2
 * @date 2021-11-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

// States of the CSV parser.
enum parser_state {
    IN_QUOTE,   // Current character is within a quote (i.e. "..c..").
    OUT_QUOTE,  // Current character is not within a quote (i.e. ..c..).
};

vector<string> parse_line(const string &line);