/*
Copyright © 2016 Devin Carr
Permission is hereby granted, free of charge, to any person obtaining a 
copy of this software and associated documentation files (the “Software”), 
to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.
*/

#include "auth.h"
#include "json.hpp"

#include <ostream>
#include <string>
#include <curl/curl.h>

#define VERSION 1.0

using json = nlohmann::json;

// Curl write function borrowed from http://stackoverflow.com/questions/2329571/c-libcurl-get-output-into-a-string
size_t curl_writefunc(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e)
    {
        //handle memory problem
        return 0;
    }

    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
}

int main(int argc, char* argv[])
{
    // host url
    std::string search_url = "https://api.cognitive.microsoft.com/bing/v5.0/suggestions/";

    // custom auth header setup
    std::string default_header = "Ocp-Apim-Subscription-Key: ";
    std::string auth_header(default_header+AUTHPWD);

    // parse input arguments into a single string
    if (argc < 2) {
        std::cerr << "No input query provided!" << std::endl;
        return 1;
    }
    std::string query;
    for (int i = 1; i < argc; i++) {
        if (i == 1) {
            query += std::string(argv[i]);
        } else {
            // add a space between query strings if not first input
            query += "%20" + std::string(argv[i]);
        }
    }
    // combine search url and query
    search_url += "?q=" + query;

    // curl setup
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    std::string response;
    if (curl) {
        struct curl_slist *chunk = NULL;
        // Add a custom header
        chunk = curl_slist_append(chunk, auth_header.c_str());

        // set our custom set of headers
        res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        // set return options
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
        // set target url
        curl_easy_setopt(curl, CURLOPT_URL, search_url.c_str());

        // output info before http call
        std::cout << "Suggest (v" << VERSION << "):" << std::endl;

        // preform http call
        res = curl_easy_perform(curl);
        // check for errors
        if (res != CURLE_OK) {
            std::cerr << "http query failed: " << 
                    curl_easy_strerror(res) << std::endl;
        } else {
            auto json_data = json::parse(response);
            // output the search auto suggestions
            json suggestions = json_data["suggestionGroups"][0]["searchSuggestions"];
            for (auto& suggestion: suggestions) {
                std::cout << suggestion["displayText"] << std::endl;
            }
        }

        // always cleanup
        curl_easy_cleanup(curl);
        // free the custom headers
        curl_slist_free_all(chunk);
    }
    return 0;
}
