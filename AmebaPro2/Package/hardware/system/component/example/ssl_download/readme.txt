SSL DOWNLOAD EXAMPLE

Description:
Download file from Web server via https.

Configuration:
Modify SERVER_HOST, SERVER_PORT and RESOURCE in example_ssl_download.c based on your SSL server.

Modify SSL_MAX_CONTENT_LEN in SSL config and configTOTAL_HEAP_SIZE in freertos config for large size file.
	If the transmitted fils size is larger than 16kbytes, SSL_MAX_CONTENT_LEN should be set to 16384.
	FreeRTOS heap may be increased for ssl buffer allocation.
	(ex. If using 16kbytes * 2 for ssl input/output buffer, heap should be increased from 60kbytes to 80kbytes.)
[config_rsa.h]
	#define SSL_MAX_CONTENT_LEN            16384
[FreeRTOSConfig.h]
	#define configTOTAL_HEAP_SIZE          ( ( size_t ) ( 80 * 1024 ) )

[platform_opts.h]
	#define CONFIG_EXAMPLE_SSL_DOWNLOAD    1
	For AmebaD2 :Amebad2 Changes how example is compiled, and Removed macro controls (CONFIG_EXAMPLE_XXX)in platform_opts.h
		GCC:use CMD "make xip EXAMPLE=ssl_download" to compile ssl_download example.

Execution:
Can make automatical Wi-Fi connection when booting by using wlan fast connect example.
A ssl download example thread will be started automatically when booting.

[Supported List]
	Supported :
	    Ameba-1, Ameba-z, Ameba-z2, AmebaD, AmebaD2
	Source code not in project:
	    Ameba-pro