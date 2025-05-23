redis_server_install() {
  if [[ "$CENTOS_SEVEN" -eq '7' || "$CENTOS_EIGHT" -eq '8' || "$CENTOS_NINE" -eq '9' ]] && [[ "$REDIS_SERVER_INSTALL" = [yY] ]]; then
    {
    pushd "${SCRIPT_DIR}/addons/"
    # echo "Download to ${SCRIPT_DIR}/addons/redis-server-install.sh"
    # wget${ipv_forceopt_wget} https://github.com/centminmod/centminmod-redis/raw/master/redis-install.sh -O ${SCRIPT_DIR}/addons/redis-server-install.sh
    # chmod +x redis-server-install.sh
    if [ -f "${SCRIPT_DIR}/addons/redis-server-install.sh" ]; then
      echo "Run redis installer ${SCRIPT_DIR}/addons/redis-server-install.sh"
      ${SCRIPT_DIR}/addons/redis-server-install.sh install
      echo
      echo "Redis Info"
      redis-cli info server
      echo
    else
      echo
      echo "error: ${SCRIPT_DIR}/addons/redis-server-install.sh not found"
      echo
    fi
    popd
    } 2>&1 | tee -a "${CENTMINLOGDIR}/redis-server-install_${DT}.log"
  fi
}

checkredis_server_install() {
  # if redis-cli not installed, install it
  if [[ "$CENTOS_SEVEN" -eq '7' || "$CENTOS_EIGHT" -eq '8' || "$CENTOS_NINE" -eq '9' ]] && [[ "$REDIS_SERVER_INSTALL" = [yY] ]] && [[ ! -f /usr/bin/redis-cli ]]; then
    echo "*************************************************"
    cecho "* Installing redis server" $boldgreen
    echo "*************************************************"
    echo "detected centmin.sh menu option 13 run"
    echo "assumes you want to use redis PHP extension"
    echo "but redis server isn't installed"
    echo
    echo "installing redis server..."
    echo
    redis_server_install
    echo
  fi
}

