/*
 * Provider.hpp
 *
 *  Created on: Jul. 13, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_LCUPM_PROVIDER_HPP_
#define INCLUDE_LCUPM_PROVIDER_HPP_

#include <lcupm/Forward.hpp>
#include <string>
#include <openssl/rsa.h>
#include <openssl/x509v3.h>
#include <variant>
#include <cstdio>
#include <jsoncpp/json/json.h>
#include <optional>

namespace lightningcreations::lcupm::provider{
	struct certificate_key_t{
		constexpr explicit certificate_key_t()=default;
	};
	constexpr certificate_key_t certificate_key{};

	class LCUPM_API ProviderKey{
		std::variant<std::monostate,X509*,RSA*> key;
	public:
		ProviderKey()=default;
		ProviderKey(FILE*);
		ProviderKey(FILE*,certificate_key_t);
		~ProviderKey();
		bool verify(std::string signature,const unsigned char* data,std::size_t dlen);
	};

	class LCUPM_API KeyRef{
		std::string keyUri;
		std::string keyFingerprint;
		mutable std::optional<ProviderKey> resolved;
		//Mutable b/c the const versions may need to follow the keyref
	public:
		KeyRef(std::string keyUri,std::string fingerprint);
		const ProviderKey& operator*()const;
		const ProviderKey* operator->()const;
	};

	class LCUPM_API Provider{
	private:
		std::optional<ProviderKey> key;
		KeyRef ref;
		std::string name;
	public:
		Provider(std::string,KeyRef);
		Provider(std::string,ProviderKey);
		Provider(Json::Value);
		const std::string& getName()const;
		const ProviderKey& getKey()const;
	};
}

#endif /* INCLUDE_LCUPM_PROVIDER_HPP_ */
