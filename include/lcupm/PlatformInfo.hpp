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
		friend std::vector<std::reference_wrapper<const PlatformInfo>> getAvailablePlatforms();
		const char* os;
		const char* toolkit;
		const char* arch;
		PlatformInfo(const char* os,const char* toolkit,const char* toolkit,const char* distName);
		PlatformInfo(const PlatformInfo&)=delete;
		PlatformInfo& operator=(const PlatformInfo&)=delete;
		PlatformInfo(PlatformInfo&&)=delete;
		PlatformInfo& operator=(PlatformInfo&&)=delete;
	public:
		const char* getOSName()const;
		const char* getToolkitName()const;
		const char* getArchName()const;
	};
}



#endif /* INCLUDE_PLATFORMINFO_HPP_ */
