# ============================================================================
# Validate parameters
# ============================================================================

if(NOT DEFINED SPIRV_FILE)
    message(FATAL_ERROR
        "SPIRV_FILE not specified"
    )
endif()

if(NOT DEFINED SOURCE_FILE)
    message(FATAL_ERROR
        "SOURCE_FILE not specified"
    )
endif()

if(NOT DEFINED OUTPUT_CPP)
    message(FATAL_ERROR
        "OUTPUT_CPP not specified"
    )
endif()

if(NOT DEFINED OUTPUT_HPP)
    message(FATAL_ERROR
        "OUTPUT_HPP not specified"
    )
endif()

if(NOT DEFINED SHADER_IDENTIFIER)
    message(FATAL_ERROR
        "SHADER_IDENTIFIER not specified"
    )
endif()

if(NOT DEFINED SHADER_NAMESPACE)
    message(FATAL_ERROR
        "SHADER_NAMESPACE not specified"
    )
endif()

if(NOT DEFINED SHADER_PATH)
    message(FATAL_ERROR
        "SHADER_PATH not specified"
    )
endif()

if(NOT EXISTS "${SPIRV_FILE}")
    message(FATAL_ERROR
        "SPIR-V file does not exist: ${SPIRV_FILE}"
    )
endif()

if(NOT EXISTS "${SOURCE_FILE}")
    message(FATAL_ERROR
        "Shader source does not exist: ${SOURCE_FILE}"
    )
endif()

# ============================================================================
# Read SPIR-V
# ============================================================================

file(
    READ
    "${SPIRV_FILE}"
    SPIRV_HEX
    HEX
)

string(
    LENGTH
    "${SPIRV_HEX}"
    SPIRV_HEX_LENGTH
)

math(
    EXPR
    SPIRV_BYTE_COUNT
    "${SPIRV_HEX_LENGTH} / 2"
)

# SPIR-V consists of 32-bit words.

math(
    EXPR
    SPIRV_REMAINDER
    "${SPIRV_BYTE_COUNT} % 4"
)

if(NOT SPIRV_REMAINDER EQUAL 0)
    message(
        FATAL_ERROR
        "Invalid SPIR-V file size "
        "(${SPIRV_BYTE_COUNT} bytes): "
        "${SPIRV_FILE}"
    )
endif()

math(
    EXPR
    SPIRV_WORD_COUNT
    "${SPIRV_BYTE_COUNT} / 4"
)

# ============================================================================
# Convert SPIR-V bytes into uint32_t literals
# ============================================================================

set(SPIRV_WORDS "")

if(SPIRV_WORD_COUNT GREATER 0)

    math(
        EXPR
        LAST_SPIRV_WORD
        "${SPIRV_WORD_COUNT} - 1"
    )

    foreach(
        WORD_INDEX
        RANGE
        0
        ${LAST_SPIRV_WORD}
    )

        #
        # HEX string has two characters per byte.
        #
        # One uint32_t = 4 bytes = 8 hex characters.
        #

        math(
            EXPR
            HEX_OFFSET
            "${WORD_INDEX} * 8"
        )

        string(
            SUBSTRING
            "${SPIRV_HEX}"
            "${HEX_OFFSET}"
            8
            WORD_HEX
        )

        # --------------------------------------------------------------------
        # SPIR-V files are little endian.
        #
        # File bytes:
        #
        #     03 02 23 07
        #
        # should become:
        #
        #     0x07230203
        # --------------------------------------------------------------------

        string(
            SUBSTRING
            "${WORD_HEX}"
            0
            2
            B0
        )

        string(
            SUBSTRING
            "${WORD_HEX}"
            2
            2
            B1
        )

        string(
            SUBSTRING
            "${WORD_HEX}"
            4
            2
            B2
        )

        string(
            SUBSTRING
            "${WORD_HEX}"
            6
            2
            B3
        )

        set(
            WORD_LITERAL
            "0x${B3}${B2}${B1}${B0}u"
        )

        string(
            APPEND
            SPIRV_WORDS
            "    ${WORD_LITERAL},\n"
        )

    endforeach()

endif()

# ============================================================================
# Read original GLSL source
# ============================================================================
#
# Read as HEX rather than text so absolutely any source characters can safely
# be represented in generated C++.
#

file(
    READ
    "${SOURCE_FILE}"
    SOURCE_HEX
    HEX
)

string(
    LENGTH
    "${SOURCE_HEX}"
    SOURCE_HEX_LENGTH
)

math(
    EXPR
    SOURCE_BYTE_COUNT
    "${SOURCE_HEX_LENGTH} / 2"
)

# ============================================================================
# Convert GLSL source into a C++ char array
# ============================================================================

set(SOURCE_BYTES "")

if(SOURCE_BYTE_COUNT GREATER 0)

    math(
        EXPR
        LAST_SOURCE_BYTE
        "${SOURCE_BYTE_COUNT} - 1"
    )

    foreach(
        BYTE_INDEX
        RANGE
        0
        ${LAST_SOURCE_BYTE}
    )

        math(
            EXPR
            HEX_OFFSET
            "${BYTE_INDEX} * 2"
        )

        string(
            SUBSTRING
            "${SOURCE_HEX}"
            "${HEX_OFFSET}"
            2
            BYTE_HEX
        )

        string(
            APPEND
            SOURCE_BYTES
            "    static_cast<char>(0x${BYTE_HEX}),\n"
        )

    endforeach()

endif()

#
# Add a null terminator for convenience.
#
# std::string_view still receives the explicit original source size, meaning
# the terminator is NOT considered part of the shader source.
#

string(
    APPEND
    SOURCE_BYTES
    "    '\\0',\n"
)

# ============================================================================
# Generate header
# ============================================================================

file(
    WRITE
    "${OUTPUT_HPP}"
"#pragma once

namespace ${SHADER_NAMESPACE}
{

struct ShaderBinary;

extern const ShaderBinary ${SHADER_IDENTIFIER};

}
"
)

# ============================================================================
# Generate source
# ============================================================================

file(
    WRITE
    "${OUTPUT_CPP}"
"#include \"${SHADER_IDENTIFIER}.hpp\"
#include \"ShaderRegistry.hpp\"

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string_view>

namespace ${SHADER_NAMESPACE}
{

namespace
{

constexpr std::array<std::uint32_t, ${SPIRV_WORD_COUNT}>
${SHADER_IDENTIFIER}_spirv =
{
${SPIRV_WORDS}
};

constexpr std::array<char, ${SOURCE_BYTE_COUNT} + 1>
${SHADER_IDENTIFIER}_source =
{
${SOURCE_BYTES}
};

}

const ShaderBinary ${SHADER_IDENTIFIER}
{
    .path = \"${SHADER_PATH}\",

    .spirv = std::span<const std::uint32_t>
    {
        ${SHADER_IDENTIFIER}_spirv.data(),
        ${SHADER_IDENTIFIER}_spirv.size()
    },

    .source = std::string_view
    {
        ${SHADER_IDENTIFIER}_source.data(),
        ${SOURCE_BYTE_COUNT}
    }
};

}
"
)