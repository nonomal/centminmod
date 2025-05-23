# Centmin Mod User Guide: centmin.sh Menu Option 21

This guide provides an overview of centmin.sh menu option 21 in Centmin Mod, which focuses on data management tasks. You'll learn about the available menu and submenu options, as well as their functionalities. The underlying `backups.sh` script used has its own documentation [here](https://github.com/centminmod/centminmod/blob/140.00beta01/datamanagement/backups.sh.md). If you appreciate the work and effort, please consider [supporting Centmin Mod](https://community.centminmod.com/threads/ways-to-support-centmin-mod.11435/). Shorten url to [PayPal donation link](https://centminmod.com/donate/).

**Getting Started**

If it's first time using centmin.sh menu option 21, you'd want to at least do the following:

1. In CSF Firewall on both source and destination Centmin Mod servers, whitelist allow their IP addresses i.e. `csf -a remoteip_address` on source server and on destination server `csf -a sourcedata_ip_address`.
2. centmin.sh menu option 21, submenu option 1 `Manage SSH keys` select [3. Create New SSH Key For Remote Host](#3-create-new-ssh-key-for-remote-host). This will give you the ability to transfer data remotely in unattended manner. 
   **Tip:** ensure remote server supports root user SSH with a password for this process for initial SSH key setup. Otherise if you're using an existing SSH key, you'd be prompted for the SSH private key path during the process.
3. centmin.sh menu option 21, submenu option 2 `Manage AWS CLI S3 Profile Credentials` select [3. Create New AWS CLI S3 Profile](#3-create-new-aws-cli-s3-profile). This will give you the ability to transfer data to your S3 compatible provider.

Then if you are concerned with migrating all Centmin Mod data to a new server, centmin.sh menu option 21, submenu option 3 for [Migrate Centmin Mod Data To New Centmin Mod Server](#submenu-option-3-migrate-centmin-mod-data-to-new-centmin-mod-server) would be the one where it's essentially same as [Submenu Option 4: Backup Nginx Vhosts Data + MariaBackup MySQL Backups](#submenu-option-4-backup-nginx-vhosts-data--mariabackup-mysql-backups) just with auto transfer part. As such restoration is the same.

Migrations aren't finalised until you change domain's DNS records, so you can do test migrations on test remote servers until you're comfortable with the final move.

## Table of Contents

- [Menu Option 21: Data Management](#menu-option-21-data-management)
  - [Submenu Option 1: Manage SSH Keys](#submenu-option-1-manage-ssh-keys)
    - [1. List Registered SSH Keys](#1-list-registered-ssh-keys)
    - [2. Register Existing SSH Keys](#2-register-existing-ssh-keys)
    - [3. Create New SSH Key For Remote Host](#3-create-new-ssh-key-for-remote-host)
    - [4. Use Existing SSH Key For Remote Host](#4-use-existing-ssh-key-for-remote-host)
    - [5. Rotate Existing SSH Key For Remote Host](#5-rotate-existing-ssh-key-for-remote-host)
    - [6. Delete Existing SSH Key For Remote Host](#6-delete-existing-ssh-key-for-remote-host)
    - [7. Export Existing SSH Key](#7-export-existing-ssh-key)
    - [8. Backup All Existing SSH Keys](#8-backup-all-existing-ssh-keys)
    - [9. Back to Main Menu](#9-back-to-main-menu)
  - [Submenu Option 2: Manage AWS CLI S3 Profile Credentials](#submenu-option-2-manage-aws-cli-s3-profile-credentials)
    - [1. List Registered AWS CLI S3 Profiles](#1-list-registered-aws-cli-s3-profiles)
    - [2. List AWS CLI S3 Profile Configuration](#2-list-aws-cli-s3-profile-configuration)
    - [3. Create New AWS CLI S3 Profile](#3-create-new-aws-cli-s3-profile)
    - [4. Edit Existing AWS CLI S3 Profile](#4-edit-existing-aws-cli-s3-profile)
    - [5. Delete Existing AWS CLI S3 Profile](#5-delete-existing-aws-cli-s3-profile)
    - [6. Export Existing AWS CLI S3 Profile](#6-export-existing-aws-cli-s3-profile)
    - [7. Backup All Existing AWS CLI S3 Profiles](#7-backup-all-existing-aws-cli-s3-profiles)
    - [8. Back to Main Menu](#8-back-to-main-menu)
  - [Submenu Option 3: Migrate Centmin Mod Data To New Centmin Mod Server](#submenu-option-3-migrate-centmin-mod-data-to-new-centmin-mod-server)
    * [Submenu Option 3 Command Line:](#submenu-option-3-command-line)
  - [Submenu Option 4: Backup Nginx Vhosts Data + MariaBackup MySQL Backups](#submenu-option-4-backup-nginx-vhosts-data--mariabackup-mysql-backups)
    * [Submenu Option 4 Command Line:](#submenu-option-4-command-line)
  - [Submenu Option 5: Backup Nginx Vhosts Data Only](#submenu-option-5-backup-nginx-vhosts-data-only)
    * [Submenu Option 5 Command Line:](#submenu-option-5-command-line)
  - [Submenu Option 6: Backup MariaDB MySQL With MariaBackup Only](#submenu-option-6-backup-mariadb-mysql-with-mariabackup-only)
    * [Submenu Option 6 Command Line:](#submenu-option-6-command-line)
  - [Submenu Option 7: Backup MariaDB MySQL With mysqldump Only](#submenu-option-7-backup-mariadb-mysql-with-mysqldump-only)
    * [Submenu Option 7 Command Line:](#submenu-option-7-command-line)
  - [Submenu Option 8: Transfer Directory Data To Remote Server Via SSH](#submenu-option-8-transfer-directory-data-to-remote-server-via-ssh)
    * [Submenu Option 8 Command Line:](#submenu-option-8-command-line)
  - [Submenu Option 9: Transfer Directory Data To S3 Compatible Storage](#submenu-option-9-transfer-directory-data-to-s3-compatible-storage)
    * [Submenu Option 9 Command Line:](#submenu-option-9-command-line)
  - [Submenu Option 10: Transfer Files To S3 Compatible Storage](#submenu-option-10-transfer-files-to-s3-compatible-storage)
    * [Submenu Option 10 Command Line:](#submenu-option-10-command-line)
  - [Submenu Option 11: Download S3 Compatible Stored Data To Server](#submenu-option-11-download-s3-compatible-stored-data-to-server)
    * [Submenu Option 11 Command Line:](#submenu-option-11-command-line)
  - [Submenu Option 12: S3 To S3 Compatible Storage Transfers](#submenu-option-12-s3-to-s3-compatible-storage-transfers)
    * [Submenu Option 12 Command Line:](#submenu-option-12-command-line)
  - [Submenu Option 13: List S3 Storage Buckets](#submenu-option-13-list-s3-storage-buckets)
    * [Submenu Option 13 Command Line:](#submenu-option-13-command-line)
  - [Submenu Option 14: Back to Main Menu](#submenu-option-14-back-to-main-menu)


## Menu Option 21: Data Management

When you select option 21 from the main Centmin Mod menu, you will access the `datamanager_menu` function. 

```bash
--------------------------------------------------------
     Centmin Mod Data Management        
--------------------------------------------------------
1).   Manage SSH Keys
2).   Manage AWS CLI S3 Profile Credentials
3).   Migrate Centmin Mod Data To New Centmin Mod Server
4).   Backup Nginx Vhosts Data + MariaBackup MySQL Backups
5).   Backup Nginx Vhosts Data Only (no MariaDB MySQL backups)
6).   Backup MariaDB MySQL With MariaBackup Only (no Vhosts Data backups)
7).   Backup MariaDB MySQL With mysqldump only (no Vhosts Data backups)
8).   Transfer Directory Data To Remote Server Via SSH
9).   Transfer Directory Data To S3 Compatible Storage
10).  Transfer Files To S3 Compatible Storage
11).  Download S3 Compatible Stored Data To Server
12).  S3 To S3 Compatible Storage Transfers
13).  List S3 Storage Buckets
14).  Back to Main menu
--------------------------------------------------------
Enter option [ 1 - 14 ] 
--------------------------------------------------------
```

This submenu provides various options related to data management, such as:

### Submenu Option 1: Manage SSH Keys


```bash
--------------------------------------------------------
     Manage SSH Keys        
--------------------------------------------------------
1).   List Registered SSH Keys
2).   Register Existing SSH Keys
3).   Create New SSH Key For Remote Host
4).   Use Existing SSH Key For Remote Host
5).   Rotate Existing SSH Key For Remote Host
6).   Delete Existing SSH Key For Remote Host
7).   Export Existing SSH Key
8).   Backup All Existing SSH Keys
9).   Back to Main menu
--------------------------------------------------------
Enter option [ 1 - 9 ] 
--------------------------------------------------------
```

This option allows you to manage SSH keys for remote hosts. The available actions include:

1. List Registered SSH Keys
2. Register Existing SSH Keys
3. Create New SSH Key For Remote Host
4. Use Existing SSH Key For Remote Host
5. Rotate Existing SSH Key For Remote Host
6. Delete Existing SSH Key For Remote Host
7. Export Existing SSH Key
8. Backup All Existing SSH Keys
9. Back to Main Menu

#### 1. List Registered SSH Keys
This option lists all registered SSH keys on your system. There are no prompts for this option.

#### 2. Register Existing SSH Keys
This option allows you to register an existing SSH key with a remote host. You will be prompted for the following information:
- Private key path: Enter the full path to the private key file that you want to register.
- Public key path: Enter the full path to the public key file that you want to register.

#### 3. Create New SSH Key For Remote Host
This option creates a new SSH key and registers it with the specified remote host. You will be prompted for the following information:
- Key type (rsa, ecdsa, ed25519): Enter the key type you want to generate. The default is `ed25519`.
- Remote IP address: Enter the IP address of the remote host you want to register the SSH key with.
- Remote SSH port: Enter the SSH port number of the remote host.
- Remote SSH username: Enter the username for the remote host.
- Key comment (unique identifier): Enter a unique comment or identifier for the key.
- Remote SSH password (optional, leave empty for manual password entry): Enter the remote host's SSH password, or leave it empty to enter the password manually when prompted.

#### 4. Use Existing SSH Key For Remote Host
This option allows you to use an existing SSH key for a specified remote host. You will be prompted for the following information:
- Private key path: Enter the full path to the private key file that you want to use.
- Remote IP address: Enter the IP address of the remote host you want to connect with the SSH key.
- Remote SSH port: Enter the SSH port number of the remote host.
- Remote SSH username: Enter the username for the remote host.

#### 5. Rotate Existing SSH Key For Remote Host
This option replaces the existing SSH key for the specified remote host with a newly generated one. You will be prompted for the following information:
- Key type (rsa, ecdsa, ed25519): Enter the key type you want to generate for the new key. The default is `ed25519`.
- Remote IP address: Enter the IP address of the remote host you want to update the SSH key for.
- Remote SSH port: Enter the SSH port number of the remote host.
- Remote SSH username: Enter the username for the remote host.
- Key comment (unique identifier): Enter a unique comment or identifier for the new key.
- Remote SSH password (optional, leave empty for manual password entry): Enter the remote host's SSH password, or leave it empty to enter the password manually when prompted.

#### 6. Delete Existing SSH Key For Remote Host
This option deletes an existing SSH key for the specified remote host. You will be prompted for the following information:
- Remote IP address: Enter the IP address of the remote host you want to delete the SSH key for.
- Remote SSH port: Enter the SSH port number of the remote host.
- Remote SSH username: Enter the username for the remote host.
- Optional private key path for SSH `-i` option: Enter the full path to the private key file that you want to use for the SSH `-i` option, or leave it empty if you don't want to use this option.

#### 7. Export Existing SSH Key
This option exports an existing SSH key to a specified file. You will be prompted for the following information:
- Key name: Enter the unique identifier or comment of the SSH key you want to export.
- Destination path: Enter the full path to the file where you want to export the SSH key.

#### 8. Backup All Existing SSH Keys
This option creates a backup of all existing SSH keys on your system. You will be prompted for the following information:
- Destination path for SSH keys backup: Enter the full path to the directory where you want to save the backup of all your existing SSH keys. The directory will be created if it does not exist.

#### 9. Back to Main Menu
This option takes you back to the main Data Management menu.

### Submenu Option 2: Manage AWS CLI S3 Profile Credentials

This option allows you to manage AWS CLI S3 profile credentials. 

```bash
--------------------------------------------------------
     Manage AWS CLI S3 Profile Credentials        
--------------------------------------------------------
1).   List Registered AWS CLI S3 Profiles
2).   List AWS CLI S3 Profile Configuration
3).   Create New AWS CLI S3 Profile
4).   Edit Existing AWS CLI S3 Profile
5).   Delete Existing AWS CLI S3 Profile
6).   Export Existing AWS CLI S3 Profile
7).   Backup All Existing AWS CLI S3 Profiles
8).   Back to Main menu
--------------------------------------------------------
Enter option [ 1 - 8 ] 
--------------------------------------------------------
```

The available actions include:

1. List Registered AWS CLI S3 Profiles
2. List AWS CLI S3 Profile Configuration
3. Create New AWS CLI S3 Profile
4. Edit Existing AWS CLI S3 Profile
5. Delete Existing AWS CLI S3 Profile
6. Export Existing AWS CLI S3 Profile
7. Backup All Existing AWS CLI S3 Profiles
8. Back to Main Menu

#### 1. List Registered AWS CLI S3 Profiles
This option lists all registered AWS CLI S3 profiles on your system. It will display the names of all available profiles that have been configured with the `aws configure` command.

#### 2. List AWS CLI S3 Profile Configuration
This option displays the configuration details of a specified AWS CLI S3 profile. You will be prompted to enter the profile name, and then the script will display the Access Key, Secret Key, Default Region, and Default Output format associated with that profile.

#### 3. Create New AWS CLI S3 Profile
This option allows you to create a new AWS CLI S3 profile by providing the necessary information, such as S3 storage provider, profile name, endpoint URL, Access Key, Secret Key, Default Region, and Default Output format. The script will guide you through the process, and once the details are confirmed, the new profile will be created.

#### 4. Edit Existing AWS CLI S3 Profile
This option allows you to edit the configuration of an existing AWS CLI S3 profile. You will be prompted to enter the profile name, and the script will display the current configuration settings for that profile. You can then choose a configuration option to edit, such as max concurrent requests, multipart threshold, multipart chunk size, max bandwidth, etc., and provide a new value for that setting.

#### 5. Delete Existing AWS CLI S3 Profile
This option enables you to delete an existing AWS CLI S3 profile. You will be prompted to enter the profile name to delete, and after confirming the details, the script will remove the profile from the configuration and credentials files.

#### 6. Export Existing AWS CLI S3 Profile
This option allows you to export an existing AWS CLI S3 profile to separate configuration and credentials files. You will be prompted to enter the profile name to export, and after confirming the details, the script will create two files containing the exported profile configuration and credentials.

#### 7. Backup All Existing AWS CLI S3 Profiles
This option enables you to create a backup of all existing AWS CLI S3 profiles on your system. The script will copy the configuration and credentials files to a specified backup directory, allowing you to restore the profiles later if needed.

#### 8. Back to Main Menu
This option takes you back to the main Data Management menu.

### Submenu Option 3: Migrate Centmin Mod Data To New Centmin Mod Server

When using the "Migrate Centmin Mod Data To New Centmin Mod Server" option, you'll be prompted to enter the following information - ideally using MariaBackup (option 1) is recommended:

1. Confirmation to continue with the migration process.
2. Backup method choice: 
   - Backup Nginx Vhosts Data + MariaBackup MySQL Backups (option 1) - only choose this method if both old and new servers run the same MariaDB MySQL server major version i.e. 10.3 or 10.4 or 10.6 on both servers. If one server is on an older version, I'd upgrade that major version to match the newer major version.
   - Backup Nginx Vhosts Data + Backup MariaDB MySQL With mysqldump (option 2) - this method more suited if you MariaDB MySQL server major versions differ where new server has a newer major version i.e. old server uses MariaDB 10.3 and new server uses MariaDB 10.4 or 10.6.
3. If you chose option 1:
   - Confirmation to continue with the chosen backup method.
   - Option to use tar + zstd compression for the backup.
4. If you chose option 2:
   - Confirmation to continue with the chosen backup method.
   - Option to use tar + zstd compression for the backup.
5. Option to transfer the backup directory to a remote server via SSH.
6. If you choose to transfer the backup directory to a remote server via SSH, you'll need to provide the following information:
   - Confirmation to continue with the transfer.
   - Remote server SSH port (default: 22).
   - Remote server SSH username (default: root).
   - Remote server SSH hostname/IP address.
   - Tunnel method (nc or socat, default: nc).
   - Buffer size for socat (in bytes, e.g., 131072 for 128 KB).
   - Listen port for nc or socat (default: 12345).
   - Source backup directory (default: the directory from the backup process).
   - Remote (destination) backup directory.
   - Path to the SSH private key.

After entering the required information, you'll be asked to confirm the details before proceeding with the migration process. If you choose MariaBackup (option 1), the restore process will be same as [Submenu Option 4: Backup Nginx Vhosts Data + MariaBackup MySQL Backups](#submenu-option-4-backup-nginx-vhosts-data--mariabackup-mysql-backups) after you have transferred the backup to the new Centmin Mod installed server running EL8+ or higher OS.

#### Submenu Option 3 Command Line:

You can also initiate the option at SSH command line which would consist of multiple commands where `/root/.ssh/my1.key` is your SSH private key setup to connect to your remote server:

With tar + zstd compression:

```
# backup Nginx vhost data + MariaBackup MySQL data
{ /usr/local/src/centminmod/datamanagement/backups.sh backup-all-mariabackup comp } 2>&1 | tee backup-all.log

# inspect backup-all.log to get the backup directory location $transfer_backup_dir
script_output=$(cat backup-all.log)
transfer_backup_dir=$(echo "$script_output" | grep 'Backup Log saved: ' | awk '{print $10}' | xargs dirname)

# transfer $transfer_backup_dir backup directory to remote server via SSH with root@123.123.123.123 user
# port 22 using netcat (nc) listening on port 12334 using zstd compressed tunnel with 262144 byte size
# transfer buffer to remote server's /home/remotebackup directory using SSH private key /root/.ssh/my1.key
/usr/local/src/centminmod/datamanagement/tunnel-transfers.sh -p 22 -u root -h 123.123.123.123 -m nc -b 262144 -l 12345 -s ${transfer_backup_dir} -r /home/remotebackup -k /root/.ssh/my1.key
```

If you choose MariaBackup (option 1), the restore process will be same as [Submenu Option 4: Backup Nginx Vhosts Data + MariaBackup MySQL Backups](#submenu-option-4-backup-nginx-vhosts-data--mariabackup-mysql-backups) after you have transferred the backup to the new Centmin Mod installed server running EL8+ or higher OS.

### Submenu Option 4: Backup Nginx Vhosts Data + MariaBackup MySQL Backups

- This option allows you to create a backup of both Nginx Vhosts data and MariaDB MySQL data using MariaBackup.
- Tar + zstd compression is optional. If you choose not to use tar + zstd, the local backup directories will have uncompressed data backups.
- When prompted with "Do you want to continue [y/n]:", enter "y" to proceed with the backup or "n" to abort the process.
- If you choose to continue, you will be asked, "Do you want tar + zstd compress backup [y/n]:". Enter "y" to create a tar + zstd compressed backup or "n" for an uncompressed backup.
- After making your selection, the backup process will commence, and the progress will be logged in the specified log file.

For example, the resulting `/home/databackup/070523-072252/centminmod_backup.tar.zst` backup file contains:

1. Nginx Vhosts data, which includes:
   - Nginx configuration files
   - Web root directories for each domain
   - Any additional related files or directories
2. MariaDB MySQL data backed up using MariaBackup
   - All the database files and related information required to restore the databases

To restore the data from the backup, follow these steps:

1. Transfer the backup file to the server where you want to restore the data from. Below instructions restore to staging directory at `/home/restoredata`
2. Extract the contents of the backup file


If you have tar version 1.31 or higher, it has native zstd compression support, and extract the backup using these 2 commands. Centmin Mod 130.00beta01's centmin.sh menu option 21, will automatically install a custom built tar 1.35 version YUM RPM binary at `/usr/local/bin/tar` to not conflict with system installed `/usr/bin/tar` and the custom tar 1.35 binary will take priority over system tar if called just as `tar`.

Change path to `/home/databackup/070523-072252/centminmod_backup.tar.zst` where you saved or transfered the backup to i.e. `/home/remotebackup/centminmod_backup.tar.zst`.

   ```
   mkdir -p /home/restoredata
   tar -I zstd -xf /home/databackup/070523-072252/centminmod_backup.tar.zst -C /home/restoredata
   ```
or

   ```
   mkdir -p /home/restoredata
   tar -I zstd -xf /home/remotebackup/centminmod_backup.tar.zst -C /home/restoredata
   ```

If you have tar version lower than 1.31, you will have to extract the tar zstd compressed backup first.

   ```
   mkdir -p /home/restoredata
   zstd -d /home/databackup/070523-072252/centminmod_backup.tar.zst
   tar -xf /home/databackup/070523-072252/centminmod_backup.tar -C /home/restoredata
   ```

or

   ```
   mkdir -p /home/restoredata
   zstd -d /home/remotebackup/centminmod_backup.tar.zst
   tar -xf /home/remotebackup/centminmod_backup.tar -C /home/restoredata
   ```

Custom tar 1.35

```
tar --version
tar (GNU tar) 1.35
Copyright (C) 2023 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Written by John Gilmore and Jay Fenlason.
```

3. Follow the instructions in the `mariabackup-restore.sh` script located in the extracted backup directory (e.g., `/home/databackup/070523-072252/mariadb_tmp/mariabackup-restore.sh`) to restore the MariaDB MySQL databases.

When you extract the backup `centminmod_backup.tar.zst` file to `/home/restoredata`, you'll find backup directories and files which correspond with the relative directory paths to root `/` for `/etc`, `/home`, `/root` and `/usr` respectively.

```
ls -lAh /home/restoredata/
total 16K
drwxr-xr-x 3 root root 4.0K May  7 07:33 etc
drwxr-xr-x 3 root root 4.0K May  7 07:33 home
drwxr-xr-x 3 root root 4.0K May  7 07:33 root
drwxr-xr-x 3 root root 4.0K May  7 07:33 usr
```

An breakdown of backup directory structure 6 directory levels max deep with the files hidden for easier visual view. Where:

1. `/home/restoredata/etc/centminmod` is the backup data for `/etc/centminmod`
2. `/home/restoredata/etc/pure-ftpd` is for /etc/pure-ftpd virtual FTP user database files
3. `/home/restoredata/home/databackup/070523-072252/domains_tmp` is the backup data for `/home/nginx/domains` for Nginx vhost directories
4. `/home/restoredata/home/databackup/070523-072252/mariadb_tmp` is the backup data for `/var/lib/mysql` MySQL data directory which also contains the MariaBackup MySQL data restore script at `/home/restoredata/home/databackup/070523-072252/mariadb_tmp/mariabackup-restore.sh`
5. `/home/restoredata/root/tools` is the backup data for `/root/tools`
6. `/home/restoredata/usr/local/nginx/` is the backup data for `/usr/local/nginx`

```
tree -d -L 6 /home/restoredata/

/home/restoredata/
├── etc
│   ├── centminmod
│   │   ├── cronjobs
│   │   ├── csf
│   │   └── php.d
│   └── pure-ftpd
├── home
│   └── databackup
│       └── 070523-072252
│           ├── domains_tmp
│           │   ├── demodomain.com
│           │   │   ├── backup
│           │   │   ├── log
│           │   │   ├── private
│           │   │   └── public
│           │   ├── domain.com
│           │   │   ├── backup
│           │   │   ├── log
│           │   │   ├── private
│           │   │   └── public
│           │   ├── log4j.domain.com
│           │   │   ├── backup
│           │   │   ├── log
│           │   │   ├── private
│           │   │   └── public
│           │   ├── domain2.com
│           │   │   ├── backup
│           │   │   ├── cronjobs
│           │   │   ├── log
│           │   │   ├── private
│           │   │   ├── public
│           │   │   └── sucuri_data_storage
│           │   └── domain3.com
│           │       ├── backup
│           │       ├── log
│           │       ├── private
│           │       └── public
│           └── mariadb_tmp
│               ├── mysql
│               ├── performance_schema
│               ├── sakila
│               └── wp3233312196db_24171
├── root
│   └── tools
│       ├── acme.sh
│       │   ├── deploy
│       │   ├── dnsapi
│       │   └── notify
│       ├── awscli
│       │   └── aws
│       │       └── dist
│       │           ├── awscli
│       │           ├── cryptography
│       │           ├── docutils
│       │           └── lib-dynload
│       └── keygen
└── usr
    └── local
        └── nginx
            ├── conf
            │   ├── acmevhostbackup
            │   ├── autoprotect
            │   │   ├── demodomain.com
            │   │   ├── domain.com
            │   │   ├── log4j.domain.com
            │   │   ├── domain2.com
            │   │   └── domain3.com
            │   ├── conf.d
            │   ├── phpfpmd
            │   ├── ssl
            │   │   ├── cloudflare
            │   │   ├── log4j.domain.com
            │   │   ├── domain2.com
            │   │   └── domain3.com
            │   └── wpincludes
            │       └── domain2.com
            └── html

78 directories
```

Then proceed to move the restored files to the correct locations. You can first use `diff` command to check backup versus destination directory files. Not all directories may exist as it's dependent on whether you have installed the software i.e. Redis and KeyDB.

```
diff -ur /etc/centminmod /home/restoredata/etc/centminmod/
diff -ur /etc/pure-ftpd /home/restoredata/etc/pure-ftpd
diff -ur /etc/redis /home/restoredata/etc/redis
diff -ur /etc/keydb /home/restoredata/etc/keydb
diff -ur /root/.acme.sh /home/restoredata/root/.acme.sh/
diff -ur /root/tools /home/restoredata/root/tools/
diff -ur /usr/local/nginx /home/restoredata/usr/local/nginx/
diff -ur /root/.my.cnf /home/restoredata/root/.my.cnf
diff -ur /var/spool/cron/root /home/remotebackup/cronjobs_tmp/root_cronjobs
```

If Elasticsearch is installed on both old and new server, centmin.sh menu option 21 backup script will backup /etc/elasticsearch as a copy located at /etc/elasticsearch-source so that restoration doesn't override, new server Elasticsearch instance. But you'd have /home/restoredata/etc/elasticsearch-source to reference old server's Elasticsearch settings.

diff -ur /etc/elasticsearch /home/restoredata/etc/elasticsearch-source

Example where `/etc/centminmod/diff.txt` file exists only on destination side

```
diff -ur /home/restoredata/etc/centminmod/ /etc/centminmod
Only in /etc/centminmod: diff.txt
```

Then copy command will force override any existing files on destination directory side and ensure to backup new destination server's files for future reference for `/etc/centminmod/custom_config.inc` and `/etc/centminmod/php.d/a_customphp.ini` and `/etc/my.cnf` and `/etc/centminmod/php.d/zendopcache.ini` and `/usr/local/nginx` and `/usr/local/nginx/conf/staticfiles.conf` files/directory as you may want to use the new server's version of these files or directories for server settings instead of using old server's transferred settings.

```
\cp -af /usr/local/nginx/conf/staticfiles.conf /usr/local/nginx/conf/staticfiles.conf.original
\cp -af /usr/local/nginx /usr/local/nginx_original
\cp -af /etc/my.cnf /etc/my.cnf.original
\cp -af /root/.my.cnf /root/.my.cnf.original
\cp -af /etc/centminmod/custom_config.inc /etc/centminmod/custom_config.inc.original
\cp -af /etc/centminmod/php.d/a_customphp.ini /etc/centminmod/php.d/a_customphp.ini.original
\cp -af /etc/centminmod/php.d/zendopcache.ini /etc/centminmod/php.d/zendopcache.ini.original
\cp -af /home/restoredata/etc/centminmod/* /etc/centminmod/
\cp -af /home/restoredata/etc/pure-ftpd/* /etc/pure-ftpd/
\cp -af /home/restoredata/etc/redis/* /etc/redis/
\cp -af /home/restoredata/etc/keydb/* /etc/keydb/
mkdir -p /root/.acme.sh
\cp -af /home/restoredata/root/.acme.sh/* /root/.acme.sh/
\cp -af /home/restoredata/root/tools/* /root/tools/
\cp -af /home/restoredata/usr/local/nginx/* /usr/local/nginx/
```

For Nginx vhost data where backup directory timestamp = `070523-072252`

```
\cp -af /home/restoredata/home/databackup/070523-072252/domains_tmp/* /home/nginx/domains/
```

Or if disk space is a concern, instead of copy command use move commands

```
\cp -af /usr/local/nginx/conf/staticfiles.conf /usr/local/nginx/conf/staticfiles.conf.original
\cp -af /usr/local/nginx /usr/local/nginx_original
\cp -af /etc/my.cnf /etc/my.cnf.original
\cp -af /root/.my.cnf /root/.my.cnf.original
\cp -af /etc/centminmod/custom_config.inc /etc/centminmod/custom_config.inc.original
\cp -af /etc/centminmod/php.d/a_customphp.ini /etc/centminmod/php.d/a_customphp.ini.original
\cp -af /etc/centminmod/php.d/zendopcache.ini /etc/centminmod/php.d/zendopcache.ini.original
mv -f /home/restoredata/etc/centminmod/* /etc/centminmod/
mv -f /home/restoredata/etc/pure-ftpd/* /etc/pure-ftpd/
mv -f /home/restoredata/etc/redis/* /etc/redis/
mv -f /home/restoredata/etc/keydb/* /etc/keydb/
mkdir -p /root/.acme.sh
mv -f /home/restoredata/root/.acme.sh/* /root/.acme.sh/
mv -f /home/restoredata/root/tools/* /root/tools/
mv -f /home/restoredata/usr/local/nginx/* /usr/local/nginx/
```

For Nginx vhost data where backup directory timestamp = `070523-072252`

```
mv -f /home/restoredata/home/databackup/070523-072252/domains_tmp/* /home/nginx/domains/
```

Check overwritten files

```
diff -ur /etc/centminmod/custom_config.inc.original /etc/centminmod/custom_config.inc
diff -ur /usr/local/nginx_original/conf/conf.d/virtual.conf /usr/local/nginx/conf/conf.d/virtual.conf
diff -ur /usr/local/nginx_original/conf/nginx.conf /usr/local/nginx/conf/nginx.conf
diff -ur /etc/redis/redis.conf.original /etc/redis/redis.conf
diff -ur /etc/keydb/keydb.conf.original /etc/keydb/keydb.conf
```

If no changes to virtual.conf and nginx.conf use new server one

```
\cp -af /usr/local/nginx_original/conf/nginx.conf /usr/local/nginx/conf/nginx.conf
\cp -af /usr/local/nginx_original/conf/conf.d/virtual.conf /usr/local/nginx/conf/conf.d/virtual.conf
diff -ur /usr/local/nginx_original/conf/nginx.conf /usr/local/nginx/conf/nginx.conf
diff -ur /usr/local/nginx_original/conf/conf.d/virtual.conf /usr/local/nginx/conf/conf.d/virtual.conf
\cp -af /etc/redis/redis.conf.original /etc/redis/redis.conf
\cp -af /etc/keydb/keydb.conf.original /etc/keydb/keydb.conf
diff -ur /etc/redis/redis.conf.original /etc/redis/redis.conf
diff -ur /etc/keydb/keydb.conf.original /etc/keydb/keydb.conf
```

Restore cronjobs

```
crontab -l > /etc/centminmod/cronjobs/cronjoblist-restore-from-migration.txt
cat /etc/centminmod/cronjobs/cronjoblist-restore-from-migration.txt
crontab /home/remotebackup/cronjobs_tmp/root_cronjobs
```

The `/home/restoredata/home/databackup/070523-072252/mariadb_tmp/mariabackup-restore.sh` script has 2 options to restore MariaDB MySQL data either via `copy-back` or `move-back`. 

1. `copy-back`: This option copies the backup files back to the original data directory at `/var/lib/mysql`. The backup files themselves are not altered or removed. The script checks if the provided backup directory is valid and if the backup and current MariaDB versions match. If everything is fine, it proceeds with copying the backup files back to the original data directory at `/var/lib/mysql`.
2. `move-back`: This option moves the backup files back to the original data directory at `/var/lib/mysql`. Unlike `copy-back`, the backup files are removed from the backup directory. The script checks if the provided backup directory is valid and if the backup and current MariaDB versions match. If everything is fine, it proceeds with moving the backup files back to the original data directory at `/var/lib/mysql`.

Both options involve the following steps:

* The script first checks if the provided directory contains valid MariaBackup data.
* It then compares the MariaDB version used for the backup with the version running on the current system. The script aborts the restore process if the versions do not match.
* The MariaDB server is stopped, and the existing data directory is backed up to `/var/lib/mysql-copy-datetimestamp` and then `/var/lib/mysql` data directory is emptied.
* The ownership of the data directory is changed to `mysql:mysql`.
* The MariaDB server is started.
* Depending on the option chosen (`copy-back` or `move-back`), the script copies or moves the backup files back to the original data directory.

`mariabackup-restore.sh` Usage help output:

```
./mariabackup-restore.sh
Usage: ./mariabackup-restore.sh [copy-back|move-back] /path/to/backup/dir/
```

Actual command where backup directory timestamp = `070523-072252`

```
time /home/restoredata/home/databackup/070523-072252/mariadb_tmp/mariabackup-restore.sh copy-back /home/restoredata/home/databackup/070523-072252/mariadb_tmp/
```

Then restore `/root/.my.cnf`

```
\cp -af /home/restoredata/root/.my.cnf /root/.my.cnf
```

**Note:** Make sure to adjust the paths in the commands above to match the actual location of your backup files.

#### Submenu Option 4 Command Line:

You can also initiate the option at SSH command line:

With tar + zstd compression:

```
/usr/local/src/centminmod/datamanagement/backups.sh backup-all-mariabackup comp
```

Tar without zstd compression:

```
/usr/local/src/centminmod/datamanagement/backups.sh backup-all-mariabackup
```

### Submenu Option 5: Backup Nginx Vhosts Data Only

- This option allows you to create a backup of Nginx Vhosts data only, without including any MariaDB MySQL data.
- Tar + zstd compression is optional. If you choose not to use tar + zstd, the local backup directories will have uncompressed data backups.
- When prompted with "Do you want to continue [y/n]:", enter "y" to proceed with the backup or "n" to abort the process.
- If you choose to continue, you will be asked, "Do you want tar + zstd compress backup [y/n]:". Enter "y" to create a tar + zstd compressed backup or "n" for an uncompressed backup.
- After making your selection, the backup process will commence, and the progress will be logged in the specified log file.

#### Submenu Option 5 Command Line:

You can also initiate the option at SSH command line:

```
/usr/local/src/centminmod/datamanagement/backups.sh backup-files
```

### Submenu Option 6: Backup MariaDB MySQL With MariaBackup Only

This option allows you to create a backup of MariaDB MySQL databases using the MariaBackup tool without including any Nginx Vhosts data backups. MariaBackup is used for all MySQL databases and MySQL system database backups, which contain your MySQL users' permissions.

The MariaBackup backup directory can either be uncompressed or tar + zstd compressed.

When prompted with "Do you want to continue [y/n]:", enter "y" to proceed with the backup or "n" to abort the process. If you choose to continue, you will be asked, "Do you want tar + zstd compress backup [y/n]:". Enter "y" to create a tar + zstd compressed backup or "n" for an uncompressed backup.

After making your selection, the backup process will commence, and the progress will be logged in the specified log file.

#### Submenu Option 6 Command Line:

You can also initiate the option at SSH command line:

```
/usr/local/src/centminmod/datamanagement/backups.sh backup-mariabackup
```

### Submenu Option 7: Backup MariaDB MySQL With mysqldump Only

This option allows you to create a backup of MariaDB MySQL databases using mysqldump without including any Nginx Vhosts data backups. The backup process uses the faster `--tab` delimited backup option, which creates separate `.sql` schema structure files and `.txt` data files for each MySQL database table, instead of a single `.sql` file containing both schema and data.

The `.sql` database schema-only table files are not compressed, while the `.txt` data files can be optionally compressed using zstd or left uncompressed.

During the backup, a `restore.sh` script is generated in the destination backup directory, which can be run to restore each database or all databases on a new server. If the database name already exists on the server, the restore process will create a new database with a suffix `_restorecopy_datetimestamp` to prevent overwriting the existing database.

When prompted with "Do you want to continue [y/n]:", enter "y" to proceed with the backup or "n" to abort the process.

#### Submenu Option 7 Command Line:

You can also initiate the option at SSH command line:

```
/usr/local/src/centminmod/datamanagement/backups.sh backup-all
```

### Submenu Option 8: Transfer Directory Data To Remote Server Via SSH

This option enables you to transfer directory data from your current server to a remote server via SSH. The following information will be required:

1. Remote server SSH port (default: 22): Enter the SSH port number for the remote server. If not specified, the default value is 22.
2. Remote server SSH username (default: root): Enter the SSH username for the remote server. If not specified, the default value is 'root'.
3. Remote server SSH hostname/IP address: Enter the hostname or IP address of the remote server.
4. Tunnel method (nc or socat, default: nc): Choose the tunnel method for data transfer. You can select between 'nc' (netcat) or 'socat'. If not specified, the default value is 'nc'.
5. Buffer size for socat (in bytes, e.g., 131072 for 128 KB): If using 'socat' as the tunnel method, specify the buffer size in bytes. For example, if you want to set the buffer size to 128 KB, enter 131072.
6. Listen port for nc or socat (default: 12345): Specify the listen port for the chosen tunnel method (nc or socat). If not specified, the default value is 12345.
7. Source backup directory: Enter the full path to the source directory you want to transfer from your current server.
8. Remote (destination) backup directory: Enter the full path to the destination directory on the remote server where you want the data to be transferred.
9. Path to the SSH private key: Provide the path to the SSH private key that will be used for authentication.

After entering the information, you will be asked to confirm the entered details. If the information is correct, the script will proceed with the data transfer. If not, you will be prompted to re-enter the information.

For example if you used `centmin.sh` menu `option 21` submenu `option 4` to create a Nginx vhost data + MariaBackup backup file at `/home/databackup/070523-072252/centminmod_backup.tar.zst`. You can transfer the directory contents for `/home/databackup/070523-072252` to a remote server's `/home/remotebackup` directory via SSH.

```
--------------------------------------------------------
     Centmin Mod Data Management        
--------------------------------------------------------
1).   Manage SSH Keys
2).   Manage AWS CLI S3 Profile Credentials
3).   Migrate Centmin Mod Data To New Centmin Mod Server
4).   Backup Nginx Vhosts Data + MariaBackup MySQL Backups
5).   Backup Nginx Vhosts Data Only (no MariaDB MySQL backups)
6).   Backup MariaDB MySQL With MariaBackup Only (no Vhosts Data backups)
7).   Backup MariaDB MySQL With mysqldump only (no Vhosts Data backups)
8).   Transfer Directory Data To Remote Server Via SSH
9).   Transfer Directory Data To S3 Compatible Storage
10).  Transfer Files To S3 Compatible Storage
11).  Download S3 Compatible Stored Data To Server
12).  S3 To S3 Compatible Storage Transfers
13).  List S3 Storage Buckets
14).  Back to Main menu
--------------------------------------------------------
Enter option [ 1 - 14 ] 8
--------------------------------------------------------
```
```
Transfer Directory Data To Remote Server Via SSH

Description:
Option allows you to specify a full path to directory name for data transfer
to a remote server via SSH at speeds near network and disk line rates using
either netcat (nc) or socat compressed tunnel using zstd fast compression levels

Do you want to continue [y/n]: y
Remote server SSH port (default: 22): 22
Remote server SSH username (default: root): root
Remote server SSH hostname/IP address: 123.123.123.123
Tunnel method (nc or socat, default: nc): nc
Buffer size for socat (in bytes, e.g., 131072 for 128 KB): 262144
Listen port for nc or socat (default: 12345): 12345
Source backup directory: /home/databackup/070523-072252
Remote (destination) backup directory: /home/remotebackup
Path to the SSH private key: /root/.ssh/my1.key

Please confirm the entered information:
Remote server SSH port: 22
Remote server SSH username: root
Remote server SSH hostname/IP address: 123.123.123.123
Tunnel method: nc
Buffer size: 262144
Listen port: 12345
Source backup directory: /home/databackup/070523-072252
Remote (destination) backup directory: /home/remotebackup
Path to the SSH private key: /root/.ssh/my1.key

Is the information correct? [y/n]: y
/usr/local/src/centminmod/datamanagement/tunnel-transfers.sh -p 22 -u root -h 123.123.123.123 -m nc -b 262144 -l 12345 -s /home/databackup/070523-072252 -r /home/remotebackup -k /root/.ssh/my1.key
 245MiB 0:00:00 [ 345MiB/s] [=================================================================>] 100%            
Transfer completed successfully in 1 seconds.
```

Contents of remote server's `/home/remotebackup/` directory

```
ls -lAh /home/remotebackup/
-rw-r--r-- 1 root root 245M May  7 07:23 /home/remotebackup/centminmod_backup.tar.zst
-rw-r--r-- 1 root root 1.6M May  7 07:23 /home/remotebackup/files-backup_070523-072252.log
```

To extract the contents of the backup file:

If you have tar version 1.31 or higher, it has native zstd compression support, and extract the backup using these 2 commands. Centmin Mod 130.00beta01's centmin.sh menu option 21, will automatically install a custom built tar 1.35 version YUM RPM binary at `/usr/local/bin/tar` to not conflict with system installed `/usr/bin/tar` and the custom tar 1.35 binary will take priority over system tar if called just as `tar`.

Change path to `/home/databackup/070523-072252/centminmod_backup.tar.zst` where you saved or transfered the backup to i.e. `/home/remotebackup/centminmod_backup.tar.zst`.

   ```
   mkdir -p /home/restoredata
   tar -I zstd -xf /home/databackup/070523-072252/centminmod_backup.tar.zst -C /home/restoredata
   ```
or

   ```
   mkdir -p /home/restoredata
   tar -I zstd -xf /home/remotebackup/centminmod_backup.tar.zst -C /home/restoredata
   ```

If you have tar version lower than 1.31, you will have to extract the tar zstd compressed backup first.

   ```
   mkdir -p /home/restoredata
   zstd -d /home/databackup/070523-072252/centminmod_backup.tar.zst
   tar -xf /home/databackup/070523-072252/centminmod_backup.tar -C /home/restoredata
   ```

or

   ```
   mkdir -p /home/restoredata
   zstd -d /home/remotebackup/centminmod_backup.tar.zst
   tar -xf /home/remotebackup/centminmod_backup.tar -C /home/restoredata
   ```

Custom tar 1.35

```
tar --version
tar (GNU tar) 1.35
Copyright (C) 2023 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Written by John Gilmore and Jay Fenlason.
```

When you extract the backup `centminmod_backup.tar.zst` file to `/home/restoredata`, you'll find backup directories and files which correspond with the relative directory paths to root `/` for `/etc`, `/home`, `/root` and `/usr` respectively.

```
ls -lAh /home/restoredata/
total 16K
drwxr-xr-x 3 root root 4.0K May  7 07:33 etc
drwxr-xr-x 3 root root 4.0K May  7 07:33 home
drwxr-xr-x 3 root root 4.0K May  7 07:33 root
drwxr-xr-x 3 root root 4.0K May  7 07:33 usr
```

An breakdown of backup directory structure 6 directory levels max deep with the files hidden for easier visual view. Where:

1. `/home/restoredata/etc/centminmod` is the backup data for `/etc/centminmod`
2. `/home/restoredata/etc/pure-ftpd` is for /etc/pure-ftpd virtual FTP user database files
3. `/home/restoredata/home/databackup/070523-072252/domains_tmp` is the backup data for `/home/nginx/domains` for Nginx vhost directories
4. `/home/restoredata/home/databackup/070523-072252/mariadb_tmp` is the backup data for `/var/lib/mysql` MySQL data directory which also contains the MariaBackup MySQL data restore script at `/home/restoredata/home/databackup/070523-072252/mariadb_tmp/mariabackup-restore.sh`
5. `/home/restoredata/root/tools` is the backup data for `/root/tools`
6. `/home/restoredata/usr/local/nginx/` is the backup data for `/usr/local/nginx`

```
tree -d -L 6 /home/restoredata/

/home/restoredata/
├── etc
│   ├── centminmod
│   │   ├── cronjobs
│   │   ├── csf
│   │   └── php.d
│   └── pure-ftpd
├── home
│   └── databackup
│       └── 070523-072252
│           ├── domains_tmp
│           │   ├── demodomain.com
│           │   │   ├── backup
│           │   │   ├── log
│           │   │   ├── private
│           │   │   └── public
│           │   ├── domain.com
│           │   │   ├── backup
│           │   │   ├── log
│           │   │   ├── private
│           │   │   └── public
│           │   ├── log4j.domain.com
│           │   │   ├── backup
│           │   │   ├── log
│           │   │   ├── private
│           │   │   └── public
│           │   ├── domain2.com
│           │   │   ├── backup
│           │   │   ├── cronjobs
│           │   │   ├── log
│           │   │   ├── private
│           │   │   ├── public
│           │   │   └── sucuri_data_storage
│           │   └── domain3.com
│           │       ├── backup
│           │       ├── log
│           │       ├── private
│           │       └── public
│           └── mariadb_tmp
│               ├── mysql
│               ├── performance_schema
│               ├── sakila
│               └── wp3233312196db_24171
├── root
│   └── tools
│       ├── acme.sh
│       │   ├── deploy
│       │   ├── dnsapi
│       │   └── notify
│       ├── awscli
│       │   └── aws
│       │       └── dist
│       │           ├── awscli
│       │           ├── cryptography
│       │           ├── docutils
│       │           └── lib-dynload
│       └── keygen
└── usr
    └── local
        └── nginx
            ├── conf
            │   ├── acmevhostbackup
            │   ├── autoprotect
            │   │   ├── demodomain.com
            │   │   ├── domain.com
            │   │   ├── log4j.domain.com
            │   │   ├── domain2.com
            │   │   └── domain3.com
            │   ├── conf.d
            │   ├── phpfpmd
            │   ├── ssl
            │   │   ├── cloudflare
            │   │   ├── log4j.domain.com
            │   │   ├── domain2.com
            │   │   └── domain3.com
            │   └── wpincludes
            │       └── domain2.com
            └── html

78 directories
```

Then proceed to move the restored files to the correct locations. You can first use `diff` command to check backup versus destination directory files. Not all directories may exist as it's dependent on whether you have installed the software i.e. Redis and KeyDB.

```
diff -ur /etc/centminmod /home/restoredata/etc/centminmod/
diff -ur /etc/pure-ftpd /home/restoredata/etc/pure-ftpd
diff -ur /etc/redis /home/restoredata/etc/redis
diff -ur /etc/keydb /home/restoredata/etc/keydb
diff -ur /root/.acme.sh /home/restoredata/root/.acme.sh/
diff -ur /root/tools /home/restoredata/root/tools/
diff -ur /usr/local/nginx /home/restoredata/usr/local/nginx/
diff -ur /root/.my.cnf /home/restoredata/root/.my.cnf
diff -ur /var/spool/cron/root /home/remotebackup/cronjobs_tmp/root_cronjobs
```

If Elasticsearch is installed on both old and new server, centmin.sh menu option 21 backup script will backup /etc/elasticsearch as a copy located at /etc/elasticsearch-source so that restoration doesn't override, new server Elasticsearch instance. But you'd have /home/restoredata/etc/elasticsearch-source to reference old server's Elasticsearch settings.

diff -ur /etc/elasticsearch /home/restoredata/etc/elasticsearch-source

Example where `/etc/centminmod/diff.txt` file exists only on destination side

```
diff -ur /home/restoredata/etc/centminmod/ /etc/centminmod
Only in /etc/centminmod: diff.txt
```

Then copy command will force override any existing files on destination directory side and ensure to backup new destination server's files for future reference for `/etc/centminmod/custom_config.inc` and `/etc/centminmod/php.d/a_customphp.ini` and `/etc/my.cnf` and `/etc/centminmod/php.d/zendopcache.ini` and `/usr/local/nginx` and `/usr/local/nginx/conf/staticfiles.conf` files/directory as you may want to use the new server's version of these files or directories for server settings instead of using old server's transferred settings.

```
\cp -af /usr/local/nginx/conf/staticfiles.conf /usr/local/nginx/conf/staticfiles.conf.original
\cp -af /usr/local/nginx /usr/local/nginx_original
\cp -af /etc/my.cnf /etc/my.cnf.original
\cp -af /root/.my.cnf /root/.my.cnf.original
\cp -af /etc/redis/redis.conf /etc/redis/redis.conf.original
\cp -af /etc/keydb/keydb.conf /etc/keydb/keydb.conf.original
\cp -af /etc/centminmod/custom_config.inc /etc/centminmod/custom_config.inc.original
\cp -af /etc/centminmod/php.d/a_customphp.ini /etc/centminmod/php.d/a_customphp.ini.original
\cp -af /etc/centminmod/php.d/zendopcache.ini /etc/centminmod/php.d/zendopcache.ini.original
\cp -af /home/restoredata/etc/centminmod/* /etc/centminmod/
\cp -af /home/restoredata/etc/pure-ftpd/* /etc/pure-ftpd/
\cp -af /home/restoredata/etc/redis/* /etc/redis/
\cp -af /home/restoredata/etc/keydb/* /etc/keydb/
\cp -af /home/restoredata/root/.acme.sh/* /root/.acme.sh/
\cp -af /home/restoredata/root/tools/* /root/tools/
\cp -af /home/restoredata/usr/local/nginx/* /usr/local/nginx/
```

For Nginx vhost data where backup directory timestamp = `070523-072252`

```
\cp -af /home/restoredata/home/databackup/070523-072252/domains_tmp/* /home/nginx/domains/
```

Or if disk space is a concern, instead of copy command use move commands

```
\cp -af /usr/local/nginx/conf/staticfiles.conf /usr/local/nginx/conf/staticfiles.conf.original
\cp -af /usr/local/nginx /usr/local/nginx_original
\cp -af /etc/my.cnf /etc/my.cnf.original
\cp -af /root/.my.cnf /root/.my.cnf.original
\cp -af /etc/redis/redis.conf /etc/redis/redis.conf.original
\cp -af /etc/keydb/keydb.conf /etc/keydb/keydb.conf.original
\cp -af /etc/centminmod/custom_config.inc /etc/centminmod/custom_config.inc.original
\cp -af /etc/centminmod/php.d/a_customphp.ini /etc/centminmod/php.d/a_customphp.ini.original
\cp -af /etc/centminmod/php.d/zendopcache.ini /etc/centminmod/php.d/zendopcache.ini.original
mv -f /home/restoredata/etc/centminmod/* /etc/centminmod/
mv -f /home/restoredata/etc/pure-ftpd/* /etc/pure-ftpd/
mv -f /home/restoredata/etc/redis/* /etc/redis/
mv -f /home/restoredata/etc/keydb/* /etc/keydb/
mv -f /home/restoredata/root/.acme.sh/* /root/.acme.sh/
mv -f /home/restoredata/root/tools/* /root/tools/
mv -f /home/restoredata/usr/local/nginx/* /usr/local/nginx/
```

For Nginx vhost data where backup directory timestamp = `070523-072252`

```
mv -f /home/restoredata/home/databackup/070523-072252/domains_tmp/* /home/nginx/domains/
```

Check overwritten files

```
diff -ur /etc/centminmod/custom_config.inc.original /etc/centminmod/custom_config.inc
diff -ur /usr/local/nginx_original/conf/conf.d/virtual.conf /usr/local/nginx/conf/conf.d/virtual.conf
diff -ur /usr/local/nginx_original/conf/nginx.conf /usr/local/nginx/conf/nginx.conf
diff -ur /etc/redis/redis.conf.original /etc/redis/redis.conf
diff -ur /etc/keydb/keydb.conf.original /etc/keydb/keydb.conf
```

If no changes to virtual.conf and nginx.conf use new server one

```
\cp -af /usr/local/nginx_original/conf/nginx.conf /usr/local/nginx/conf/nginx.conf
\cp -af /usr/local/nginx_original/conf/conf.d/virtual.conf /usr/local/nginx/conf/conf.d/virtual.conf
diff -ur /usr/local/nginx_original/conf/nginx.conf /usr/local/nginx/conf/nginx.conf
diff -ur /usr/local/nginx_original/conf/conf.d/virtual.conf /usr/local/nginx/conf/conf.d/virtual.conf
\cp -af /etc/redis/redis.conf.original /etc/redis/redis.conf
\cp -af /etc/keydb/keydb.conf.original /etc/keydb/keydb.conf
diff -ur /etc/redis/redis.conf.original /etc/redis/redis.conf
diff -ur /etc/keydb/keydb.conf.original /etc/keydb/keydb.conf
```

Restore cronjobs

```
crontab -l > /etc/centminmod/cronjobs/cronjoblist-restore-from-migration.txt
cat /etc/centminmod/cronjobs/cronjoblist-restore-from-migration.txt
crontab /home/remotebackup/cronjobs_tmp/root_cronjobs
```

The `/home/restoredata/home/databackup/070523-072252/mariadb_tmp/mariabackup-restore.sh` script has 2 options to restore MariaDB MySQL data either via `copy-back` or `move-back`. 

1. `copy-back`: This option copies the backup files back to the original data directory at `/var/lib/mysql`. The backup files themselves are not altered or removed. The script checks if the provided backup directory is valid and if the backup and current MariaDB versions match. If everything is fine, it proceeds with copying the backup files back to the original data directory at `/var/lib/mysql`.
2. `move-back`: This option moves the backup files back to the original data directory at `/var/lib/mysql`. Unlike `copy-back`, the backup files are removed from the backup directory. The script checks if the provided backup directory is valid and if the backup and current MariaDB versions match. If everything is fine, it proceeds with moving the backup files back to the original data directory at `/var/lib/mysql`.

Both options involve the following steps:

* The script first checks if the provided directory contains valid MariaBackup data.
* It then compares the MariaDB version used for the backup with the version running on the current system. The script aborts the restore process if the versions do not match.
* The MariaDB server is stopped, and the existing data directory is backed up to `/var/lib/mysql-copy-datetimestamp` and then `/var/lib/mysql` data directory is emptied.
* The ownership of the data directory is changed to `mysql:mysql`.
* The MariaDB server is started.
* Depending on the option chosen (`copy-back` or `move-back`), the script copies or moves the backup files back to the original data directory.

`mariabackup-restore.sh` Usage help output:

```
./mariabackup-restore.sh
Usage: ./mariabackup-restore.sh [copy-back|move-back] /path/to/backup/dir
```

Actual command where backup directory timestamp = `070523-072252`

```
time /home/restoredata/home/databackup/070523-072252/mariadb_tmp/mariabackup-restore.sh copy-back /home/restoredata/home/databackup/070523-072252/mariadb_tmp
```

Then restore `/root/.my.cnf`

```
\cp -af /home/restoredata/root/.my.cnf /root/.my.cnf
```

**Note:** Make sure to adjust the paths in the commands above to match the actual location of your backup files.

#### Submenu Option 8 Command Line:

You can also use equivalent SSH command line below based on above input prompt values where `/root/.ssh/my1.key` is your SSH private key setup to connect to your remote server:

```
/usr/local/src/centminmod/datamanagement/tunnel-transfers.sh -p 22 -u root -h 123.123.123.123 -m nc -b 262144 -l 12345 -s /home/databackup/070523-072252 -r /home/remotebackup -k /root/.ssh/my1.key
```

### Submenu Option 9: Transfer Directory Data To S3 Compatible Storage

This option allows you to transfer directory data from your current server to S3 compatible storage. The following information will be required:

1. AWS CLI profile name: Enter the AWS CLI profile name that you have configured with the necessary access keys and secret keys. You may have already created a AWS CLI tool profile name manually via `aws` cli client or via `centmin.sh` menu `option 21` submenu `option 2` options.
2. S3 bucket name: Enter the name of the S3 bucket to which you want to transfer the data.
3. S3 endpoint URL: Provide the endpoint URL of the S3 compatible storage provider (e.g., Amazon S3, Cloudflare R2, Backblaze, DigitalOcean, Vultr, Linode).
4. Source directory path: Enter the full path to the source directory you want to transfer from your current server.

After entering the information, you will be asked to confirm the entered details. If the information is correct, the script will proceed with the data transfer. If not, you will be prompted to re-enter the information.

For example if you used `centmin.sh` menu `option 21` submenu `option 4` to create a Nginx vhost data + MariaBackup backup file at `/home/databackup/070523-072252/centminmod_backup.tar.zst`. You can transfer the directory contents for `/home/databackup/070523-072252` to Cloudflare R2 S3 bucket named `BUCKETNAME`

```
--------------------------------------------------------
     Centmin Mod Data Management        
--------------------------------------------------------
1).   Manage SSH Keys
2).   Manage AWS CLI S3 Profile Credentials
3).   Migrate Centmin Mod Data To New Centmin Mod Server
4).   Backup Nginx Vhosts Data + MariaBackup MySQL Backups
5).   Backup Nginx Vhosts Data Only (no MariaDB MySQL backups)
6).   Backup MariaDB MySQL With MariaBackup Only (no Vhosts Data backups)
7).   Backup MariaDB MySQL With mysqldump only (no Vhosts Data backups)
8).   Transfer Directory Data To Remote Server Via SSH
9).   Transfer Directory Data To S3 Compatible Storage
10).  Transfer Files To S3 Compatible Storage
11).  Download S3 Compatible Stored Data To Server
12).  S3 To S3 Compatible Storage Transfers
13).  List S3 Storage Buckets
14).  Back to Main menu
--------------------------------------------------------
Enter option [ 1 - 14 ] 9
--------------------------------------------------------
```
```
Transfer Directory Data To S3 Compatible Storage

Description:
Option allows you to specify a full path to directory name for data transfer
to a S3 compatible storage provider like Amazon S3, Cloudflare R2, Backblaze
DigitalOcean, Vultr, Linode

Do you want to continue [y/n]: y
AWS CLI profile name: r2
S3 bucket name: BUCKETNAME
S3 endpoint URL: https://YOUR_CF_ACCOUNT_ID.r2.cloudflarestorage.com
Source directory path: /home/databackup/070523-072252

Please confirm the entered information:
AWS CLI profile name: r2
S3 bucket name: BUCKETNAME
S3 endpoint URL: https://YOUR_CF_ACCOUNT_ID.r2.cloudflarestorage.com
Source directory path: /home/databackup/070523-072252

Is the information correct? [y/n]: y
aws s3 sync --profile r2 --endpoint-url https://YOUR_CF_ACCOUNT_ID.r2.cloudflarestorage.com /home/databackup/070523-072252 s3://BUCKETNAME/
upload: ../../../../home/databackup/070523-072252/files-backup_070523-072252.log to s3://BUCKETNAME/files-backup_070523-072252.log
upload: ../../../../home/databackup/070523-072252/centminmod_backup.tar.zst to s3://BUCKETNAME/centminmod_backup.tar.zst
```

Contents of Cloudflare R2 S3 bucket named `BUCKETNAME`

```
aws s3 ls --profile r2 --endpoint-url https://YOUR_CF_ACCOUNT_ID.r2.cloudflarestorage.com s3://BUCKETNAME

2023-05-07 11:40:04  256261518 centminmod_backup.tar.zst
2023-05-07 11:39:47    1595586 files-backup_070523-072252.log
```


Linode S3 object storage

```
aws s3 ls --profile linode --endpoint-url=https://us-east-1.linodeobjects.com s3://BUCKETNAME
```

BackBlaze B2 object storage

```
aws s3 ls --profile b2 --endpoint-url=https://s3.us-west-001.backblazeb2.com s3://BUCKETNAME
```

DigitalOcean S3 object storage

```
aws s3 ls --profile do --endpoint-url=https://sfo2.digitaloceanspaces.com s3://BUCKETNAME
```

#### Submenu Option 9 Command Line:

You can also use equivalent SSH command line below based on above input prompt values:


Cloudflare R2 S3:

```
aws s3 sync --profile r2 --endpoint-url https://YOUR_CF_ACCOUNT_ID.r2.cloudflarestorage.com /home/databackup/070523-072252 s3://BUCKETNAME/
```

Linode S3 object storage

```
aws s3 sync --profile linode --endpoint-url=https://us-east-1.linodeobjects.com /home/databackup/070523-072252 s3://BUCKETNAME/
```

BackBlaze B2 object storage

```
aws s3 sync --profile b2 --endpoint-url=https://s3.us-west-001.backblazeb2.com /home/databackup/070523-072252 s3://BUCKETNAME/
```

DigitalOcean S3 object storage

```
aws s3 sync --profile do --endpoint-url=https://sfo2.digitaloceanspaces.com /home/databackup/070523-072252 s3://BUCKETNAME/
```

### Submenu Option 10: Transfer Files To S3 Compatible Storage

This option enables you to transfer individual files from your current server to S3 compatible storage. The following information will be required:

1. AWS CLI profile name: Enter the AWS CLI profile name that you have configured with the necessary access keys and secret keys.
2. S3 bucket name: Enter the name of the S3 bucket to which you want to transfer the files.
3. S3 endpoint URL: Provide the endpoint URL of the S3 compatible storage provider (e.g., Amazon S3, Cloudflare R2, Backblaze, DigitalOcean, Vultr, Linode).
4. File path to transfer: Enter the full path to the file you want to transfer from your current server.
5. (Optional) Additional files to transfer: If you want to transfer more files, answer 'yes' to the prompt and then specify the number of additional files. You will be asked to provide the full paths for each file.

After entering the information, you will be asked to confirm the entered details. If the information is correct, the script will proceed with the data transfer. If not, you will be prompted to re-enter the information.

#### Submenu Option 10 Command Line:

You can also use equivalent SSH command line below based on above input prompt values transferring file `/home/databackup/070523-072252/centminmod_backup.tar.zst` to S3 bucket named `BUCKETNAME`:


Cloudflare R2 S3:

```
aws s3 cp --profile r2 --endpoint-url https://YOUR_CF_ACCOUNT_ID.r2.cloudflarestorage.com /home/databackup/070523-072252/centminmod_backup.tar.zst s3://BUCKETNAME/
```

Linode S3 object storage

```
aws s3 cp --profile linode --endpoint-url=https://us-east-1.linodeobjects.com /home/databackup/070523-072252/centminmod_backup.tar.zst s3://BUCKETNAME/
```

BackBlaze B2 object storage

```
aws s3 cp --profile b2 --endpoint-url=https://s3.us-west-001.backblazeb2.com /home/databackup/070523-072252/centminmod_backup.tar.zst s3://BUCKETNAME/
```

DigitalOcean S3 object storage

```
aws s3 cp --profile do --endpoint-url=https://sfo2.digitaloceanspaces.com /home/databackup/070523-072252/centminmod_backup.tar.zst s3://BUCKETNAME/
```

### Submenu Option 11: Download S3 Compatible Stored Data To Server

This option allows you to download data stored in S3 compatible storage to your current server. The following information will be required:

1. AWS CLI profile name: Enter the AWS CLI profile name that you have configured with the necessary access keys and secret keys.
2. S3 bucket name: Enter the name of the S3 bucket from which you want to download the data.
3. S3 endpoint URL: Provide the endpoint URL of the S3 compatible storage provider (e.g., Amazon S3, Cloudflare R2, Backblaze, DigitalOcean, Vultr, Linode).
4. Remote S3 file path: Enter the remote path of the file in the S3 bucket that you want to download.
5. Local directory to download the file: Enter the local directory path where you want to download the file on your server.

After entering the information, you will be asked to confirm the entered details. If the information is correct, the script will proceed with the data transfer. If not, you will be prompted to re-enter the information.

#### Submenu Option 11 Command Line:

You can also use equivalent SSH command line below based on above input prompt values downloading file to local directory at `/home/localdirectory`:


Cloudflare R2 S3:

```
aws s3 cp --profile r2 --endpoint-url https://YOUR_CF_ACCOUNT_ID.r2.cloudflarestorage.com s3://BUCKETNAME/centminmod_backup.tar.zst" /home/localdirectory
```

Linode S3 object storage

```
aws s3 cp --profile linode --endpoint-url=https://us-east-1.linodeobjects.com s3://BUCKETNAME/centminmod_backup.tar.zst" /home/localdirectory
```

BackBlaze B2 object storage

```
aws s3 cp --profile b2 --endpoint-url=https://s3.us-west-001.backblazeb2.com s3://BUCKETNAME/centminmod_backup.tar.zst" /home/localdirectory
```

DigitalOcean S3 object storage

```
aws s3 cp --profile do --endpoint-url=https://sfo2.digitaloceanspaces.com s3://BUCKETNAME/centminmod_backup.tar.zst" /home/localdirectory
```

### Submenu Option 12: S3 To S3 Compatible Storage Transfers

This option enables you to transfer data between two S3 compatible storage systems. The following information will be required:

1. Source AWS CLI profile name: Enter the source AWS CLI profile name that you have configured with the necessary access keys and secret keys.
2. Source S3 bucket name: Enter the name of the source S3 bucket from which you want to transfer the data.
3. Source S3 endpoint URL: Provide the endpoint URL of the source S3 compatible storage provider (e.g., Amazon S3, Cloudflare R2, Backblaze, DigitalOcean, Vultr, Linode).
4. Source S3 object path: Enter the path of the object in the source S3 bucket that you want to transfer.
5. Destination AWS CLI profile name: Enter the destination AWS CLI profile name that you have configured with the necessary access keys and secret keys.
6. Destination S3 bucket name: Enter the name of the destination S3 bucket where you want to transfer the data.
7. Destination S3 endpoint URL: Provide the endpoint URL of the destination S3 compatible storage provider (e.g., Amazon S3, Cloudflare R2, Backblaze, DigitalOcean, Vultr, Linode).
8. Destination S3 object path: Enter the path where you want to store the object in the destination S3 bucket.

After entering the information, you will be asked to confirm the entered details. If the information is correct, the script will proceed with the data transfer. If not, you will be prompted to re-enter the information.

#### Submenu Option 12 Command Line:

You can also use equivalent SSH command line below based on above input prompt values transferring file `centminmod_backup.tar.zst` from `BUCKETNAME1` to `BUCKETNAME2`:


Cloudflare R2 S3:

```
aws s3 cp --profile r2 --endpoint-url https://YOUR_CF_ACCOUNT_ID.r2.cloudflarestorage.com "s3://BUCKETNAME1/centminmod_backup.tar.zst" "s3://BUCKETNAME2/centminmod_backup.tar.zst"
```

Linode S3 object storage

```
aws s3 cp --profile linode --endpoint-url=https://us-east-1.linodeobjects.com "s3://BUCKETNAME1/centminmod_backup.tar.zst" "s3://BUCKETNAME2/centminmod_backup.tar.zst"
```

BackBlaze B2 object storage

```
aws s3 cp --profile b2 --endpoint-url=https://s3.us-west-001.backblazeb2.com "s3://BUCKETNAME1/centminmod_backup.tar.zst" "s3://BUCKETNAME2/centminmod_backup.tar.zst"
```

DigitalOcean S3 object storage

```
aws s3 cp --profile do --endpoint-url=https://sfo2.digitaloceanspaces.com "s3://BUCKETNAME1/centminmod_backup.tar.zst" "s3://BUCKETNAME2/centminmod_backup.tar.zst"
```

### Submenu Option 13: List S3 Storage Buckets

This option allows you to list all your S3 storage buckets registered with the AWS CLI tool. The following information will be required:

To use this option, you will be prompted for the following information:

1. AWS CLI profile name: Enter the AWS CLI profile name that you have configured with the necessary access keys and secret keys.
2. S3 endpoint URL: Provide the endpoint URL of the S3 compatible storage provider (e.g., Amazon S3, Cloudflare R2, Backblaze, DigitalOcean, Vultr, Linode).

After entering the required information, the script will list all your S3 storage buckets registered with the AWS CLI tool.

#### Submenu Option 13 Command Line:

You can also use equivalent SSH command line below based on above input prompt values:

Cloudflare R2 S3

```
aws s3 ls --profile r2 --endpoint-url https://YOUR_CF_ACCOUNT_ID.r2.cloudflarestorage.com
```

Linode S3 object storage

```
aws s3 ls --profile linode --endpoint-url=https://us-east-1.linodeobjects.com
```

BackBlaze B2 object storage

```
aws s3 ls --profile b2 --endpoint-url=https://s3.us-west-001.backblazeb2.com
```

DigitalOcean S3 object storage

```
aws s3 ls --profile do --endpoint-url=https://sfo2.digitaloceanspaces.com
```

### Submenu Option 14: Back to Main Menu

This option returns you to the main Centmin Mod menu.

## Conclusion

Centmin Mod's centmin.sh menu option 21 provides various data management functionalities, such as SSH key management, AWS CLI S3 profile credential management, data migration, backup, and transfer. This guide has detailed each submenu option to help you understand and utilize these features effectively.

If you appreciate the work and effort, please consider [supporting Centmin Mod](https://community.centminmod.com/threads/ways-to-support-centmin-mod.11435/). Shorten url to [PayPal donation link](https://centminmod.com/donate/).