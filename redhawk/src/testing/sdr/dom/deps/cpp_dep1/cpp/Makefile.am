#
# This file is protected by Copyright. Please refer to the COPYRIGHT file
# distributed with this source distribution.
#
# This file is part of REDHAWK core.
#
# REDHAWK core is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# REDHAWK core is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see http://www.gnu.org/licenses/.
#
ACLOCAL_AMFLAGS = -I m4 -I${OSSIEHOME}/share/aclocal/ossie
AUTOMAKE_OPTIONS = subdir-objects

noinst_LTLIBRARIES = libcpp_dep1.la

#pkgconfigdir = $(libdir)/pkgconfig
#pkgconfig_DATA = cpp_dep1.pc

#xmldir = $(prefix)
#dist_xml_DATA = ../cpp_dep1.spd.xml

distclean-local:
	rm -rf m4


# Sources, libraries and library directories are auto-included from a file
# generated by the REDHAWK IDE. You can remove/modify the following lines if
# you wish to manually control these options.
include $(srcdir)/Makefile.am.ide
libcpp_dep1_la_SOURCES = $(redhawk_SOURCES_auto)
libcpp_dep1_la_LIBADD = $(SOFTPKG_LIBS) $(REDHAWK_LIBS)
libcpp_dep1_la_CPPFLAGS = -I $(srcdir)/include $(SOFTPKG_CFLAGS) $(REDHAWK_CFLAGS) $(BOOST_CPPFLAGS)
libcpp_dep1_la_CXXFLAGS = -Wall

#redhawk_HEADERS_auto ?= $(filter include/%,$(redhawk_SOURCES_auto))
#include_HEADERS = $(redhawk_HEADERS_auto)
