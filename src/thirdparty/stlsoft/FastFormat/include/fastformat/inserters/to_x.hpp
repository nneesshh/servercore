/* /////////////////////////////////////////////////////////////////////////
 * File:        fastformat/inserters/to_x.hpp
 *
 * Purpose:     Inserter functions for integral types in hex format
 *
 * Created:     19th December 2009
 * Updated:     10th January 2017
 *
 * Home:        http://www.fastformat.org/
 *
 * Copyright (c) 2009-2017, Matthew Wilson and Synesis Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Software nor the
 *   names of any contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file fastformat/inserters/to_x.hpp
 *
 * [C++ only] Inserter functions for integral types in hex format.
 */

#ifndef FASTFORMAT_INCL_FASTFORMAT_INSERTERS_HPP_TO_X
#define FASTFORMAT_INCL_FASTFORMAT_INSERTERS_HPP_TO_X

/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

#ifndef FASTFORMAT_DOCUMENTATION_SKIP_SECTION
# define FASTFORMAT_VER_FASTFORMAT_INSERTERS_HPP_TO_X_MAJOR     1
# define FASTFORMAT_VER_FASTFORMAT_INSERTERS_HPP_TO_X_MINOR     0
# define FASTFORMAT_VER_FASTFORMAT_INSERTERS_HPP_TO_X_REVISION  4
# define FASTFORMAT_VER_FASTFORMAT_INSERTERS_HPP_TO_X_EDIT      10
#endif /* !FASTFORMAT_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <fastformat/inserters/integer.hpp>

