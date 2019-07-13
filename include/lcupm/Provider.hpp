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
#include <istream>
#include <jsoncpp/json/json.h>
#include <optional>

namespace lightingcreations::lcupm::provider{
	struct certificate_key_t{
		constexpr explicit certificate_key_t()=default;
	};
	constexpr certificate_key_t certificate_key{};

	class ProviderKey{
		std::variant<std::monostate,X509*,RSA*> key;
	public:
		ProviderKey()=default;
		ProviderKey(std::istream&);
		ProviderKey(std::istream&,certificate_key_t);
		bool verify(std::string signature,const unsigned char* data,std::size_t dlen);
	};

	class KeyRef{
		std::string keyUri;
		std::string keyFingerprint;
		mutable std::optional<ProviderKey> resolved;
		//Mutable b/c the const versions may need to follow the keyref
	public:
		KeyRef(std::nullptr_t=nullptr);
		KeyRef(std::string keyUri,std::string fingerprint);
		KeyRef& operator=(std::nullptr_t);
		ProviderKey& operator*();
		const ProviderKey& operator*()const;
		ProviderKey* operator->();
		const ProviderKey* operator->()const;
	};

	class Provider{
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

	static_assert(std::is_same<ProviderKey,lightningcreations::lcupm::provider::ProviderKey>::value, "There's your problem.");
}

#endif /* INCLUDE_LCUPM_PROVIDER_HPP_ */
