// Show progress on lengthy operations--wx interface.
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

#ifdef __BORLANDC__
#   include "pchfile.hpp"
#   pragma hdrstop
#endif // __BORLANDC__

#include "progress_meter.hpp"

#include "force_linking.hpp"
#include "wx_utility.hpp"               // TopWindow()

#include <wx/progdlg.h>
#include <wx/utils.h>                   // wxMilliSleep()

#include <ios>                          // std::fixed, std::ios_base::precision()
#include <sstream>

LMI_FORCE_LINKING_IN_SITU(progress_meter_wx)

namespace
{
// Implicitly-declared special member functions do the right thing.

// Virtuals are private because no one has any business accessing
// them--not even derived classes, because deriving from this concrete
// class is not contemplated.

class concrete_progress_meter
    :public progress_meter
{
    enum
        {progress_dialog_style =
                wxPD_APP_MODAL
            |   wxPD_AUTO_HIDE
            |   wxPD_CAN_ABORT
            |   wxPD_ELAPSED_TIME
            |   wxPD_ESTIMATED_TIME
            |   wxPD_REMAINING_TIME
            |   wxPD_SMOOTH
        };

  public:
    concrete_progress_meter
        (int                max_count
        ,std::string const& title
        ,enum_display_mode
        );

    virtual ~concrete_progress_meter();

  private:
    // progress_meter overrides.
    virtual void do_dawdle(int seconds);
    // progress_meter required implementation.
    virtual std::string progress_message() const;
    virtual bool show_progress_message();
    virtual void culminate_ui();

    wxProgressDialog progress_dialog_;
};

// TODO ?? CALCULATION_SUMMARY Resolve this issue.
// WX !! A wxProgressDialog created with maximum = 0 is displayed even
// though that's apparently just a nuisance. Calling Update(0) right
// after creation seems to be a reasonable workaround, but it would be
// better to change this in the library itself.

concrete_progress_meter::concrete_progress_meter
    (int                               max_count
    ,std::string const&                title
    ,progress_meter::enum_display_mode display_mode
    )
    :progress_meter(max_count, title, display_mode)
    ,progress_dialog_
        (title
        ,progress_message()
        ,max_count
        ,&TopWindow()
        ,progress_dialog_style
        )
{
    if(0 == max_count)
        {
        progress_dialog_.Update(0);
        }
}

concrete_progress_meter::~concrete_progress_meter()
{
}

/// Sleep for the number of seconds given in the argument.
///
/// Sleep only for a tenth of a second at a time, to ensure that the
/// application remains responsive--see:
///   http://lists.nongnu.org/archive/html/lmi/2013-11/msg00006.html
/// Count down the remaining delay to reassure end users that activity
/// is taking place.

void concrete_progress_meter::do_dawdle(int seconds)
{
    std::ostringstream oss;
    oss.precision(1);
    oss << std::fixed;
    for(int i = 10 * seconds; 0 < i && !progress_dialog_.WasCancelled(); --i)
        {
        wxMilliSleep(100);
        oss.str("");
        oss << "Waiting " << 0.1 * i << " seconds";
        progress_dialog_.Update(count(), oss.str());
        }
}

std::string concrete_progress_meter::progress_message() const
{
    std::ostringstream oss;
    oss << "Completed " << count() << " of " << max_count();
    return oss.str();
}

bool concrete_progress_meter::show_progress_message()
{
    return progress_dialog_.Update(count(), progress_message());
}

void concrete_progress_meter::culminate_ui()
{
}

boost::shared_ptr<progress_meter> concrete_progress_meter_creator
    (int                               max_count
    ,std::string const&                title
    ,progress_meter::enum_display_mode display_mode
    )
{
    return boost::shared_ptr<progress_meter>
        (new concrete_progress_meter(max_count, title, display_mode)
        );
}

volatile bool ensure_setup = set_progress_meter_creator
    (concrete_progress_meter_creator
    );
} // Unnamed namespace.

