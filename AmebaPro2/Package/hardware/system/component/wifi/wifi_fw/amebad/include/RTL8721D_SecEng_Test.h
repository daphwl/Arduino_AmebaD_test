#ifndef __RTL8192F_SEC_ENG_TEST_H__
#define __RTL8192F_SEC_ENG_TEST_H__

#ifndef __ASSEMBLY__

#define GTK_DEBUG_HMAC_SHA1_VERIFY 1
#define GTK_DEBUG_AES_UNWRAP_VERIFY 2
#define GTK_DEBUG_HMAC_MD5_VERIFY 3
#define GTK_DEBUG_TKIP_MIC_VERIFY 4
#define GTK_DEBUG_RC4_VERIFY   5
#define GTK_DEBUG_AES_128_ENC_VERIFY 6
#define GTK_DEBUG_AES_128_DEC_VERIFY 7
#define GTK_DEBUG_11W_VERIFY 8
#define GTK_DEBUG_INFO 9
#define GTK_DEBUG_SET_TXBUFFER_ADDR 10
#define GTK_DEBUG_SET_MODE 11

extern void
SecEngTest(
	IN u8 *argv[]
);
#endif

#endif      //#ifndef __RTL8192F_SEC_ENG_TEST_H__

