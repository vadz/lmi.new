// Stratified charges manager.
//
// Copyright (C) 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016 Gregory W. Chicares.
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

#ifndef tier_view_hpp
#define tier_view_hpp

#include "config.hpp"

#include "product_editor.hpp"

#include "obstruct_slicing.hpp"
#include "uncopyable_lmi.hpp"

#include <boost/shared_ptr.hpp>

class TierDocument;
class TierTableAdapter;
class WXDLLIMPEXP_FWD_CORE wxTreeEvent;

class TierView
    :        public  TreeGridViewBase
    ,        private lmi::uncopyable <TierView>
    ,virtual private obstruct_slicing<TierView>
{
  public:
    TierView();
    virtual ~TierView();

  private:
    // ViewEx required implementation.
    virtual char const* icon_xrc_resource   () const;
    virtual char const* menubar_xrc_resource() const;

    // ProductEditorView required implementation.
    virtual bool IsModified() const;
    virtual void DiscardEdits();

    // TreeGridViewBase required implementation.
    virtual wxTreeCtrl*   CreateTreeCtrl(wxWindow* parent);
    virtual MultiDimGrid* CreateGridCtrl(wxWindow* parent);
    virtual void SetupControls();

    TierDocument& document() const;

    void UponTreeSelectionChange(wxTreeEvent&);

    boost::shared_ptr<TierTableAdapter> table_adapter_;

    DECLARE_DYNAMIC_CLASS(TierView)
    DECLARE_EVENT_TABLE()
};

#endif // tier_view_hpp

