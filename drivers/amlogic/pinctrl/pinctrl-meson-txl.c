/*
 * drivers/amlogic/pinctrl/pinctrl-meson-txl.c
 *
 * Copyright (C) 2017 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 */

#include "pinctrl-meson.h"
#include <linux/arm-smccc.h>
#include <dt-bindings/gpio/meson-txl-gpio.h>
#include "pinctrl-meson8-pmx.h"

static const struct pinctrl_pin_desc meson_txl_periphs_pins[] = {
	MESON_PIN(GPIOZ_0),
	MESON_PIN(GPIOZ_1),
	MESON_PIN(GPIOZ_2),
	MESON_PIN(GPIOZ_3),
	MESON_PIN(GPIOZ_4),
	MESON_PIN(GPIOZ_5),
	MESON_PIN(GPIOZ_6),
	MESON_PIN(GPIOZ_7),
	MESON_PIN(GPIOZ_8),
	MESON_PIN(GPIOZ_9),
	MESON_PIN(GPIOZ_10),
	MESON_PIN(GPIOZ_11),
	MESON_PIN(GPIOZ_12),
	MESON_PIN(GPIOZ_13),
	MESON_PIN(GPIOZ_14),
	MESON_PIN(GPIOZ_15),
	MESON_PIN(GPIOZ_16),
	MESON_PIN(GPIOZ_17),
	MESON_PIN(GPIOZ_18),
	MESON_PIN(GPIOZ_19),
	MESON_PIN(GPIOZ_20),
	MESON_PIN(GPIOZ_21),
	MESON_PIN(GPIOH_0),
	MESON_PIN(GPIOH_1),
	MESON_PIN(GPIOH_2),
	MESON_PIN(GPIOH_3),
	MESON_PIN(GPIOH_4),
	MESON_PIN(GPIOH_5),
	MESON_PIN(GPIOH_6),
	MESON_PIN(GPIOH_7),
	MESON_PIN(GPIOH_8),
	MESON_PIN(GPIOH_9),
	MESON_PIN(BOOT_0),
	MESON_PIN(BOOT_1),
	MESON_PIN(BOOT_2),
	MESON_PIN(BOOT_3),
	MESON_PIN(BOOT_4),
	MESON_PIN(BOOT_5),
	MESON_PIN(BOOT_6),
	MESON_PIN(BOOT_7),
	MESON_PIN(BOOT_8),
	MESON_PIN(BOOT_9),
	MESON_PIN(BOOT_10),
	MESON_PIN(BOOT_11),
	MESON_PIN(CARD_0),
	MESON_PIN(CARD_1),
	MESON_PIN(CARD_2),
	MESON_PIN(CARD_3),
	MESON_PIN(CARD_4),
	MESON_PIN(CARD_5),
	MESON_PIN(CARD_6),
	MESON_PIN(GPIODV_0),
	MESON_PIN(GPIODV_1),
	MESON_PIN(GPIODV_2),
	MESON_PIN(GPIODV_3),
	MESON_PIN(GPIODV_4),
	MESON_PIN(GPIODV_5),
	MESON_PIN(GPIODV_6),
	MESON_PIN(GPIODV_7),
	MESON_PIN(GPIODV_8),
	MESON_PIN(GPIODV_9),
	MESON_PIN(GPIODV_10),
	MESON_PIN(GPIODV_11),
	MESON_PIN(GPIOW_0),
	MESON_PIN(GPIOW_1),
	MESON_PIN(GPIOW_2),
	MESON_PIN(GPIOW_3),
	MESON_PIN(GPIOW_4),
	MESON_PIN(GPIOW_5),
	MESON_PIN(GPIOW_6),
	MESON_PIN(GPIOW_7),
	MESON_PIN(GPIOW_8),
	MESON_PIN(GPIOW_9),
	MESON_PIN(GPIOW_10),
	MESON_PIN(GPIOW_11),
	MESON_PIN(GPIOW_12),
	MESON_PIN(GPIOW_13),
	MESON_PIN(GPIOW_14),
	MESON_PIN(GPIOW_15),
	MESON_PIN(GPIOCLK_0),
	MESON_PIN(GPIOCLK_1),
};

/* emmc & nand */
static const unsigned int emmc_nand_d07_pins[] = {
	BOOT_0, BOOT_1, BOOT_2,
	BOOT_3, BOOT_4, BOOT_5,
	BOOT_6, BOOT_7,
};

/* emmc */
static const unsigned int emmc_clk_pins[] = { BOOT_8 };
static const unsigned int emmc_cmd_pins[] = { BOOT_10 };
static const unsigned int emmc_ds_pins[] = { BOOT_11 };

/* nor */
static const unsigned int nor_d_pins[] = { BOOT_4 };
static const unsigned int nor_q_pins[] = { BOOT_5 };
static const unsigned int nor_c_pins[] = { BOOT_6 };
static const unsigned int nor_cs_pins[] = { BOOT_11 };

/* sacard */
static const unsigned int sdcard_d1_pins[] = { CARD_0 };
static const unsigned int sdcard_d0_pins[] = { CARD_1 };
static const unsigned int sdcard_clk_pins[] = { CARD_2 };
static const unsigned int sdcard_cmd_pins[] = { CARD_3 };
static const unsigned int sdcard_d3_pins[] = { CARD_4 };
static const unsigned int sdcard_d2_pins[] = { CARD_5 };

/* i2c_a */
static const unsigned int i2c0_sda_pins[] = { GPIOZ_9 };
static const unsigned int i2c0_sck_pins[] = { GPIOZ_8 };

/* i2c_b */
static const unsigned int i2c1_sda_pins[] = { GPIODV_0 };
static const unsigned int i2c1_sck_pins[] = { GPIODV_1 };

/* i2c_c */
static const unsigned int i2c2_sda_pins[] = { GPIOH_3 };
static const unsigned int i2c2_sck_pins[] = { GPIOH_2 };

/* i2c_d */
static const unsigned int i2c3_sda_pins[] = { GPIOZ_2 };
static const unsigned int i2c3_sck_pins[] = { GPIOZ_3 };

