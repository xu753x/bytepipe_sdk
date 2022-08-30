#ifndef SRC_RFLAN_UART_H_
#define SRC_RFLAN_UART_H_
/***************************************************************************//**
*  \ingroup    RFLAN
*  \defgroup   RFLAN_UART RFLAN Uart
*  @{
*******************************************************************************/
/***************************************************************************//**
*  \file       rflan_uart.h
*
*  \details    This file contains the RFLAN UART application definitions.
*
*  \copyright
*
*  Copyright 2021(c) NextGen RF Design, Inc.
*
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*   - The use of this software may or may not infringe the patent rights of one
*     or more patent holders.  This license does not release you from the
*     requirement that you obtain separate licenses from these patent holders
*     to use this software.
*   - Use of the software either in source or binary form, must be run on or
*     directly connected to a NextGen RF Design, Inc. product.
*
*  THIS SOFTWARE IS PROVIDED BY NEXTGEN RF DESIGN "AS IS" AND ANY EXPRESS OR
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
*  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
*  EVENT SHALL NEXTGEN RF DESIGN BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*  INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/
#include "xuartps.h"


typedef void (*rflan_uart_callback_t)( char c, void *CallbackRef );

typedef struct
{
  XUartPs           		  RflanUart;
  rflan_uart_callback_t   ParentCallback;     /*!< Callback provided by parent request, executed once request is complete */
  void                   *ParentCallbackRef;  /*!< Callback data provided by parent request, provided in callback relative to specific request */
  volatile uint8_t  		  RxChar;
} rflan_uart_t;

typedef struct
{
	uint32_t 				        DeviceId;
	uint32_t				        BaudRate;
	uint32_t				        IntrId;
	rflan_uart_callback_t   ParentCallback;     /*!< Callback provided by parent request, executed once request is complete */
	void                   *ParentCallbackRef;  /*!< Callback data provided by parent request, provided in callback relative to specific request */
} rflan_uart_init_t;

int32_t RflanUart_Send( rflan_uart_t *Instance, char c );
int32_t RflanUart_Initialize( rflan_uart_t *Instance, rflan_uart_init_t *Init );


#endif /* SRC_RFLAN_H_ */