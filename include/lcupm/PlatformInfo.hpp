/*
 * PlatformInfo.hpp
 *
 *  Created on: Jul. 12, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_PLATFORMINFO_HPP_
#define INCLUDE_PLATFORMINFO_HPP_

#include <lcupm/Forward.hpp>

namespace lightningcreations::lcupm{
	class PlatformInfo final{
	private:
		friend const PlatformInfo& getCurrentPlatform();
		friend const std::vector<PlatformInfo>& getAvailablePlatforms();
		const char* os;
		const char* toolkit;
		const char* arch;
		PlatformInfo(const char* os,const char* toolkit,const char* arch);
		PlatformInfo(const PlatformInfo&)=delete;
		PlatformInfo& operator=(const PlatformInfo&)=delete;
	public:
		PlatformInfo(PlatformInfo&&)=default;
		PlatformInfo& operator=(PlatformInfo&&)=default;
		const char* getOSName()const;
		const char* getToolkitName()const;
		const char* getArchName()const;
	};
}



#endif /* INCLUDE_PLATFORMINFO_HPP_ */
