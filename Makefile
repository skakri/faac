prefix = /usr/local

DESTDIR = 

SOURCE=aac_qc.c aac_se_enc.c bitstream.c enc_tf.c encoder.c is.c mc_enc.c ms.c psych.c pulse.c tns.c transfo.c fastfft.c nok_ltp_enc.c nok_pitch.c winswitch.c rateconv.c

OBJ = $(SOURCE:.c=.o)

CC=gcc

CC_OPTS=-DHAS_ULONG -O3 -funroll-loops -finline-functions
LD_OPTS=

TARGETS=faac

all: $(TARGETS)

faac: $(OBJ) Makefile
	$(CC) $(LD_OPTS) -o faac $(OBJ) -lsndfile -lm

%.o: %.c
	$(CC) $(CC_OPTS) -c $< -o $@	

install:
	@if test -f faac; then \
	  install -d ${DESTDIR}${prefix}/bin && \
	  install faac ${DESTDIR}${prefix}/bin; \
	fi

clean:
	@rm -f *.o $(TARGETS)
