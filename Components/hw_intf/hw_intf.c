#include "spi.h"
#include "hw_intf.h"

#define NRF24L01_SPI                 	&hspi1
#define NRF24L01_SPI_CS_PORT         	GPIOA
#define NRF24L01_SPI_CS_PIN_NUM      	GPIO_PIN_11
#define NRF24L01_SPI_CE_PORT         	GPIOA
#define NRF24L01_SPI_CE_PIN_NUM      	GPIO_PIN_12
#define NRF24L01_IRQ_PORT            	GPIOA
#define NRF24L01_IRQ_PIN_NUM         	GPIO_PIN_13

nrf24l01_handle_t nrf24l01_handle;

err_code_t hw_intf_nrf24l01_spi_send(uint8_t *buf_send, uint16_t len, uint32_t timeout_ms)
{
	HAL_SPI_Transmit(NRF24L01_SPI, buf_send, len, timeout_ms);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_nrf24l01_spi_recv(uint8_t *buf_recv, uint16_t len, uint32_t timeout_ms)
{
	HAL_SPI_Receive(NRF24L01_SPI, buf_recv, len, timeout_ms);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_nrf24l01_set_cs(uint8_t level)
{
	HAL_GPIO_WritePin(NRF24L01_SPI_CS_PORT, NRF24L01_SPI_CS_PIN_NUM, level);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_nrf24l01_set_ce(uint8_t level)
{
	HAL_GPIO_WritePin(NRF24L01_SPI_CE_PORT, NRF24L01_SPI_CE_PIN_NUM, level);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_init_nrf24l01(void)
{
	nrf24l01_handle = nrf24l01_init();
	nrf24l01_cfg_t nrf24l01_cfg = {
		.channel = 2500,
		.payload_len = 8,
		.crc_len = 1,
		.addr_width = 5,
		.retrans_cnt = 3,
		.retrans_delay = 250,
		.data_rate = NRF24L01_DATA_RATE_1Mbps,
		.output_pwr = NRF24L01_OUTPUT_PWR_0dBm,
		.mode = NRF24L01_MODE_TRANSMITTER,
		.spi_send = hw_intf_nrf24l01_spi_send,
		.spi_recv = hw_intf_nrf24l01_spi_recv,
		.set_cs = hw_intf_nrf24l01_set_cs,
		.set_ce = hw_intf_nrf24l01_set_ce
	};
	nrf24l01_set_config(nrf24l01_handle, nrf24l01_cfg);
	nrf24l01_config(nrf24l01_handle);

	return ERR_CODE_SUCCESS;
}