#----------------------------------------------------------------------------------
# Commom settings
#----------------------------------------------------------------------------------
TARGET=led
PRJ_ROOT=../..
include $(PRJ_ROOT)/conf/build.def

#----------------------------------------------------------------------------------
# Files to build
#----------------------------------------------------------------------------------

SRCS  = $(CMSIS_STARTUP_SRC) $(CMSIS_SYSTEM_SRC)
SRCS += $(STM_DIR)/src/stm32f4xx_gpio.c
SRCS += $(STM_DIR)/src/stm32f4xx_rcc.c
SRCS += led.c

C_OBJS = $(patsubst %.c, %.o, $(SRCS))   # translate *.c to *.o
OBJS   = $(patsubst %.s, %.o, $(C_OBJS)) # also *.s to *.o files

OUT_OBJS = $(addprefix $(OUT_DIR)/, $(OBJS))


#----------------------------------------------------------------------------------
# Build here
#----------------------------------------------------------------------------------
$(OUT_DIR)/$(TARGET).bin: $(OUT_OBJS)
	$(TOOL_CHAIN_PREFIX)-gcc -Wl,-Map=$(OUT_DIR)/$(TARGET).map,-T$(TARGET).ld -nostartfiles \
		$(CFLAGS) $(OUT_OBJS) $(ROOTFS_OBJ) -o $(OUT_DIR)/$(TARGET).elf
	$(TOOL_CHAIN_PREFIX)-objcopy -Obinary $(OUT_DIR)/$(TARGET).elf $@
	$(TOOL_CHAIN_PREFIX)-objdump -S $(OUT_DIR)/$(TARGET).elf > $(OUT_DIR)/$(TARGET).list
	@echo $(SRCS)

$(OUT_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(TOOL_CHAIN_PREFIX)-gcc -c $(CFLAGS) $< -o $@

$(OUT_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(TOOL_CHAIN_PREFIX)-gcc -c $(CFLAGS) $< -o $@

clean:
	rm -fr $(OUT_DIR) gdb.txt
