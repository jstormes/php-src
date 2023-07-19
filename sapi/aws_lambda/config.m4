PHP_ARG_ENABLE([aws_lambda],,
  [AS_HELP_STRING([--disable-aws_lambda],
    [Disable building AWS Lambda version of PHP])],
  [yes],
  [no])


dnl AWSLAMBDA setup.
AC_MSG_CHECKING(for AWS Lambda build)
if test "$PHP_AWSLAMBDA" != "no"; then
    PHP_ADD_MAKEFILE_FRAGMENT($abs_srcdir/sapi/aws_lambda/Makefile.frag)

    lambda_c_runtime="lib/hashmap.c lib/response.c lib/runtime.c lib/service-integration.c lib/service-logic.c
                         lib/string-builder.c lib/utils.c lib/version.c"

    dnl Set filename.
    SAPI_AWS_LAMBDA_PATH=sapi/aws_lambda/aws_lambda_php

    dnl Select SAPI.
    PHP_SELECT_SAPI(aws_lambda, program, aws_lambda_php.c $lambda_c_runtime, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1, '$(SAPI_AWS_LAMBDA_PATH)')

    BUILD_AWS_LAMBDA="\$(LIBTOOL) --mode=link \$(CC) -export-dynamic \$(CFLAGS_CLEAN) \$(EXTRA_CFLAGS) \$(EXTRA_LDFLAGS_PROGRAM) \$(LDFLAGS) \$(PHP_RPATHS) \$(PHP_GLOBAL_OBJS:.lo=.o) \$(PHP_BINARY_OBJS:.lo=.o) \$(PHP_AWS_LAMBDA_OBJS:.lo=.o) \$(EXTRA_LIBS) \$(ZEND_EXTRA_LIBS) -o \$(SAPI_AWS_LAMBDA_PATH)"

    dnl Set executable for tests.
    PHP_EXECUTABLE="\$(top_builddir)/\$(SAPI_AWS_LAMBDA_PATH)"
    PHP_SUBST(PHP_EXECUTABLE)

    dnl Expose to Makefile.
    PHP_SUBST(SAPI_AWS_LAMBDA_PATH)
    PHP_SUBST(BUILD_AWS_LAMBDA)

    PHP_OUTPUT(sapi/aws_lambda/aws-lambda-php.1)

    PHP_INSTALL_HEADERS([sapi/awslambda/aws_lambda_php.h])

else
  AC_MSG_RESULT(no)
fi