/*
 * Downloader.hpp
 *
 *  Created on: Jul. 16, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_LCUPM_DOWNLOADER_HPP_
#define INCLUDE_LCUPM_DOWNLOADER_HPP_

#include <lcupm/Forward.hpp>
#include <memory>
#include <lcupm/Exceptions.hpp>

namespace lightningcreations::lcupm{
	class LCUPM_API URI{
	private:
		std::string scheme;
		std::string rest;
	public:
		URI(std::string uri);
		URI(std::string scheme,std::string domain,std::string path, std::string query="",std::string schemeSpecificPart="",unsigned short port=0);
		const std::string& getScheme()const;
		const std::string& getRemaining()const;
		std::string getURI()const;
	};
	namespace exception{
		class LCUPM_API DownloadException:public LCUPMException{
		public:
			using LCUPMException::LCUPMException;
		};
	}
}

namespace lightningcreations::lcupm::downloader{
	class LCUPM_API Downloader{
	private:
		const char* scheme;
	protected:
		Downloader(const char* scheme);
		~Downloader()=default;
		static void registerDownloader(const char* scheme,std::shared_ptr<Downloader> src);
		virtual bool do_downloadTo(FILE*,const URI&)const=0;
		const char* getScheme()const;
	public:
		static void downloadTo(FILE*,const URI&);
	};

}




#endif /* INCLUDE_LCUPM_DOWNLOADER_HPP_ */
