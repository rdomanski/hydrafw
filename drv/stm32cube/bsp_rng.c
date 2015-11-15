/*
HydraBus/HydraNFC - Copyright (C) 2014 Benjamin VERNOUX
HydraBus/HydraNFC - Copyright (C) 2015 Nicolas OBERLI

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "bsp_rng.h"
#include "stm32f405xx.h"

static RNG_HandleTypeDef *hrng;

/** \brief Init RNG device.
 *
 * \return bsp_status_t: status of the init.
 *
 */
bsp_status_t bsp_rng_init()
{
        hrng->Instance = RNG;

        /* Configure the RNG peripheral */
        __RNG_CLK_ENABLE();

        __HAL_RNG_ENABLE(hrng);

        /*
        if(HAL_RNG_Init(hrng) != HAL_OK) {
        	return BSP_ERROR;
        }
        */

        return BSP_OK;
}

/** \brief De-initialize the RNG device.
 *
 * \return bsp_status_t: Status of the deinit.
 *
 */
bsp_status_t bsp_rng_deinit()
{
        __RNG_CLK_DISABLE();

        __HAL_RNG_DISABLE(hrng);

        return BSP_OK;
}

/** \brief
 *
 * \param dev_num bsp_dev_rng_t: RNG dev num.
 * \param rx_data uint16_t*: The received byte.
 * \param nb_data uint8_t: Number of byte to received.
 * \return bsp_status_t: Status of the transfer.
 *
 */
uint32_t bsp_rng_read()
{
        while (!(__HAL_RNG_GET_FLAG(hrng, RNG_FLAG_DRDY)) || USER_BUTTON) {
        }

        return hrng->Instance->DR;
}