/* pwm_a */
static const unsigned int pwm_a_dv_pins[] = { GPIODV_2 };
static const unsigned int pwm_a_z_pins[] = { GPIOZ_5 };

/* pwm_b */
static const unsigned int pwm_b_dv_pins[] = { GPIODV_3 };
static const unsigned int pwm_b_z_pins[] = { GPIOZ_6 };

/* pwm_c */
static const unsigned int pwm_c_pins[] = { GPIOZ_7 };

/* pwm_d */
static const unsigned int pwm_d_z4_pins[] = { GPIOZ_4 };
static const unsigned int pwm_d_z19_pins[] = { GPIOZ_19 };

/* pwm_vs */
static const unsigned int pwm_vs_dv2_pins[] = { GPIODV_2 };
static const unsigned int pwm_vs_dv3_pins[] = { GPIODV_3 };
static const unsigned int pwm_vs_z4_pins[] = { GPIOZ_4 };
static const unsigned int pwm_vs_z6_pins[] = { GPIOZ_6 };
static const unsigned int pwm_vs_z7_pins[] = { GPIOZ_7 };
static const unsigned int pwm_vs_z19_pins[] = { GPIOZ_19 };

/* pwm_e */
static const unsigned int pwm_e_h4_pins[] = { GPIOH_4 };
static const unsigned int pwm_e_h8_pins[] = { GPIOH_8 };

/* pwm_f */
static const unsigned int pwm_f_clk_pins[] = { GPIOCLK_1 };
static const unsigned int pwm_f_h_pins[] = { GPIOH_9 };

/* tsin_a */
static const unsigned int tsin_d0_a_pins[] = { GPIODV_7 };
static const unsigned int tsin_clk_a_pins[] = { GPIODV_8 };
static const unsigned int tsin_sop_a_pins[] = { GPIODV_9 };
static const unsigned int tsin_valid_a_pins[] = { GPIODV_10 };
static const unsigned int tsin_fail_a_pins[] = { GPIODV_11 };

static const unsigned int tsin_d1_7_a_pins[] = {
	GPIODV_0, GPIODV_1,
	GPIODV_2, GPIODV_3,
	GPIODV_4, GPIODV_5,
	GPIODV_6,
};

/* tsin_b */
static const unsigned int tsin_clk_b_pins[] = { GPIOH_5 };
static const unsigned int tsin_d0_b_pins[] = { GPIOH_6 };
static const unsigned int tsin_sop_b_pins[] = { GPIOH_7 };
static const unsigned int tsin_valid_b_pins[] = { GPIOH_8 };
static const unsigned int tsin_fail_b_pins[] = { GPIOH_9 };

/* atv */
static const unsigned int atv_if_agc_pins[] = { GPIODV_2 };

/* dtv */
static const unsigned int dtv_if_agc_pins[] = { GPIODV_2 };
static const unsigned int dtv_rf_agc_pins[] = { GPIODV_3 };

/* spi_a */
static const unsigned int spi_miso_a_pins[] = { GPIOZ_1 };
static const unsigned int spi_mosi_a_pins[] = { GPIOZ_0 };
static const unsigned int spi_clk_a_pins[] = { GPIOZ_2 };
static const unsigned int spi_ss0_a_pins[] = { GPIOZ_3 };
static const unsigned int spi_ss1_a_pins[] = { GPIOZ_4 };
static const unsigned int spi_ss2_a_pins[] = { GPIOZ_5 };

/* pcm_a */
static const unsigned int pcm_clk_a_pins[] = { GPIOZ_2 };
static const unsigned int pcm_fs_a_pins[] = { GPIOZ_3 };
static const unsigned int pcm_in_a_pins[] = { GPIOZ_1 };
static const unsigned int pcm_out_a_pins[] = { GPIOZ_0 };

/* uart_a */
static const unsigned int uart_tx_a_pins[] = { GPIODV_8 };
static const unsigned int uart_rx_a_pins[] = { GPIODV_9 };
static const unsigned int uart_cts_a_pins[] = { GPIODV_10 };
static const unsigned int uart_rts_a_pins[] = { GPIODV_11 };

/* uart_b */
static const unsigned int uart_tx_b_pins[] = { GPIOZ_15 };
static const unsigned int uart_rx_b_pins[] = { GPIOZ_16 };
static const unsigned int uart_cts_b_pins[] = { GPIOZ_18 };
static const unsigned int uart_rts_b_pins[] = { GPIOZ_19 };

/*uart_c*/
static const unsigned int uart_tx_c_pins[] = { GPIOZ_0 };
static const unsigned int uart_rx_c_pins[] = { GPIOZ_1 };
static const unsigned int uart_cts_c_pins[] = { GPIOZ_2 };
static const unsigned int uart_rts_c_pins[] = { GPIOZ_3 };

/* uart_ao_a_ee */
static const unsigned int uart_tx_ao_a_c4_pins[] = { CARD_4 };
static const unsigned int uart_rx_ao_a_c5_pins[] = { CARD_5 };

static const unsigned int uart_rx_ao_a_c4_pins[] = { CARD_4 };
static const unsigned int uart_tx_ao_a_c5_pins[] = { CARD_5 };

static const unsigned int uart_tx_ao_a_w2_pins[] = { GPIOW_2 };
static const unsigned int uart_rx_ao_a_w3_pins[] = { GPIOW_3 };

static const unsigned int uart_tx_ao_a_w6_pins[] = { GPIOW_6 };
static const unsigned int uart_rx_ao_a_w7_pins[] = { GPIOW_7 };

static const unsigned int uart_tx_ao_a_w10_pins[] = { GPIOW_10 };
static const unsigned int uart_rx_ao_a_w11_pins[] = { GPIOW_11 };

static const unsigned int uart_tx_ao_a_w14_pins[] = { GPIOW_14 };
static const unsigned int uart_rx_ao_a_w15_pins[] = { GPIOW_15 };

/* spdif_out */
static const unsigned int spdif_out_pins[] = { GPIOZ_17 };

/* spdif_in */
static const unsigned int spdif_in_pins[] = { GPIOZ_16 };

