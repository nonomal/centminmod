yumlog_check() {
  if [[ "$CENTOS_EIGHT" = '8' || "$CENTOS_NINE" = '9' ]]; then
    YUMLOG_FILE='/var/log/dnf.log'
  else
    YUMLOG_FILE='/var/log/yum.log'
  fi
}

grub_efi_fix() {
    if [[ "$VPS_GEOIPCHECK_V3" = [yY] ]]; then
      VPS_GEOIPCHECK=$(curl -${ipv_forceopt}s${CURL_TIMEOUTS} -A "$CURL_AGENT VPS GRUB CHECK $SCRIPT_VERSION $CURL_CPUMODEL $CURL_CPUSPEED $VPS_VIRTWHAT" https://geoip.centminmod.com/v3 | jq -r)
      VPS_ASNCHECK=$(echo "$VPS_GEOIPCHECK" | jq -r '"\(.data.asn) \(.data.description_short)"')
    elif [[ "$VPS_GEOIPCHECK_V4" = [yY] ]]; then
      VPS_GEOIPCHECK=$(curl -${ipv_forceopt}s${CURL_TIMEOUTS} -A "$CURL_AGENT VPS GRUB CHECK $SCRIPT_VERSION $CURL_CPUMODEL $CURL_CPUSPEED $VPS_VIRTWHAT" https://geoip.centminmod.com/v4 | jq -r)
      VPS_ASNCHECK=$(echo "$VPS_GEOIPCHECK" | jq -r '"\(.asn) \(.asOrganization)"')
    fi
    if [[ "$CENTOS_SEVEN" -eq '7' && "$(echo "$VPS_ASNCHECK" | grep -o 'OVH' >/dev/null 2>&1; echo $?)" -eq '0' && -d /boot/efi/EFI/centos && ! -f /boot/efi/EFI/centos/grub.cfg ]]; then
      if [[ "$(lsblk | grep nvme)" && -d /boot/efi/EFI/centos ]]; then
        if [ ! -f /usr/sbin/efibootmgr ]; then
          yum -q -y install efibootmgr
        fi
        # check EFI bios support
        check_efibios=$(efibootmgr 2>&1 | grep -o 'not supported')
        check_bootefi=$(df -P --local | grep nvme | grep -o '/boot/efi')
        check_grubefi=$(egrep 'linuxefi|initrdefi' /boot/grub2/grub.cfg)
        check_grub_noefi=$(egrep 'linux16|initrd16' /boot/grub2/grub.cfg)
      fi
      if [[ "$check_grubefi" && "$check_bootefi" = '/boot/efi' && "$check_efibios" != 'not supported' && "$(lsblk | grep nvme)" && -d /boot/efi/EFI/centos && -d /sys/firmware/efi ]]; then
        echo
        cecho "--------------------------------------------------------" $boldyellow
        cecho "Fix CentOS 7 EFI Bios based systems with missing" $boldyellow
        cecho "/boot/efi/EFI/centos/grub.cfg" $boldyellow
        cecho "https://community.centminmod.com/posts/57100/" $boldyellow
        echo
        grub2-mkconfig -o /boot/efi/EFI/centos/grub.cfg

        echo
        ls -lah /boot/efi/EFI/centos/grub.cfg
        cecho "--------------------------------------------------------" $boldyellow
        echo
      fi
    fi
}

function checkcentosver {

if [[ "$INITIALINSTALL" = [yY] ]]; then
    VERCOMPARE=`expr $CENTOSVER \> $TESTEDCENTOSVER`
    
    if [[ "$VERCOMPARE" = "1"  ]]; then
    
     echo "-----------------------------------------------------"
            if [[ "$ALMALINUX_EIGHT" -eq '8' || "$ALMALINUX_NINE" -eq '9' ]]; then
              echo "Detected AlmaLinux OS"
              echo
              echo "AlmaLinux 8/9 is currently not supported by Centmin Mod, please use CentOS 7.9+"
              echo
            elif [[ "$CENTOS_EIGHT" -eq '8' || "$CENTOS_NINE" -eq '9' ]]; then
              echo "Detected CentOS version greater than > CentOS $TESTEDCENTOSVER"
              echo "CentOS $TESTEDCENTOSVER is the latest tested version for Centmin Mod"
              echo "No guarantee 100% working install with your CentOS $CENTOSVER"
              echo
              echo "CentOS 8 is currently not supported by Centmin Mod, please use CentOS 7.9+"
              echo
            fi
     echo "-----------------------------------------------------"
            if [[ "$CENTOS_ALPHATEST" = [yY] && "$CENTOS_NINE" -eq '9' ]]; then
              centoscheckcont='y'
            elif [[ "$CENTOS_ALPHATEST" = [yY] && "$CENTOS_EIGHT" -eq '8' ]]; then
              centoscheckcont='y'
            else
              echo ""
              read -ep "Do you still want to continue with install ? [y/n]: " centoscheckcont
            fi
    
            if [[ "$centoscheckcont" != [yY] ]]; then
    
            echo ""
            echo "Regularly check centminmod.com for news on new CentOS versions support"
            echo "aborting script..."
            exit
    
            fi
    
    else
    
            centoscheckcont='y'
    
    fi
fi

sshdtweaks

# swap file detection and setup routine add a 1GB swap file 
# to servers without swap setup and non-openvz based as a 
# precaution for low memory vps systems <1GB which require
# memory intensive initial install and running i.e. php fileinfo
# extension when enabled via PHPFINFO='y' need more memory ~1GB
# on <1GB systems this can be a problem without a swap file as 
# an additional memory buffer
  FINDSWAPSIZE=$(free -m | awk '/Swap: / {print $2}' | head -n1)
  # if free -m output swap size = 0, create a 1GB swap file for
  # non-openvz systems or if less than 1GB of memory and swap 
  # smaller than 512MB on non-openvz systems, create a 1GB additional
  # swap file
  if [[ "$FINDSWAPSIZE" -eq '0' && ! -f /proc/user_beancounters && "$CHECK_LXD" != [yY] && ! -f /swapfile ]] || [[ "$(awk '/MemTotal/ {print $2}' /proc/meminfo)" -le '1048576' && "$FINDSWAPSIZE" -le '512' && ! -f /proc/user_beancounters && "$CHECK_LXD" != [yY] && ! -f /swapfile ]]; then
    {
    echo
    free -m
    echo
    echo "create 4GB swap file"; 
    if [[ "$(df -hT | grep -w xfs)" || "$(virt-what | grep -o lxc)" = 'lxc' ]]; then
        dd if=/dev/zero of=/swapfile bs=4096 count=1024k;
    else
        fallocate -l 4G /swapfile
    fi
    ls -lah /swapfile;
    mkswap /swapfile;
    swapon /swapfile;
    chown root:root /swapfile;
    chmod 0600 /swapfile;
    swapon -s;
    echo "/swapfile swap swap defaults 0 0" >> /etc/fstab;
    mount -a;
    free -m
    echo
    } 2>&1 | tee "${CENTMINLOGDIR}/centminmod_swapsetup_${DT}.log"
  elif [[ "$FINDSWAPSIZE" -eq '0' && ! -f /proc/user_beancounters && "$CHECK_LXD" != [yY] && -f /swapfile && "$(grep '/swapfile' /etc/fstab)" ]] || [[ "$(awk '/MemTotal/ {print $2}' /proc/meminfo)" -le '1048576' && "$FINDSWAPSIZE" -le '512' && ! -f /proc/user_beancounters && "$CHECK_LXD" != [yY] && -f /swapfile && "$(grep '/swapfile' /etc/fstab)" ]]; then
    {
    echo
    free -mlt
    echo
    echo "re-create 1GB swap file";
    swapoff -a
    if [[ "$(df -hT | grep -w xfs)" || "$(virt-what | grep -o lxc)" = 'lxc' ]]; then
        dd if=/dev/zero of=/swapfile bs=4096 count=1024k;
    else
        fallocate -l 4G /swapfile
    fi
    ls -lah /swapfile;
    mkswap /swapfile;
    swapon /swapfile;
    chown root:root /swapfile;
    chmod 0600 /swapfile;
    swapon -s;
    # echo "/swapfile swap swap defaults 0 0" >> /etc/fstab;
    mount -a;
    free -mlt
    echo
    } 2>&1 | tee "${CENTMINLOGDIR}/centminmod_swapsetup_${DT}.log"
  fi

if [ ! -f /etc/ld.so.preload ]; then
  touch /etc/ld.so.preload
fi

MACHINE_TYPE=$(uname -m) # Used to detect if OS is 64bit or not.

    if [ "${MACHINE_TYPE}" == 'x86_64' ];
    then
        ARCH='x86_64'
    else
        ARCH='i386'
    fi

# Set LIBDIR
if [ "${ARCH}" == 'x86_64' ];
then
    LIBDIR='lib64'
else
    LIBDIR='lib'
fi

if [ -f "/usr/${LIBDIR}/sa/sa2" ]; then

  # SAR extend log from 7 to 21 days
  SARDAYCHECK=$(awk -F "=" '/^HISTORY/ { print $2 }' /usr/${LIBDIR}/sa/sa2)

  if [ "$SARDAYCHECK" == '7' ]; then
  sed -i 's/HISTORY=7/HISTORY=21/g' /usr/${LIBDIR}/sa/sa2
  fi
fi

if [[ -f ~/.bash_profile ]]; then
    # Check if EDITOR is already set to the value of USEEDITOR
    if ! grep -q "export EDITOR=$USEEDITOR" ~/.bash_profile; then
        # Append the default editor settings using USEEDITOR
        echo -e "\nexport EDITOR=$USEEDITOR\nexport VISUAL=$USEEDITOR" >> ~/.bash_profile
    fi
else
    cat > ~/.bash_profile <<EOF
# .bash_profile

# Get the aliases and functions
if [ -f ~/.bashrc ]; then
    . ~/.bashrc
fi

# User specific environment and startup programs
PATH=\$PATH:\$HOME/bin

export PATH
export EDITOR=$USEEDITOR
export VISUAL=$USEEDITOR
export HISTTIMEFORMAT="%a %h %d – %r "
EOF
fi

if [[ "$(id -u)" -ne '0' ]]; then
if [[ -f "$HOME/.bash_profile" ]]; then
    NANOCHECK=$(grep nano $HOME/.bash_profile)
    if [ -z "$NANOCHECK" ]; then
    sed -i 's/export PATH/export PATH\nexport EDITOR=nano/g' "$HOME/.bash_profile"
    fi
else
    cat > "$HOME/.bash_profile" <<EOF
# .bash_profile

# Get the aliases and functions
if [ -f $HOME/.bashrc ]; then
        . $HOME/.bashrc
fi

# User specific environment and startup programs

PATH=\$PATH:\$HOME/bin

export PATH
export EDITOR=nano
export HISTTIMEFORMAT="%a %h %d – %r "
EOF

# cat $HOME/.bash_profile
fi
fi

if [ -f /root/.screenrc ]; then
  DEFSCROLLCHECK=$(grep defscrollback /root/.screenrc)
  if [ -z "$DEFSCROLLCHECK" ]; then
  echo "defscrollback 200000" >> /root/.screenrc
  fi
else
  echo "defscrollback 200000" >> /root/.screenrc
fi
if [[ "$(id -u)" -ne '0' ]]; then
  if [ -f "$HOME/.screenrc" ]; then
    DEFSCROLLCHECK=$(grep defscrollback $HOME/.screenrc)
    if [ -z "$DEFSCROLLCHECK" ]; then
    echo "defscrollback 200000" >> "$HOME/.screenrc"
    fi
  else
    echo "defscrollback 200000" >> "$HOME/.screenrc"
  fi
fi

if [[ -f /usr/bin/ccache && ! -f "${DIR_TMP}/${CCACHEFILE}" ]];then
    ccacheinstall
fi

if [[ -f /usr/local/bin/ccache && ! -f "${DIR_TMP}/${CCACHEFILE}" ]] || [[ -f /usr/local/bin/ccache && -d "${DIR_TMP}/ccache-${CCACHE_VER}" && "$CCACHE_VER" != "$(ccache -V | head -n 1 | awk '{print $3}')" ]]; then
    ccacheinstall
fi

if [ -f /etc/centminmod-release ];then
  if [[ "$SCRIPT_VERSION" != "$(cat /etc/centminmod-release >/dev/null)" ]]; then
  setupmotd
  fi
else
  setupmotd
fi

countcpus

nano_highlight

yumlog_check

}