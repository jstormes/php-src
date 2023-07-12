
PHP_ARG_ENABLE([cgi2],,
  [AS_HELP_STRING([--disable-cgi2],
    [Disable building CGI2 version of PHP])],
  [yes],
  [no])

dnl CGI2 setup.
AC_MSG_CHECKING(for CGI2 build)
if test "$PHP_CGI2" != "no"; then
    AC_MSG_RESULT(yes)

    AC_MSG_CHECKING([for sun_len in sys/un.h])
    AC_EGREP_HEADER([sun_len], [sys/un.h],
      [AC_MSG_RESULT([yes])
       AC_DEFINE([HAVE_SOCKADDR_UN_SUN_LEN], [1],
        [Define if sockaddr_un in sys/un.h contains a sun_len component])],
      AC_MSG_RESULT([no]))

    AC_MSG_CHECKING([whether cross-process locking is required by accept()])
    case "`uname -sr`" in
      IRIX\ 5.* | SunOS\ 5.* | UNIX_System_V\ 4.0)
        AC_MSG_RESULT([yes])
        AC_DEFINE([USE_LOCKING], [1],
          [Define if cross-process locking is required by accept()])
      ;;
      *)
        AC_MSG_RESULT([no])
      ;;
    esac

    PHP_ADD_MAKEFILE_FRAGMENT($abs_srcdir/sapi/cgi2/Makefile.frag)

    dnl Set filename.
    case $host_alias in
      *cygwin* )
        SAPI_CGI2_PATH=sapi/cgi2/php-cgi2.exe
        ;;
      * )
        SAPI_CGI2_PATH=sapi/cgi2/php-cgi2
        ;;
    esac

    dnl Select SAPI.
    PHP_SELECT_SAPI(cgi2, program, cgi_main.c, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1, '$(SAPI_CGI2_PATH)')

    case $host_alias in
      *aix*)
        if test "$php_sapi_module" = "shared"; then
          BUILD_CGI2="echo '\#! .' > php.sym && echo >>php.sym && nm -BCpg \`echo \$(PHP_GLOBAL_OBJS) \$(PHP_BINARY_OBJS) \$(PHP_CGI2_OBJS) | sed 's/\([A-Za-z0-9_]*\)\.lo/.libs\/\1.o/g'\` | \$(AWK) '{ if (((\$\$2 == \"T\") || (\$\$2 == \"D\") || (\$\$2 == \"B\")) && (substr(\$\$3,1,1) != \".\")) { print \$\$3 } }' | sort -u >> php.sym && \$(LIBTOOL) --mode=link \$(CC) -export-dynamic \$(CFLAGS_CLEAN) \$(EXTRA_CFLAGS) \$(EXTRA_LDFLAGS_PROGRAM) \$(LDFLAGS) -Wl,-brtl -Wl,-bE:php.sym \$(PHP_RPATHS) \$(PHP_GLOBAL_OBJS) \$(PHP_BINARY_OBJS) \$(PHP_FASTCGI_OBJS) \$(PHP_CGI2_OBJS) \$(EXTRA_LIBS) \$(ZEND_EXTRA_LIBS) -o \$(SAPI_CGI2_PATH)"
        else
          BUILD_CGI2="echo '\#! .' > php.sym && echo >>php.sym && nm -BCpg \`echo \$(PHP_GLOBAL_OBJS) \$(PHP_BINARY_OBJS) \$(PHP_CGI2_OBJS) | sed 's/\([A-Za-z0-9_]*\)\.lo/\1.o/g'\` | \$(AWK) '{ if (((\$\$2 == \"T\") || (\$\$2 == \"D\") || (\$\$2 == \"B\")) && (substr(\$\$3,1,1) != \".\")) { print \$\$3 } }' | sort -u >> php.sym && \$(LIBTOOL) --mode=link \$(CC) -export-dynamic \$(CFLAGS_CLEAN) \$(EXTRA_CFLAGS) \$(EXTRA_LDFLAGS_PROGRAM) \$(LDFLAGS) -Wl,-brtl -Wl,-bE:php.sym \$(PHP_RPATHS) \$(PHP_GLOBAL_OBJS) \$(PHP_BINARY_OBJS) \$(PHP_FASTCGI_OBJS) \$(PHP_CGI2_OBJS) \$(EXTRA_LIBS) \$(ZEND_EXTRA_LIBS) -o \$(SAPI_CGI2_PATH)"
        fi
        ;;
      *darwin*)
        BUILD_CGI2="\$(CC) \$(CFLAGS_CLEAN) \$(EXTRA_CFLAGS) \$(EXTRA_LDFLAGS_PROGRAM) \$(LDFLAGS) \$(NATIVE_RPATHS) \$(PHP_GLOBAL_OBJS:.lo=.o) \$(PHP_BINARY_OBJS:.lo=.o) \$(PHP_FASTCGI_OBJS:.lo=.o) \$(PHP_CGI2_OBJS:.lo=.o) \$(PHP_FRAMEWORKS) \$(EXTRA_LIBS) \$(ZEND_EXTRA_LIBS) -o \$(SAPI_CGI2_PATH)"
      ;;
      *)
        BUILD_CGI2="\$(LIBTOOL) --mode=link \$(CC) -export-dynamic \$(CFLAGS_CLEAN) \$(EXTRA_CFLAGS) \$(EXTRA_LDFLAGS_PROGRAM) \$(LDFLAGS) \$(PHP_RPATHS) \$(PHP_GLOBAL_OBJS:.lo=.o) \$(PHP_BINARY_OBJS:.lo=.o) \$(PHP_FASTCGI_OBJS:.lo=.o) \$(PHP_CGI2_OBJS:.lo=.o) \$(EXTRA_LIBS) \$(ZEND_EXTRA_LIBS) -o \$(SAPI_CGI2_PATH)"
      ;;
    esac

    dnl Expose to Makefile.
    PHP_SUBST(SAPI_CGI2_PATH)
    PHP_SUBST(BUILD_CGI2)

    PHP_OUTPUT(sapi/cgi2/php-cgi.1)
else
  AC_MSG_RESULT(no)
fi
