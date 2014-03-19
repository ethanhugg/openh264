/*!
 * \copy
 *     Copyright (c)  2013, Cisco Systems
 *     All rights reserved.
 *
 *     Redistribution and use in source and binary forms, with or without
 *     modification, are permitted provided that the following conditions
 *     are met:
 *
 *        * Redistributions of source code must retain the above copyright
 *          notice, this list of conditions and the following disclaimer.
 *
 *        * Redistributions in binary form must reproduce the above copyright
 *          notice, this list of conditions and the following disclaimer in
 *          the documentation and/or other materials provided with the
 *          distribution.
 *
 *     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *     "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *     LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *     FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *     COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *     INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *     BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *     CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *     LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *     ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *     POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef WELS_VIDEO_CODEC_APPLICATION_DEFINITION_H__
#define WELS_VIDEO_CODEC_APPLICATION_DEFINITION_H__

////////////////Data and /or structures introduced in Cisco OpenH264 application////////////////

/* Constants */
#define MAX_TEMPORAL_LAYER_NUM		4
#define MAX_SPATIAL_LAYER_NUM		4
#define MAX_QUALITY_LAYER_NUM		4

#define MAX_LAYER_NUM_OF_FRAME		128
#define MAX_NAL_UNITS_IN_LAYER		128	// predetermined here, adjust it later if need

#define MAX_RTP_PAYLOAD_LEN		1000
#define AVERAGE_RTP_PAYLOAD_LEN		800


#define SAVED_NALUNIT_NUM_TMP		( (MAX_SPATIAL_LAYER_NUM*MAX_QUALITY_LAYER_NUM) + 1 + MAX_SPATIAL_LAYER_NUM ) //SPS/PPS + SEI/SSEI + PADDING_NAL
#define MAX_SLICES_NUM_TMP			( ( MAX_NAL_UNITS_IN_LAYER - SAVED_NALUNIT_NUM_TMP ) / 3 )

typedef enum {
  /* Errors derived from bitstream parsing */
  dsErrorFree			= 0x00,	/* Bitstream error-free */
  dsFramePending		= 0x01,	/* Need more throughput to generate a frame output,  */
  dsRefLost			= 0x02,	/* layer lost at reference frame with temporal id 0  */
  dsBitstreamError	= 0x04,	/* Error bitstreams(maybe broken internal frame) the decoder cared */
  dsDepLayerLost		= 0x08,	/* Dependented layer is ever lost */
  dsNoParamSets		= 0x10, /* No parameter set NALs involved */

  /* Errors derived from logic level */
  dsInvalidArgument	= 0x1000,	/* Invalid argument specified */
  dsInitialOptExpected = 0x2000,	/* Initializing operation is expected */
  dsOutOfMemory		= 0x4000,	/* Out of memory due to new request */
  /* ANY OTHERS? */
  dsDstBufNeedExpand	= 0x8000	/* Actual picture size exceeds size of dst pBuffer feed in decoder, so need expand its size */

} DECODING_STATE;

/* Option types introduced in SVC encoder application */
typedef enum {
  ENCODER_OPTION_DATAFORMAT = 0,
  ENCODER_OPTION_IDR_INTERVAL,
  ENCODER_OPTION_SVC_ENCODE_PARAM_BASE,
  ENCODER_OPTION_SVC_ENCODE_PARAM_EXT,
  ENCODER_OPTION_FRAME_RATE,
  ENCODER_OPTION_BITRATE,
  ENCODER_OPTION_INTER_SPATIAL_PRED,
  ENCODER_OPTION_RC_MODE,
  ENCODER_PADDING_PADDING,

  ENCODER_LTR_RECOVERY_REQUEST,
  ENCODER_LTR_MARKING_FEEDBACK,
  ENCOCER_LTR_MARKING_PERIOD,
  ENCODER_OPTION_LTR,

  ENCODER_OPTION_ENABLE_SSEI,               //disable SSEI: true--disable ssei; false--enable ssei
  ENCODER_OPTION_ENABLE_PREFIX_NAL_ADDING,   //enable prefix: true--enable prefix; false--disable prefix
  ENCODER_OPTION_ENABLE_SPS_PPS_ID_ADDITION, //disable pSps/pPps id addition: true--disable pSps/pPps id; false--enable pSps/pPps id addistion

  ENCODER_OPTION_CURRENT_PATH,
  ENCODER_OPTION_DUMP_FILE,
  ENCODER_OPTION_TRACE_LEVEL
} ENCODER_OPTION;

