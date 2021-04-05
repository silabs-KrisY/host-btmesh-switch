/***************************************************************************//**
 * @file main.c
 * @brief This example implements a Bluetooth Mesh node as an NCP host application.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *******************************************************************************
 * # Evaluation Quality
 * This code has been minimally tested to ensure that it builds and is suitable
 * as a demonstration for evaluation purposes only. This code will be maintained
 * at the sole discretion of Silicon Labs.
 ******************************************************************************/

/* Includes *********************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#include "app.h"
#include "uart.h"

/* Defines  *********************************************************** */
/** Usage string */
#define USAGE "Usage: %s [serial port] [baud rate] \n\n"

/* Static Variables *************************************************** */
static pthread_t consoleThreadId, appMainThreadId;

/** The serial port to use for BGAPI communication. */
char* uart_port = NULL;
/** The baud rate to use. */
static uint32_t baud_rate = 0;
/* Global Variables *************************************************** */

/* Static Functions Declaractions ************************************* */
/**
 * Function called when a message needs to be written to the serial port.
 * @param msg_len Length of the message.
 * @param msg_data Message data, including the header.
 * @param data_len Optional variable data length.
 * @param data Optional variable data.
 */
void on_message_send(uint32_t msg_len,
                     uint8_t* msg_data)
{
  /** Variable for storing function return values. */
  int ret;

#if DEBUG
  CS_OUTPUT("on_message_send()\n");
#endif /* DEBUG */

  ret = uartTx(msg_len, msg_data);
  if (ret < 0) {
    CS_OUTPUT("on_message_send() - failed to write to serial port %s, ret: %d, errno: %d\n", uart_port, ret, errno);
    exit(EXIT_FAILURE);
  }
}
int hw_init(int argc, char* argv[])
{
  if (argc < 3) {
    printf(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }
  /**
   * Handle the command-line arguments.
   */

  baud_rate = atoi(argv[2]);
  uart_port = argv[1];

  if (!uart_port || !baud_rate ) {
    printf(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }

  /**
   * Initialise the serial port.
   */
  return uartOpen((int8_t*)uart_port, baud_rate, 1, 100);
}

int main(int argc, char *argv[])
{
  if (hw_init(argc, argv) < 0) {
    printf("HW init failure\n");
    exit(EXIT_FAILURE);
  }

  if (-1 == pthread_create(&consoleThreadId,
                           NULL,
                           pConsoleThread,
                           NULL)) {
    perror("Error creating console thread.\n");
    exit(1);
  }

  if (-1 == pthread_create(&appMainThreadId,
                           NULL,
                           pAppMainThread,
                           NULL)) {
    perror("Error creating App Main thread.\n");
    exit(1);
  }

  if ((-1 == pthread_join(consoleThreadId, NULL))
      || (-1 == pthread_join(appMainThreadId, NULL))) {
    perror("Error join console thread.\n");
    exit(1);
  }

  return 0;
}
