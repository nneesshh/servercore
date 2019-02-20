/* /////////////////////////////////////////////////////////////////////////
 * File:        fastformat/shims/access/string/string_slice.hpp
 *
 * Purpose:     Defines string access shims for ff_string_slice_t
 *
 * Created:     11th November 2013
 * Updated:     10th January 2017
 *
 * Home:        http://www.fastformat.org/
 *
 * Copyright (c) 2006-2017, Matthew Wilson and Synesis Software
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
 * - Neither the names of Matthew Wilson and Synesis Software nor the names
 *   of any contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
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


/** \file fastformat/shims/access/string/string_slice.hpp
 *
 * [C++ only] Defines string access shims for ff_string_slice_t
 */

#ifndef FASTFORMAT_INCL_FASTFORMAT_SHIMS_ACCESS_STRING_HPP_STRING_SLICE
#define FASTFORMAT_INCL_FASTFORMAT_SHIMS_ACCESS_STRING_HPP_STRING_SLICE

/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

#ifndef FASTFORMAT_DOCUMENTATION_SKIP_SECTION
# define FASTFORMAT_VER_FASTFORMAT_SHIMS_ACCESS_STRING_HPP_STRING_SLICE_MAJOR       1
# define FASTFORMAT_VER_FASTFORMAT_SHIMS_ACCESS_STRING_HPP_STRING_SLICE_MINOR       0
# define FASTFORMAT_VER_FASTFORMAT_SHIMS_ACCESS_STRING_HPP_STRING_SLICE_REVISION    3
# define FASTFORMAT_VER_FASTFORMAT_SHIMS_ACCESS_STRING_HPP_STRING_SLICE_EDIT        6
#endif /* !FASTFORMAT_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef FASTFORMAT_DOCUMENTATION_SKIP_SECTION
# include <fastformat/fastformat.h>
#endif /* !FASTFORMAT_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#if !defined(FASTFORMAT_NO_NAMESPACE)
namespace fastformat
{
#endif /* !FASTFORMAT_NO_NAMESPACE */
#ifndef FASTFORMAT_DOCUMENTATION_SKIP_SECTION
namespace ximpl_SAS_string_slice_
{
#endif /* !FASTFORMAT_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * string access shims
 *
 * Shims are defined as follows (where F+ means fastformat namespace enabled;
 * S- means stlsoft namespace disabled):
 *
 * 1. F+ / S+ : in stlsoft namespace only
 * 2. F+ / S- : in fastformat namespace only
 * 3. F- / S+ : in stlsoft namespace only
 * 3. F- / S- : in global namespace only
 *
 * In all cases, the shims are defined within the (enclosed) namespace
 * ximpl_SAS_string_slice_ and then introduced into the appropriate
 * namespace proper via using statement.
 *
 * Furthermore, for compilers that do not support ADL, in case 2 above, the
 * symbols are also introduced into the global namespace.
 */

# if defined(FASTFORMAT_NO_NAMESPACE)
 /* F- */
# else /* ? FASTFORMAT_NO_NAMESPACE */
 /* F+ */
using ::fastformat::ff_char_t;
using ::fastformat::ff_string_slice_t;
# endif /* FASTFORMAT_NO_NAMESPACE */

/** Returns a possibly non-nul-terminated non-NULL C-style string representing the slice */
inline
#ifdef FASTFORMAT_USE_WIDE_STRINGS
wchar_t const*
c_str_data_w(
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
char const*
c_str_data_a(
#endif /* !FASTFORMAT_USE_WIDE_STRINGS */
    ff_string_slice_t const& slice
)
{
    return slice.ptr;
}

/** Returns a possibly non-nul-terminated non-NULL C-style string representing the slice */
inline
ff_char_t const*
c_str_data(
    ff_string_slice_t const& slice
)
{
#ifdef FASTFORMAT_USE_WIDE_STRINGS
    return c_str_data_w(slice);
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
    return c_str_data_a(slice);
#endif /* !FASTFORMAT_USE_WIDE_STRINGS */
}

/** Returns the number of characters in the length of the C-style string representing the slice */
inline
size_t
#ifdef FASTFORMAT_USE_WIDE_STRINGS
c_str_len_w(
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
c_str_len_a(
#endif /* !FASTFORMAT_USE_WIDE_STRINGS */
    ff_string_slice_t const& slice
)
{
    return slice.len;
}

/** Returns the number of characters in the length of the C-style string representing the slice */
inline
size_t
c_str_len(
    ff_string_slice_t const& slice
)
{
#ifdef FASTFORMAT_USE_WIDE_STRINGS
    return c_str_len_w(slice);
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
    return c_str_len_a(slice);
#endif /* !FASTFORMAT_USE_WIDE_STRINGS */
}

/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef FASTFORMAT_DOCUMENTATION_SKIP_SECTION
} /* namespace ximpl_SAS_string_slice_ */
#endif /* !FASTFORMAT_DOCUMENTATION_SKIP_SECTION */
# if !defined(FASTFORMAT_NO_NAMESPACE)
} /* namespace fastformat */
#endif /* !FASTFORMAT_NO_NAMESPACE */

/* /////////////////////////////////////////////////////////////////////////
 * Introduction of shim overloads into appropriate namespace, ...
 */

#ifdef _STLSOFT_NO_NAMESPACE
 /* S- */
# if defined(FASTFORMAT_NO_NAMESPACE)
 /* F- */
# else /* ? FASTFORMAT_NO_NAMESPACE */
 /* F+ */
namespace fastformat
{
# endif /* FASTFORMAT_NO_NAMESPACE */
#else /* ? _STLSOFT_NO_NAMESPACE */
 /* S+ */
namespace stlsoft
{
#endif /* _STLSOFT_NO_NAMESPACE */

#if defined(FASTFORMAT_NO_NAMESPACE)
 /* F- */
# ifdef FASTFORMAT_USE_WIDE_STRINGS
    using             ::ximpl_SAS_string_slice_::c_str_data_w;
    using             ::ximpl_SAS_string_slice_::c_str_len_w;
# else /* ? FASTFORMAT_USE_WIDE_STRINGS */
    using             ::ximpl_SAS_string_slice_::c_str_data_a;
    using             ::ximpl_SAS_string_slice_::c_str_len_a;
# endif /* !FASTFORMAT_USE_WIDE_STRINGS */
    using             ::ximpl_SAS_string_slice_::c_str_data;
    using             ::ximpl_SAS_string_slice_::c_str_len;
#else /* ?FASTFORMAT_NO_NAMESPACE */
 /* F+ */
# ifdef FASTFORMAT_USE_WIDE_STRINGS
    using ::fastformat::ximpl_SAS_string_slice_::c_str_data_w;
    using ::fastformat::ximpl_SAS_string_slice_::c_str_len_w;
# else /* ? FASTFORMAT_USE_WIDE_STRINGS */
    using ::fastformat::ximpl_SAS_string_slice_::c_str_data_a;
    using ::fastformat::ximpl_SAS_string_slice_::c_str_len_a;
# endif /* !FASTFORMAT_USE_WIDE_STRINGS */
    using ::fastformat::ximpl_SAS_string_slice_::c_str_data;
    using ::fastformat::ximpl_SAS_string_slice_::c_str_len;
#endif /* FASTFORMAT_NO_NAMESPACE */

#ifdef _STLSOFT_NO_NAMESPACE
 /* S- */
# if defined(FASTFORMAT_NO_NAMESPACE)
 /* F- */
# else /* ? FASTFORMAT_NO_NAMESPACE */
 /* F+ */
} /* namespace fastformat */
# endif /* FASTFORMAT_NO_NAMESPACE */
#else /* ? _STLSOFT_NO_NAMESPACE */
 /* S+ */
} /* namespace stlsoft */
#endif /* _STLSOFT_NO_NAMESPACE */

/* /////////////////////////////////////
 * ... and support for those compilers
 * that don't fully implement ADL.
 */

#ifndef STLSOFT_CF_ADL_SUPPORT
# ifdef _STLSOFT_NO_NAMESPACE
 /* S- */
#  if defined(FASTFORMAT_NO_NAMESPACE)
 /* F- */
#  else /* ? FASTFORMAT_NO_NAMESPACE */
 /* F+ */
#   ifdef FASTFORMAT_USE_WIDE_STRINGS
    using ::fastformat::c_str_data_w;
    using ::fastformat::c_str_len_w;
#   else /* ? FASTFORMAT_USE_WIDE_STRINGS */
    using ::fastformat::c_str_data_a;
    using ::fastformat::c_str_len_a;
#   endif /* !FASTFORMAT_USE_WIDE_STRINGS */
    using ::fastformat::c_str_data;
    using ::fastformat::c_str_len;
#  endif /* FASTFORMAT_NO_NAMESPACE */
# else /* ? _STLSOFT_NO_NAMESPACE */
 /* S+ */
# endif /* _STLSOFT_NO_NAMESPACE */
#endif /* !STLSOFT_CF_ADL_SUPPORT */

/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

/* ////////////////////////////////////////////////////////////////////// */

#endif /* !FASTFORMAT_INCL_FASTFORMAT_SHIMS_ACCESS_STRING_HPP_STRING_SLICE */

/* ///////////////////////////// end of file //////////////////////////// */
