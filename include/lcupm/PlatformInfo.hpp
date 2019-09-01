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
	class LCUPM_API PlatformInfo final{
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

namespace std{
	template<> struct hash<lightningcreations::lcupm::PlatformInfo>{
	public:
		using result_type = std::size_t;
		result_type operator()(const lightningcreations::lcupm::PlatformInfo& dist){
			auto hash_content = [](const char* c){
				result_type hash{};
				for(;*c!=0;c++)
					hash=31*hash+*c;
				return hash;
			};
			return 31*31*hash_content(dist.getOSName())+31*hash_content(dist.getArchName())+hash_content(dist.getToolkitName());
		}
	};
}



#endif /* INCLUDE_PLATFORMINFO_HPP_ */
