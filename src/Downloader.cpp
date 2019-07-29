/*
 * Downloader.cpp
 *
 *  Created on: Jul. 16, 2019
 *      Author: chorm
 */

#include <lcupm/Downloader.hpp>

#include <curl/curl.h>
#include <map>

using namespace std::string_literals;

namespace lightningcreations::lcupm::exception{
	class LCUPM_API NoSuchDownloader: public DownloadException{
	public:
		explicit NoSuchDownloader(const std::string& scheme):DownloadException("Cannot Find Downloader for URI with Scheme"+scheme){}
	};
	class LCUPM_API CURLException: public DownloadException{
	public:
		explicit CURLException(CURLcode code):DownloadException("LibCURL Returned Error: "s+curl_easy_strerror(code)){}
	};

	class LCUPM_API LocalcacheFileError: public DownloadException{
	public:
		explicit LocalcacheFileError(const std::string& cacheId):DownloadException("Cannot open cachefile with id: "s+cacheId){}
	};
}

namespace lightningcreations::lcupm::downloader{

	class CurlController{
	public:
		CurlController(){
			if(CURLcode code =curl_global_init(CURL_GLOBAL_ALL);code!=CURLE_OK)
				throw exception::CURLException{code};
		}
		~CurlController(){
			curl_global_cleanup();
		}
	};

	class Curl{
	private:
		CURL* curl;
		static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
			return fwrite(ptr,size,nmemb,(FILE*)userdata);
		}
	public:
		Curl(FILE* target){
			static CurlController controller{};
			curl = curl_easy_init();
			curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_callback);
			curl_easy_setopt(curl,CURLOPT_WRITEDATA,target);
		}

		bool doDownload(const std::string& url){
			curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
			if(CURLcode code =curl_easy_perform(curl);code!=CURLE_OK)
				throw exception::CURLException(code);
			else
				return true;
		}

		~Curl(){
			curl_easy_cleanup(curl);
		}
	};

	template<typename target> class DownloaderImpl:public Downloader,std::enable_shared_from_this<target>{
	protected:
		DownloaderImpl(const char* scheme):Downloader(scheme){
			registerDownloader(scheme,this->shared_from_this());
		}
	private:
		static std::shared_ptr<target> impl;
	};


	class HTTPDownloader final:public DownloaderImpl<HTTPDownloader>{
	private:
		friend class DownloaderImpl<HTTPDownloader>;
		static std::shared_ptr<HTTPDownloader> http;
		HTTPDownloader():DownloaderImpl("https"){}
		HTTPDownloader(const char* alt):DownloaderImpl(alt){}
	protected:
		bool do_downloadTo(FILE* target,const URI& uri)const override{
			Curl curl{target};
			return curl.doDownload(uri.getURI());
		}
	};
	std::shared_ptr<HTTPDownloader> HTTPDownloader::http{new HTTPDownloader("http")};


	class FTPDownloader final:public DownloaderImpl<FTPDownloader>{
	private:
		friend class DownloaderImpl<FTPDownloader>;
		FTPDownloader():DownloaderImpl("ftp"){}
	protected:
		bool do_downloadTo(FILE* target,const URI& uri)const override{
			Curl curl{target};
			return curl.doDownload(uri.getURI());
		}
	};

	class SMBDownloader final:public DownloaderImpl<SMBDownloader>{
	private:
		friend class DownloaderImpl<SMBDownloader>;
		SMBDownloader():DownloaderImpl("smb"){}
	protected:
		bool do_downloadTo(FILE* target,const URI& uri)const override{
			Curl curl{target};
			return curl.doDownload(uri.getURI());
		}
	};

	template<typename target> std::shared_ptr<target> DownloaderImpl<target>::impl{new target{}};

	class LocalCacheDownloader final:public DownloaderImpl<LocalCacheDownloader>{
	private:
		friend class DownloaderImpl<LocalCacheDownloader>;
		LocalCacheDownloader():DownloaderImpl("localcache"){}
	protected:
		bool do_downloadTo(FILE* target,const URI& uri){
			auto cacheFile{"./.localcache"+uri.getRemaining()};
			FILE* cached = std::fopen(cacheFile.c_str(),"r");
			if(!cached)
				throw exception::LocalcacheFileError(uri.getRemaining());
			decltype(std::fread(nullptr,0,0,cached)) sz;
			unsigned char block[1024];
			while((sz=std::fread(block,1,1024,cached))!=-1)
				std::fwrite(block,1,1024,target);
			return true;
		}
	};

	static std::map<std::string,std::shared_ptr<Downloader>>& getSchemeMap(){
		static std::map<std::string,std::shared_ptr<Downloader>> schemeMap{};
		return schemeMap;
	}

	void Downloader::downloadTo(FILE* target,const URI& uri){
		if(!getSchemeMap().count(uri.getScheme()))
			throw exception::NoSuchDownloader(uri.getScheme());
		if(!(getSchemeMap()[uri.getScheme()])->do_downloadTo(target,uri))
			throw exception::DownloadException("Downloader failed for unknown reason");
	}

	void Downloader::registerDownloader(const char* scheme,std::shared_ptr<Downloader> ptr){
		getSchemeMap()[scheme] = ptr;
	}

	Downloader::Downloader(const char* scheme):scheme{scheme}{}

	const char* Downloader::getScheme()const{
		return this->scheme;
	}

}

namespace lightningcreations::lcupm{
	URI::URI(std::string scheme,std::string domain,std::string path,std::string query,std::string schemeSpecificPart,unsigned short port):scheme(std::move(scheme))
		{
			if(!schemeSpecificPart.empty())
				this->rest = schemeSpecificPart+"@";
			this->rest += domain;
			if(port!=0)
				(this->rest += ":"),(this->rest += port);
			this->rest += "/";
			this->rest += path;
			if(!query.empty())
				this->rest += "?"+query;
		}
	URI::URI(std::string uri){
		std::string::size_type pos = uri.find("://");
		this->scheme = uri.substr(0, pos);
		this->rest = uri.substr(pos+3);
	}

	const std::string& URI::getScheme()const{
		return scheme;
	}
	const std::string& URI::getRemaining()const{
		return rest;
	}
	std::string URI::getURI()const{
		return scheme+"://"+rest;
	}
}

