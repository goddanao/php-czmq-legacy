FROM ubuntu:14.04

MAINTAINER Andrea Nanni (goddanao) <goddanao@gmail.com>

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y wget git build-essential libtool autoconf automake pkg-config unzip libkrb5-dev php5 php5-dev
RUN cd /tmp && git clone git://github.com/jedisct1/libsodium.git ./libsodium && cd ./libsodium && ./autogen.sh && ./configure && make check && make install && ldconfig
RUN cd /tmp && git clone git://github.com/zeromq/libzmq.git ./libzmq && cd ./libzmq && ./autogen.sh && ./configure && make && make install && ldconfig
RUN cd /tmp && git clone git://github.com/zeromq/czmq.git ./czmq && cd ./czmq && ./autogen.sh && ./configure && make check && make install && ldconfig
RUN cd /tmp && git clone git://github.com/zeromq/zyre.git ./zyre && cd ./zyre && ./autogen.sh && ./configure && make check && make install && ldconfig
RUN cd /tmp && git clone git://github.com/zeromq/majordomo.git ./majordomo && cd ./majordomo && ./autogen.sh && ./configure && make check && make install && ldconfig
RUN cd /tmp && git clone git://github.com/zeromq/malamute.git ./malamute && cd ./malamute && ./autogen.sh && ./configure && make check && make install && ldconfig
RUN cd /tmp && git clone git://github.com/zeromq/filemq.git ./filemq && cd ./filemq && ./autogen.sh && ./configure && make check && make install && ldconfig
RUN cd /tmp && git clone git://github.com/CopernicaMarketingSoftware/PHP-CPP.git ./phpcpp && cd ./phpcpp && make && make install && ldconfig
RUN cd /tmp && git clone https://github.com/msgpack/msgpack-c.git ./msgpack-c && cd ./msgpack-c && cmake -DMSGPACK_CXX11=ON . && make install && ldconfig
RUN cd /tmp && wget https://phar.phpunit.de/phpunit.phar && chmod +x phpunit.phar && mv phpunit.phar /usr/bin/phpunit
RUN rm /tmp/* -rf
RUN cd ~ && git clone https://github.com/goddanao/php-czmq.git ./php-czmq && cd ./php-czmq && make && make install && ldconfig
RUN cp ~/php-czmq/czmq.ini /etc/php5/cli/conf.d/020-czmq.ini
RUN cp ~/php-czmq/czmq.ini /etc/php5/apache2/conf.d/020-czmq.ini
RUN cd ~/php-czmq && composer update && php /usr/bin/phpunit


