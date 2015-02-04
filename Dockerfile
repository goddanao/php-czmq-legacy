FROM ubuntu:14.04

MAINTAINER Andrea Nanni (goddanao) <goddanao@gmail.com>

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y wget git build-essential libtool autoconf automake pkg-config unzip libkrb5-dev php5 php5-dev
RUN cd /tmp && git clone --branch 1.0.2 https://github.com/jedisct1/libsodium.git ./libsodium && cd ./libsodium && ./autogen.sh && ./configure && make check && make install && ldconfig
RUN cd /tmp && git clone --branch v4.1.0 git://github.com/zeromq/zeromq4-1.git ./libzmq && cd ./libzmq && ./autogen.sh && ./configure && make && make install && ldconfig
RUN cd /tmp && git clone --branch v3.0.0 git://github.com/zeromq/czmq.git ./czmq && cd ./czmq && ./autogen.sh && ./configure && make check && make install && ldconfig
RUN cd /tmp && git clone git://github.com/CopernicaMarketingSoftware/PHP-CPP.git ./phpcpp && cd ./phpcpp && make && make install && ldconfig
RUN cd /tmp && wget https://phar.phpunit.de/phpunit.phar && chmod +x phpunit.phar && mv phpunit.phar /usr/bin/phpunit
RUN rm /tmp/* -rf
RUN cd ~ && git clone https://github.com/goddanao/php-czmq.git ./php-czmq && cd ./php-czmq && make && make install && ldconfig
RUN cp ~/php-czmq/czmq.ini /etc/php5/cli/conf.d/020-czmq.ini
RUN cp ~/php-czmq/czmq.ini /etc/php5/apache2/conf.d/020-czmq.ini
RUN cd ~/php-czmq && php /usr/bin/phpunit


