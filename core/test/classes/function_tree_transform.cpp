//This file is part of Bertini 2.
//
//b2/core/test/classes/function_tree_transform.cpp is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//b2/core/test/classes/function_tree_transform.cpp is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with b2/core/test/classes/function_tree_transform.cpp.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright(C) 2017 by Bertini2 Development Team
//
// See <http://www.gnu.org/licenses/> for a copy of the license, 
// as well as COPYING.  Bertini2 is provided with permitted 
// additional terms in the b2/licenses/ directory.

// individual authors of this file include:
//  Dani Brake
//  University of Wisconsin Eau Claire
//  ACMS
//  Fall 2017

/**
\file Testing suite for transforms applied to the function tree.  In this suite, we content ourselves to evaluation in double precision, exercising multiple precision evaluation elsewhere.
*/

#include <iostream>

#include <cstdlib>
#include <cmath>

#include "bertini2/function_tree.hpp"


#include <boost/spirit/include/qi.hpp>
#include <boost/test/unit_test.hpp>

#include "externs.hpp"

using Nd = std::shared_ptr<bertini::node::Node>;
using Nd = std::shared_ptr<bertini::node::Node>;

using bertini::MakeVariable;
using bertini::MakeInteger;

using dbl = bertini::dbl;

auto MakeZero(){return Nd(MakeInteger(0));}
auto MakeOne(){return Nd(MakeInteger(1));}

BOOST_AUTO_TEST_SUITE(function_tree)

BOOST_AUTO_TEST_SUITE(transform)

BOOST_AUTO_TEST_SUITE(eliminate_zeros)


BOOST_AUTO_TEST_CASE(cant_eliminate_self)
{
	auto zero = MakeZero();
	auto num_eliminated = zero->EliminateZeros();
	BOOST_CHECK_EQUAL(num_eliminated, 0);
	BOOST_CHECK_EQUAL(zero->Eval<dbl>(), 0.);
}

BOOST_AUTO_TEST_CASE(cant_eliminate_self2)
{
	auto zero = MakeZero();
	auto n = zero;
	auto num_eliminated = n->EliminateZeros();
	BOOST_CHECK_EQUAL(num_eliminated, 0);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 0.);
}


BOOST_AUTO_TEST_CASE(eliminate_single_zero_sum)
{
	auto zero = MakeZero();
	auto n = zero+zero;
	auto num_eliminated = n->EliminateZeros();
	BOOST_CHECK(num_eliminated >= 1);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 0.);
}


BOOST_AUTO_TEST_CASE(eliminate_single_zero_sum2)
{
	auto zero = MakeZero();
	auto n = zero+0;
	auto num_eliminated = n->EliminateZeros();
	BOOST_CHECK(num_eliminated >= 1);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 0.);
}


BOOST_AUTO_TEST_CASE(eliminate_single_zero_sum3)
{
	auto zero = MakeZero();
	auto n = 0+zero;
	auto num_eliminated = n->EliminateZeros();
	BOOST_CHECK(num_eliminated >= 1);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 0.);
}



BOOST_AUTO_TEST_CASE(eliminate_zero_product)
{
	auto zero = MakeZero();
	auto n = 1*zero;
	auto num_eliminated = n->EliminateZeros();
	BOOST_CHECK(num_eliminated >= 1);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 0.);
}


BOOST_AUTO_TEST_CASE(eliminate_zero_product2)
{
	auto zero = MakeZero();
	auto n = 1*zero;
	auto num_eliminated = n->EliminateZeros();
	BOOST_CHECK(num_eliminated >= 1);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 0.);
}

BOOST_AUTO_TEST_CASE(eliminate_zero_product3)
{
	auto zero = MakeZero();
	auto n = zero*zero;
	auto num_eliminated = n->EliminateZeros();
	BOOST_CHECK(num_eliminated >= 1);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 0.);
}



BOOST_AUTO_TEST_CASE(eliminate_zero_sum_zero_summand)
{
	auto x = MakeVariable("x");
	auto zero = MakeZero();


	auto n = pow(x,2) + zero*2;

	x->set_current_value(dbl(2.0));

	auto num_eliminated = n->EliminateZeros();
	BOOST_CHECK(num_eliminated >= 1);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 4.);
}



BOOST_AUTO_TEST_CASE(eliminate_zero_sum_zero_summand2)
{
	auto x = MakeVariable("x");
	auto zero = MakeZero();


	auto n = pow(x,2) + x*zero*2*(x*x*x);

	x->set_current_value(dbl(2.0));

	auto num_eliminated = n->EliminateZeros();
	BOOST_CHECK(num_eliminated >= 1);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 4.);
}

BOOST_AUTO_TEST_CASE(eliminate_zero_in_sum_level2)
{
	auto x = MakeVariable("x");
	auto zero = MakeZero();


	auto n = (x + sqrt(x) + zero) + x*2*(x*x*x);

	x->set_current_value(dbl(2.0));

	auto num_eliminated = n->EliminateZeros();

	std::cout << n << '\n';
	BOOST_CHECK(num_eliminated >= 1);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 35.414213562373095048801688724209698078569671875377);
}


BOOST_AUTO_TEST_SUITE_END() // eliminate zeros











//////////////////////////////
//
//   ONES
//
//      1
//     11
//    1 1
//      1
//      1
//    11111
//
/////////////////////////

BOOST_AUTO_TEST_SUITE(eliminate_ones)

BOOST_AUTO_TEST_CASE(cant_eliminate_self)
{
	auto one = MakeOne();
	auto num_eliminated = one->EliminateOnes();
	BOOST_CHECK_EQUAL(num_eliminated, 0);
	BOOST_CHECK_EQUAL(one->Eval<dbl>(), 1.);
}

BOOST_AUTO_TEST_CASE(cant_eliminate_self2)
{
	auto one = MakeOne();
	auto n = one;
	auto num_eliminated = n->EliminateOnes();
	BOOST_CHECK_EQUAL(num_eliminated, 0);
	BOOST_CHECK_EQUAL(n->Eval<dbl>(), 1.);
}


BOOST_AUTO_TEST_SUITE_END() // eliminate ones




BOOST_AUTO_TEST_SUITE_END() // transform


BOOST_AUTO_TEST_SUITE_END() // function_tree






