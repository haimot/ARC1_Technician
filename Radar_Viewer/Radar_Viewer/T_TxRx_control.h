#ifndef T_TXRX_CONTROL_H
#define T_TXRX_CONTROL_H

#include <stdint.h>
//-----------------------------------------
//		T_TxRx_control
//-----------------------------------------
typedef struct T_TxRx_control
{
	uint32_t         	Profile_AD9910A;
	uint32_t            Profile_AD9910B;
	uint32_t            chip_length_AD9910A;
	uint32_t            chip_length_AD9910B;
	uint32_t            IF_SELECT_TX1;
	uint32_t            IF_SELECT_TX2;
	uint32_t            IF_SELECT_TX3;
	uint32_t            IF_SELECT_PROBE;
	uint32_t            IO_UPDATE_rate;
	uint32_t            TX1_ON;
	uint32_t            TX2_ON;
	uint32_t            TX3_ON;
	uint32_t            PROBE_ON;
	uint32_t            TX_LO_TR;
	uint32_t            ANT_SAMPLE_SELECT;
	uint32_t            ATTN_TX1;
	uint32_t            ATTN_TX2;
	uint32_t            ATTN_TX3;
	uint32_t            ATTN_RX1;
	uint32_t            ATTN_RX2;
	uint32_t            ATTN_RX3;
	uint32_t            ATTN_RX4;
	uint32_t            AD9910_Set_aux_dac_A;
	uint32_t            AD9910_Set_aux_dac_B;
	uint32_t            Buffer_length;
	uint32_t            FIFO_length;
	uint32_t            IO_UPDATE_ON;
} T_TxRx_control;
#endif