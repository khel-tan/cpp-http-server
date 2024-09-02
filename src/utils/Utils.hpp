#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>

/**
 * @file Utils.hpp
 * @brief Utility functions for trimming whitespace from strings.
 *
 * This file contains utility functions for trimming whitespace
 * from the left, right, and both sides of a string respectively.
 */

/**
 * @brief Trims whitespace on the left of the input in place.
 * @param s The string to be modified in place.
 */
void ltrim(std::string &s);

/**
 * @brief Trims whitespace on the right of the input in place.
 * @param s The string to be modified in place.
 */
void rtrim(std::string &s);

/**
 * @brief Trims whitespace on both ends of the input in place.
 * @param s The string to be modified in place.
 */
void trim(std::string &s);

#endif // UTILS_HPP_