/* hdmirx_a */
static const unsigned int hdmirx_hpd_a_pins[] = { GPIOW_4 };
static const unsigned int hdmirx_det_a_pins[] = { GPIOW_5 };
static const unsigned int hdmirx_sda_a_pins[] = { GPIOW_6 };
static const unsigned int hdmirx_sck_a_pins[] = { GPIOW_7 };

/* hdmirx_b */
static const unsigned int hdmirx_hpd_b_pins[] = { GPIOW_12 };
static const unsigned int hdmirx_det_b_pins[] = { GPIOW_13 };
static const unsigned int hdmirx_sda_b_pins[] = { GPIOW_14 };
static const unsigned int hdmirx_sck_b_pins[] = { GPIOW_15 };

/* hdmirx_c */
static const unsigned int hdmirx_hpd_c_pins[] = { GPIOW_8 };
static const unsigned int hdmirx_det_c_pins[] = { GPIOW_9 };
static const unsigned int hdmirx_sda_c_pins[] = { GPIOW_10 };
static const unsigned int hdmirx_sck_c_pins[] = { GPIOW_11 };

/* hdmirx_d */
static const unsigned int hdmirx_hpd_d_pins[] = { GPIOW_0 };
static const unsigned int hdmirx_det_d_pins[] = { GPIOW_1 };
static const unsigned int hdmirx_sda_d_pins[] = { GPIOW_2 };
static const unsigned int hdmirx_sck_d_pins[] = { GPIOW_3 };

/* i2s */
static const unsigned int i2s_aoclk_out_dv_pins[] = { GPIODV_7 };
static const unsigned int i2s_lrclk_out_dv_pins[] = { GPIODV_8 };
static const unsigned int i2s_aoclk_in_dv_pins[] = { GPIODV_7 };
static const unsigned int i2s_lrclk_in_dv_pins[] = { GPIODV_8 };
static const unsigned int i2s_amclk_dv_pins[] = { GPIODV_9 };
static const unsigned int i2s_out_ch01_dv_pins[] = { GPIODV_6 };
static const unsigned int i2s_in_ch01_dv_pins[] = { GPIODV_10 };

static const unsigned int i2s_aoclk_out_z_pins[] = { GPIOZ_11 };
static const unsigned int i2s_lrclk_out_z_pins[] = { GPIOZ_12 };
static const unsigned int i2s_aoclk_in_z_pins[] = { GPIOZ_11 };
static const unsigned int i2s_lrclk_in_z_pins[] = { GPIOZ_12 };
static const unsigned int i2s_amclk_z_pins[] = { GPIOZ_10 };
static const unsigned int i2s_out_ch01_z_pins[] = { GPIOZ_14 };
static const unsigned int i2s_in_ch01_z_pins[] = { GPIOZ_13 };

static const unsigned int i2s_out_ch23_pins[] = { GPIOZ_15 };
static const unsigned int i2s_out_ch45_pins[] = { GPIOZ_16 };
static const unsigned int i2s_out_ch67_pins[] = { GPIOZ_18 };

/* acodec_i2s */
static const unsigned int a_i2s_amclk_pins[] = { GPIOZ_10 };
static const unsigned int a_i2s_aoclk_in_pins[] = { GPIOZ_11 };
static const unsigned int a_i2s_lrclk_in_pins[] = { GPIOZ_12 };
static const unsigned int a_i2s_in_ch01_pins[] = { GPIOZ_13 };

/* eth */
static const unsigned int eth_link_led_pins[] = { GPIOZ_18 };
static const unsigned int eth_act_led_pins[] = { GPIOZ_19 };

/* vbyone */
static const unsigned int vx1_lockn_pins[] = { GPIOH_0 };
static const unsigned int vx1_htpdn_pins[] = { GPIOH_1 };

static struct meson_pmx_group meson_txl_periphs_groups[] = {
	GPIO_GROUP(GPIOZ_0),
	GPIO_GROUP(GPIOZ_1),
	GPIO_GROUP(GPIOZ_2),
	GPIO_GROUP(GPIOZ_3),
	GPIO_GROUP(GPIOZ_4),
	GPIO_GROUP(GPIOZ_5),
	GPIO_GROUP(GPIOZ_6),
	GPIO_GROUP(GPIOZ_7),
	GPIO_GROUP(GPIOZ_8),
	GPIO_GROUP(GPIOZ_9),
	GPIO_GROUP(GPIOZ_10),
	GPIO_GROUP(GPIOZ_11),
	GPIO_GROUP(GPIOZ_12),
	GPIO_GROUP(GPIOZ_13),
	GPIO_GROUP(GPIOZ_14),
	GPIO_GROUP(GPIOZ_15),
	GPIO_GROUP(GPIOZ_16),
	GPIO_GROUP(GPIOZ_17),
	GPIO_GROUP(GPIOZ_18),
	GPIO_GROUP(GPIOZ_19),
	GPIO_GROUP(GPIOZ_20),
	GPIO_GROUP(GPIOZ_21),
	GPIO_GROUP(GPIOH_0),
	GPIO_GROUP(GPIOH_1),
	GPIO_GROUP(GPIOH_2),
	GPIO_GROUP(GPIOH_3),
	GPIO_GROUP(GPIOH_4),
	GPIO_GROUP(GPIOH_5),
	GPIO_GROUP(GPIOH_6),
	GPIO_GROUP(GPIOH_7),
	GPIO_GROUP(GPIOH_8),
	GPIO_GROUP(GPIOH_9),
	GPIO_GROUP(BOOT_0),
	GPIO_GROUP(BOOT_1),
	GPIO_GROUP(BOOT_2),
	GPIO_GROUP(BOOT_3),
	GPIO_GROUP(BOOT_4),
	GPIO_GROUP(BOOT_5),
	GPIO_GROUP(BOOT_6),
	GPIO_GROUP(BOOT_7),
	GPIO_GROUP(BOOT_8),
	GPIO_GROUP(BOOT_9),
	GPIO_GROUP(BOOT_10),
	GPIO_GROUP(BOOT_11),
	GPIO_GROUP(CARD_0),
	GPIO_GROUP(CARD_1),
	GPIO_GROUP(CARD_2),
	GPIO_GROUP(CARD_3),
	GPIO_GROUP(CARD_4),
	GPIO_GROUP(CARD_5),
	GPIO_GROUP(CARD_6),
	GPIO_GROUP(GPIODV_0),
	GPIO_GROUP(GPIODV_1),
	GPIO_GROUP(GPIODV_2),
	GPIO_GROUP(GPIODV_3),
	GPIO_GROUP(GPIODV_4),
	GPIO_GROUP(GPIODV_5),
	GPIO_GROUP(GPIODV_6),
	GPIO_GROUP(GPIODV_7),
	GPIO_GROUP(GPIODV_8),
	GPIO_GROUP(GPIODV_9),
	GPIO_GROUP(GPIODV_10),
	GPIO_GROUP(GPIODV_11),
	GPIO_GROUP(GPIOW_0),
	GPIO_GROUP(GPIOW_1),
	GPIO_GROUP(GPIOW_2),
	GPIO_GROUP(GPIOW_3),
	GPIO_GROUP(GPIOW_4),
	GPIO_GROUP(GPIOW_5),
	GPIO_GROUP(GPIOW_6),
	GPIO_GROUP(GPIOW_7),
	GPIO_GROUP(GPIOW_8),
	GPIO_GROUP(GPIOW_9),
	GPIO_GROUP(GPIOW_10),
	GPIO_GROUP(GPIOW_11),
	GPIO_GROUP(GPIOW_12),
	GPIO_GROUP(GPIOW_13),
	GPIO_GROUP(GPIOW_14),
	GPIO_GROUP(GPIOW_15),
	GPIO_GROUP(GPIOCLK_0),
	GPIO_GROUP(GPIOCLK_1),

