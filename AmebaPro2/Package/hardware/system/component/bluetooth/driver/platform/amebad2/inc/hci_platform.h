/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef _HCI_PLATFORM_H_
#define _HCI_PLATFORM_H_

#include "hci/hci_common.h"
#include "./hci_uart.h"
#include "ameba_soc.h"
#include "wifi_conf.h"

//#define hci_platform_START_IQK
//#define hci_platform_WRITE_IQK

#define HCI_DEFAULT_LMP_SUBVER   0x8730

void hci_platform_get_baudrate(uint8_t *baudrate, uint8_t len);
void hci_platform_cfg_bd_addr(uint8_t *bdaddr);
void hci_platform_record_chipid(uint8_t chipid);
void hci_platform_dl_patch_done(void);
uint8_t hci_platform_set_baudrate(void);
uint8_t hci_platform_dl_patch_init(void);
uint8_t hci_platform_get_patch_cmd_len(uint8_t *cmd_len);
uint8_t hci_platform_get_patch_cmd_buf(uint8_t *cmd_buf, uint8_t cmd_len);

uint8_t hci_platform_init(void);
uint8_t hci_platform_deinit(void);

void hci_platform_bt_log_init(void);
void hci_platform_bt_log_deinit(void);
void hci_platform_bt_fw_log_open(void);
void hci_platform_bt_fw_log_close(void);
void hci_platform_bt_trace_log_open(void);
void hci_platform_bt_trace_log_close(void);
#endif