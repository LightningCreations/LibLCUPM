/*
 * Provider.cpp
 *
 *  Created on: Jul. 13, 2019
 *      Author: chorm
 */

#include <lcupm/Provider.hpp>

namespace lightningcreations::lcupm::provider{

	ProviderKey::ProviderKey(std::istream& i){
		this->key = RSA_new();

	}
}


