#!/bin/bash
iogs readsimulation test4.xml
#iogs addparam int i1 1 7
#iogs addparam int i2 2 7

#iogs addparam double d1 1.1 7
#iogs addparam double d2 2.2 7

#iogs addparam string s1 test1 7
#iogs addparam string s2 test2 7

#iogs addmetadata met1 metcont1
#iogs addmetadata met2 metcont2

iogs listparam double
iogs listparam int
iogs listparam string
iogs listmetadata

iogs getparam int i1
iogs getparam int i2

iogs getparam double d1
iogs getparam double d2

iogs getparam string s1
iogs getparam string s2

iogs getmetadata met1
iogs getmetadata met2

iogs setparam double d1 6.6
iogs setparam string s1 newtest1

iogs writesimulation test5.xml
