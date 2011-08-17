// Edit input parameters using lmi's MVC framework with wx docview.
//
// Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011 Gregory W. Chicares.
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

// $Id$

#ifndef edit_mvc_docview_parameters_hpp
#define edit_mvc_docview_parameters_hpp

#include "config.hpp"

#include "mvc_controller.hpp"
#include "oecumenic_enumerations.hpp"

#include <wx/docview.h>
#include <wx/window.h>

#include <stdexcept>
#include <string>

/// Edit input parameters using lmi's MVC framework with wx docview.

template<typename ViewT, typename ModelT>
oenum_mvc_dv_rc edit_mvc_docview_parameters
    (ModelT&            parameters
    ,wxDocument&        document
    ,wxWindow*          frame
    ,std::string const& title = "Edit parameters"
    )
{
    bool dirty = document.IsModified();
    ModelT edited_parameters = parameters;
    ViewT const view;
    MvcController controller(frame, edited_parameters, view);
    controller.SetTitle(title);
    int const z = controller.ShowModal();
    oenum_mvc_dv_rc rc =
          (wxID_CANCEL == z) ? oe_mvc_dv_cancelled
        : (wxID_OK     == z) ? oe_mvc_dv_unchanged
        : throw std::logic_error("Unexpected ShowModal() return code.")
        ;
    if(wxID_OK == z)
        {
        if(parameters != edited_parameters)
            {
            rc = oe_mvc_dv_changed;
            parameters = edited_parameters;
            dirty = true;
            }
        document.Modify(dirty);
        }
    return rc;
}

#endif // edit_mvc_docview_parameters_hpp
