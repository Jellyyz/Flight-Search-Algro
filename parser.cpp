/**
 * @file parser.cpp
 * @brief Definitions of the functions declared in "parser.h".
 * @version 0.2
 * @date 2021-11-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "parser.h"
#include <iostream>

/** parse_line
 * @brief Parse a single CSV line to its separate fields (a field is whatever is enclosed by commas -> "fields[0]",field[1],field[2]).
 * 
 * @param line = CSV line.
 * @return vector<string> = Fields.
 */
vector<string> parse_line(const string &line) {
    enum parser_state current_state = OUT_QUOTE;
    vector<string> return_fields;

    // For the first field that is not enclosed between two commas.
    return_fields.push_back("");

    size_t i = 0;
    for (const char c : line) {
        switch (c) {
            case ',' :
                switch (current_state) {
                    // Required for edge cases where commas are within a quoted field.
                    case IN_QUOTE :
                        return_fields[i].push_back(c);
                        break;
                    // Finalize the last field and push a new field.
                    case OUT_QUOTE :
                        return_fields.push_back("");
                        i++;
                        break;
                }
                break;
            case '\"':
                // Update state just in case for those edge cases.
                current_state = (current_state == IN_QUOTE) ? OUT_QUOTE : IN_QUOTE;
                break;
            default:
                return_fields[i].push_back(c);
                break;
        }
    }
    return return_fields;
}