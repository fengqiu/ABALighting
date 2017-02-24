#include <curl/curl.h>
#include <iostream>
#include <fstream>

using namespace std;
/* the function to invoke as the data received */

int main(void)
{
  CURL *curl;
  CURLcode res;
  struct curl_slist *list = NULL;
  list = curl_slist_append(list, "api_key: EUNtTgodXM");
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://platform.aklbadminton.com/api/bookings?since=1456023600&court=11");
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER ,list);
	//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	//FILE *fp = fopen("Court1Bookings","w");
	//curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
     /* use a GET to fetch this */
   curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);


    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
