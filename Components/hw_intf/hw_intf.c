#include "spi.h"
#include "adc.h"
#include "hw_intf.h"

#define NRF24L01_SPI                 	&hspi1
#define NRF24L01_SPI_CS_PORT         	GPIOA
#define NRF24L01_SPI_CS_PIN_NUM      	GPIO_PIN_11
#define NRF24L01_SPI_CE_PORT         	GPIOA
#define NRF24L01_SPI_CE_PIN_NUM      	GPIO_PIN_12
#define NRF24L01_IRQ_PORT            	GPIOA
#define NRF24L01_IRQ_PIN_NUM         	GPIO_PIN_13

#define LEFT_JOYSTICK_ADC               hadc2
#define LEFT_JOYSTICK_POSX_ADC_CHNL     ADC_CHANNEL_0
#define LEFT_JOYSTICK_POSY_ADC_CHNL     ADC_CHANNEL_1
#define LEFT_JOYSTICK_BUTTON_PORT       GPIOB
#define LEFT_JOYSTICK_BUTTON_PIN        GPIO_PIN_1

#define RIGHT_JOYSTICK_ADC              hadc2
#define RIGHT_JOYSTICK_POSX_ADC_CHNL    ADC_CHANNEL_2
#define RIGHT_JOYSTICK_POSY_ADC_CHNL    ADC_CHANNEL_3
#define RIGHT_JOYSTICK_BUTTON_PORT      GPIOB
#define RIGHT_JOYSTICK_BUTTON_PIN       GPIO_PIN_2

#define ADC_SAMPLE_CYCLES               ADC_SAMPLETIME_13CYCLES_5
#define ADC_CONV_TIMEOUT_MS             10

nrf24l01_handle_t nrf24l01_handle;
joystick_handle_t left_joystick_handle, right_joystick_handle;

err_code_t hw_intf_nrf24l01_spi_send(uint8_t *buf_send, uint16_t len)
{
	HAL_SPI_Transmit(NRF24L01_SPI, buf_send, len, 100);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_nrf24l01_spi_recv(uint8_t *buf_recv, uint16_t len)
{
	HAL_SPI_Receive(NRF24L01_SPI, buf_recv, len, 100);

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

err_code_t hw_intf_left_joystick_get_pos_x(uint16_t *pos_x)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = LEFT_JOYSTICK_POSX_ADC_CHNL;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLE_CYCLES;
	if (HAL_ADC_ConfigChannel(&LEFT_JOYSTICK_ADC, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_ADC_Start(&LEFT_JOYSTICK_ADC);
	HAL_ADC_PollForConversion(&LEFT_JOYSTICK_ADC, ADC_CONV_TIMEOUT_MS);
	*pos_x = HAL_ADC_GetValue(&LEFT_JOYSTICK_ADC);
	HAL_ADC_Stop(&LEFT_JOYSTICK_ADC);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_left_joystick_get_pos_y(uint16_t *pos_y)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = LEFT_JOYSTICK_POSY_ADC_CHNL;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLE_CYCLES;
	if (HAL_ADC_ConfigChannel(&LEFT_JOYSTICK_ADC, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_ADC_Start(&LEFT_JOYSTICK_ADC);
	HAL_ADC_PollForConversion(&LEFT_JOYSTICK_ADC, ADC_CONV_TIMEOUT_MS);
	*pos_y = HAL_ADC_GetValue(&LEFT_JOYSTICK_ADC);
	HAL_ADC_Stop(&LEFT_JOYSTICK_ADC);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_left_joystick_get_bt_status(uint8_t *bt_status)
{
	*bt_status = HAL_GPIO_ReadPin(LEFT_JOYSTICK_BUTTON_PORT, LEFT_JOYSTICK_BUTTON_PIN);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_right_joystick_get_pos_x(uint16_t *pos_x)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = RIGHT_JOYSTICK_POSX_ADC_CHNL;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLE_CYCLES;
	if (HAL_ADC_ConfigChannel(&RIGHT_JOYSTICK_ADC, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_ADC_Start(&RIGHT_JOYSTICK_ADC);
	HAL_ADC_PollForConversion(&RIGHT_JOYSTICK_ADC, ADC_CONV_TIMEOUT_MS);
	*pos_x = HAL_ADC_GetValue(&RIGHT_JOYSTICK_ADC);
	HAL_ADC_Stop(&RIGHT_JOYSTICK_ADC);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_right_joystick_get_pos_y(uint16_t *pos_y)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = RIGHT_JOYSTICK_POSY_ADC_CHNL;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLE_CYCLES;
	if (HAL_ADC_ConfigChannel(&RIGHT_JOYSTICK_ADC, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_ADC_Start(&RIGHT_JOYSTICK_ADC);
	HAL_ADC_PollForConversion(&RIGHT_JOYSTICK_ADC, ADC_CONV_TIMEOUT_MS);
	*pos_y = HAL_ADC_GetValue(&RIGHT_JOYSTICK_ADC);
	HAL_ADC_Stop(&RIGHT_JOYSTICK_ADC);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_right_joystick_get_bt_status(uint8_t *bt_status)
{
	*bt_status = HAL_GPIO_ReadPin(RIGHT_JOYSTICK_BUTTON_PORT, RIGHT_JOYSTICK_BUTTON_PIN);

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

err_code_t hw_init_joystick(void)
{
	left_joystick_handle = joystick_init();
	joystick_cfg_t left_joystick_cfg = {
		.get_pos_x = hw_intf_left_joystick_get_pos_x,
		.get_pos_y = hw_intf_left_joystick_get_pos_y,
		.get_bt_status = hw_intf_left_joystick_get_bt_status,
	};
	joystick_set_config(left_joystick_handle, left_joystick_cfg);
	joystick_config(left_joystick_handle);

	right_joystick_handle = joystick_init();
	joystick_cfg_t right_joystick_cfg = {
		.get_pos_x = hw_intf_right_joystick_get_pos_x,
		.get_pos_y = hw_intf_right_joystick_get_pos_y,
		.get_bt_status = hw_intf_right_joystick_get_bt_status,
	};
	joystick_set_config(right_joystick_handle, right_joystick_cfg);
	joystick_config(right_joystick_handle);

	return ERR_CODE_SUCCESS;
}
