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
#include <filesystem>

namespace lightningcreations::lcupm::provider{
	struct certificate_key_t{
		constexpr explicit certificate_key_t()=default;
	};
	constexpr certificate_key_t certificate_key{};

	class LCUPM_API ProviderKey{
		std::variant<std::monostate,X509*,RSA*> key;
	public:
		friend void swap(ProviderKey&,ProviderKey&);
		ProviderKey()=default;
		ProviderKey(FILE*);
		ProviderKey(FILE*,certificate_key_t);
		ProviderKey(const ProviderKey&);
		ProviderKey(ProviderKey&&);
		ProviderKey& operator=(ProviderKey);
		~ProviderKey();
		bool verify(std::string signature,const unsigned char* data,std::size_t dlen);
	};

	class LCUPM_API KeyRef{
		std::string keyUri;
		std::string keyFingerprint;
		mutable std::optional<ProviderKey> resolved;
		bool isCertificate;
	public:
		KeyRef(std::string keyUri,std::string fingerprint);
		KeyRef(std::string keyUri,std::string fingerprint,certificate_key_t);
		const ProviderKey& operator*()const;
		const ProviderKey* operator->()const;
	};

	class LCUPM_API Provider{
	private:
		ProviderKey key;
		std::string name;
	public:
		Provider(std::string,KeyRef);
		Provider(std::string,ProviderKey);
		Provider(Json::Value);
		const std::string& getName()const;
		const ProviderKey& getKey()const;
	};

	class LCUPM_API ProviderRef{
	private:
		std::string uri;
		mutable std::optional<Provider> provider;
	public:
		ProviderRef(std::string uri);
		const Provider& operator*()const;
		const Provider* operator->()const;
	};

	class LCUPM_API ProviderCache{
	private:

	};
}

#endif /* INCLUDE_LCUPM_PROVIDER_HPP_ */
