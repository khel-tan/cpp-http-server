#ifndef UTILS_HPP_

#define UTILS_HPP_

#include <string>

/*
 * INFO: Utility functions for trimming whitespace from
 * left and right of a string respectively
 */

/**
 * @brief Trims whitespace on the left of the input in place
 */
void ltrim(std::string &s);

/**
 * @brief Trims whitespace on the right of the input in
 * place
 */
void rtrim(std::string &s);
/**
 * @brief Trims whitespace on both ends of the input in
 * place
 */
void trim(std::string &s);

#endif // !MESSAGE_UTILS_HPP_
