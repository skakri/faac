/*
 *	Function prototypes for AAC encoder
 *
 *	Copyright (c) 1999 M. Bakker
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/**************************************************************************
  Version Control Information			Method: CVS
  Identifiers:
  $Revision: 1.19 $
  $Date: 2000/10/05 08:39:02 $ (check in)
  $Author: menno $
  *************************************************************************/

#include <stdio.h>
#include <sndfile.h>

typedef struct RCBufStruct RCBuf;	/* buffer handle */

#define PROFILE                 1
#define HEADER_TYPE             2
#define MS_STEREO               3
#define IS_STEREO               4
#define BITRATE                 5
#define CUT_OFF                 6
#define OUT_SAMPLING_RATE       7
#define RAW_AUDIO               8
#define TNS                     9
#define LTP                     10
#define PNS                     11
#define IN_SAMPLING_RATE        12
#define NUMBER_OF_CHANNELS      13
#define LFE_PRESENT             14

#define MAIN_PROFILE 0
#define LOW_PROFILE 1

#define NO_HEADER	0
#define ADIF_HEADER     1
#define ADTS_HEADER     2

#define NO_MS           -1
#define FORCE_MS        1
#define SWITCHING_MS    0

#define USE_TNS         1
#define NO_TNS          0

#define USE_LTP         1
#define NO_LTP          0

#define USE_LFE         1
#define NO_LFE          0

#define USE_PNS         1
#define NO_PNS          0

#define USE_RAW_AUDIO   1
#define NO_RAW_AUDIO    0

#define FNO_ERROR 0
#define FERROR 1
#define F_FINISH 2


typedef struct {
	int DLLMajorVersion; // These 2 values should always be checked, because the DLL
	int DLLMinorVersion; // interface can change from version to version.
	int MajorVersion;
	int MinorVersion;
	char HomePage[255];
} faacVersion;

// This structure is for AAC stream object
typedef struct {
	long total_bits;
	long frames;
	long cur_frame;
	int is_first_frame;
	int channels;
	int out_sampling_rate;
	int in_sampling_rate;
	int frame_bits;
	int available_bits;
	int header_type;
	int use_MS;
	int use_TNS;
	int use_LTP;
	int use_PNS;
	int profile;
	double **inputBuffer;
	RCBuf *rc_buf;
	int rc_needed;
	int savedSize;
	float saved[2048];
	int cut_off;
	int bit_rate;
	int raw_audio;
	SNDFILE *in_file;
	FILE *out_file;
	unsigned char *bitBuffer;
	int bitBufferSize;
	short *sampleBuffer;
	int samplesToRead;
	int lfePresent;
} faacAACStream;

#ifndef FAAC_DLL

int faac_EncodeInit(faacAACStream *as, char *in_file, char *out_file);
int faac_EncodeFrame(faacAACStream *as);
int faac_BlockEncodeFrame(faacAACStream *as, short *input_samples, int Samples);
void faac_EncodeFree(faacAACStream *as);
faacVersion *faac_Version(void);
void faac_InitParams(faacAACStream *as);
void faac_SetParam(faacAACStream *as, int param, int value);

#else

__declspec(dllexport) int faac_EncodeInit(faacAACStream *as, char *in_file, char *out_file);
__declspec(dllexport) int faac_EncodeFrame(faacAACStream *as);
__declspec(dllexport) int faac_BlockEncodeFrame(faacAACStream *as, short *input_samples, int Samples);
__declspec(dllexport) void faac_EncodeFree(faacAACStream *as);
__declspec(dllexport) faacVersion *faac_Version(void);
__declspec(dllexport) void faac_InitParams(faacAACStream *as);
__declspec(dllexport) void faac_SetParam(faacAACStream *as, int param, int value);

#endif

