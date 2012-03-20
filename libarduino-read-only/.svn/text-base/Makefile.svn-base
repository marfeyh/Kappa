# AVR Makefile

# what do you want to call your binary
PROG=avr-arduino

# please uncomment the CPU that is used on your arduino
CPU=atmega328p
#CPU=atmega168

# please uncomment the speed that corresponds to your arduino (normally 16MHz)
F_CPU=16000000
#F_CPU=8000000

#############################################################################
# no additional config needed below (except perpapse the 'make install')
#############################################################################

CFLAGS= -g -Os -Wall -Wstrict-prototypes -Wa,-ahlms=$(PROG).lst -mmcu=$(CPU) -DF_CPU=$(F_CPU)

LFLAGS= -Wl,-Map=$(PROG).map,--cref -mmcu=$(CPU) -lm
# use LFLAGS below if you need to printf floating point numbers
#LFLAGS= -Wl,-u,vfprintf,-Map=$(PROG).map,--cref -mmcu=$(CPU) -lprintf_min -lm
INCL = libarduino.h irkeys.h timercountercalcs.h
SRC = main.c libarduino.c
OBJ = $(SRC:.c=.o)

# default target when "make" is run w/o arguments
all: $(PROG).rom

# compile .c into .o
%.o: %.c
	avr-gcc -c $(CFLAGS) -I. $*.c
	
# link up sample.o and timer.o into sample.elf
$(PROG).elf: $(OBJ)
	avr-gcc $(OBJ) $(LFLAGS) -o $(PROG).elf

$(OBJ): $(INCL)

# copy ROM (FLASH) object out of sample.elf into sample.rom
$(PROG).rom: $(PROG).elf
	avr-objcopy -O srec $(PROG).elf $(PROG).rom
	./checksize $(PROG).elf

# command to program chip (optional) (invoked by running "make install")
install:
	# SparkFun pocket ISP programmer
	# avrdude -p atmega168 -c usbtiny -U flash:w:$(PROG).rom 
	# atmega328 based Duemilanove
	 avrdude -p m328p -P /dev/ttyUSB0 -c stk500v1 -b 57600 -F -u -U flash:w:$(PROG).rom
	# atmega168 based Diecimila
	# avrdude -p m328p -P /dev/ttyUSB0 -c stk500v1 -b 19200 -F -u -U flash:w:$(PROG).rom

# reprogram the fuses for the right clock source
fuse:
	avrdude -p atmega168 -c stk200 -U lfuse:w:0x62:m

# command to clean up junk (no source files) (invoked by "make clean")
clean:
	rm -f *.o *.rom *.elf *.map *~ *.lst

