PHP_ARG_ENABLE(iophp, whether to enable iomephp support,
[ --enable-iophp   Enable iomephp support])

if test "$PHP_IOPHP" = "yes"; then
  AC_DEFINE(HAVE_IOPHP, 1, [Whether you have iophp])
  PHP_NEW_EXTENSION(iophp, iophp.c, $ext_shared)
fi
