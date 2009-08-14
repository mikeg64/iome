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
    char *fullresponse;
    char *command = "ioclient ";
    char *fullrequest;

    char *request;
    int s_len;
    double b;
    char buf[1000];
    FILE *ptr;
    zval *zname;
        

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &request,&s_len) == FAILURE) {
        RETURN_NULL();
    }
  
    
    
    fullrequest=emalloc(s_len+9);
    fullresponse=(char *)pemalloc(1000,1);
    sprintf(fullrequest,"%s%s",command,request);
    //printf('%s',zname);

    if ((ptr = popen(fullrequest, "r")) != NULL)
              while (fgets(buf, 1000, ptr) != NULL)
                              (void) sprintf(fullresponse,"%s", buf);
    (void) pclose(ptr);
  
    
    /*php_printf("2: %s",fullresponse);*/
    
    
    //fullrequest = strcat(command, request);
    response = (char *)pestrdup(fullresponse, 1);
    /*php_printf("3: %s",response);*/
    RETURN_STRING(fullresponse, 1);
    //RETVAL_STRINGL(fullresponse, strlen(fullresponse),0);

    //RETURN_STRING("iophp done", 1);
}