	/* Bank DV */
	GROUP(i2c1_sda,		2,	25),
	GROUP(i2c1_sck,		2,	24),
	GROUP(pwm_a_dv,		2,	20),
	GROUP(pwm_b_dv,		2,	18),
	GROUP(pwm_vs_dv2,	2,	19),
	GROUP(pwm_vs_dv3,	2,	17),
	GROUP(tsin_d0_a,	2,	30),
	GROUP(tsin_clk_a,	2,	29),
	GROUP(tsin_sop_a,	2,	28),
	GROUP(tsin_valid_a,	2,	27),
	GROUP(tsin_fail_a,	2,	26),
	GROUP(tsin_d1_7_a,	2,	31),
	GROUP(atv_if_agc,	2,	23),
	GROUP(dtv_if_agc,	2,	22),
	GROUP(dtv_rf_agc,	2,	21),
	GROUP(uart_tx_a,	2,	14),
	GROUP(uart_rx_a,	2,	13),
	GROUP(uart_cts_a,	2,	12),
	GROUP(uart_rts_a,	2,	11),
	GROUP(i2s_lrclk_out_dv,	2,	6),
	GROUP(i2s_aoclk_in_dv,	2,	4),
	GROUP(i2s_lrclk_in_dv,	2,	3),
	GROUP(i2s_amclk_dv,	2,	5),
	GROUP(i2s_out_ch01_dv,	2,	8),
	GROUP(i2s_in_ch01_dv,	2,	2),

	/* Bank C */
	GROUP(sdcard_d1,	6,	5),
	GROUP(sdcard_d0,	6,	4),
	GROUP(sdcard_clk,	6,	3),
	GROUP(sdcard_cmd,	6,	2),
	GROUP(sdcard_d3,	6,	0),
	GROUP(sdcard_d2,	6,	1),
	GROUP(uart_tx_ao_a_c4,	6,	9),
	GROUP(uart_rx_ao_a_c5,	6,	8),
	GROUP(uart_rx_ao_a_c4,	6,	11),
	GROUP(uart_tx_ao_a_c5,	6,	10),

	/* Bank H */
	GROUP(pwm_e_h4,		0,	26),
	GROUP(pwm_e_h8,		0,	13),
	GROUP(pwm_f_h,		0,	12),
	GROUP(tsin_d0_b,	0,	17),
	GROUP(tsin_clk_b,	0,	18),
	GROUP(tsin_sop_b,	0,	16),
	GROUP(tsin_valid_b,	0,	15),
	GROUP(tsin_fail_b,	0,	14),
	GROUP(i2c2_sck,		0,	29),
	GROUP(i2c2_sda,		0,	28),
	GROUP(vx1_lockn,	0,	31),
	GROUP(vx1_htpdn,	0,	30),

	/* Bank BOOT */
	GROUP(emmc_nand_d07,	7,	31),
	GROUP(emmc_clk,		7,	30),
	GROUP(emmc_cmd,		7,	29),
	GROUP(emmc_ds,		7,	28),
	GROUP(nor_d,		7,	13),
	GROUP(nor_q,		7,	12),
	GROUP(nor_c,		7,	11),
	GROUP(nor_cs,		7,	10),

