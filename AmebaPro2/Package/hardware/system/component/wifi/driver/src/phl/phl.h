#ifndef _PHL_H_
#define _PHL_H_

void rtw_phl_init_stainfo(_adapter *padapter, struct sta_info *psta);
void rtw_phl_deinit_stainfo(_adapter *padapter, struct sta_info *psta);
int rtw_phl_com_init(_adapter *padapter);
void rtw_phl_com_deinit(_adapter *padapter);

#ifdef USE_HALBB_HALRF/*ax ic : AmebaSmart, AmebaLite*/
void rtw_phl_final_cap_decision(_adapter *padapter);
void rtw_phl_rx_count(struct rtw_stats *stats,  u8 is_bcmc, int size);
void rtw_phl_tx_count(struct rtw_stats *stats,  u8 is_bcmc, int size);
void rtw_phl_traffic_statistics(struct rtw_stats *stats);
void rtw_phl_set_edcca_mode(_adapter *padapter);
#else/*non-ax ic, not use halbb and halrf, don't need the functions below*/
#define rtw_phl_final_cap_decision(padapter)
#define rtw_phl_rx_count(stats, is_bcmc, size)
#define rtw_phl_tx_count(stats, is_bcmc, size)
#define rtw_phl_traffic_statistics(stats)
#define rtw_phl_set_edcca_mode(padapter)
#endif/*USE_HALBB_HALRF*/

#endif