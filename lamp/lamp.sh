#!/bin/sh

apt-get install mysql-server php5-mysql
apt-get install phpmyadmin

ln -sfn /etc/phpmyadmin/apache.conf /etc/apache2/conf-enabled/phpmyadmin.conf
