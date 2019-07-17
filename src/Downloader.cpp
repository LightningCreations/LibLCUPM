/*
 * Downloader.cpp
 *
 *  Created on: Jul. 16, 2019
 *      Author: chorm
 */

#include <lcupm/Downloader.hpp>

#include <curl/curl.h>
#include <map>

namespace lightningcreations::lcupm::downloader{

	class CurlController{
	public:
		CurlController(){
			curl_global_init(CURL_GLOBAL_ALL);
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
			curl_easy_setopt(curl,CURLOPT_WRITEDATA,target);\
		}

		bool doDownload(const std::string& url){
			curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
			return curl_easy_perform(curl)==CURLcode::CURLE_OK;
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
			return std::freopen(cacheFile.c_str(),"rb",target);
		}
	};

	static std::map<std::string,std::shared_ptr<Downloader>>& getSchemeMap(){
		static std::map<std::string,std::shared_ptr<Downloader>> schemeMap{};
		return schemeMap;
	}

	void Downloader::downloadTo(FILE* target,const URI& uri){
		(getSchemeMap()[uri.getScheme()])->do_downloadTo(target,uri);
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

