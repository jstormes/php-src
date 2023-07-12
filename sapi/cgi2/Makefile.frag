cgi2: $(SAPI_CGI2_PATH)

$(SAPI_CGI2_PATH): $(PHP_GLOBAL_OBJS) $(PHP_BINARY_OBJS) $(PHP_FASTCGI_OBJS) $(PHP_CGI2_OBJS)
	$(BUILD_CGI2)

install-cgi2: $(SAPI_CGI2_PATH)
	@echo "Installing PHP CGI2 binary:        $(INSTALL_ROOT)$(bindir)/"
	@$(mkinstalldirs) $(INSTALL_ROOT)$(bindir)
	@$(INSTALL) -m 0755 $(SAPI_CGI2_PATH) $(INSTALL_ROOT)$(bindir)/$(program_prefix)php-cgi2$(program_suffix)$(EXEEXT)
	@echo "Installing PHP CGI2 man page:      $(INSTALL_ROOT)$(mandir)/man1/"
	@$(mkinstalldirs) $(INSTALL_ROOT)$(mandir)/man1
	@$(INSTALL_DATA) sapi/cgi2/php-cgi2.1 $(INSTALL_ROOT)$(mandir)/man1/$(program_prefix)php-cgi2$(program_suffix).1
