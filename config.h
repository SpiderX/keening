/* Template for the temp file. See mkstemp(3) */
static char PATH_TMP[] = "/var/www/pastes/temp/kng.XXXXXX";

/* Path to persistent paste directory */
static const char* PATH_PRS = "/var/www/pastes/";

/* URL prefix used to construct the URL to a named/persistent file */
static const char* URL_PRS = "http://domain.com/p/";

/* URL prefix used to construct the URL to a temporary file */
static const char* URL_TMP = "http://domain.com/t/";
