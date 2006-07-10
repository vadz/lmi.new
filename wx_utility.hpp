// Utilities for use with wxWidgets.
//
// Copyright (C) 2006 Gregory W. Chicares.
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
// email: <chicares@cox.net>
// snail: Chicares, 186 Belle Woods Drive, Glastonbury CT 06033, USA

// $Id: wx_utility.hpp,v 1.3 2006-07-10 13:15:31 chicares Exp $

#ifndef wx_utility_hpp
#define wx_utility_hpp

#include "config.hpp"

#include "so_attributes.hpp"

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include <wx/event.h>

#include <stdexcept>
#include <string>
#include <vector>

class LMI_SO calendar_date;
class WXDLLEXPORT wxDateTime;
class WXDLLEXPORT wxWindow;

/// Function template c_cast() performs an explicit type conversion
/// (C++98 5.4), which is inherently unsafe. Its sole virtue is that
/// it is easily searched for.

template<typename To, typename From>
To c_cast(From z)
{
    return (To)(z);
}

/// Function template Connect() forwards to wxEvtHandler::Connect().
/// It is simpler to write, because it casts its 'handler' argument
/// automatically, and performs some type checking, although the
/// unsafe cast apparently cannot be avoided.

template<typename Return, typename Class, typename Argument>
void Connect
    (wxEvtHandler*   object
    ,wxEventType     event
    ,Return (Class::*handler)(Argument)
    ,int             id = wxID_ANY
    )
{
    // Double parentheses: don't parse comma as a macro parameter separator.
    BOOST_STATIC_ASSERT((boost::is_same<void,Return>::value));
    BOOST_STATIC_ASSERT((boost::is_base_and_derived<wxObject,Class>::value));
    typedef typename boost::remove_reference<Argument>::type argument_type;
    BOOST_STATIC_ASSERT
        ((
            boost::is_same            <wxEvent,argument_type>::value
        ||  boost::is_base_and_derived<wxEvent,argument_type>::value
        ));

    if(!object)
        {
        throw std::runtime_error("Connect(): null pointer.");
        }

    object->Connect(id, event, c_cast<wxObjectEventFunction>(handler));
}

/// Convert wxDateTime to calendar_date.

calendar_date ConvertDateFromWx(wxDateTime const&);

/// Convert calendar_date to wxDateTime.

wxDateTime ConvertDateToWx(calendar_date const&);

bool operator==(calendar_date const& lmi_date, wxDateTime const& wx_date);
bool operator==(wxDateTime const& wx_date, calendar_date const& lmi_date);

/// Test ConvertDateFromWx() and ConvertDateToWx().

void TestDateConversions();

/// Return a string comprising a window's id, label, and name.

std::string Describe(wxWindow const*);

/// Return a vector populated with a window's children, grandchildren,
/// and so on, unto the ultimate generation: its entire lineage.
///
/// Motivation: Often it is necessary to iterate over a window's
/// entire lineage, but wx provides direct access only to the first
/// generation--immediate children. Writing a recursive traversal
/// inline wherever wanted is cumbersome, opaque, and error prone.
///
/// Commonly enough, subwindows don't change after a complex dialog
/// has been initialized; then, the result is suitable for caching.

std::vector<wxWindow*> Lineage(wxWindow const*);

#endif // wx_utility_hpp

