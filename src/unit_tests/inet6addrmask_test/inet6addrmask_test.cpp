/* 

                          Firewall Builder

                 Copyright (C) 2008 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@fwbuilder.org

  $Id: dns_test.cpp 918 2006-03-05 06:07:10Z vkurland $

  This program is free software which we release under the GNU General Public
  License. You may redistribute and/or modify this program under the terms
  of that license as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  To get a copy of the GNU General Public License, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "fwbuilder/libfwbuilder-config.h"

#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif

#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <deque>
#include <vector>
#include <map>

#ifndef _WIN32
#  include <unistd.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#ifdef HAVE_GETOPT_H
#  include <getopt.h>
#else
#  ifdef _WIN32
#    include <getopt.h>
#  else
#    include <stdlib.h>
#  endif
#endif

#include "fwbuilder/Resources.h"

#include "fwbuilder/FWObjectDatabase.h"
#include "fwbuilder/XMLTools.h"
#include "fwbuilder/FWException.h"
#include "fwbuilder/Inet6AddrMask.h"

#include <assert.h>

using namespace libfwbuilder;
using namespace std;


int main(int, char * const *)
{   
    string sa;

    try 
    {
        libfwbuilder::init();

        cout << endl;
        cout << "Start test for Inet6AddrMask" << endl;

        Inet6Addr A1(0);
        cout << "Inet6Addr::Inet6Addr(0) "
             << A1.toString() << "  length=" << A1.getLength() << endl;

        Inet6Addr A2(8);
        cout << "Inet6Addr::Inet6Addr(8) "
             << A2.toString() << "  length=" << A2.getLength() << endl;

        Inet6Addr A3(16);
        cout << "Inet6Addr::Inet6Addr(16) "
             << A3.toString() << "  length=" << A3.getLength() << endl;

        Inet6Addr A4(64);
        cout << "Inet6Addr::Inet6Addr(64) "
             << A4.toString() << "  length=" << A4.getLength() << endl;

        Inet6Addr A5(128);
        cout << "Inet6Addr::Inet6Addr(128) "
             << A5.toString() << "  length=" << A5.getLength() << endl;


        cout << endl;

        Inet6AddrMask *a1 = new Inet6AddrMask();
        sa = a1->getAddress().toString();
        cout << "a1=" << sa << endl;
        assert(sa=="::");
//        assert(a1->dimension()==0);


        cout << endl;

        Inet6AddrMask *a2 = new Inet6AddrMask(Inet6Addr("fe80::21d:9ff:fe8b:8e94"),
                                              Inet6Addr(128));
        sa = a2->getAddress().toString();
        cout << "a2.address=" << sa << endl;
        assert(sa=="fe80::21d:9ff:fe8b:8e94");
        sa = a2->getNetmask().toString();
        cout << "a2.netmask=" << sa
             << " length=" << a2->getNetmask().getLength() << endl;
        assert(sa=="ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff");
        assert(a2->getNetmask().getLength()==128);

//        assert(a2->dimension()==18446744073709551616);

        cout << "a2.toString=" << a2->toString() << endl;
        assert(a2->toString()=="fe80::21d:9ff:fe8b:8e94");


        cout << endl;

        Inet6AddrMask *a3 = new Inet6AddrMask(Inet6Addr("fe80::21d:9ff:fe8b:8e94"),
                                              Inet6Addr(128));
        a3->setNetmask(Inet6Addr(64));
        sa = a3->getAddress().toString();
        cout << "a3.address=" << sa << endl;
        assert(sa=="fe80::21d:9ff:fe8b:8e94");
        sa = a3->getNetmask().toString();
        cout << "a3.netmask=" << sa
             << " length=" << a3->getNetmask().getLength() << endl;
        assert(sa=="64");
//        assert(a3->dimension()==18446744073709551616);
        assert(a3->toString()=="fe80::21d:9ff:fe8b:8e94/64");


        cout << endl;

        Inet6AddrMask *a4 = new Inet6AddrMask(
            string("fe80::21d:9ff:fe8b:8e94/64"));
        sa = a4->getAddress().toString();
        cout << "a4.address=" << sa << endl;
        assert(sa=="fe80::21d:9ff:fe8b:8e94");
        sa = a4->getNetmask().toString();
        cout << "a4.netmask=" << sa << endl;
        assert(sa=="ffff:ffff:ffff:ffff:0000:0000:0000:0000");
//        assert(a4->dimension()==1);

//        assert(a3->belongs(a2->getAddress()));


        cout << endl;

        Inet6AddrMask *a5 = new Inet6AddrMask(*a3);
        sa = a5->getAddress().toString();
        assert(sa=="1.1.1.1");
        sa = a5->getNetmask().toString();
        assert(sa=="255.255.255.255");
//        assert(a5->dimension()==1);

        a5->setAddress(Inet6Addr("2.2.2.2"));
        sa = a5->getAddress().toString();
        assert(sa=="2.2.2.2");
        sa = a5->getNetmask().toString();
        assert(sa=="255.255.255.255");
//        assert(a5->dimension()==1);

        a5->setNetmask(Inet6Addr("255.255.0.0"));
        sa = a5->getAddress().toString();
        assert(sa=="2.2.2.2");
        sa = a5->getNetmask().toString();
        assert(sa=="255.255.0.0");
//        assert(a5->dimension()==256*256);

        cout << "All tests passed" << endl;

    } catch(FWException &ex)  {
    cerr << ex.toString() << endl;
        exit(1);
    } catch (std::string s) {
    cerr << s;
        exit(1);
    } catch (std::exception ex) {
    cerr << ex.what();
        exit(1);
    } catch (...) {
    cerr << "Unsupported exception";
        exit(1);
    }

}