	/* Bank Z */
	GROUP(pwm_d_z4,		4,	19),
	GROUP(pwm_d_z19,	3,	27),
	GROUP(pwm_vs_z4,	4,	18),
	GROUP(pwm_vs_z6,	4,	15),
	GROUP(pwm_vs_z7,	4,	13),
	GROUP(pwm_vs_z19,	3,	26),
	GROUP(spi_miso_a,	4,	30),
	GROUP(spi_mosi_a,	4,	31),
	GROUP(spi_clk_a,	4,	29),
	GROUP(spi_ss0_a,	4,	28),
	GROUP(spi_ss1_a,	4,	27),
	GROUP(spi_ss2_a,	4,	26),
	GROUP(pcm_clk_a,	3,	14),
	GROUP(pcm_fs_a,		3,	13),
	GROUP(pcm_in_a,		3,	15),
	GROUP(pcm_out_a,	3,	16),
	GROUP(uart_tx_b,	3,	25),
	GROUP(uart_rx_b,	3,	24),
	GROUP(uart_cts_b,	3,	23),
	GROUP(uart_rts_b,	3,	22),
	GROUP(uart_tx_c,	4,	25),
	GROUP(uart_rx_c,	4,	24),
	GROUP(uart_cts_c,	4,	23),
	GROUP(uart_rts_c,	4,	22),
	GROUP(spdif_out,	3,	30),
	GROUP(spdif_in,		3,	31),
	GROUP(i2s_aoclk_out_z,  4,  9),
	GROUP(i2s_lrclk_out_z,	4,	8),
	GROUP(i2s_aoclk_in_z,	4,	3),
	GROUP(i2s_lrclk_in_z,	4,	2),
	GROUP(i2s_amclk_z,	4,	10),
	GROUP(i2s_out_ch01_z,	4,	7),
	GROUP(i2s_in_ch01_z,	4,	1),
	GROUP(i2s_out_ch23,	4,	6),
	GROUP(i2s_out_ch45,	4,	5),
	GROUP(i2s_out_ch67,	4,	4),
	GROUP(a_i2s_amclk,	3,	20),
	GROUP(a_i2s_aoclk_in,	3,	19),
	GROUP(a_i2s_lrclk_in,	3,	18),
	GROUP(a_i2s_in_ch01,	3,	17),
	GROUP(eth_link_led,	3,	29),
	GROUP(eth_act_led,	3,	28),
	GROUP(i2c0_sda,		4,	11),
	GROUP(i2c0_sck,		4,	12),
	GROUP(pwm_a_z,		4,	17),
	GROUP(pwm_b_z,		4,	16),
	GROUP(pwm_c,		4,	14),
	GROUP(i2c3_sda,		4,	21),
	GROUP(i2c3_sck,		4,	20),

	/* Bank W */
	GROUP(uart_tx_ao_a_w2,	5,	15),
	GROUP(uart_rx_ao_a_w3,	5,	14),
	GROUP(uart_tx_ao_a_w6,	5,	13),
	GROUP(uart_rx_ao_a_w7,	5,	12),
	GROUP(uart_tx_ao_a_w10,	5,	11),
	GROUP(uart_rx_ao_a_w11,	5,	10),
	GROUP(uart_tx_ao_a_w14,	5,	9),
	GROUP(uart_rx_ao_a_w15,	5,	8),
	GROUP(hdmirx_hpd_a,	5,	27),
	GROUP(hdmirx_det_a,	5,	26),
	GROUP(hdmirx_sda_a,	5,	25),
	GROUP(hdmirx_sck_a,	5,	24),
	GROUP(hdmirx_hpd_b,	5,	19),
	GROUP(hdmirx_det_b,	5,	18),
	GROUP(hdmirx_sda_b,	5,	17),
	GROUP(hdmirx_sck_b,	5,	16),
	GROUP(hdmirx_hpd_c,	5,	23),
	GROUP(hdmirx_det_c,	5,	22),
	GROUP(hdmirx_sda_c,	5,	21),
	GROUP(hdmirx_sck_c,	5,	20),
	GROUP(hdmirx_hpd_d,	5,	31),
	GROUP(hdmirx_det_d,	5,	30),
	GROUP(hdmirx_sda_d,	5,	29),
	GROUP(hdmirx_sck_d,	5,	28),

	/* Bank CLK */
	GROUP(pwm_f_clk,	8,	30),
};

static const struct pinctrl_pin_desc meson_txl_aobus_pins[] = {
	MESON_PIN(GPIOAO_0),
	MESON_PIN(GPIOAO_1),
	MESON_PIN(GPIOAO_2),
	MESON_PIN(GPIOAO_3),
	MESON_PIN(GPIOAO_4),
	MESON_PIN(GPIOAO_5),
	MESON_PIN(GPIOAO_6),
	MESON_PIN(GPIOAO_7),
	MESON_PIN(GPIOAO_8),
	MESON_PIN(GPIOAO_9),
	MESON_PIN(GPIOAO_10),
	MESON_PIN(GPIOAO_11),
	MESON_PIN(GPIO_TEST_N),
};

/* uart_ao_a */
static const unsigned int uart_tx_ao_a_pins[] = { GPIOAO_0 };
static const unsigned int uart_rx_ao_a_pins[] = { GPIOAO_1 };
static const unsigned int uart_cts_ao_a_pins[] = { GPIOAO_2 };
static const unsigned int uart_rts_ao_a_pins[] = { GPIOAO_3 };

/* uart_ao_b */
static const unsigned int uart_tx_ao_b_ao0_pins[] = { GPIOAO_0 };
static const unsigned int uart_rx_ao_b_ao1_pins[] = { GPIOAO_1 };
static const unsigned int uart_cts_ao_b_pins[] = { GPIOAO_2 };
static const unsigned int uart_rts_ao_b_pins[] = { GPIOAO_3 };

static const unsigned int uart_tx_ao_b_ao4_pins[] = { GPIOAO_4 };
static const unsigned int uart_rx_ao_b_ao5_pins[] = { GPIOAO_5 };

/* ir_out */
static const unsigned int remote_out_ao2_pins[] = { GPIOAO_2 };
static const unsigned int remote_out_ao6_pins[] = { GPIOAO_6 };

/* ir_in */
static const unsigned int remote_in_pins[] = { GPIOAO_6 };

/* pwm_ao_a */
static const unsigned int pwm_ao_a_ao3_pins[] = { GPIOAO_3 };
static const unsigned int pwm_ao_a_ao7_pins[] = { GPIOAO_7 };

/* pwm_ao_b */
static const unsigned int pwm_ao_b_ao8_pins[] = { GPIOAO_8 };
static const unsigned int pwm_ao_b_ao9_pins[] = { GPIOAO_9 };

/* i2c_ao */
static const unsigned int i2c_sck_ao_pins[] = { GPIOAO_4 };
static const unsigned int i2c_sda_ao_pins[] = { GPIOAO_5 };

/* i2c_slave_ao */
static const unsigned int i2c_slave_sck_ao_pins[] = { GPIOAO_4 };
static const unsigned int i2c_slave_sda_ao_pins[] = { GPIOAO_5 };

/* ao_cec */
static const unsigned int ao_cec_pins[] = { GPIOAO_7 };

/* ee_cec */
static const unsigned int ee_cec_pins[] = { GPIOAO_7 };

