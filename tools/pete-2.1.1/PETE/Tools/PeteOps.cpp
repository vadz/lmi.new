// -*- C++ -*-
//
// Copyright (C) 1998, 1999, 2000, 2002  Los Alamos National Laboratory,
// Copyright (C) 1998, 1999, 2000, 2002  CodeSourcery, LLC
//
// This file is part of FreePOOMA.
//
// FreePOOMA is free software; you can redistribute it and/or modify it
// under the terms of the Expat license.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the Expat
// license for more details.
//
// You should have received a copy of the Expat license along with
// FreePOOMA; see the file LICENSE.
//

///////////////////////////////////////////////////////////////////////////////
//
// WARNING: THIS FILE WAS GENERATED AUTOMATICALLY!
// YOU SHOULD MODIFY THE INPUT FILES INSTEAD OF CHANGING THIS FILE DIRECTLY!
//
// THE FOLLOWING INPUT FILES WERE USED TO MAKE THIS FILE:
//
// MakeOperators
// PeteOps.in
//
///////////////////////////////////////////////////////////////////////////////

#include "Tools/OperatorDescriptor.h"
#include <vector>
#include <map>
#include <string>
using std::map;
using std::vector;
using std::string;


void peteOps(map<string,vector<OperatorDescriptor> > &m)
{
  m["assignOp"].push_back(
              OperatorDescriptor("OpAssign",
                                 "assign",
                                 "return (const_cast<T1 &>(a) = b);",
                                 ""));
  m["binaryAssignOps"].push_back(
              OperatorDescriptor("OpAddAssign",
                                 "operator+=",
                                 "(const_cast<T1 &>(a) += b); return const_cast<T1 &>(a);",
                                 ""));
  m["binaryAssignOps"].push_back(
              OperatorDescriptor("OpSubtractAssign",
                                 "operator-=",
                                 "(const_cast<T1 &>(a) -= b); return const_cast<T1 &>(a);",
                                 ""));
  m["binaryAssignOps"].push_back(
              OperatorDescriptor("OpMultiplyAssign",
                                 "operator*=",
                                 "(const_cast<T1 &>(a) *= b); return const_cast<T1 &>(a);",
                                 ""));
  m["binaryAssignOps"].push_back(
              OperatorDescriptor("OpDivideAssign",
                                 "operator/=",
                                 "(const_cast<T1 &>(a) /= b); return const_cast<T1 &>(a);",
                                 ""));
  m["binaryAssignOps"].push_back(
              OperatorDescriptor("OpModAssign",
                                 "operator%=",
                                 "(const_cast<T1 &>(a) %= b); return const_cast<T1 &>(a);",
                                 ""));
  m["binaryAssignOps"].push_back(
              OperatorDescriptor("OpBitwiseOrAssign",
                                 "operator|=",
                                 "(const_cast<T1 &>(a) |= b); return const_cast<T1 &>(a);",
                                 ""));
  m["binaryAssignOps"].push_back(
              OperatorDescriptor("OpBitwiseAndAssign",
                                 "operator&=",
                                 "(const_cast<T1 &>(a) &= b); return const_cast<T1 &>(a);",
                                 ""));
  m["binaryAssignOps"].push_back(
              OperatorDescriptor("OpBitwiseXorAssign",
                                 "operator^=",
                                 "(const_cast<T1 &>(a) ^= b); return const_cast<T1 &>(a);",
                                 ""));
  m["binaryAssignOps"].push_back(
              OperatorDescriptor("OpLeftShiftAssign",
                                 "operator<<=",
                                 "(const_cast<T1 &>(a) <<= b); return const_cast<T1 &>(a);",
                                 ""));
  m["binaryAssignOps"].push_back(
              OperatorDescriptor("OpRightShiftAssign",
                                 "operator>>=",
                                 "(const_cast<T1 &>(a) >>= b); return const_cast<T1 &>(a);",
                                 ""));
  m["binaryBoolOps"].push_back(
              OperatorDescriptor("OpLT",
                                 "operator<",
                                 "return (a < b);",
                                 ""));
  m["binaryBoolOps"].push_back(
              OperatorDescriptor("OpLE",
                                 "operator<=",
                                 "return (a <= b);",
                                 ""));
  m["binaryBoolOps"].push_back(
              OperatorDescriptor("OpGT",
                                 "operator>",
                                 "return (a > b);",
                                 ""));
  m["binaryBoolOps"].push_back(
              OperatorDescriptor("OpGE",
                                 "operator>=",
                                 "return (a >= b);",
                                 ""));
  m["binaryBoolOps"].push_back(
              OperatorDescriptor("OpEQ",
                                 "operator==",
                                 "return (a == b);",
                                 ""));
  m["binaryBoolOps"].push_back(
              OperatorDescriptor("OpNE",
                                 "operator!=",
                                 "return (a != b);",
                                 ""));
  m["binaryBoolOps"].push_back(
              OperatorDescriptor("OpAnd",
                                 "operator&&",
                                 "return (a && b);",
                                 ""));
  m["binaryBoolOps"].push_back(
              OperatorDescriptor("OpOr",
                                 "operator||",
                                 "return (a || b);",
                                 ""));
  m["binaryLeftOps"].push_back(
              OperatorDescriptor("OpLeftShift",
                                 "operator<<",
                                 "return (a << b);",
                                 ""));
  m["binaryLeftOps"].push_back(
              OperatorDescriptor("OpRightShift",
                                 "operator>>",
                                 "return (a >> b);",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("OpAdd",
                                 "operator+",
                                 "return (a + b);",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("OpSubtract",
                                 "operator-",
                                 "return (a - b);",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("OpMultiply",
                                 "operator*",
                                 "return (a * b);",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("OpDivide",
                                 "operator/",
                                 "return (a / b);",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("OpMod",
                                 "operator%",
                                 "return (a % b);",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("OpBitwiseAnd",
                                 "operator&",
                                 "return (a & b);",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("OpBitwiseOr",
                                 "operator|",
                                 "return (a | b);",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("OpBitwiseXor",
                                 "operator^",
                                 "return (a ^ b);",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("FnLdexp",
                                 "ldexp",
                                 "return (ldexp(a,b));",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("FnPow",
                                 "pow",
                                 "return (pow(a,b));",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("FnFmod",
                                 "fmod",
                                 "return (fmod(a,b));",
                                 ""));
  m["binaryOps"].push_back(
              OperatorDescriptor("FnArcTan2",
                                 "atan2",
                                 "return (atan2(a,b));",
                                 ""));
  m["trinaryOps"].push_back(
              OperatorDescriptor("FnWhere",
                                 "where",
                                 "if (a) return b; else return c;",
                                 ""));
  m["unaryBoolOps"].push_back(
              OperatorDescriptor("OpNot",
                                 "operator!",
                                 "return (!a);",
                                 ""));
  m["unaryCastOps"].push_back(
              OperatorDescriptor("OpCast",
                                 "peteCast",
                                 "return T1(a);",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnArcCos",
                                 "acos",
                                 "return (acos(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnArcSin",
                                 "asin",
                                 "return (asin(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnArcTan",
                                 "atan",
                                 "return (atan(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnCeil",
                                 "ceil",
                                 "return (ceil(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnCos",
                                 "cos",
                                 "return (cos(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnHypCos",
                                 "cosh",
                                 "return (cosh(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnExp",
                                 "exp",
                                 "return (exp(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnFabs",
                                 "fabs",
                                 "return (fabs(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnFloor",
                                 "floor",
                                 "return (floor(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnLog",
                                 "log",
                                 "return (log(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnLog10",
                                 "log10",
                                 "return (log10(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnSin",
                                 "sin",
                                 "return (sin(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnHypSin",
                                 "sinh",
                                 "return (sinh(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnSqrt",
                                 "sqrt",
                                 "return (sqrt(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnTan",
                                 "tan",
                                 "return (tan(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("FnHypTan",
                                 "tanh",
                                 "return (tanh(a));",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("OpUnaryMinus",
                                 "operator-",
                                 "return (-a);",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("OpUnaryPlus",
                                 "operator+",
                                 "return (+a);",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("OpBitwiseNot",
                                 "operator~",
                                 "return (~a);",
                                 ""));
  m["unaryOps"].push_back(
              OperatorDescriptor("OpIdentity",
                                 "PETE_identity",
                                 "return (a);",
                                 ""));
}

// ACL:rcsinfo
// ----------------------------------------------------------------------
// $RCSfile: PeteOps.cpp,v $   $Author: chicares $
// $Revision: 1.1 $   $Date: 2008-09-04 13:55:30 $
// ----------------------------------------------------------------------
// ACL:rcsinfo