#!/bin/sh

apt-get update
apt-get upgrade
apt-get install apache2
service apache2 start

usermod -a -G www-data student

chgrp -R www-data /var/www
chmod -R g+wr /var/www

cat <<EOF > /etc/apache2/sites-available/public.conf
<VirtualHost *:80>
  ServerAdmin webmaster@localhost
  DocumentRoot /var/www/public
  ErrorLog ${APACHE_LOG_DIR}/error.log
  CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>
EOF

cat <<EOF > /etc/apache2/sites-available/microsoftfake134.conf
<VirtualHost *:80>
    ServerName microsoftfake134.com
    DocumentRoot /var/www/microsoftfake134
</VirtualHost>
EOF


cat <<EOF > /etc/apache2/sites-available/githubfake134.conf
<VirtualHost *:80>
    ServerName githubfake134.com
    DocumentRoot /var/www/githubfake134
</VirtualHost>
EOF

cat <<EOF > /etc/apache2/sites-available/secret.conf
Listen 4567

<VirtualHost *:4567>
  ServerAdmin webmaster@localhost
  DocumentRoot /var/www/secret
  ErrorLog ${APACHE_LOG_DIR}/error.log
  CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>
EOF

rm -f /etc/apache2/sites-enabled/000-default.conf
ln -sfn /etc/apache2/sites-enabled/public.conf /etc/apache2/sites-available/public.conf
ln -sfn /etc/apache2/sites-enabled/secret.conf /etc/apache2/sites-available/secret.conf

mkdir -p /var/www/public
mkdir -p /var/www/secret

mkdir -p /var/www/githubfake134
mkdir -p /var/www/microsoftfake134

cat <<EOF > /var/www/public/index.html
<!DOCTYPE html>
<html>
  <body>
    <pre>Diese Seite tut nichts Verbotenes.</pre>
  </body>
</html>
EOF

cat <<EOF > /var/www/microsoftfake134/index.html
<!DOCTYPE html>
<html>
  <body>
    <pre>fakehost[1,2] tut nichts Verbotenes.</pre>
  </body>
</html>
EOF

cat <<EOF > /var/www/githubfake134/index.html
<!DOCTYPE html>
<html>
  <body>
    <pre>fakehost[2,2] tut nichts Verbotenes.</pre>
  </body>
</html>
EOF

mkdir -p /var/www/secret/base64
mkdir -p /var/www/secret/dns
