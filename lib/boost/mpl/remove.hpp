
#ifndef BOOST_MPL_REMOVE_HPP_INCLUDED
#define BOOST_MPL_REMOVE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: remove.hpp 49239 2008-10-10 09:10:26Z agurtovoy $
// $Date: 2008-10-10 06:10:26 -0300 (Fri, 10 Oct 2008) $
// $Revision: 49239 $

#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct remove_impl
    : remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct reverse_remove_impl
    : reverse_remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, remove)

}}

#endif // BOOST_MPL_REMOVE_HPP_INCLUDED
