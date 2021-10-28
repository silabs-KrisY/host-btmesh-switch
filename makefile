################################################################################
# General project settings                                                     #
################################################################################

PROJECTNAME = host-btmesh-switch
SDK_DIR = ../../../..


################################################################################
# Components                                                                   #
#                                                                              #
# After setting up the toolchain, components can contribute to the project by  #
# appending items to the project variables like INCLUDEPATHS or C_SRC.         #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/toolchain.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_log.mk
include $(SDK_DIR)/app/bluetooth/component_host/app_assert.mk
include $(SDK_DIR)/app/bluetooth/component_host/ncp_host_btmesh.mk


################################################################################
# Include paths                                                                #
################################################################################

override INCLUDEPATHS += . \
$(SDK_DIR)/app/bluetooth/common_host/app_signal \
$(SDK_DIR)/app/bluetooth/common_host/system \
$(SDK_DIR)/platform/common/inc \
$(SDK_DIR)/protocol/bluetooth/inc


################################################################################
# Input files                                                                  #
################################################################################

override C_SRC += \
$(SDK_DIR)/app/bluetooth/common_host/app_signal/app_signal_$(OS).c \
$(SDK_DIR)/app/bluetooth/common_host/system/system.c \
$(SDK_DIR)/app/bluetooth/common_host/system/sl_btmesh.c \
sl_btmesh_lib.c \
$(SDK_DIR)/protocol/bluetooth/src/sl_btmesh_serdeser.c \
app.c \
main.c


################################################################################
# Target rules                                                                 #
################################################################################

include $(SDK_DIR)/app/bluetooth/component_host/targets.mk
