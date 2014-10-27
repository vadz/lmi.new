// Test pasting data into a census.
//
// Copyright (C) 2014 Gregory W. Chicares.
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

#ifdef __BORLANDC__
#   include "pchfile.hpp"
#   pragma hdrstop
#endif

#include "assert_lmi.hpp"
#include "data_directory.hpp"
#include "wx_test_case.hpp"
#include "wx_test_mvc_dialog.hpp"
#include "wx_test_new.hpp"
#include "wx_utility.hpp"

#include <wx/app.h>
#include <wx/dataview.h>
#include <wx/dialog.h>
#include <wx/ffile.h>
#include <wx/filefn.h>
#include <wx/html/htmlpars.h>
#include <wx/mdi.h>
#include <wx/radiobox.h>
#include <wx/testing.h>
#include <wx/uiaction.h>

namespace
{

// Helper function to get the census data to be pasted.
wxString get_census_data()
{
    // Get the census example from help. This is an HTML file but we don't have
    // an HTML parser and HTML is not valid XML, so it can't be parsed as such.
    // Instead we just rely on the very particular format of this file: right
    // now it contains the census data between the only occurrences of <pre>
    // and </pre> tags in it, so locate them and take everything inside.

    wxFFile f(AddDataDir("pasting_to_a_census.html"));
    LMI_ASSERT(f.IsOpened());

    wxString html;
    LMI_ASSERT(f.ReadAll(&html));

    size_t const pos_pre = html.find("<pre>\n");
    LMI_ASSERT(pos_pre != wxString::npos);

    size_t const pos_pre_end = html.find("</pre>", pos_pre);
    LMI_ASSERT(pos_pre_end != wxString::npos);

    size_t const pos_pre_start = pos_pre + strlen("<pre>\n");
    wxString const text_pre = html.substr
                                (pos_pre_start
                                , pos_pre_end - pos_pre_start
                                );

    // We're not done yet, we need to deal with the HTML entities. Do use HTML
    // parsing code in wxWidgets for this at least.
    return wxHtmlEntitiesParser().Parse(text_pre);
}

// Helper function to find the wxDataViewCtrl used for the census display.
//
// Precondition: the currently active window must be a CensusView.
wxDataViewCtrl* find_census_list_window()
{
    wxWindow* const top_window = wxTheApp->GetTopWindow();
    LMI_ASSERT(top_window);

    wxMDIParentFrame* const
        parent_frame = dynamic_cast<wxMDIParentFrame*>(top_window);
    LMI_ASSERT(parent_frame);

    wxMDIChildFrame* const child_frame = parent_frame->GetActiveChild();
    LMI_ASSERT(child_frame);

    wxWindowList const& census_children = child_frame->GetChildren();
    wxWindowList::const_iterator z = census_children.begin();
    LMI_ASSERT(z != census_children.end());

    wxDataViewCtrl* const dvc = dynamic_cast<wxDataViewCtrl*>(*z);
    LMI_ASSERT(dvc);

    return dvc;
}

// Retrieve the list model from list window.
//
// Precondition: this wxDataViewCtrl must actually use a list model.
wxDataViewListModel* get_census_list_model(wxDataViewCtrl* dvc)
{
    wxDataViewModel* const model = dvc->GetModel();
    LMI_ASSERT(model);

    wxDataViewListModel* const
        list_model = dynamic_cast<wxDataViewListModel*>(model);
    LMI_ASSERT(list_model);

    return list_model;
}

// Check for the presence of the column with the given name.
bool does_list_have_column(wxDataViewCtrl* dvc, wxString const& name)
{
    unsigned int const num_columns = dvc->GetColumnCount();
    for(unsigned int n = 0; n < num_columns; ++n)
        {
        if (dvc->GetColumn(n)->GetTitle() == name)
            {
            return true;
            }
        }
    return false;
}

} // Unnamed namespace.

LMI_WX_TEST_CASE(paste_census)
{
    // Put the data to paste on clipboard.
    ClipboardEx::SetText(get_census_data().ToStdString());

    // Create a new census.
    wx_test_new_census census;

    // Paste data into it.
    wxUIActionSimulator ui;
    ui.Char('s', wxMOD_CONTROL | wxMOD_SHIFT); // "Census|Paste census data"
    wxYield();

    // Find the model containing the cells and check that it was filled in
    // correctly.
    wxDataViewCtrl* const list_window = find_census_list_window();
    wxDataViewListModel* const list_model = get_census_list_model(list_window);
    LMI_ASSERT_EQUAL(list_model->GetCount(), 7);

    static char const* column_title = "Underwriting Class";
    LMI_ASSERT(does_list_have_column(list_window, column_title));

    // Change the case defaults to get rid of the underwriting class.
    ui.Char('e', wxMOD_CONTROL | wxMOD_SHIFT); // "Census|Edit case defaults"

    struct change_class_in_case_defaults_dialog
        :public ExpectMvcDialog
    {
        virtual void DoRunDialog(MvcController* dialog) const
            {
            wxUIActionSimulator ui;

            // Go to the third page: as the dialog remembers its last opened
            // page, ensure that we start from the first one.
            ui.Char(WXK_HOME);
            ui.Char(WXK_RIGHT);
            ui.Char(WXK_RIGHT);
            wxYield();

            // We can't find directly the radio button we're interested in,
            // because it's not a real wxWindow, so we need to find the radio
            // box containing it.
            wxWindow* const class_window = wxWindow::FindWindowByName
                ("UnderwritingClass"
                ,dialog
                );
            LMI_ASSERT(class_window);

            wxRadioBox* const
                class_radiobox = dynamic_cast<wxRadioBox*>(class_window);
            LMI_ASSERT(class_radiobox);

            // It's difficult to select the radiobox using just
            // wxUIActionSimulator as there is no keyboard shortcut to navigate
            // to it and emulating a mouse click on it is tricky as we don't
            // want to change its selection by clicking on the item, so do it
            // programmatically, the effect should be absolutely the same.
            class_radiobox->SetFocus();
            wxYield();

            ui.Char(WXK_UP); // Select the first, "Preferred", radio button.
            wxYield();

            LMI_ASSERT_EQUAL(class_radiobox->GetSelection(), 0);
            }
    };

    // The menu command above should have opened the "Case defaults" dialog and
    // our code dealing with it above is supposed to result in an appearance of
    // "Apply all changes to every cell?" message box for which we provide an
    // affirmative answer.
    wxTEST_DIALOG
        (wxYield()
        ,change_class_in_case_defaults_dialog()
        ,wxExpectModal<wxMessageDialog>(wxYES)
        );

    // Check that we still have the same cells but that now the underwriting
    // class column has disappeared as its value has been fixed.
    LMI_ASSERT_EQUAL(list_model->GetCount(), 7);
    LMI_ASSERT(!does_list_have_column(list_window, column_title));

    // Finally save the census with the pasted data for later inspection.
    static char const* census_file_name = "PasteCensus.cns";

    ui.Char('a', wxMOD_CONTROL);    // "File|Save as"
    wxTEST_DIALOG
        (wxYield()
        ,wxExpectModal<wxFileDialog>(census_file_name)
        );

    LMI_ASSERT(wxFileExists(census_file_name));

    census.close();
}