/* Option types introduced in decoder application */
typedef enum {
  DECODER_OPTION_DATAFORMAT = 0,	/* Set color space of decoding output frame */
  DECODER_OPTION_END_OF_STREAM,	/* Indicate bitstream of the final frame to be decoded */
  DECODER_OPTION_VCL_NAL,        //feedback whether or not have VCL NAL in current AU for application layer
  DECODER_OPTION_TEMPORAL_ID,      //feedback temporal id for application layer
  DECODER_OPTION_FRAME_NUM,	//feedback current decoded frame number
  DECODER_OPTION_IDR_PIC_ID,	// feedback current frame belong to which IDR period
  DECODER_OPTION_LTR_MARKING_FLAG,	// feedback wether current frame mark a LTR
  DECODER_OPTION_LTR_MARKED_FRAME_NUM,	// feedback frame num marked by current Frame

} DECODER_OPTION;
typedef enum { //feedback that whether or not have VCL NAL in current AU
  FEEDBACK_NON_VCL_NAL = 0,
  FEEDBACK_VCL_NAL,
  FEEDBACK_UNKNOWN_NAL
} FEEDBACK_VCL_NAL_IN_AU;

/* Type of layer being encoded */
typedef enum {
  NON_VIDEO_CODING_LAYER = 0,
  VIDEO_CODING_LAYER = 1
} LAYER_TYPE;

//enumerate the type of video bitstream which is provided to decoder
typedef enum {
  VIDEO_BITSTREAM_AVC               = 0,
  VIDEO_BITSTREAM_SVC               = 1,
  VIDEO_BITSTREAM_DEFAULT           = VIDEO_BITSTREAM_SVC,
} VIDEO_BITSTREAM_TYPE;

typedef enum {
  NO_RECOVERY_REQUSET  = 0,
  LTR_RECOVERY_REQUEST = 1,
  IDR_RECOVERY_REQUEST = 2,
  NO_LTR_MARKING_FEEDBACK = 3,
  LTR_MARKING_SUCCESS = 4,
  LTR_MARKING_FAILED = 5,
} KEY_FRAME_REQUEST_TYPE;

typedef struct {
  unsigned int uiFeedbackType; //IDR request or LTR recovery request
  unsigned int uiIDRPicId; // distinguish request from different IDR
  int		  iLastCorrectFrameNum;
  int		  iCurrentFrameNum; //specify current decoder frame_num.
} SLTRRecoverRequest;

typedef struct {
  unsigned int  uiFeedbackType; //mark failed or successful
  unsigned int  uiIDRPicId; // distinguish request from different IDR
  int			  iLTRFrameNum; //specify current decoder frame_num
} SLTRMarkingFeedback;

typedef struct {
    unsigned int
    uiSliceMbNum[MAX_SLICES_NUM_TMP];  //here we use a tmp fixed value since MAX_SLICES_NUM is not defined here and its definition may be changed;
    unsigned int		uiSliceNum;
    unsigned int		uiSliceSizeConstraint;
  } SSliceArgument;//not all the elements in this argument will be used, how it will be used depends on uiSliceMode; see below

typedef enum {
  SM_SINGLE_SLICE         = 0, //	| SliceNum==1
  SM_FIXEDSLCNUM_SLICE    = 1, //	| according to SliceNum		| Enabled dynamic slicing for multi-thread
  SM_RASTER_SLICE         = 2, //	| according to SlicesAssign	| Need input of MB numbers each slice. In addition, if other constraint in SSliceArgument is presented, need to follow the constraints. Typically if MB num and slice size are both constrained, re-encoding may be involved.
  SM_ROWMB_SLICE          = 3, //	| according to PictureMBHeight	| Typical of single row of mbs each slice?+ slice size constraint which including re-encoding
  SM_DYN_SLICE            = 4, //	| according to SliceSize	| Dynamic slicing (have no idea about slice_nums until encoding current frame)
  SM_AUTO_SLICE           = 5, //   | according to thread number
  SM_RESERVED             = 6
} SliceModeEnum;

typedef struct {
  SliceModeEnum uiSliceMode; //by default, uiSliceMode will be SM_SINGLE_SLICE
  SSliceArgument sSliceArgument;
} SSliceConfig;

typedef struct {
  int	iVideoWidth;		// video size in cx specified for a layer
  int	iVideoHeight;		// video size in cy specified for a layer
  float	fFrameRate;		// frame rate specified for a layer
  int	iSpatialBitrate;	// target bitrate for a spatial layer
  unsigned int	uiProfileIdc;	// value of profile IDC (0 for auto-detection)
  int    iDLayerQp;

  SSliceConfig sSliceCfg;
} SSpatialLayerConfig;

/* SVC Encoding Parameters */
typedef struct TagEncParamBase{

  int       iUsageType;	//enable_screen_content_signal;// 0: //camera video signal; 1: screen content signal;
  int		iInputCsp;	// color space of input sequence

  int		iPicWidth;			// width of picture in samples
  int		iPicHeight;			// height of picture in samples
  int		iTargetBitrate;		// target bitrate desired
  int       iRCMode;                 // RC mode
  float	    fMaxFrameRate;			// input maximal frame rate

} SEncParamBase, *PEncParamBase;


