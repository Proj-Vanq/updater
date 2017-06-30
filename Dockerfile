FROM freeslave/qt5-base-static:5.9.1-1
RUN apt-get install -y autopoint autoconf gettext libcppunit-dev libtool libgcrypt11-dev pkgconf
COPY . /updater2
WORKDIR /updater2/aria2
RUN autoreconf -i && ./configure --without-libxml2 --without-libexpat --without-sqlite3 --disable-ssl --enable-libaria2 --without-zlib --without-libcares --enable-static=yes ARIA2_STATIC=yes --without-libssh2 --disable-websocket && make clean && make -j`nproc`
WORKDIR /updater2
RUN qmake -config release && make clean && make -j`nproc`
CMD cp updater2 /build-docker
