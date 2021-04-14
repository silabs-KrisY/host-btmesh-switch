This example duplicates the functionalities of the SDK example - soc-btmesh-switch with NCP mode, instead of controlling the light by the push buttons on the WSTK, it implements a lightweight console, so that you can use the CLI to control the lights in the network. For more information about the ncp mode and ncp host and target, please go through [KBA_BT_1602: NCP Host Implementation and Example](https://www.silabs.com/community/wireless/bluetooth/knowledge-base.entry.html/2018/01/18/ncp_host_implementat-PEsT).

Hardware & SDK Requirements
---------------------------

-   IDE - [Simplicity Studio 4](http://www.silabs.com/products/mcu/Pages/simplicity-studio.aspx)
-   SDK - Silicon Labs Bluetooth Mesh SDK 1.x GA. Tested on both 1.4 and 1.6.3. May need API changes to work with Mesh SDK 2.x.
-   NCP target - At least 1 Bluetooth Mesh compatible boards - EFR32xG12, EFR32xG13 or EFR32xG21 (x= M, B) based, SLWRB4104A and SLWRB4103A are recommended.
-   NCP host - **POSIX compatible** machine to run the host application. Running the application on Windows needs some porting effort, this has only been tested with Linux, Cygwin, and Mac.

How to Use It
-------------

The NCP mode requires both the host and target to work.

### Supported Commands

A simple console is implemented to receive commands from user. Users can add any customized command by adding an new item to the *CMDs* array in app.c.

| Command | Usage | Description |
| --- | --- | --- |
| l | l [1/0] | Set light on[1] or off[0] |
| ln | ln [0-100] | Set lightness [0% - 100%] |
| ct | ct [0-100] | Set Color Temperature [0% - 100%] |
| fr | fr [1/0] | 1 - Factory Reset, 0 - normal reset |
| h | h | Print usage |
| exit | exit | Exit program |

### Generate NCP target

1.  Create "NCP - Mesh Empty Target" project based on the attached board and the latest Bluetooth Mesh SDK.
2.  We need to make the DCD (device configuration data) of our NCP firmware look like soc-btmesh-switch so the reference mobile app will configure it properly.
    1. Open the ${projectname}.isc file.
    2. Remove the second element if present.
    3. Make sure the first element has the following models:
         * Configuration Server
         * Health Server
         * Generic OnOff Client
         * Light Lightness Client
         * Light CTL Client
    4. Modify the *Features Bitmask* to 0x000b, then click "Generate" button.
3.  If the NCP target needs to sleep, you need to make the changes in steps 4 and 5 below to the project. The provided example **DOES NOT** enable the sleep mode. If you don't need to enable sleep mode in the NCP target, skip to step 6.
4.  Add below code right before while(1) in main.c:

```
#if defined(_SILICON_LABS_32B_SERIES_1_CONFIG_3)
  /* xG13 devices have two RTCCs, one for the stack and another for the application.
     * The clock for RTCC needs to be enabled in application code. In xG12 RTCC init
     * is handled by the stack */
  CMU_ClockEnable(cmuClock_RTCC, true);
#endif

```

5.  Open the hal-config.h file and define the symbol *NCP_DEEP_SLEEP_ENABLED*. After that, you need to specify the wake up pin location to the symbols *NCP_WAKEUP_PORT*, *NCP_WAKEUP_PIN* and *NCP_WAKEUP_POLARITY*. The same rule applies to the symbol *NCP_HOST_WAKEUP_ENABLED* if you want the NCP target could wakeup the host.
6.  Erase the attached board, then build and program to it.

### Run the example

-   Download the attachment and extract it.
-   cd to the folder and run "make SDK_DIR=xxx", where xxx is the real directory of your BT Mesh SDK. Assuming it builds without errors.
-   The executable takes 2 parameters - serial port and baud rate. Run it as "sudo ./exe/switch /dev/ttyACM2 115200"
-   If the shell starts normally, type "h" to get usage example
-   Find a provisioner and light node to test it.