static struct meson_pmx_group meson_txl_aobus_groups[] = {
	GPIO_GROUP(GPIOAO_0),
	GPIO_GROUP(GPIOAO_1),
	GPIO_GROUP(GPIOAO_2),
	GPIO_GROUP(GPIOAO_3),
	GPIO_GROUP(GPIOAO_4),
	GPIO_GROUP(GPIOAO_5),
	GPIO_GROUP(GPIOAO_6),
	GPIO_GROUP(GPIOAO_7),
	GPIO_GROUP(GPIOAO_8),
	GPIO_GROUP(GPIOAO_9),
	GPIO_GROUP(GPIOAO_10),
	GPIO_GROUP(GPIOAO_11),
	GPIO_GROUP(GPIO_TEST_N),

	/* bank AO */
	GROUP(uart_tx_ao_a,		0,	12),
	GROUP(uart_rx_ao_a,		0,	11),
	GROUP(uart_cts_ao_a,		0,	10),
	GROUP(uart_rts_ao_a,		0,	9),
	GROUP(uart_tx_ao_b_ao0,		0,	26),
	GROUP(uart_rx_ao_b_ao1,		0,	25),
	GROUP(uart_cts_ao_b,		0,	8),
	GROUP(uart_rts_ao_b,		0,	7),
	GROUP(uart_tx_ao_b_ao4,		0,	24),
	GROUP(uart_rx_ao_b_ao5,		0,	23),
	GROUP(remote_out_ao2,		0,	28),
	GROUP(remote_out_ao6,		0,	21),
	GROUP(remote_in,		0,	0),
	GROUP(pwm_ao_a_ao3,		0,	22),
	GROUP(pwm_ao_a_ao7,		0,	17),
	GROUP(pwm_ao_b_ao8,		0,	27),
	GROUP(pwm_ao_b_ao9,		0,	3),
	GROUP(i2c_sck_ao,		0,	6),
	GROUP(i2c_sda_ao,		0,	5),
	GROUP(i2c_slave_sck_ao,		0,	2),
	GROUP(i2c_slave_sda_ao,		0,	1),
	GROUP(ao_cec,			0,	15),
	GROUP(ee_cec,			0,	14),
};

static const char * const gpio_periphs_groups[] = {
	"GPIOZ_0", "GPIOZ_1", "GPIOZ_2", "GPIOZ_3", "GPIOZ_4",
	"GPIOZ_5", "GPIOZ_6", "GPIOZ_7", "GPIOZ_8", "GPIOZ_9",
	"GPIOZ_10", "GPIOZ_11", "GPIOZ_12", "GPIOZ_13", "GPIOZ_14",
	"GPIOZ_15", "GPIOZ_16", "GPIOZ_17", "GPIOZ_18", "GPIOZ_19",
	"GPIOZ_20", "GPIOZ_21",

	"GPIOH_0", "GPIOH_1", "GPIOH_2", "GPIOH_3", "GPIOH_4",
	"GPIOH_5", "GPIOH_6", "GPIOH_7", "GPIOH_8", "GPIOH_9",

	"BOOT_0", "BOOT_1", "BOOT_2", "BOOT_3", "BOOT_4",
	"BOOT_5", "BOOT_6", "BOOT_7", "BOOT_8", "BOOT_9",
	"BOOT_10", "BOOT_11",

	"CARD_0", "CARD_1", "CARD_2", "CARD_3", "CARD_4",
	"CARD_5", "CARD_6",

	"GPIODV_0", "GPIODV_1", "GPIODV_2", "GPIODV_3", "GPIODV_4",
	"GPIODV_5", "GPIODV_6", "GPIODV_7", "GPIODV_8", "GPIODV_9",
	"GPIODV_10", "GPIODV_11",

	"GPIOW_0", "GPIOW_1", "GPIOW_2", "GPIOW_3", "GPIOW_4",
	"GPIOW_5", "GPIOW_6", "GPIOW_7", "GPIOW_8", "GPIOW_9",
	"GPIOW_10", "GPIOW_11", "GPIOW_12", "GPIOW_13", "GPIOW_14",
	"GPIOW_15",

	"GPIOCLK_0", "GPIOCLK_1",
};

static const char * const emmc_groups[] = {
	"emmc_nand_d07", "emmc_clk", "emmc_cmd", "emmc_ds",
};

static const char * const sdcard_groups[] = {
	"sdcard_d0", "sdcard_d1", "sdcard_d2", "sdcard_d3",
	"sdcard_cmd", "sdcard_clk",
};

static const char *const nor_groups[] = {
	"nor_d", "nor_q", "nor_c", "nor_cs",
};

static const char * const i2c0_groups[] = {
	"i2c0_sda", "i2c0_sck",
};

static const char * const i2c1_groups[] = {
	"i2c1_sda", "i2c1_sck",
};

static const char * const i2c2_groups[] = {
	"i2c2_sda", "i2c2_sck",
};

static const char * const i2c3_groups[] = {
	"i2c3_sda", "i2c3_sck",
};

static const char * const pwm_a_groups[] = {
	"pwm_a_z", "pwm_a_dv",
};

static const char * const pwm_b_groups[] = {
	"pwm_b_z", "pwm_b_dv",
};

static const char * const pwm_c_groups[] = {
	"pwm_c",
};

static const char * const pwm_d_groups[] = {
	"pwm_d_z4", "pwm_d_z19",
};

static const char * const pwm_vs_groups[] = {
	"pwm_vs_dv2", "pwm_vs_dv3",
	"pwm_vs_z4", "pwm_vs_z6",
	"pwm_vs_z7", "pwm_vs_z19",
};

static const char * const pwm_e_groups[] = {
	"pwm_e_h4", "pwm_e_h8",
};

static const char * const pwm_f_groups[] = {
	"pwm_f_clk", "pwm_f_h",
};

static const char * const tsin_a_groups[] = {
	"tsin_d0_a", "tsin_clk_a", "tsin_sop_a",
	"tsin_valid_a", "tsin_fail_a", "tsin_d1_7_a",
};

static const char * const tsin_b_groups[] = {
	"tsin_d0_b", "tsin_clk_b", "tsin_sop_b",
	"tsin_valid_b", "tsin_fail_b",
};

