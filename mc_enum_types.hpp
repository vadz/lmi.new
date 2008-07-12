// Declaration of specific mc_enum types.
//
// Copyright (C) 2004, 2005, 2006, 2007, 2008 Gregory W. Chicares.
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

// $Id: mc_enum_types.hpp,v 1.19 2008-07-12 00:37:17 chicares Exp $

#ifndef mc_enum_types_hpp
#define mc_enum_types_hpp

#include "config.hpp"

#include "mc_enum_fwd.hpp"        // Template class forward declaration.
#include "mc_enum_type_enums.hpp" // Plain enumerators.

// Here write illustrative examples and anything that doesn't follow
// the macro paradigm, such as enumerators with nonsuccessive values.

extern enum_option const option_enums[3];
extern char const*const option_strings[3];
typedef mc_enum<enum_option, 3, option_enums, option_strings> e_option;

extern mcenum_emission const emission_enums[10];
extern char const*const emission_strings[10];
typedef mc_enum<mcenum_emission, 10, emission_enums, emission_strings> e_emission;

#include "mc_enum_types.xpp"

#define MC_DECLARE(TYPE,NUMBER) \
extern mcenum_##TYPE const TYPE##_enums[NUMBER]; \
extern char const*const TYPE##_strings[NUMBER]; \
typedef mc_enum<mcenum_##TYPE, NUMBER, TYPE##_enums, TYPE##_strings> mce_##TYPE;

MC_DECLARE(yes_or_no,2)
MC_DECLARE(gender,3)
MC_DECLARE(smoking,3)
MC_DECLARE(class,4)
MC_DECLARE(dbopt,3)
MC_DECLARE(dbopt_7702,2)
MC_DECLARE(mode,4)
MC_DECLARE(gen_basis,3)
MC_DECLARE(sep_basis,3)
MC_DECLARE(rate_period,2)
MC_DECLARE(run_basis,7)
MC_DECLARE(ledger_type,8)
MC_DECLARE(uw_basis,5)
MC_DECLARE(table_rating,11)
MC_DECLARE(solve_type,9)
MC_DECLARE(solve_target,2)
MC_DECLARE(solve_tgt_at,4)
MC_DECLARE(solve_from,4)
MC_DECLARE(solve_to,4)
MC_DECLARE(pmt_strategy,9)
MC_DECLARE(sa_strategy,9)
MC_DECLARE(loan_strategy,4)
MC_DECLARE(wd_strategy,4)
MC_DECLARE(interest_rate_type,3)
MC_DECLARE(loan_rate_type,2)
MC_DECLARE(fund_input_method,3)
MC_DECLARE(run_order,2)
MC_DECLARE(survival_limit,4)
MC_DECLARE(term_adj_method,3)
MC_DECLARE(state,53)
MC_DECLARE(country,239)
MC_DECLARE(defn_life_ins,3)
MC_DECLARE(mec_avoid_method,3)
MC_DECLARE(defn_material_change,5)
MC_DECLARE(spread_method,2)
MC_DECLARE(coi_rate_method,2)
MC_DECLARE(anticipated_deduction,4)
MC_DECLARE(part_mort_table,1)
MC_DECLARE(premium_table,1)
MC_DECLARE(from_point,4)
MC_DECLARE(to_point,4)
MC_DECLARE(report_column,47)

#undef MC_DECLARE

#endif // mc_enum_types_hpp