typedef struct TagEncParamExt
{
  int       iUsageType;	//application type;// 0: //camera video signal; 1: screen content signal;
  int		iInputCsp;	// color space of input sequence

  int		iPicWidth;			// width of picture in samples
  int		iPicHeight;			// height of picture in samples
  int		iTargetBitrate;		// target bitrate desired
  int       iRCMode;                 // RC mode
  float	    fMaxFrameRate;			// input maximal frame rate

  int		iTemporalLayerNum;	// layer number at temporal level
  int		iSpatialLayerNum;	// layer number at spatial level
  SSpatialLayerConfig sSpatialLayers[MAX_SPATIAL_LAYER_NUM];

  unsigned int		uiIntraPeriod;		// period of Intra frame
  int		        iNumRefFrame;		// number of reference frame used
  unsigned int	    uiFrameToBeCoded;	// frame to be encoded (at input frame rate)
  bool    bEnableSpsPpsIdAddition;
  bool    bPrefixNalAddingCtrl;
  bool	  bEnableSSEI;
  int      iPaddingFlag;            // 0:disable padding;1:padding
  int      iEtropyCodingModeFlag;

  /* rc control */
  bool    bEnableRc;
  bool    bEnableFrameSkip; // allow skipping frames to keep the bitrate within limits
  int     iMaxQp;
  int     iMinQp;

  /*LTR settings*/
  bool     bEnableLongTermReference; // 0: on, 1: off
  int	   iLTRRefNum;
  unsigned int      iLtrMarkPeriod;

  /* multi-thread settings*/
  unsigned short		iMultipleThreadIdc;		// 1	# 0: auto(dynamic imp. internal encoder); 1: multiple threads imp. disabled; > 1: count number of threads;

   /* Deblocking loop filter */
  int		iLoopFilterDisableIdc;	// 0: on, 1: off, 2: on except for slice boundaries
  int		iLoopFilterAlphaC0Offset;// AlphaOffset: valid range [-6, 6], default 0
  int		iLoopFilterBetaOffset;	// BetaOffset:	valid range [-6, 6], default 0
  /*pre-processing feature*/
  bool    bEnableDenoise;	    // denoise control
  bool    bEnableBackgroundDetection;// background detection control //VAA_BACKGROUND_DETECTION //BGD cmd
  bool    bEnableAdaptiveQuant; // adaptive quantization control
  bool	  bEnableFrameCroppingFlag;// enable frame cropping flag: TRUE always in application
  bool    bEnableSceneChangeDetect;
}SEncParamExt;

//Define a new struct to show the property of video bitstream.
typedef struct {
  unsigned int          size; //size of the struct
  VIDEO_BITSTREAM_TYPE  eVideoBsType;
} SVideoProperty;

/* SVC Decoding Parameters, reserved here and potential applicable in the future */
typedef struct TagSVCDecodingParam {
  char*		pFileNameRestructed;	// File name of restructed frame used for PSNR calculation based debug

  int				iOutputColorFormat;	// color space format to be outputed, EVideoFormatType specified in codec_def.h
  unsigned int	uiCpuLoad;		// CPU load
  unsigned char	uiTargetDqLayer;	// Setting target dq layer id

  unsigned char	uiEcActiveFlag;		// Whether active error concealment feature in decoder

  SVideoProperty   sVideoProperty;
} SDecodingParam, *PDecodingParam;

/* Bitstream inforamtion of a layer being encoded */
typedef struct {
  unsigned char uiTemporalId;
  unsigned char uiSpatialId;
  unsigned char uiQualityId;

  unsigned char uiPriorityId; //ignore it currently

  unsigned char uiLayerType;

  int	iNalCount;					// Count number of NAL coded already
  int	iNalLengthInByte[MAX_NAL_UNITS_IN_LAYER];	// Length of NAL size in byte from 0 to iNalCount-1
  unsigned char*	pBsBuf;		// Buffer of bitstream contained
} SLayerBSInfo, *PLayerBSInfo;


typedef struct {
  int		iTemporalId;	// Temporal ID
  unsigned char	uiFrameType;

  int		iLayerNum;
  SLayerBSInfo	sLayerInfo[MAX_LAYER_NUM_OF_FRAME];

  int eOutputFrameType;
  long long uiTimeStamp;
} SFrameBSInfo, *PFrameBSInfo;

typedef struct Source_Picture_s {
  int		    iColorFormat;	// color space type
  int  		iStride[4];		// stride for each plane pData
  unsigned char*  pData[4];		// plane pData
  int  		iPicWidth;				// luma picture width in x coordinate
  int 		iPicHeight;				// luma picture height in y coordinate
  long long uiTimeStamp;
} SSourcePicture;

typedef struct Dump_Layer_s{
	int iLayer;
	char *pFileName;
}SDumpLayer;
#endif//WELS_VIDEO_CODEC_APPLICATION_DEFINITION_H__