#######################################################
checkredistar() {

  if [[ "$REDIS_PHPCURRENTVER" = '8.4' || "$PHPMUVER" = '8.4' || "$REDIS_PHPCURRENTVER" = '8.3' || "$PHPMUVER" = '8.3' || "$REDIS_PHPCURRENTVER" = '8.2' || "$PHPMUVER" = '8.2' || "$REDIS_PHPCURRENTVER" = '8.1' || "$PHPMUVER" = '8.1' || "$REDIS_PHPCURRENTVER" = '8.0' || "$PHPMUVER" = '8.0' || "$PHPVER_ID" -ge '80000' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.4' || "$PHPMUVER" = '7.4' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.3' || "$PHPMUVER" = '7.3' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.2' || "$PHPMUVER" = '7.2' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.1' || "$PHPMUVER" = '7.1' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.0' || "$PHPMUVER" = '7.0' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$INITIALINSTALL" = [yY] && "$(echo "$PHP_VERSION" | cut -d . -f1,2)" = '7.1' ]] || [[ "$INITIALINSTALL" = [yY] && "$(echo "$PHP_VERSION" | cut -d . -f1,2)" = '7.0' ]]; then
    if [[ "$REDISPHP_GIT" != [yY] ]]; then
      if [[ "$REDIS_PHPCURRENTVER" = '8.4' || "$PHPMUVER" = '8.4' || "$REDIS_PHPCURRENTVER" = '8.3' || "$PHPMUVER" = '8.3' || "$REDIS_PHPCURRENTVER" = '8.2' || "$PHPMUVER" = '8.2' || "$REDIS_PHPCURRENTVER" = '8.1' || "$PHPMUVER" = '8.1' || "$REDIS_PHPCURRENTVER" = '8.0' || "$PHPMUVER" = '8.0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.4' || "$PHPMUVER" = '7.4' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.3' || "$PHPMUVER" = '7.3' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.2' || "$PHPMUVER" = '7.2' ]]; then
        REDISPHP_VER="$REDISPHPSEVENTWO_VER"
        echo "checkredistar: REDISPHP_VER=$REDISPHP_VER"
      elif [[ "$INITIALINSTALL" = [yY] ]] && [[ "$PHPMVER" = '8.4' || "$PHPMVER" = '8.3' || "$PHPMVER" = '8.2' || "$PHPMVER" = '8.1' || "$PHPMVER" = '8.0' || "$PHPMVER" = '7.4' || "$PHPMVER" = '7.3' || "$PHPMVER" = '7.2' ]]; then
        REDISPHP_VER="$REDISPHPSEVENTWO_VER"
        echo "checkredistar: REDISPHP_VER=$REDISPHP_VER"
      else
        REDISPHP_VER="$REDISPHPSEVEN_VER"
        echo "checkredistar: REDISPHP_VER=$REDISPHP_VER"
      fi
      PHPEXT_REDISLINKFILE="phpredis-${REDISPHP_VER}.tgz"
      PHPEXT_REDISLINK="https://github.com/phpredis/phpredis/archive/${REDISPHP_VER}.tar.gz"
      PHPEXT_REDISLINKGITLAB="https://gitlab.com/centminmod-github-mirror/phpredis/repository/archive.tar.gz?ref=${REDISPHP_VER}"
      PHPEXT_REDISLINKLOCAL="${LOCALCENTMINMOD_MIRROR}/centminmodparts/redis/${PHPEXT_REDISLINKFILE}"
    fi
  fi

cecho "Check if ${PHPEXT_REDISLINKFILE} exists" $boldyellow
if [ ! -f "${DIR_TMP}/${PHPEXT_REDISLINKFILE}" ]; then
  cecho "Downloading redis PHP extension.." $boldgreen
  redisphptarball
elif [[ -f "${DIR_TMP}/${PHPEXT_REDISLINKFILE}" && ! -d "${DIR_TMP}/phpredis-${REDISPHP_VER}" ]]; then
  pushd "$DIR_TMP"
  tar xzf "${PHPEXT_REDISLINKFILE}"
  popd
fi

}

checkigbinary() {
    PHPEXTDIRD=`cat /usr/local/bin/php-config | awk '/^extension_dir/ {extdir=$1} END {gsub(/\047|extension_dir|=|)/,"",extdir); print extdir}'`
    cecho "Checking for igbinary.so ..." $boldgreen
    cecho "Check if ${PHPEXTDIRD}/igbinary.so or ${CONFIGSCANDIR}/igbinary.ini exists" $boldyellow

    if [[ ! -f ${CONFIGSCANDIR}/igbinary.ini || ! -f "${PHPEXTDIRD}/igbinary.so" ]]; then
     funct_igbinaryinstall
     #echo "will need to reinstall memcached extensions if needed"
    fi
    
    # check for different igbinary versions
    if [ -f /usr/local/bin/php ]; then
        if [[ "$(php --ri igbinary | awk '/igbinary version/ {print $4}')" != "${IGBINARY_VERSION}" ]]; then
            cecho "Check for different igbinary versions ..." $boldgreen
            funct_igbinaryinstall
        fi
    fi
}

#######################################################
redisinstall() {
    if [[ "$PHP_INSTALL" = [yY] ]]; then

    REDIS_SUBMENU=$1

    if [[ "$REDIS_SUBMENU" = 'submenu' ]]; then
        REDIS_PHPCURRENTVER=$(php-config --version | cut -d . -f1,2)
    fi

    PHPEXTDIRD=`cat /usr/local/bin/php-config | awk '/^extension_dir/ {extdir=$1} END {gsub(/\047|extension_dir|=|)/,"",extdir); print extdir}'`

    echo "*************************************************"
    cecho "* Installing redis PHP extension" $boldgreen
    echo "*************************************************"
    echo "Downloading redis PHP extension..."
    cd $DIR_TMP
      # set extra cflags fro devtoolset-7 and devtoolset-8 compatibility
      check_devtoolset_php
      enable_devtoolset

if [[ "$INITIALINSTALL" != [yY] ]]; then
    checkigbinary
fi

checkredistar

echo
echo "redisinstall: PHPVER_ID=$PHPVER_ID"
echo "redisinstall: REDIS_PHPCURRENTVER=$REDIS_PHPCURRENTVER"
echo "redisinstall: PHPMUVER=$PHPMUVER"
echo "redisinstall: REDIS_PHPCURRENTVER=$REDIS_PHPCURRENTVER"
echo

if [[ "$REDIS_PHPCURRENTVER" = '8.4' || "$PHPMUVER" = '8.4' || "$REDIS_PHPCURRENTVER" = '8.3' || "$PHPMUVER" = '8.3' || "$REDIS_PHPCURRENTVER" = '8.2' || "$PHPMUVER" = '8.2' || "$REDIS_PHPCURRENTVER" = '8.1' || "$PHPMUVER" = '8.1' || "$REDIS_PHPCURRENTVER" = '8.0' || "$PHPMUVER" = '8.0' || "$PHPVER_ID" -ge '80000' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.4' || "$PHPMUVER" = '7.4' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.3' || "$PHPMUVER" = '7.3' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.2' || "$PHPMUVER" = '7.2' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.1' || "$PHPMUVER" = '7.1' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.0' || "$PHPMUVER" = '7.0' || "$PHPMUVER" = 'NGDEBUG' || "$PHPSEVEN_CHECKVER" = '0' ]] || [[ "$INITIALINSTALL" = [yY] && "$(echo "$PHP_VERSION" | cut -d . -f1,2)" = '7.1' ]] || [[ "$INITIALINSTALL" = [yY] && "$(echo "$PHP_VERSION" | cut -d . -f1,2)" = '7.0' ]]; then
    cecho "Compiling PHP redis-${REDISPHP_VER} extension for PHP ..." $boldgreen

    if [[ "$CENTOS_SEVEN" -eq '7' ]] && [[ "$REDIS_PHPCURRENTVER" = '8.0' || "$PHPMUVER" = '8.0' || "$REDIS_PHPCURRENTVER" = '8.1' || "$PHPMUVER" = '8.1' || "$REDIS_PHPCURRENTVER" = '8.2' || "$PHPMUVER" = '8.2' || "$REDIS_PHPCURRENTVER" = '8.3' || "$PHPMUVER" = '8.3' ]]; then
        REDISPHP_GIT='y'
        AUTODETECPHP_OVERRIDE='y'
    fi

    if [[ "$REDIS_PHPCURRENTVER" = '8.4' || "$PHPMUVER" = '8.4' ]]; then
        REDISPHP_GIT='y'
        AUTODETECPHP_OVERRIDE='y'
    fi

    pwd
    echo "cd $DIR_TMP"
    cd $DIR_TMP
    if [[ "$REDISPHP_GIT" = [yY] ]]; then
        rm -rf redis-develop
    
        PHPREDISGITLINK='https://github.com/phpredis/phpredis'
        # fallback mirror if official github is down, use gitlab mirror
        curl -${ipv_forceopt}Is --connect-timeout 30 --max-time 30 $PHPREDISGITLINK | grep 'HTTP\/' | grep '200' >/dev/null 2>&1
        PHPREDISGITCURLCHECK=$?
        if [[ "$PHPREDISGITCURLCHECK" != '0' ]]; then
            PHPREDISGITLINK='https://gitlab.com/centminmod-github-mirror/phpredis.git'
        fi
        if [ ! -d redis-develop ]; then
            time git clone -b develop "$PHPREDISGITLINK" redis-develop
            git submodule update --init
        fi
        cd redis-develop
        if [[ "$INITIALINSTALL" != [yY] ]]; then
            make clean
        fi
        if [[ "$CENTOS_SIX" -eq '6' ]]; then
            # PHP 7.3.0 + centos 6 issue https://community.centminmod.com/posts/69561/
            if [ ! -f /usr/bin/autoconf268 ]; then
                echo "yum -q -y install autoconf268"
                yum -q -y install autoconf268
            fi
            if [ -f /usr/bin/autoconf268 ]; then
                export PHP_AUTOCONF=/usr/bin/autoconf268
                export PHP_AUTOHEADER=/usr/bin/autoheader268
            fi
        fi
        /usr/local/bin/phpize
        redis_check_zstd=$(grep -o 'enable-redis-zstd' config.m4)
        if [[ "$redis_check_zstd" = 'enable-redis-zstd' ]]; then
            if [[ ! "$(rpm -qa libzstd-devel)" ]]; then
                yum -q -y install libzstd libzstd-devel
            fi
            redis_zstd_opt=' --enable-redis-zstd'
        else
            redis_zstd_opt=''
        fi
        redis_check_lz4=$(grep -o 'enable-redis-lz4' config.m4)
        if [[ "$redis_check_lz4" = 'enable-redis-lz4' ]]; then
            if [[ ! "$(rpm -qa lz4-devel)" ]]; then
                yum -q -y install lz4 lz4-devel
            fi
            redis_lzfour_opt=' --enable-redis-lz4 --with-liblz4'
        else
            redis_lzfour_opt=''
        fi
        redis_check_lzf=$(grep -o 'enable-redis-lzf' config.m4)
        if [[ "$redis_check_lzf" = 'enable-redis-lzf' ]]; then
            if [[ ! "$(rpm -qa liblzf)" ]]; then
                yum -q -y install liblzf liblzf-devel
            fi
            # redis_lzf_opt=' --enable-redis-lzf'
            redis_lzf_opt=''
        else
            redis_lzf_opt=''
        fi
        if [[ -f "${PHPEXTDIRD}/igbinary.so" ]] && [ "$IGBINARY_INSTALL" == 'y' ]; then
            if [[ "$REDIS_PHPCURRENTVER" = '7.4' || "$REDIS_PHPCURRENTVER" = '8.0' || "$REDIS_PHPCURRENTVER" = '8.1' || "$REDIS_PHPCURRENTVER" = '8.2' || "$REDIS_PHPCURRENTVER" = '8.3' || "$PHPMUVER" = '7.4' || "$PHPMUVER" = '8.0' || "$PHPMUVER" = '8.1' || "$PHPMUVER" = '8.2' || "$PHPMUVER" = '8.3' || "$PHPVER_ID" -ge '80000' || "$PHPMUVER" = 'NGDEBUG' ]]; then
                # disable igbinary on PHP 8.0+ due to segfaulting
                echo "redis php configure"
                echo "CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}"
                CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}
            else
                echo "redis php configure"
                echo "CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config --enable-redis-igbinary${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}"
                CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config --enable-redis-igbinary${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}
            fi
        else
            echo "redis php configure"
            echo "CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}"
            CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}
        fi
        make${MAKETHREADS}
        make install
    else
        if [[ "$REDIS_PHPCURRENTVER" = '8.4' || "$PHPMUVER" = '8.4' || "$REDIS_PHPCURRENTVER" = '8.3' || "$PHPMUVER" = '8.3' || "$REDIS_PHPCURRENTVER" = '8.2' || "$PHPMUVER" = '8.2' || "$REDIS_PHPCURRENTVER" = '8.1' || "$PHPMUVER" = '8.1' || "$REDIS_PHPCURRENTVER" = '8.0' || "$PHPMUVER" = '8.0' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.4' || "$PHPMUVER" = '7.4' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.3' || "$PHPMUVER" = '7.3' ]] || [[ "$REDIS_PHPCURRENTVER" = '7.2' || "$PHPMUVER" = '7.2' ]]; then
            REDISPHP_VER="$REDISPHPSEVENTWO_VER"
            echo "REDISPHP_GIT=n: REDISPHP_VER=$REDISPHP_VER"
        elif [[ "$INITIALINSTALL" = [yY] ]] && [[ "$PHPMVER" = '8.4' || "$PHPMVER" = '8.3' || "$PHPMVER" = '8.2' || "$PHPMVER" = '8.1' || "$PHPMVER" = '8.0' || "$PHPMVER" = '7.4' || "$PHPMVER" = '7.3' || "$PHPMVER" = '7.2' ]]; then
            REDISPHP_VER="$REDISPHPSEVENTWO_VER"
            echo "REDISPHP_GIT=n: REDISPHP_VER=$REDISPHP_VER"
        else
            REDISPHP_VER="$REDISPHPSEVEN_VER"
            echo "REDISPHP_GIT=n: REDISPHP_VER=$REDISPHP_VER"
        fi
        pwd
        echo "cd $DIR_TMP"
        cd $DIR_TMP
        #tar xvzf ${PHPEXT_REDISLINKFILE}
        cd ${DIR_TMP}/phpredis-${REDISPHP_VER}
        if [[ "$INITIALINSTALL" != [yY] ]]; then
            make clean
        fi
        /usr/local/bin/phpize
        redis_check_zstd=$(grep -o 'enable-redis-zstd' config.m4)
        if [[ "$redis_check_zstd" = 'enable-redis-zstd' ]]; then
            if [[ ! "$(rpm -qa libzstd-devel)" ]]; then
                yum -q -y install libzstd libzstd-devel
            fi
            redis_zstd_opt=' --enable-redis-zstd'
        else
            redis_zstd_opt=''
        fi
        redis_check_lz4=$(grep -o 'enable-redis-lz4' config.m4)
        if [[ "$redis_check_lz4" = 'enable-redis-lz4' ]]; then
            if [[ ! "$(rpm -qa lz4-devel)" ]]; then
                yum -q -y install lz4 lz4-devel
            fi
            redis_lzfour_opt=' --enable-redis-lz4 --with-liblz4'
        else
            redis_lzfour_opt=''
        fi
        redis_check_lzf=$(grep -o 'enable-redis-lzf' config.m4)
        if [[ "$redis_check_lzf" = 'enable-redis-lzf' ]]; then
            if [[ ! "$(rpm -qa liblzf)" ]]; then
                yum -q -y install liblzf liblzf-devel
            fi
            # redis_lzf_opt=' --enable-redis-lzf'
            redis_lzf_opt=''
        else
            redis_lzf_opt=''
        fi
        if [[ -f "${PHPEXTDIRD}/igbinary.so" ]] && [ "$IGBINARY_INSTALL" == 'y' ]; then
            if [[ "$PHPMUVER" = '5.5' ]] || [[ "$INITIALINSTALL" = [yY] && "$(echo "$PHP_VERSION" | cut -d . -f1,2)" = '5.5' ]]; then
                echo "php configure alt"
                echo "CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config"
                CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config
            else
                if [[ "$REDIS_PHPCURRENTVER" = '7.4' || "$REDIS_PHPCURRENTVER" = '8.0' || "$PHPMUVER" = '7.4' || "$PHPMUVER" = '8.0' || "$PHPMUVER" = '8.1' || "$PHPVER_ID" -ge '80000' || "$PHPMUVER" = 'NGDEBUG' ]]; then
                    # disable igbinary on PHP 8.0+ due to segfaulting
                    echo "redis php configure alt"
                    echo "CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}"
                    CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}
                else
                    echo "redis php configure alt"
                    echo "CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config --enable-redis-igbinary${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}"
                    CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config --enable-redis-igbinary${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}
                fi
            fi
        else
            echo "php configure alt"
            echo "CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}"
            CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config${redis_zstd_opt}${redis_lzfour_opt}${redis_lzf_opt}
        fi
        make${MAKETHREADS}
        make install   
    fi
else
    cecho "Compiling PHP redis-${REDISPHP_VER} extension..." $boldgreen

    pwd
    echo "cd $DIR_TMP"
    cd $DIR_TMP
    #tar xvzf ${PHPEXT_REDISLINKFILE}
    cd ${DIR_TMP}/phpredis-${REDISPHP_VER}
    if [[ "$INITIALINSTALL" != [yY] ]]; then
        make clean
    fi
    /usr/local/bin/phpize
    if [[ -f "${PHPEXTDIRD}/igbinary.so" ]] && [ "$IGBINARY_INSTALL" == 'y' ]; then
        if [[ "$PHPMUVER" = '5.5' ]] || [[ "$INITIALINSTALL" = [yY] && "$(echo "$PHP_VERSION" | cut -d . -f1,2)" = '5.5' ]]; then
            CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config
        else
            CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config --enable-redis-igbinary
        fi
    else
        CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config
    fi
    make${MAKETHREADS}
    make install
fi # php 7 or not

#######################################################
# check to see if redis.so already loaded in php.ini

REDISSOCHECK=`grep 'redis.so' /usr/local/lib/php.ini`
REDISSOCHECKB=$(grep 'redis.so' ${CONFIGSCANDIR}/redis.ini)
PHPEXTDIRD=`cat /usr/local/bin/php-config | awk '/^extension_dir/ {extdir=$1} END {gsub(/\047|extension_dir|=|)/,"",extdir); print extdir}'`

if [[ -z "$REDISSOCHECK" || -z "$REDISSOCHECKB" ]]; then
    #echo "" >> /usr/local/lib/php.ini
    echo "extension=redis.so" > ${CONFIGSCANDIR}/redis.ini
else
    echo ""
    echo "redis.so already loaded in ${CONFIGSCANDIR}/redis.ini"
    echo "$REDISSOCHECK"
    echo ""
fi # redis.so check

    # if [[ "$PHPMUVER" = '8.0' || "$PHPVER_ID" -ge '80000' || "$PHPMUVER" = 'NGDEBUG' ]] && [ -f "${CONFIGSCANDIR}/redis.ini" ]; then
    #     # disable redis on PHP 8.0+ due to segfaulting
    #     cecho "PHP 8.0 detected removing incompatible ${CONFIGSCANDIR}/redis.ini" $boldyellow
    #     cecho "rm -f ${CONFIGSCANDIR}/redis.ini" $boldyellow
    #     rm -f ${CONFIGSCANDIR}/redis.ini
    #     echo
    # fi
    if [[ "$REDIS_SUBMENU" = 'submenu' ]]; then
        cmservice php-fpm restart
    fi
    fi # PHP_INSTALL=y
}