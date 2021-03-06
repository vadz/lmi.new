// Handlers for exceptional situations--unit test.
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

#include "handle_exceptions.hpp"

#include "test_tools.hpp"

#include <stdexcept>

/// This function is normally unimplemented.

stealth_exception::stealth_exception(std::string const& what_arg)
    :std::runtime_error(what_arg)
{}

class sneaky_exception
    :public stealth_exception
{
  public:
    explicit sneaky_exception(std::string const& what_arg)
        :stealth_exception(what_arg)
    {}
};

int test_main(int, char*[])
{
    try
        {
        throw std::runtime_error("  This message should appear on stderr.");
        }
    catch(...)
        {
        report_exception();
        BOOST_TEST(true);
        }

    // Test the
    //   catch(...) { try{report_exception();} catch(...){/*warning*/} }
    // technique to trap every exception--even stealth_exception or an
    // exception derived from it.
    try
        {
        std::cout << "Expect a success message..." << std::endl;
        throw sneaky_exception("ERROR");
        }
    catch(...)
        {
        try
            {
            report_exception(); // Should rethrow.
            BOOST_TEST(false);
            }
        catch(...)
            {
            std::cout << "...Success: caught elusive exception." << std::endl;
            BOOST_TEST(true);
            }
        }

    return 0;
}

