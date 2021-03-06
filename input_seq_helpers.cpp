// Interpret sequence strings.
//
// Copyright (C) 2002, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016 Gregory W. Chicares.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
//
// http://savannah.nongnu.org/projects/lmi
// email: <gchicares@sbcglobal.net>
// snail: Chicares, 186 Belle Woods Drive, Glastonbury CT 06033, USA

#ifdef __BORLANDC__
#   include "pchfile.hpp"
#   pragma hdrstop
#endif // __BORLANDC__

#include "input_seq_helpers.hpp"

namespace detail
{
    std::vector<std::string> extract_keys_from_string_map
        (stringmap const& keyword_dictionary
        )
    {
        std::vector<std::string> keywords;
        stringmap_iterator i_keyword_dictionary = keyword_dictionary.begin();
        for
            (
            ;i_keyword_dictionary != keyword_dictionary.end()
            ;++i_keyword_dictionary
            )
            {
            keywords.push_back((*i_keyword_dictionary).first);
            }
        return keywords;
    }
} // namespace detail

