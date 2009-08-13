#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_iophp.h"

static function_entry iophp_functions[] = {
    PHP_FE(iophp, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry iophp_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_IOPHP_EXTNAME,
    iophp_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_IOPHP_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_IOPHP
ZEND_GET_MODULE(iophp)
#endif

PHP_FUNCTION(iophp)
{
    
    char *response;

    char *request;
    int s_len;
    double b;
    

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &request, &s_len) == FAILURE) {
        RETURN_NULL();
    }
    
    


    response = estrndup(request, s_len);
    RETURN_STRING(response, 0);

    //RETURN_STRING("iophp", 1);
}
