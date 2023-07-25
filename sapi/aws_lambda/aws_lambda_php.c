//
// Created by jstormes on 7/14/23.
//

#include "aws_lambda_php.h"
#include "aws-lambda/c-runtime/runtime.h"

#include "php.h"
#include "php_globals.h"
#include "php_variables.h"
#include "php_ini_builder.h"
#include "zend_modules.h"
#include "zend_hash.h"
#include "zend_modules.h"
#include "zend_interfaces.h"

#include "SAPI.h"

#include <stdio.h>

#if HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <signal.h>
#include <locale.h>
#include "zend.h"
#include "zend_extensions.h"
#include "php_ini.h"
#include "php_globals.h"
#include "php_main.h"
#include "fopen_wrappers.h"
#include "ext/standard/php_standard.h"
#include "ext/standard/dl_arginfo.h"

#ifdef __riscos__
#include <unixlib/local.h>
#endif

#include "zend_compile.h"
#include "zend_execute.h"
#include "zend_highlight.h"
#include "zend_exceptions.h"

#include "php_getopt.h"


# define php_select(m, r, w, e, t)	select(m, r, w, e, t)

PHPAPI extern char *php_ini_opened_path;
PHPAPI extern char *php_ini_scanned_path;
PHPAPI extern char *php_ini_scanned_files;

#ifndef O_BINARY
#define O_BINARY 0
#endif

#define PHP_MODE_STANDARD      1
#define PHP_MODE_HIGHLIGHT     2
#define PHP_MODE_LINT          4
#define PHP_MODE_STRIP         5
#define PHP_MODE_CLI_DIRECT    6
#define PHP_MODE_PROCESS_STDIN 7
#define PHP_MODE_REFLECTION_FUNCTION    8
#define PHP_MODE_REFLECTION_CLASS       9
#define PHP_MODE_REFLECTION_EXTENSION   10
#define PHP_MODE_REFLECTION_EXT_INFO    11
#define PHP_MODE_REFLECTION_ZEND_EXTENSION 12
#define PHP_MODE_SHOW_INI_CONFIG        13

static int php_lambda_startup(sapi_module_struct *sapi_module) /* {{{ */
{
    return php_module_startup(sapi_module, NULL);
}
/* }}} */

typedef struct php_lambda_server_request {
//    enum php_http_method request_method;
//    int protocol_version;
//    zend_string *request_uri;
//    char *vpath;
//    size_t vpath_len;
//    char *path_translated;
//    size_t path_translated_len;
//    char *path_info;
//    size_t path_info_len;
//    char *query_string;
//    size_t query_string_len;
    HashTable headers;
//    HashTable headers_original_case;
//    char *content;
//    size_t content_len;
//    const char *ext;
//    size_t ext_len;
//    zend_stat_t sb;
} php_lambda_server_request;

typedef struct php_lambda_server_client {
    struct php_lambda_server *server;
//    php_socket_t sock;
//    struct sockaddr *addr;
//    socklen_t addr_len;
//    zend_string *addr_str;
//    php_http_parser parser;
//    bool request_read;
//    zend_string *current_header_name;
//    zend_string *current_header_value;
//    enum { HEADER_NONE=0, HEADER_FIELD, HEADER_VALUE } last_header_element;
//    size_t post_read_offset;
    php_lambda_server_request request;
//    bool content_sender_initialized;
//    php_cli_server_content_sender content_sender;
//    int file_fd;
} php_lambda_server_client;

typedef struct php_lambda_server {
//    php_socket_t server_sock;
//    php_cli_server_poller poller;
//    int is_running;
//    char *host;
//    int port;
//    int address_family;
//    char *document_root;
//    size_t document_root_len;
//    char *router;
//    size_t router_len;
//    socklen_t socklen;
//    HashTable clients;
//    HashTable extension_mime_types;
} php_lambda_server;

// ssize_t nbytes_sent;
static size_t sapi_lambda_server_ub_write(const char *str, size_t str_length) /* {{{ */
{
    return 0;
} /* }}} */

static void sapi_lambda_server_flush(void *server_context) /* {{{ */
{

} /* }}} */

static int sapi_lambda_server_send_headers(sapi_headers_struct *sapi_headers) /* {{{ */
{
    return SAPI_HEADER_SENT_SUCCESSFULLY;
}
/* }}} */

// return number of bytes copied
static size_t sapi_lambda_server_read_post(char *buf, size_t count_bytes) /* {{{ */
{
    return 0;
} /* }}} */

static char *sapi_lambda_server_read_cookies(void) /* {{{ */
{
//    php_cli_server_client *client = SG(server_context);
    zval *val;
//    if (NULL == (val = zend_hash_str_find(&client->request.headers, "cookie", sizeof("cookie")-1))) {
//        return NULL;
//    }
    return Z_STRVAL_P(val);
} /* }}} */

static void sapi_lambda_server_register_variables(zval *track_vars_array) /* {{{ */
{
} /* }}} */


static void sapi_lambda_server_log_message(const char *msg, int syslog_type_int) /* {{{ */
{
} /* }}} */

