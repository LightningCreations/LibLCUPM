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

#include <jsoncpp/json/json.h>
#include <string>
#include <vector>

#include <utility>

namespace lightningcreations::lcupm::package{


	class PackageInfo{
	private:
		std::string name;
		std::vector<std::string> description;
		Version ver;
		std::string licenseCode;
		std::string group;
	public:
		PackageInfo(const Json::Value&);
		const std::string& getName()const;
		const std::vector<std::string>& getDescription()const;
		Version getVersion()const;
		const std::string& getLicense()const;
		const std::string& getGroup()const;
	};
}



#endif /* INCLUDE_LCUPM_PACKAGE_HPP_ */
