/***************************************************************************//**
 * @file
 * @brief main() function.
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
 ******************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include "system.h"
#include "app_signal.h"
#include "app.h"

/* Static Variables *************************************************** */
static pthread_t consoleThreadId, appMainThreadId;

extern volatile bool run;

// Custom signal handler.
static void signal_handler(int sig)
{
  (void)sig;
  run = false;
  // Deinitialize the application.
  app_deinit();
}

int main(int argc, char *argv[])
{
  // Set up custom signal handler for user interrupt and termination request.
  app_signal(SIGINT, signal_handler);
  app_signal(SIGTERM, signal_handler);

  // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
  // Note that if the kernel is present, processing task(s) will be created by
  // this call.
  sl_system_init();

  // Initialize the application. For example, create periodic timer(s) or
  // task(s) if the kernel is present.
  app_init(argc, argv);

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

  return EXIT_SUCCESS;
}
