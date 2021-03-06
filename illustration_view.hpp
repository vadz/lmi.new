// Document view for illustrations.
//
// Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016 Gregory W. Chicares.
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

// This is a derived work based on wxWindows file
//   samples/docvwmdi/view.cpp (C) 1998 Julian Smart and Markus Holzem
// which is covered by the wxWindows license.
//
// The original was modified by GWC in 2003 to create a standalone
// view class customized for illustration documents, and in the later
// years given in the copyright notice above.

#ifndef illustration_view_hpp
#define illustration_view_hpp

#include "config.hpp"

#include "view_ex.hpp"

#include "mc_enum_type_enums.hpp"       // enum mcenum_emission
#include "obstruct_slicing.hpp"
#include "oecumenic_enumerations.hpp"
#include "uncopyable_lmi.hpp"

#include <boost/shared_ptr.hpp>

#include <wx/event.h>

class IllustrationDocument;
class Input;
class Ledger;
class WXDLLIMPEXP_FWD_CORE wxHtmlWindow;

// TODO ?? Consider adding an input reference member. Here, it's used
// only for edit and run; in the census view class, it's used widely.

class IllustrationView
    :        public  ViewEx
    ,        private lmi::uncopyable <IllustrationView>
    ,virtual private obstruct_slicing<IllustrationView>
{
    friend class IllustrationDocument;

  public:
    IllustrationView();
    virtual ~IllustrationView();

    // Making these functions public so that they can be invoked by
    // class CensusView is arguably less bad than making that class a
    // friend.
    //
    void DisplaySelectedValuesAsHtml();
    void Run(Input* = 0);
    void SetLedger(boost::shared_ptr<Ledger const>);

  private:
    IllustrationDocument& document() const;

    oenum_mvc_dv_rc edit_parameters();

    void emit_pdf(mcenum_emission);

    // ViewEx required implementation.
    virtual wxWindow* CreateChildWindow();
    virtual char const* icon_xrc_resource   () const;
    virtual char const* menubar_xrc_resource() const;

    // ViewEx overrides.
    virtual bool OnCreate(wxDocument*, long int);

    void UponCopyFull           (wxCommandEvent&);
    void UponCopySummary        (wxCommandEvent&);
    void UponPreviewPdf         (wxCommandEvent&);
    void UponPrint              (wxCommandEvent&);
    void UponPrintPdf           (wxCommandEvent&);
    void UponProperties         (wxCommandEvent&);
    void UponUpdateAlwaysEnabled(wxUpdateUIEvent&);
    void UponUpdateFileSave     (wxUpdateUIEvent&);
    void UponUpdateFileSaveAs   (wxUpdateUIEvent&);
    void UponUpdateIllustration (wxUpdateUIEvent&);
    void UponUpdateInapplicable (wxUpdateUIEvent&);
    void UponUpdateProperties   (wxUpdateUIEvent&);

    Input& input_data();

    wxHtmlWindow* html_window_;
    bool is_phony_;
    boost::shared_ptr<Ledger const> ledger_values_;

    DECLARE_DYNAMIC_CLASS(IllustrationView)
    DECLARE_EVENT_TABLE()
};

IllustrationView& MakeNewIllustrationDocAndView
    (wxDocManager* dm
    ,char const*   filename
    );

bool custom_io_0_run_if_file_exists(wxDocManager*);
bool custom_io_1_run_if_file_exists();

#endif // illustration_view_hpp

