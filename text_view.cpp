// Document view for plain text.
//
// Copyright (C) 2002, 2003, 2004, 2005 Gregory W. Chicares.
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
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// http://savannah.nongnu.org/projects/lmi
// email: <chicares@cox.net>
// snail: Chicares, 186 Belle Woods Drive, Glastonbury CT 06033, USA

// $Id: text_view.cpp,v 1.4 2005-08-04 02:20:13 chicares Exp $

// This is a derived work based on wxWindows file
//   samples/docvwmdi/view.cpp (C) 1998 Julian Smart and Markus Holzem
// which is covered by the wxWindows license.
//
// The original was modified by GWC in 2002 to factor the text-view
// class out of a larger file, and in the later years given in the
// copyright notice above.

#ifdef __BORLANDC__
#   include "pchfile.hpp"
#   pragma hdrstop
#endif

#include "text_view.hpp"

#include "alert.hpp"
#include "wx_new.hpp"

#include <wx/icon.h>
#include <wx/log.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

#include <stdexcept>

IMPLEMENT_DYNAMIC_CLASS(TextEditView, ViewEx)

BEGIN_EVENT_TABLE(TextEditView, ViewEx)
    EVT_MENU(XRCID("test_alert_streams"),TextEditView::OnTestAlertStreams)
    EVT_MENU(XRCID("test_exception"    ),TextEditView::OnTestException)
END_EVENT_TABLE()

TextEditView::TextEditView()
    :ViewEx      ()
    ,text_window_(0)
{
}

TextEditView::~TextEditView()
{
}

wxWindow* TextEditView::CreateChildWindow()
{
    return text_window_ = new(wx) wxTextCtrl
        (GetFrame()     // Parent.
        ,-1             // Window ID.
        ,""             // Default contents.
        ,wxDefaultPosition
        ,wxDefaultSize
        ,wxTE_MULTILINE // Style.
        );
}

wxIcon TextEditView::Icon() const
{
    return IconFromXmlResource("text_view_icon");
}

wxMenuBar* TextEditView::MenuBar() const
{
    return MenuBarFromXmlResource("text_view_menu");
}

void TextEditView::OnTestAlertStreams(wxCommandEvent&)
{
    status()         << "Test status()"         << LMI_FLUSH;
    warning()        << "Test warning()"        << LMI_FLUSH;
    hobsons_choice() << "Test hobsons_choice()" << LMI_FLUSH;
    fatal_error()    << "Test fatal_error()"    << LMI_FLUSH;
    wxLogError("Calling FlushActive()");
    wxLog::FlushActive();
}

void TextEditView::OnTestException(wxCommandEvent&)
{
    throw std::runtime_error("Test std::runtime_error");
}

