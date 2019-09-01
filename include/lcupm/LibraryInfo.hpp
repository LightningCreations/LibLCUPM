/*
 * LibraryInfo.hpp
 *
 *  Created on: Sep. 1, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_LCUPM_LIBRARYINFO_HPP_
#define INCLUDE_LCUPM_LIBRARYINFO_HPP_

#include <lcupm/Version.hpp>

namespace lightningcreations::lcupm{
	struct LCUPM_API LibraryInfo{
	public:
		static const char libname[];
		static const char distributor[];
		static const char packname[];
		static const Version version;
		static const char buildSalt[];
		static const char buildTime[];
		static const char buildDate[];
	};
}



#endif /* INCLUDE_LCUPM_LIBRARYINFO_HPP_ */