static const char * const dtv_groups[] = {
	"dtv_if_agc", "dtv_rf_agc",
};

static const char * const atv_groups[] = {
	"atv_if_agc",
};

static const char * const spi_a_groups[] = {
	"spi_miso_a", "spi_mosi_a", "spi_clk_a",
	"spi_ss0_a", "spi_ss1_a", "spi_ss2_a",
};

static const char * const pcm_a_groups[] = {
	"pcm_clk_a", "pcm_fs_a", "pcm_in_a", "pcm_out_a",
};

static const char * const uart_a_groups[] = {
	"uart_tx_a", "uart_rx_a", "uart_cts_a", "uart_rts_a",
};

static const char * const uart_b_groups[] = {
	"uart_tx_b", "uart_rx_b",
	"uart_cts_b", "uart_rts_b",
};

static const char * const uart_c_groups[] = {
	"uart_tx_c", "uart_rx_c", "uart_cts_c", "uart_rts_c",
};

static const char * const uart_ao_a_ee_groups[] = {
	"uart_tx_ao_a_c4", "uart_rx_ao_a_c5",
	"uart_rx_ao_a_c4", "uart_tx_ao_a_c5",
	"uart_tx_ao_a_w2", "uart_rx_ao_a_w3",
	"uart_tx_ao_a_w6", "uart_rx_ao_a_w7",
	"uart_tx_ao_a_w10", "uart_rx_ao_a_w11",
	"uart_tx_ao_a_w14", "uart_rx_ao_a_w15",
};

static const char * const spdif_out_groups[] = {
	"spdif_out",
};

static const char * const spdif_in_groups[] = {
	"spdif_in",
};

static const char * const hdmirx_a_groups[] = {
	"hdmirx_hpd_a", "hdmirx_det_a", "hdmirx_sda_a", "hdmirx_sck_a",
};

static const char * const hdmirx_b_groups[] = {
	"hdmirx_hpd_b", "hdmirx_det_b", "hdmirx_sda_b", "hdmirx_sck_b",
};

static const char * const hdmirx_c_groups[] = {
	"hdmirx_hpd_c", "hdmirx_det_c", "hdmirx_sda_c", "hdmirx_sck_c",
};

static const char * const hdmirx_d_groups[] = {
	"hdmirx_hpd_d", "hdmirx_det_d", "hdmirx_sda_d", "hdmirx_sck_d",
};

static const char * const i2s_groups[] = {
	"i2s_lrclk_out_dv", "i2s_aoclk_in_dv", "i2s_lrclk_in_dv",
	"i2s_amclk_dv", "i2s_out_ch01_dv", "i2s_in_ch01_dv",
	"i2s_aoclk_out_z",
	"i2s_lrclk_out_z", "i2s_aoclk_in_z", "i2s_lrclk_in_z",
	"i2s_amclk_z", "i2s_out_ch01_z", "i2s_in_ch01_z",

	"i2s_out_ch23", "i2s_out_ch45", "i2s_out_ch67",
};

static const char * const acodec_i2s_groups[] = {
	"a_i2s_amclk", "a_i2s_aoclk_in", "a_i2s_lrclk_in",
	"a_i2s_in_ch01",
};

static const char * const eth_groups[] = {
	"eth_link_led", "eth_act_led",
};

static const char * const vbyone_groups[] = {
	"vx1_lockn", "vx1_htpdn",
};

static struct meson_pmx_func meson_txl_periphs_functions[] = {
	FUNCTION(gpio_periphs),
	FUNCTION(emmc),
	FUNCTION(nor),
	FUNCTION(sdcard),
	FUNCTION(i2c0),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(pwm_a),
	FUNCTION(pwm_b),
	FUNCTION(pwm_c),
	FUNCTION(pwm_d),
	FUNCTION(pwm_vs),
	FUNCTION(pwm_e),
	FUNCTION(pwm_f),
	FUNCTION(tsin_a),
	FUNCTION(tsin_b),
	FUNCTION(atv),
	FUNCTION(dtv),
	FUNCTION(spi_a),
	FUNCTION(pcm_a),
	FUNCTION(uart_a),
	FUNCTION(uart_b),
	FUNCTION(uart_c),
	FUNCTION(uart_ao_a_ee),
	FUNCTION(spdif_out),
	FUNCTION(spdif_in),
	FUNCTION(hdmirx_a),
	FUNCTION(hdmirx_b),
	FUNCTION(hdmirx_c),
	FUNCTION(hdmirx_d),
	FUNCTION(i2s),
	FUNCTION(acodec_i2s),
	FUNCTION(eth),
	FUNCTION(vbyone),
};

static const char * const gpio_aobus_groups[] = {
	"GPIOAO_0", "GPIOAO_1", "GPIOAO_2", "GPIOAO_3", "GPIOAO_4",
	"GPIOAO_5", "GPIOAO_6", "GPIOAO_7", "GPIOAO_8", "GPIOAO_9",
	"GPIOAO_10", "GPIOAO_11", "GPIO_TEST_N",
};

static const char * const uart_ao_a_groups[] = {
	"uart_tx_ao_a", "uart_rx_ao_a", "uart_cts_ao_a",
	"uart_rts_ao_a",
};

static const char * const uart_ao_b_groups[] = {
	"uart_tx_ao_b_ao0", "uart_rx_ao_b_ao1",
	"uart_tx_ao_b_ao4", "uart_rx_ao_b_ao5",
	"uart_cts_ao_b", "uart_rts_ao_b",
};

static const char * const ir_in_groups[] = {
	"remote_in",
};

static const char *const ir_out_groups[] = {
	"remote_out_ao2", "remote_out_ao6",
};

static const char * const pwm_ao_a_groups[] = {
	"pwm_ao_a_ao3", "pwm_ao_a_ao7",
};

static const char * const pwm_ao_b_groups[] = {
	"pwm_ao_b_ao8", "pwm_ao_b_ao9",
};

static const char * const i2c_ao_groups[] = {
	"i2c_sck_ao", "i2c_sda_ao",
};

