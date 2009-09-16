#ifndef PHP_IOPHP_H
#define PHP_IOPHP_H 1

#define PHP_IOPHP_VERSION "1.0"
#define PHP_IOPHP_EXTNAME "iophp"


PHP_FUNCTION(iophp);

extern zend_module_entry iophp_module_entry;
#define phpext_iophp_ptr &iophp_module_entry

#endif
