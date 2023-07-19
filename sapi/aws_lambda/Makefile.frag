aws_lambda: $(SAPI_AWS_LAMBDA_PATH)

$(SAPI_AWS_LAMBDA_PATH): $(PHP_GLOBAL_OBJS) $(PHP_BINARY_OBJS) $(PHP_AWS_LAMBDA_OBJS)
	$(BUILD_AWS_LAMBDA)

install-aws_lambda: $(SAPI_AWS_LAMBDA_PATH)
	@echo "Installing PHP AWS Lambda binary:        $(INSTALL_ROOT)$(bindir)/"
	@$(mkinstalldirs) $(INSTALL_ROOT)$(bindir)
	@$(INSTALL) -m 0755 $(SAPI_AWS_LAMBDA_PATH) $(INSTALL_ROOT)$(bindir)/$(program_prefix)php-aws-lambda$(program_suffix)$(EXEEXT)
	@echo "Installing PHP AWS Lambda man page:      $(INSTALL_ROOT)$(mandir)/man1/"
	@$(mkinstalldirs) $(INSTALL_ROOT)$(mandir)/man1
	@$(INSTALL_DATA) sapi/aws_lambda/aws-lambda-php.1 $(INSTALL_ROOT)$(mandir)/man1/$(program_prefix)aws-lambda-php$(program_suffix).1
