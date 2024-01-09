#include <stdio.h>
// If curl not present, use sudo apt-get install libcurl4-openssl-dev 
#include <curl/curl.h>


int main(void) {
    CURL *curl;
    CURLcode res;

    // Example credentials (DO NOT use real credentials)
    const char *username = "fakeusername";
    const char *password = "fakepassword";

    // Initialize CURL
    curl = curl_easy_init();
    if (curl) {
        // Set the URL for the fake authentication request
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com/login");

        // Specify the POST data (username and password)
        char postdata[100];
        snprintf(postdata, sizeof(postdata), "username=%s&password=%s", username, password);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Cleanup
        curl_easy_cleanup(curl);
    }

    return 0;
}
