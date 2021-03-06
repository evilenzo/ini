/**
 * @file
 * @brief This file contains declaration of Error struct
 * @author Evilenzo
 * @version 1.0
 */

#pragma once

#include <memory>

namespace ES {


/// @brief Error codes enum
enum class Code { BROKEN_INPUT_STREAM, MISSING_FIRST_SECTION, WRONG_LINE };

/// @brief Error struct containing code and line number
struct Error {
    /// @brief Error code
    Code code = {};

    /// @brief Line number
    std::size_t line = {};

    /**
     * @brief Constructor with param initialization
     * @param _code error code
     * @param _line line number
     */
    Error(Code _code = {}, std::size_t _line = {}) : code(_code), line(_line) {}

    /// @brief Copy constructor
    Error(const Error& error) = default;

    /// @brief Move constructor
    Error(Error&& error) noexcept = default;

    /// @brief Copy assignment operator
    auto operator=(const Error& error) -> Error& = default;

    /// @brief Move assignment operator
    auto operator=(Error&& error) noexcept -> Error& = default;

    /// @brief Empty destructor
    ~Error() = default;
};


}  // namespace ES