/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#if !defined(FASTFORMAT_NO_NAMESPACE)
namespace fastformat
{
namespace inserters
{
#endif /* !FASTFORMAT_NO_NAMESPACE */

/* /////////////////////////////////////////////////////////////////////////
 * inserter functions
 */

/** Inserts the hexadecimal string form of an integral value
 *
 * \ingroup group__inserters
 *
 * \param value The integral value to be converted to hexadecimal string
 *   form
 *
 * \return An instance of an insertable type containing the string form of
 *   the integer
 *
 * \pre I is an integral type
 */
template <typename I>
inline ximpl_integer::ff_to_i_r_t_ to_x(
    I const& value
)
{
    STLSOFT_STATIC_ASSERT(stlsoft::is_integral_type<I>::value);

    return 
#if !defined(FASTFORMAT_NO_NAMESPACE)
      ::fastformat::inserters::
#endif /* !FASTFORMAT_NO_NAMESPACE */
        ximpl_integer::integer_helper_hex_3(
                value
            ,   ximpl_integer::default_width_sentinel_()
            ,   ximpl_integer::default_precision_sentinel_()
            ,   ximpl_integer::FF_ximpl_REQUIRE_LOWERCASE
            );
}

/** Inserts the hexadecimal string form of an integral value
 *
 * \ingroup group__inserters
 *
 * \param value The integral value to be converted to hexadecimal string
 *   form
 *
 * \return An instance of an insertable type containing the string form of
 *   the integer
 *
 * \pre I is an integral type
 */
template <typename I>
inline ximpl_integer::ff_to_i_r_t_ to_X(
    I const& value
)
{
    STLSOFT_STATIC_ASSERT(stlsoft::is_integral_type<I>::value);

    return 
#if !defined(FASTFORMAT_NO_NAMESPACE)
      ::fastformat::inserters::
#endif /* !FASTFORMAT_NO_NAMESPACE */
        ximpl_integer::integer_helper_hex_3(
                value
            ,   ximpl_integer::default_width_sentinel_()
            ,   ximpl_integer::default_precision_sentinel_()
            ,   ximpl_integer::FF_ximpl_REQUIRE_UPPERCASE
            );
}

/** Inserts the hexadecimal string form of an integral value
 *
 * \ingroup group__inserters
 *
 * \param value The integral value to be converted to hexadecimal string
 *   form
 * \param minimumWidth The minimum width of the result. If negative, the
 *   integer is aligned to the left of the resulting field
 *
 * \return An instance of an insertable type containing the string form of
 *   the integer
 *
 * \pre I is an integral type
 * \pre abs(minimumWidth) < 512
 */
template <typename I>
inline ximpl_integer::ff_to_i_r_t_ to_x(
    I const&    value
,   int         minimumWidth
)
{
    STLSOFT_STATIC_ASSERT(stlsoft::is_integral_type<I>::value);

    return 
#if !defined(FASTFORMAT_NO_NAMESPACE)
      ::fastformat::inserters::
#endif /* !FASTFORMAT_NO_NAMESPACE */
        ximpl_integer::integer_helper_hex_3(
                value
            ,   minimumWidth
            ,   ximpl_integer::default_precision_sentinel_()
            ,   ximpl_integer::FF_ximpl_REQUIRE_LOWERCASE
            );
}

/** Inserts the hexadecimal string form of an integral value
 *
 * \ingroup group__inserters
 *
 * \param value The integral value to be converted to hexadecimal string
 *   form
 * \param minimumWidth The minimum width of the result. If negative, the
 *   integer is aligned to the left of the resulting field
 *
 * \return An instance of an insertable type containing the string form of
 *   the integer
 *
 * \pre I is an integral type
 * \pre abs(minimumWidth) < 512
 */
template <typename I>
inline ximpl_integer::ff_to_i_r_t_ to_X(
    I const&    value
,   int         minimumWidth
)
{
    STLSOFT_STATIC_ASSERT(stlsoft::is_integral_type<I>::value);

    return 
#if !defined(FASTFORMAT_NO_NAMESPACE)
      ::fastformat::inserters::
#endif /* !FASTFORMAT_NO_NAMESPACE */
        ximpl_integer::integer_helper_hex_3(
                value
            ,   minimumWidth
            ,   ximpl_integer::default_precision_sentinel_()
            ,   ximpl_integer::FF_ximpl_REQUIRE_UPPERCASE
            );
}

/** Inserts the hexadecimal string form of an integral value
 *
 * \ingroup group__inserters
 *
 * \param value The integral value to be converted to hexadecimal string
 *   form
 * \param minimumWidth The minimum width of the result. If negative, the
 *   integer is aligned to the left of the resulting field
 * \param precision The minimum number of digits in the field, which will
 *   result in zero-padding if the given integer has fewer digits
 *
 * \return An instance of an insertable type containing the string form of
 *   the integer
 *
 * \pre I is an integral type
 * \pre abs(minimumWidth) < 512
 * \pre decimalPlaces <= minimumWidth
 */
template <typename I>
inline ximpl_integer::ff_to_i_r_t_ to_x(
    I const&    value
,   int         minimumWidth
,   int         precision
)
{
    STLSOFT_STATIC_ASSERT(stlsoft::is_integral_type<I>::value);

    return 
#if !defined(FASTFORMAT_NO_NAMESPACE)
      ::fastformat::inserters::
#endif /* !FASTFORMAT_NO_NAMESPACE */
        ximpl_integer::integer_helper_hex_3(
                value
            ,   minimumWidth
            ,   precision
            ,   ximpl_integer::FF_ximpl_REQUIRE_LOWERCASE
            );
}

/** Inserts the hexadecimal string form of an integral value
 *
 * \ingroup group__inserters
 *
 * \param value The integral value to be converted to hexadecimal string
 *   form
 * \param minimumWidth The minimum width of the result. If negative, the
 *   integer is aligned to the left of the resulting field
 * \param precision The minimum number of digits in the field, which will
 *   result in zero-padding if the given integer has fewer digits
 *
 * \return An instance of an insertable type containing the string form of
 *   the integer
 *
 * \pre I is an integral type
 * \pre abs(minimumWidth) < 512
 * \pre decimalPlaces <= minimumWidth
 */
template <typename I>
inline ximpl_integer::ff_to_i_r_t_ to_X(
    I const&    value
,   int         minimumWidth
,   int         precision
)
{
    STLSOFT_STATIC_ASSERT(stlsoft::is_integral_type<I>::value);

    return 
#if !defined(FASTFORMAT_NO_NAMESPACE)
      ::fastformat::inserters::
#endif /* !FASTFORMAT_NO_NAMESPACE */
        ximpl_integer::integer_helper_hex_3(
                value
            ,   minimumWidth
            ,   precision
            ,   ximpl_integer::FF_ximpl_REQUIRE_UPPERCASE
            );
}

/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#if !defined(FASTFORMAT_NO_NAMESPACE)
} // namespace inserters
using ::fastformat::inserters::to_x;
using ::fastformat::inserters::to_X;
} // namespace fastformat
#endif /* !FASTFORMAT_NO_NAMESPACE */

/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

/* ////////////////////////////////////////////////////////////////////// */

#endif /* !FASTFORMAT_INCL_FASTFORMAT_INSERTERS_HPP_TO_X */

/* ///////////////////////////// end of file //////////////////////////// */
