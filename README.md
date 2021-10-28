This example duplicates the functionalities of the SDK example - soc-btmesh-switch with NCP (Network Co-Processor) mode, instead of controlling the light by the push buttons on the WSTK, it implements a lightweight console, so that you can use the CLI to control the lights in the network. For more information about the ncp mode and ncp host and target, please go through [KBA_BT_1602: NCP Host Implementation and Example](https://www.silabs.com/community/wireless/bluetooth/knowledge-base.entry.html/2018/01/18/ncp_host_implementat-PEsT).

# Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

1. IDE - [Simplicity Studio 5](http://www.silabs.com/products/mcu/Pages/simplicity-studio.aspx). This is required to download the SDK and to build the required NCP firmware image.
2. Gecko SDK Suite 3.2 with Silicon Labs Bluetooth Mesh SDK 2.x installed. Tested on Gecko SDK Suite 3/.2/Bluetooth Mesh SDK 2.1.4. NOTE: This version is no longer compatible with Gecko SDK Suite 2.x/Simplicity Studio v4/Bluetooth Mesh SDK 1.x. For Bluetooth Mesh 1.x support, revert to the v1.0 tag on this repo.
3. Linux/Posix build environment (OSX, Cygwin, Raspberry Pi, etc.).
4. Bluetooth Mesh compatible Blue Gecko / Mighty Gecko device running a serial UART Bluetooth Mesh NCP (Network Co-Processor) firmware image. Bluetooth Mesh compatible devices are EFR32xG12, EFR32xG13 or EFR32xG21 (x= M, B) based. See the "To Run" section below for more details.

### Installing

This project can be built as supplied within the Blue Gecko SDK frameworks.

#### For Cygwin/OSX/Linux with SDK installed

Clone or copy the contents of this repository into the Blue Gecko SDK, into a subfolder of app/bluetooth/example_host. Commands shown here are from OSX using Gecko SDK Suite v3.2, but will be similar in Linux/Cygwin. Make sure you have the Bluetooth Mesh SDK installed within your Gecko SDK Suite.

```
$ cd /Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/gecko_sdk_suite/v3.2/app/bluetooth/example_host/
$ git clone https://github.com/silabs-KrisY/host-btmesh-switch.git
$ cd host-btmesh-switch
$ make
```

#### For Raspberry Pi

1. On the PC with the Gecko SDK installed, create a compressed file archive containing the required SDK source files (command line example here on OS X using Gecko SDK Suite v3.2).

```
$ cd Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/gecko_sdk_suite/v3.2
$ tar -cvf ble_3p2.tgz "app/bluetooth/component_host" "app/bluetooth/common_host" "platform/common/inc" "protocol/bluetooth/inc" "protocol/bluetooth/src" "app/common/util/app_log" "app/common/util/app_assert"
```

You can also create a zip archive including the same files/paths using your favorite Windows Zip tool (7zip, etc.). Make sure you preserve paths relative to the Gecko SDK root when creating the archive!

2. Transfer archive to Raspberry Pi, extract, clone, cd to the new directory, and make. Note that the SDK root directory can be specified on the make command line via the SDK_DIR parameter.

```
$ mkdir ble_3p2
$ tar -xvf ble_3p2.tgz
$ git clone https://github.com/silabs-KrisY/host-btmesh-switch.git
$ cd host-btmesh-switch
$ make SDK_DIR=..
```

If using a zip archive with preserved paths relative to the Gecko SDK root, the extraction process is as follows:
```
$ mkdir ble_3p2
$ unzip ble_3p2.zip -d ble_3p2
```

#### To Run
### Generate NCP target

1.  Create "Bluetooth Mesh - NCP Empty" project based on the attached board and the latest Bluetooth Mesh SDK.
2.  The default configuration of this project in the latest SDK (2.1.4 as of this writing) contains the models and settings needed to run this example. Just build and flash to the target.

### Run the example

-   Download the attachment and extract it.
-   cd to the folder and run "make SDK_DIR=xxx", where xxx is the real directory of your BT Mesh SDK. Assuming it builds without errors.
-   The executable takes 2 parameters - serial port and baud rate. Run it as "sudo ./exe/switch /dev/ttyACM2 115200"
-   If the shell starts normally, type "h" to get usage example
-   Find a provisioner and light node to test it.

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

## Support

I am a Field Applications Engineer for Silicon Labs, not a full time software developer, so I've created this application in my "spare time" to provide an example for Silicon Labs customers to use to bring up their hardware, do some testing, and perhaps form as the basis to extend with additional functionality. If needed, I can provide limited support for this specific software via email <<kris.young@silabs.com>>. For support on building NCP firmware images, bringing up NCP firmware, and building target firmware images using examples under Simplicity Studio, please obtain support through the [official Silicon Labs support portal](http://silabs.com/support).

## Versioning

I plan to use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/host-thermometer-client/tags). All notable changes to this project will be documented in [CHANGELOG.md](CHANGELOG.md).

## Authors

* **Kevin Fu** - *Initial work* [Kevin Fu](https://github.com/silabs-kevin)
* **Kris Young** - *Docs and Mesh 2.x Migration* - [Kris Young](https://github.com/silabs-KrisY) <<kris.young@silabs.com>>

## License

This AS-IS example project is licensed under Zlib by Silicon Laboratories Inc. See the [LICENSE.md](LICENSE.md) file for details
