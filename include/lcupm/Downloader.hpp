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

namespace lightningcreations::lcupm{
	class URI{
	private:
		std::string scheme;
		std::string domain;
		std::string path;
		std::string query;
	public:
		URI(std::string uri);
		URI(std::string scheme,std::string domain,std::string path, std::string query);
		const std::string& getScheme()const;
		const std::string& getDomain()const;
		const std::string& getPath()const;
		const std::string& getQuery()const;
		std::string getURI()const;
	};
}

namespace lightningcreations::lcupm::downloader{
	class Downloader{
	private:
		const char* scheme;
	protected:
		Downloader(const char* scheme);
		~Downloader();
		static void registerDownloader(const char* scheme,std::shared_ptr<Downloader> src);
		virtual bool do_downloadTo(FILE*,const URI&)const=0;
	public:
		static std::shared_ptr<Downloader> getDownloaderFor(const URI&);
		void downloadTo(FILE*,const URI&)const;
		const char* getScheme()const;
	};

}




#endif /* INCLUDE_LCUPM_DOWNLOADER_HPP_ */
