/*
 * Provider.cpp
 *
 *  Created on: Jul. 13, 2019
 *      Author: chorm
 */

#include <lcupm/Provider.hpp>
#include <lcupm/Downloader.hpp>
#include <openssl/pem.h>

#include <functional>

///////////////////////////////////////////////////////////////////////////
//Base64 Encoding Library
/*
   base64.cpp and base64.h

   Copyright (C) 2004-2008 René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

/*
static std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}
*/
static std::string base64_decode(std::string const& encoded_string) {//Nice std::string const&.
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}
//End of Base64 Encoding Library
/////////////////////////////////////////////////////////////

namespace lightningcreations::lcupm::provider{

	struct DestroyVisitor{
		public:
		void operator()(std::monostate s){}
		void operator()(RSA* r){
			RSA_free(r);
		}
		void operator()(X509* c){
			X509_free(c);
		}
	};

	struct VerifyVisitor{
	private:
		std::string_view signature;
		const unsigned char* data;
		std::size_t dlen;
	public:
		VerifyVisitor(std::string_view sig,const unsigned char* data,std::size_t dlen):
		signature{sig},data{data},dlen{dlen}{

		}
		bool operator()(std::monostate s){
			return false;
		}
		bool operator()(RSA* r){
			return RSA_verify(NID_sha256WithRSAEncryption,data,dlen,(const unsigned char*)&*signature.begin(),signature.size(),r);
		}
		bool operator()(X509* cert){
			EVP_PKEY* key = X509_get_pubkey(cert);
			RSA* r = EVP_PKEY_get1_RSA(key);
			bool verify{std::invoke(*this,r)};
			RSA_free(r);
			EVP_PKEY_free(key);
			return verify;
		}
	};

	ProviderKey::ProviderKey(FILE* f){
		this->key = RSA_new();
		PEM_read_RSAPublicKey(f,&std::get<RSA*>(this->key),NULL,NULL);
	}
	ProviderKey::ProviderKey(FILE* f,certificate_key_t){
		this->key = X509_new();
		PEM_read_X509(f,&std::get<X509*>(this->key),NULL,NULL);
	}
	ProviderKey::~ProviderKey(){
		std::visit(DestroyVisitor{},this->key);
	}

	bool ProviderKey::verify(std::string s,const unsigned char* data,size_t dlen){
		s = base64_decode(s);//Wow Ok, you gonna const me so I can't decode and move.
		return std::visit(VerifyVisitor{s,data,dlen},this->key);
	}

	static ProviderKey downloadKey(const std::string& uri){
		FILE* f = std::tmpfile();
		lcupm::downloader::Downloader::downloadTo(f,URI{uri});
		ProviderKey k{f};
		std::fclose(f);
		return std::move(k);
	}

	KeyRef::KeyRef(std::string uri,std::string fingerprint):keyUri(uri),keyFingerprint(fingerprint){}

	const ProviderKey& KeyRef::operator *()const{
		if(resolved.has_value())
			return *resolved;
		else{
			resolved = downloadKey(keyUri);
			return *resolved;
		}
	}
	const ProviderKey* KeyRef::operator->()const{
		return &**this;
	}
}


