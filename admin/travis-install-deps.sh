#! /bin/sh
# Copyright 2014 The Kyua Authors.
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

set -e -x

sudo apt-get update -qq
sudo apt-get install -y gdb liblua5.2-0 liblua5.2-dev \
    libsqlite3-0 libsqlite3-dev pkg-config sqlite3

install_from_github() {
    local name="${1}"; shift
    local release="${1}"; shift

    local distname="${name}-${release}"

    local baseurl="https://github.com/jmmv/${name}"
    wget --no-check-certificate \
        "${baseurl}/releases/download/${distname}/${distname}.tar.gz"
    tar -xzvf "${distname}.tar.gz"

    cd "${distname}"
    ./configure \
        --disable-developer \
        --without-atf \
        --without-doxygen \
        CPPFLAGS="-I/usr/local/include" \
        LDFLAGS="-L/usr/local/lib -Wl,-R/usr/local/lib" \
        PKG_CONFIG_PATH="/usr/local/lib/pkgconfig"
    make
    sudo make install
    cd -

    rm -rf "${distname}" "${distname}.tar.gz"
}

install_from_bintray() {
    local name="20160204-usr-local-kyua-ubuntu-12-04-amd64-${CC:-gcc}.tar.gz"
    wget "http://dl.bintray.com/jmmv/kyua/${name}" || return 1
    sudo tar -xzvp -C / -f "${name}"
    rm -f "${name}"
}

install_configure_deps() {
    if ! install_from_bintray; then
        install_from_github atf 0.21
        install_from_github lutok 0.4
        install_from_github kyua 0.12
    fi
}

do_apidocs() {
    sudo apt-get install -y doxygen
    install_configure_deps
}

do_distcheck() {
    install_configure_deps
}

do_style() {
    install_configure_deps
}

main() {
    if [ -z "${DO}" ]; then
        echo "DO must be defined" 1>&2
        exit 1
    fi
    for step in ${DO}; do
        "do_${DO}" || exit 1
    done
}

main "${@}"
