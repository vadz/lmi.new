// Product database entity names.
//
// Copyright (C) 1998, 1999, 2000, 2001, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016 Gregory W. Chicares.
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

#include "dbnames.hpp"
#include "dbnames.xpp"

#include "alert.hpp"
#include "assert_lmi.hpp"
#include "map_lookup.hpp"
#include "miscellany.hpp"

#include <map>

namespace
{
bool check_order(std::vector<db_names> const& v)
{
    LMI_ASSERT(DB_LAST == v.size());

    int parent = DB_FIRST;
    bool is_okay = true;
    for(int j = 0; j < DB_LAST; ++j)
        {
        if(DB_FIRST == v[j].ParentIdx)
            {
            parent = j;
            }
        if(j != v[j].Idx)
            {
            is_okay = false;
            warning()
                << "Entity '"      << v[j].ShortName
                << "' with index " << v[j].Idx
                << " is out of order.\n"
                ;
            }
        if(parent != v[j].ParentIdx && DB_FIRST != v[j].ParentIdx)
            {
            is_okay = false;
            warning()
                << "Entity '"      << v[j].ShortName
                << "' with index " << v[j].Idx
                << " has incorrect parent.\n"
                ;
            }
        }
    if(false == is_okay)
        {
        warning() << LMI_FLUSH;
        }
    return is_okay;
}

std::vector<db_names> const& static_get_db_names()
{
    static int const n = DB_LAST;

    static db_names const static_DBNames[n] = {DB_NAMES};

    static std::vector<db_names> const v(static_DBNames, static_DBNames + n);

    static volatile bool b = check_order(v);
    stifle_warning_for_unused_variable(b);

    return v;
}

std::map<std::string,int> static_get_short_names()
{
    std::map<std::string,int> m;
    static std::vector<db_names> const names = static_get_db_names();
    typedef std::vector<db_names>::const_iterator vdbnci;
    for(vdbnci i = names.begin(); i != names.end(); ++i)
        {
        m[i->ShortName] = i->Idx;
        }
    return m;
}

} // Unnamed namespace.

std::vector<db_names> const& GetDBNames()
{
    return static_get_db_names();
}

int db_key_from_name(std::string const& name)
{
    static std::map<std::string,int> const m = static_get_short_names();
    return map_lookup(m, name);
}

std::string db_name_from_key(int key)
{
    static std::vector<db_names> const names = static_get_db_names();
    LMI_ASSERT(0 <= key && key < DB_LAST);
    return names[key].ShortName;
}

