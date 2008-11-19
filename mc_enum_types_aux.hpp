// Auxiliary functions for specific mc_enum types.
//
// Copyright (C) 2008 Gregory W. Chicares.
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

// $Id: mc_enum_types_aux.hpp,v 1.9 2008-11-19 16:36:36 chicares Exp $

#ifndef mc_enum_types_aux_hpp
#define mc_enum_types_aux_hpp

#include "config.hpp"

#include "mc_enum_type_enums.hpp"
#include "so_attributes.hpp"

#include <string>
#include <vector>

/// Cardinality of certain enumerations, useful as ICEs.
///
/// Correctness of these values is asserted in the corresponding TU.

enum
    {mc_n_gen_bases    = 3
    ,mc_n_sep_bases    = 3
    ,mc_n_rate_periods = 2
    };

std::vector<std::string> const& LMI_SO all_strings_gender   ();
std::vector<std::string> const& LMI_SO all_strings_class    ();
std::vector<std::string> const& LMI_SO all_strings_smoking  ();
std::vector<std::string> const& LMI_SO all_strings_uw_basis ();
std::vector<std::string> const& LMI_SO all_strings_state    ();

mcenum_dbopt_7702 effective_dbopt_7702
    (mcenum_dbopt      actual_dbopt
    ,mcenum_dbopt_7702 rop_equivalent
    );

bool is_subject_to_ill_reg(mcenum_ledger_type);

bool is_three_rate_nasd(mcenum_ledger_type);

/// Transform a plain enumerator to its string equivalent.
///
/// This is rarely useful, but it's beneficial where it's used--see:
///   http://lists.nongnu.org/archive/html/lmi/2008-08/msg00022.html
/// Of course, a more general facility could easily be created.
/// Perhaps these should be written as a template anyway.

std::string mc_str(mcenum_dbopt);
std::string mc_str(mcenum_run_basis);
std::string mc_str(mcenum_state);

mcenum_state mc_state_from_string(std::string const&);

void set_cloven_bases_from_run_basis
    (mcenum_run_basis
    ,mcenum_gen_basis&
    ,mcenum_sep_basis&
    );

void set_run_basis_from_cloven_bases
    (mcenum_run_basis&
    ,mcenum_gen_basis
    ,mcenum_sep_basis
    );

#endif // mc_enum_types_aux_hpp