static const char * const i2c_slave_ao_groups[] = {
	"i2c_slave_sck_ao", "i2c_slave_sda_ao",
};

static const char * const ao_cec_groups[] = {
	"ao_cec",
};

static const char * const ee_cec_groups[] = {
	"ee_cec",
};

static struct meson_pmx_func meson_txl_aobus_functions[] = {
	FUNCTION(gpio_aobus),
	FUNCTION(uart_ao_a),
	FUNCTION(uart_ao_b),
	FUNCTION(ir_in),
	FUNCTION(ir_out),
	FUNCTION(pwm_ao_a),
	FUNCTION(pwm_ao_b),
	FUNCTION(i2c_ao),
	FUNCTION(i2c_slave_ao),
	FUNCTION(ao_cec),
	FUNCTION(ee_cec),
};

static struct meson_bank meson_txl_periphs_banks[] = {
	/*   name    first   last  irq  pullen  pull    dir     out     in  */
	BANK("Z", GPIOZ_0, GPIOZ_21, 12,
	3,  0,  3,  0,  9,  0,  10, 0,  11, 0),
	BANK("H", GPIOH_0, GPIOH_9, 34,
	1,  20, 1,  20, 3,  20, 4,  20, 5,  20),
	BANK("BOOT", BOOT_0, BOOT_11, 44,
	2,  0,  2,  0,  6,  0,  7,  0,  8,  0),
	BANK("CARD", CARD_0, CARD_6, 56,
	2,  20, 2,  20, 6,  20, 7,  20, 8,  20),
	BANK("DV", GPIODV_0, GPIODV_11, 63,
	0,  0,  0,  0,  0,  0,  1,  0,  2,  0),
	BANK("W", GPIOW_0, GPIOW_15, 75,
	4,  0,  4,  0,  12,  0, 13,  0,  14,  0),
	BANK("CLK", GPIOCLK_0, GPIOCLK_1, 91,
	3,  28,  3,  28,  9, 28,  10, 28,  11, 28),
};

/*
 * TEST_N is special pin, only used as gpio output at present.
 * the direction control bit from AO_SEC_REG0 bit[0], it
 * configured to output when pinctrl driver is initialized.
 * to make the api of gpiolib work well, the reserved bit(bit[14])
 * seen as direction control bit.
 *
 * AO_GPIO_O_EN_N       0x09<<2=0x24     bit[31]     output level
 * AO_GPIO_I            0x0a<<2=0x28     bit[31]     input level
 * AO_SEC_REG0          0x50<<2=0x140    bit[0]      input enable
 * AO_RTI_PULL_UP_REG   0x0b<<2=0x2c     bit[14]     pull-up/down
 * AO_RTI_PULL_UP_REG   0x0b<<2=0x2c     bit[30]     pull-up enable
 */
static struct meson_bank meson_txl_aobus_banks[] = {
	/* name    first   last  irq  pullen  pull    dir     out     in  */
	BANK("AO", GPIOAO_0, GPIOAO_11,	0,
	0,  16, 0,  0,  0,  0,  0,  16, 1,  0),
	BANK("TEST", GPIO_TEST_N, GPIO_TEST_N,	-1,
	0,  30, 0,  14, 0,  14, 0,  31, 1,  31),
};

int meson_txl_aobus_init(struct meson_pinctrl *pc)
{
	struct arm_smccc_res res;
	/*set TEST_N to output*/
	arm_smccc_smc(CMD_TEST_N_DIR, TEST_N_OUTPUT, 0, 0, 0, 0, 0, 0, &res);

	return 0;
}

struct meson_pinctrl_data meson_txl_periphs_pinctrl_data = {
	.name		= "periphs-banks",
	.init		= NULL,
	.pins		= meson_txl_periphs_pins,
	.groups		= meson_txl_periphs_groups,
	.funcs		= meson_txl_periphs_functions,
	.banks		= meson_txl_periphs_banks,
	.num_pins	= ARRAY_SIZE(meson_txl_periphs_pins),
	.num_groups	= ARRAY_SIZE(meson_txl_periphs_groups),
	.num_funcs	= ARRAY_SIZE(meson_txl_periphs_functions),
	.num_banks	= ARRAY_SIZE(meson_txl_periphs_banks),
	.pmx_ops	= &meson8_pmx_ops,
};

struct meson_pinctrl_data meson_txl_aobus_pinctrl_data = {
	.name		= "aobus-banks",
	.init		= meson_txl_aobus_init,
	.pins		= meson_txl_aobus_pins,
	.groups		= meson_txl_aobus_groups,
	.funcs		= meson_txl_aobus_functions,
	.banks		= meson_txl_aobus_banks,
	.num_pins	= ARRAY_SIZE(meson_txl_aobus_pins),
	.num_groups	= ARRAY_SIZE(meson_txl_aobus_groups),
	.num_funcs	= ARRAY_SIZE(meson_txl_aobus_functions),
	.num_banks	= ARRAY_SIZE(meson_txl_aobus_banks),
	.pmx_ops	= &meson8_pmx_ops,
};

static const struct of_device_id meson_txl_pinctrl_dt_match[] = {
	{
		.compatible = "amlogic,meson-txl-periphs-pinctrl",
		.data = &meson_txl_periphs_pinctrl_data,
	},
	{
		.compatible = "amlogic,meson-txl-aobus-pinctrl",
		.data = &meson_txl_aobus_pinctrl_data,
	},
	{}	/* Make KASAN shut up */
};

static struct platform_driver meson_txl_pinctrl_driver = {
	.probe		= meson_pinctrl_probe,
	.driver = {
		.name	= "meson-txl-pinctrl",
		.of_match_table = meson_txl_pinctrl_dt_match,
	},
};

static int __init txl_pmx_init(void)
{
	return platform_driver_register(&meson_txl_pinctrl_driver);
}

static void __exit txl_pmx_exit(void)
{
	platform_driver_unregister(&meson_txl_pinctrl_driver);
}

arch_initcall(txl_pmx_init);
module_exit(txl_pmx_exit);
MODULE_DESCRIPTION("txl pin control driver");
MODULE_LICENSE("GPL v2");
