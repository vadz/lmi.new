// A value-Constrained Enumeration for product names.
//
// Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016 Gregory W. Chicares.
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

#include "ce_product_name.hpp"

#include "alert.hpp"
#include "contains.hpp"
#include "facets.hpp"
#include "global_settings.hpp"
#include "miscellany.hpp"               // lmi_tolower()
#include "path_utility.hpp"             // fs::path inserter

#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <algorithm>                    // std::find(), std::transform()

namespace
{
std::vector<std::string> fetch_product_names()
{
    fs::path path(global_settings::instance().data_directory());
    std::vector<std::string> names;
    fs::directory_iterator i(path);
    fs::directory_iterator end_i;
    for(; i != end_i; ++i)
        {
        if(is_directory(*i) || ".policy" != fs::extension(*i))
            {
            continue;
            }
        std::string name(basename(*i));
        std::transform
            (name.begin()
            ,name.end()
            ,name.begin()
            ,lmi_tolower
            );
        names.push_back(name);
        }

    if(names.empty())
        {
        fatal_error()
            << "Data directory '"
            << path
            << "' contains no product files."
            << LMI_FLUSH
            ;
        }

    return names;
}

std::vector<std::string> const& product_names()
{
    static std::vector<std::string> const names(fetch_product_names());
    return names;
}

/// Default product name is "sample" if that product is available,
/// else the name of the first product found.
///
/// Rationale: It is always possible to specify a different default
/// product by using a default-input file. If none is used, then the
/// first product found is not necessarily a better default than
/// "sample". Defaults hardcoded in the input class are designed to
/// be generally suitable, but might be inappropriate for some exotic
/// product. If a user creates an invalid product that appears first
/// in the list, then the system will still work in default cases
/// with "sample".

std::string const& default_product_name()
{
    static std::string const default_name =
        contains(product_names(), "sample")
        ? std::string("sample")
        : product_names().front()
        ;
    return default_name;
}
} // Unnamed namespace.

ce_product_name::ce_product_name()
    :mc_enum_base(product_names().size())
    ,value_(default_product_name())
{}

ce_product_name::ce_product_name(std::string const& s)
    :mc_enum_base(product_names().size())
    ,value_(product_names()[ordinal(s)])
{}

ce_product_name& ce_product_name::operator=(std::string const& s)
{
    value_ = product_names()[ordinal(s)];
    return *this;
}

bool ce_product_name::operator==(ce_product_name const& z) const
{
    return z.value_ == value_;
}

bool ce_product_name::operator==(std::string const& s) const
{
    return s == str();
}

std::size_t ce_product_name::ordinal(std::string const& s)
{
    std::size_t v =
            std::find
                (product_names().begin()
                ,product_names().end()
                ,s
                )
        -   product_names().begin()
        ;
    if(v == product_names().size())
        {
        fatal_error()
            << "Value '"
            << s
            << "' invalid for type '"
            << "ce_product_name"
            << "'."
            << LMI_FLUSH
            ;
        }
    return v;
}

std::vector<std::string> const& ce_product_name::all_strings() const
{
    return product_names();
}

std::size_t ce_product_name::cardinality() const
{
    return product_names().size();
}

/// No product is ever proscribed.

void ce_product_name::enforce_proscription()
{}

std::size_t ce_product_name::ordinal() const
{
    return ordinal(value_);
}

std::string ce_product_name::str(int j) const
{
    return product_names()[j];
}

std::string ce_product_name::str() const
{
    return value_;
}

std::string ce_product_name::value() const
{
    return value_;
}

std::istream& ce_product_name::read(std::istream& is)
{
    std::locale old_locale = is.imbue(blank_is_not_whitespace_locale());
    std::string s;
    is >> s;
    operator=(s);
    is.imbue(old_locale);
    return is;
}

std::ostream& ce_product_name::write(std::ostream& os) const
{
    return os << str();
}

