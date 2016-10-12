/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 *
 * This file is part of REDHAWK core.
 *
 * REDHAWK core is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * REDHAWK core is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */
// Not copyrighted - public domain.
//
// This sample parser implementation was generated by CodeSynthesis XSD,
// an XML Schema to C++ data binding compiler. You may use it in your
// programs without any restrictions.
//

#include "scd-pimpl.h"

// softwarecomponent_pimpl
//
using namespace scd;

void softwarecomponent_pimpl::
pre ()
{
    _data.reset(new ossie::ComponentDescriptor::SCD());
}

void softwarecomponent_pimpl::
corbaversion (const ::std::string& corbaversion)
{
  // TODO
  //
}

void softwarecomponent_pimpl::
componentrepid ()
{
}

void softwarecomponent_pimpl::
componenttype (const ::std::string& componenttype)
{
    _data->componentType = componenttype;
}

void softwarecomponent_pimpl::
componentfeatures ()
{
}

void softwarecomponent_pimpl::
interfaces ()
{
}

void softwarecomponent_pimpl::
propertyfile ()
{
}

std::auto_ptr<ossie::ComponentDescriptor::SCD> softwarecomponent_pimpl::
post_softwarecomponent ()
{
  return _data;
}

// propertyFile_pimpl
//

void propertyFile_pimpl::
pre ()
{
}

void propertyFile_pimpl::
localfile ()
{
}

void propertyFile_pimpl::
type (const ::std::string& type)
{
  // TODO
  //
}

void propertyFile_pimpl::
post_propertyFile ()
{
}

// localFile_pimpl
//

void localFile_pimpl::
pre ()
{
}

void localFile_pimpl::
name (const ::std::string& name)
{
  // TODO
  //
}

void localFile_pimpl::
post_localFile ()
{
}

// componentRepId_pimpl
//

void componentRepId_pimpl::
pre ()
{
}

void componentRepId_pimpl::
repid (const ::std::string& repid)
{
  // TODO
  //
}

void componentRepId_pimpl::
post_componentRepId ()
{
}

// componentFeatures_pimpl
//

void componentFeatures_pimpl::
pre ()
{
}

void componentFeatures_pimpl::
supportsinterface ()
{
}

void componentFeatures_pimpl::
ports ()
{
}

void componentFeatures_pimpl::
post_componentFeatures ()
{
}

// supportsInterface_pimpl
//

void supportsInterface_pimpl::
pre ()
{
}

void supportsInterface_pimpl::
repid (const ::std::string& repid)
{
  // TODO
  //
}

void supportsInterface_pimpl::
supportsname (const ::std::string& supportsname)
{
  // TODO
  //
}

void supportsInterface_pimpl::
post_supportsInterface ()
{
}

// ports_pimpl
//

void ports_pimpl::
pre ()
{
}

void ports_pimpl::
provides ()
{
}

void ports_pimpl::
uses ()
{
}

void ports_pimpl::
post_ports ()
{
}

// provides_pimpl
//

void provides_pimpl::
pre ()
{
}

void provides_pimpl::
description (const ::std::string& description)
{
}

void provides_pimpl::
porttype ()
{
}

void provides_pimpl::
repid (const ::std::string& repid)
{
  // TODO
  //
}

void provides_pimpl::
providesname (const ::std::string& providesname)
{
  // TODO
  //
}

void provides_pimpl::
post_provides ()
{
}

// uses_pimpl
//

void uses_pimpl::
pre ()
{
}

void uses_pimpl::
description (const ::std::string& description)
{
}

void uses_pimpl::
porttype ()
{
}

void uses_pimpl::
repid (const ::std::string& repid)
{
  // TODO
  //
}

void uses_pimpl::
usesname (const ::std::string& usesname)
{
  // TODO
  //
}

void uses_pimpl::
post_uses ()
{
}

// portType_pimpl
//

void portType_pimpl::
pre ()
{
}

void portType_pimpl::
type ()
{
}

void portType_pimpl::
post_portType ()
{
}

// interfaces_pimpl
//

void interfaces_pimpl::
pre ()
{
}

void interfaces_pimpl::
interface ()
{
}

void interfaces_pimpl::
post_interfaces ()
{
}

// interface_pimpl
//

void interface_pimpl::
pre ()
{
}

void interface_pimpl::
inheritsinterface ()
{
}

void interface_pimpl::
repid (const ::std::string& repid)
{
  // TODO
  //
}

void interface_pimpl::
name (const ::std::string& name)
{
  // TODO
  //
}

void interface_pimpl::
post_interface ()
{
}

// inheritsInterface_pimpl
//

void inheritsInterface_pimpl::
pre ()
{
}

void inheritsInterface_pimpl::
repid (const ::std::string& repid)
{
  // TODO
  //
}

void inheritsInterface_pimpl::
post_inheritsInterface ()
{
}

// type_pimpl
//

void type_pimpl::
pre ()
{
}

void type_pimpl::
post_type ()
{
  const ::std::string& v (post_nmtoken ());
  (void)v;

  // TODO
  //
}