/* {{{ sapi_module_struct cli_server_sapi_module */
sapi_module_struct lambda_server_sapi_module = {
        "lambda-server",				/* name */
        "AWS Lambda HTTP server",		/* pretty name */

        php_lambda_startup,		        /* startup */
        php_module_shutdown_wrapper,	/* shutdown */

        NULL,							/* activate */
        NULL,							/* deactivate */

        sapi_lambda_server_ub_write,	/* unbuffered write */
        sapi_lambda_server_flush,		/* flush */
        NULL,							/* get uid */
        NULL,							/* getenv */

        php_error,						/* error handler */

        NULL,							/* header handler */
        sapi_lambda_server_send_headers,	/* send headers handler */
        NULL,							/* send header handler */

        sapi_lambda_server_read_post,	/* read POST data */
        sapi_lambda_server_read_cookies,/* read Cookies */

        sapi_lambda_server_register_variables,	/* register server variables */
        sapi_lambda_server_log_message,	/* Log message */
        NULL,							/* Get request time */
        NULL,							/* Child terminate */

        STANDARD_SAPI_MODULE_PROPERTIES
}; /* }}} */

void my_handler(invocation_request *request, invocation_response **response){
//    *response = success(request->payload,"text/plain");
        *response = success("Hello World from AWS Lambda C Runtime for PHP","text/plain");
}

typedef struct _php_cgi_globals_struct {
    HashTable user_config_cache;
    char *redirect_status_env;
    bool rfc2616_headers;
    bool nph;
    bool check_shebang_line;
    bool fix_pathinfo;
    bool force_redirect;
    bool discard_path;
    bool fcgi_logging;
} php_cgi_globals_struct;

/* {{{ user_config_cache
 *
 * Key for each cache entry is dirname(PATH_TRANSLATED).
 *
 * NOTE: Each cache entry config_hash contains the combination from all user ini files found in
 *       the path starting from doc_root through to dirname(PATH_TRANSLATED).  There is no point
 *       storing per-file entries as it would not be possible to detect added / deleted entries
 *       between separate files.
 */
typedef struct _user_config_cache_entry {
    time_t expires;
    HashTable *user_config;
} user_config_cache_entry;

static void user_config_cache_entry_dtor(zval *el)
{
    user_config_cache_entry *entry = (user_config_cache_entry *)Z_PTR_P(el);
    zend_hash_destroy(entry->user_config);
    free(entry->user_config);
    free(entry);
}
/* }}} */

/* {{{ php_cgi_globals_ctor */
static void php_lambda_globals_ctor(php_cgi_globals_struct *php_cgi_globals)
{
#if defined(ZTS) && defined(PHP_WIN32)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    php_cgi_globals->rfc2616_headers = 0;
    php_cgi_globals->nph = 0;
    php_cgi_globals->check_shebang_line = 1;
    php_cgi_globals->force_redirect = 1;
    php_cgi_globals->redirect_status_env = NULL;
    php_cgi_globals->fix_pathinfo = 1;
    php_cgi_globals->discard_path = 0;
    php_cgi_globals->fcgi_logging = 1;
    zend_hash_init(&php_cgi_globals->user_config_cache, 8, NULL, user_config_cache_entry_dtor, 1);
}
/* }}} */

#ifdef ZTS
static int php_cgi_globals_id;
#define CGIG(v) ZEND_TSRMG(php_cgi_globals_id, php_cgi_globals_struct *, v)
#if defined(PHP_WIN32)
ZEND_TSRMLS_CACHE_DEFINE()
#endif
#else
static php_cgi_globals_struct php_cgi_globals;
#define CGIG(v) (php_cgi_globals.v)
#endif

int main(int argc, char *argv[])
{
    struct php_ini_builder ini_builder;
    char *bindpath = NULL;

#ifdef ZTS
    php_tsrm_startup();
#endif

    zend_signal_startup();

#ifdef ZTS
    ts_allocate_id(&php_cgi_globals_id, sizeof(php_cgi_globals_struct), (ts_allocate_ctor) php_cgi_globals_ctor, NULL);
#else
    php_lambda_globals_ctor(&php_cgi_globals);
#endif

    sapi_startup(&lambda_server_sapi_module);

    php_ini_builder_init(&ini_builder);



    /* startup after we get the above ini override se we get things right */
    if (lambda_server_sapi_module.startup(&lambda_server_sapi_module) == FAILURE) {
        printf("Crap\n");
        /* there is no way to see if we must call zend_ini_deactivate()
         * since we cannot check if EG(ini_directives) has been initialized
         * because the executor's constructor does not set initialize it.
         * Apart from that there seems no need for zend_ini_deactivate() yet.
         * So we goto out_err.*/
#ifdef ZTS
        tsrm_shutdown();
#endif
        free(bindpath);
        return FAILURE;
    }
//    module_started = 1;

    /* -e option */
//    if (use_extended_info) {
//        CG(compiler_options) |= ZEND_COMPILE_EXTENDED_INFO;
//    }

    zend_first_try {
        /***** Entry point into PHP engine *****/
//        exit_status = do_cli(argc, argv);

    } zend_end_try();

//    out:
//    if (ini_path_override) {
//        free(ini_path_override);
//    }
//    php_ini_builder_deinit(&ini_builder);
//    if (module_started) {
//        php_module_shutdown();
//    }
//    if (sapi_started) {
//        sapi_shutdown();
//    }

#ifdef ZTS
    tsrm_shutdown();
#endif

    /*
	 * Do not move this de-initialization. It needs to happen right before
	 * exiting.
	 */
//    cleanup_ps_args(argv);
//    exit(exit_status);

//    run_handler(&my_handler);

    return 0;
}
