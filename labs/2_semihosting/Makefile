#----------------------------------------------------------------------------------
# Commom settings
#----------------------------------------------------------------------------------
TARGET=semihosting
PRJ_ROOT=$(shell cd ../../ ; pwd)
include $(PRJ_ROOT)/conf/build.def

#----------------------------------------------------------------------------------
# Files to build
#----------------------------------------------------------------------------------
SRCS  = $(CMSIS_STARTUP_SRC) $(CMSIS_SYSTEM_SRC)
SRCS += my_utils.c semihosting.c

C_OBJS = $(patsubst %.c, %.o, $(SRCS))   # translate *.c to *.o
OBJS   = $(patsubst %.s, %.o, $(C_OBJS)) # also *.s to *.o files

OUT_OBJS = $(addprefix $(OUT_DIR)/, $(OBJS))

#----------------------------------------------------------------------------------
# Build here
#----------------------------------------------------------------------------------
$(OUT_DIR)/$(TARGET).bin: $(OUT_OBJS)
	$(TOOL_CHAIN_PREFIX)-gcc -Wl,-Map=$(OUT_DIR)/$(TARGET).map,-T$(TARGET).ld -nostartfiles \
		$(CFLAGS) $(OUT_OBJS) -o $(OUT_DIR)/$(TARGET).elf
	$(TOOL_CHAIN_PREFIX)-objcopy -Obinary $(OUT_DIR)/$(TARGET).elf $@
	$(TOOL_CHAIN_PREFIX)-objdump -S $(OUT_DIR)/$(TARGET).elf > $(OUT_DIR)/$(TARGET).list

$(OUT_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(TOOL_CHAIN_PREFIX)-gcc -c $(CFLAGS) $< -o $@

$(OUT_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(TOOL_CHAIN_PREFIX)-gcc -c $(CFLAGS) $< -o $@

flash: $(OUT_DIR)/$(TARGET).bin
	openocd -f interface/stlink-v2.cfg  \
            -f target/stm32f4x.cfg      \
            -c "init"                   \
            -c "reset init"             \
            -c "stm32f2x unlock 0"      \
            -c "flash probe 0"          \
            -c "flash info 0"           \
            -c "flash write_image erase $< 0x8000000" \
            -c "reset run" -c shutdown

run: $(OUT_DIR)/$(TARGET).bin
	openocd -f interface/stlink-v2.cfg  \
            -f target/stm32f4x.cfg      \
            -c "init"                   \
            -c "reset init"             \
            -c "arm semihosting enable" \
            -c "reset run"
clean:
	rm -fr $(OUT_DIR) gdb.txt
