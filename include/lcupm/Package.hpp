/*
 * Package.hpp
 *
 *  Created on: Jul. 28, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_LCUPM_PACKAGE_HPP_
#define INCLUDE_LCUPM_PACKAGE_HPP_

#include <lcupm/Forward.hpp>
#include <lcupm/Provider.hpp>
#include <lcupm/Version.hpp>
#include <lcupm/PlatformInfo.hpp>



#include <jsoncpp/json/json.h>
#include <unordered_map>
#include <string>
#include <vector>

#include <utility>

namespace lightningcreations::lcupm::package{


	class LCUPM_API PackageInfo{
	private:
		std::string name;
		std::vector<std::string> description;
		Version ver;
		std::string licenseCode;
		std::string group;
	public:
		PackageInfo(const Json::Value&);
		PackageInfo(std::string name,std::vector<std::string> description,Version ver,std::string licenseCode,std::string group);
		const std::string& getName()const;
		const std::vector<std::string>& getDescription()const;
		Version getVersion()const;
		const std::string& getLicense()const;
		const std::string& getGroup()const;
	};

	class LCUPM_API Package{
	private:
		PackageInfo info;
		provider::Provider provider;

	};
}



#endif /* INCLUDE_LCUPM_PACKAGE_HPP_ */
