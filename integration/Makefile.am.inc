# Copyright 2011 Google Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# * Neither the name of Google Inc. nor the names of its contributors
#   may be used to endorse or promote products derived from this software
#   without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

tests_integrationdir = $(pkgtestsdir)/integration

tests_integration_DATA = integration/Atffile integration/Kyuafile
EXTRA_DIST += $(tests_integration_DATA)

ATF_SH_BUILD = \
    echo "Creating $${dst}"; \
    echo "\#! $(ATF_SH)" >$${dst}; \
    echo "\# AUTOMATICALLY GENERATED FROM Makefile" >>$${dst}; \
    if [ -n "$${substs}" ]; then \
        cat $(srcdir)/integration/utils.sh $${src} \
            | sed "$${substs}" >>$${dst}; \
    else \
        cat $(srcdir)/integration/utils.sh $${src} >>$${dst}; \
    fi; \
    chmod +x $${dst}

ATF_SH_DEPS = \
    $(srcdir)/integration/utils.sh \
    Makefile

EXTRA_DIST += integration/utils.sh

tests_integration_SCRIPTS = integration/cmd_about_test
CLEANFILES += integration/cmd_about_test
EXTRA_DIST += integration/cmd_about_test.sh
integration/cmd_about_test: $(srcdir)/integration/cmd_about_test.sh $(ATF_SH_DEPS)
	test -d integration || mkdir -p integration
	@src="$(srcdir)/integration/cmd_about_test.sh"; \
	dst="integration/cmd_about_test"; \
	substs='s,__KYUA_DOCDIR__,$(docdir),g'; $(ATF_SH_BUILD)

tests_integration_SCRIPTS += integration/cmd_help_test
CLEANFILES += integration/cmd_help_test
EXTRA_DIST += integration/cmd_help_test.sh
integration/cmd_help_test: $(srcdir)/integration/cmd_help_test.sh $(ATF_SH_DEPS)
	test -d integration || mkdir -p integration
	@src="$(srcdir)/integration/cmd_help_test.sh"; \
	dst="integration/cmd_help_test"; $(ATF_SH_BUILD)

tests_integration_SCRIPTS += integration/cmd_test_test
CLEANFILES += integration/cmd_test_test
EXTRA_DIST += integration/cmd_test_test.sh
integration/cmd_test_test: $(srcdir)/integration/cmd_test_test.sh $(ATF_SH_DEPS)
	test -d integration || mkdir -p integration
	@src="$(srcdir)/integration/cmd_test_test.sh"; \
	dst="integration/cmd_test_test"; $(ATF_SH_BUILD)

tests_integration_SCRIPTS += integration/global_test
CLEANFILES += integration/global_test
EXTRA_DIST += integration/global_test.sh
integration/global_test: $(srcdir)/integration/global_test.sh $(ATF_SH_DEPS)
	test -d integration || mkdir -p integration
	@src="$(srcdir)/integration/global_test.sh"; \
	dst="integration/global_test"; $(ATF_SH_BUILD)

include integration/helpers/Makefile.am.inc