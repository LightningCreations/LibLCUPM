/*
 * LibraryInfo.cpp
 *
 *  Created on: Sep. 1, 2019
 *      Author: chorm
 */

#include <lcupm/Version.hpp>
#include <lcupm/LibraryInfo.hpp>

#ifndef LCUPM_PACKNAME
#define LCUPM_PACKNAME liblcupm
#endif

#ifndef LCUPM_PROVIDER
#define LCUPM_PROVIDER lcroot
#endif

#ifndef LCUPM_BUILD_SALT
#define LCUPM_BUILD_SALT AAAAAAAAAAAABBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCC
#endif

#define _quote(a) #a
#define quote(a) _quote(a)

#define ACTUAL_BUILD_SALT quote(LCUPM_BUILD_SALT)
#define ACTUAL_PACKNAME quote(LCUPM_PACKNAME)
#define ACTUAL_PROVIDER quote(LCUPM_PROVIDER)


namespace lightningcreations::lcupm{

	const char LibraryInfo::libname[]{"LibLCUPM"};
	const char LibraryInfo::distributor[]{ACTUAL_PROVIDER};
	const char LibraryInfo::packname[]{ACTUAL_PACKNAME};
	const Version LibraryInfo::version{1,0};
	const char LibraryInfo::buildSalt[]{ACTUAL_BUILD_SALT};
	const char LibraryInfo::buildTime[]{__TIME__};
	const char LibraryInfo::buildDate[]{__DATE__};

}
