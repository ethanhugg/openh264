CODEC_UNITTEST_SRCDIR=test
CODEC_UNITTEST_CPP_SRCS=\
	$(CODEC_UNITTEST_SRCDIR)/BaseDecoderTest.cpp\
	$(CODEC_UNITTEST_SRCDIR)/BaseEncoderTest.cpp\
	$(CODEC_UNITTEST_SRCDIR)/cpp_interface_test.cpp\
	$(CODEC_UNITTEST_SRCDIR)/DataGenerator.cpp\
	$(CODEC_UNITTEST_SRCDIR)/decode_encode_test.cpp\
	$(CODEC_UNITTEST_SRCDIR)/decoder_test.cpp\
	$(CODEC_UNITTEST_SRCDIR)/DecUT_IdctResAddPred.cpp\
	$(CODEC_UNITTEST_SRCDIR)/DecUT_IntraPrediction.cpp\
	$(CODEC_UNITTEST_SRCDIR)/encoder_test.cpp\
	$(CODEC_UNITTEST_SRCDIR)/EncUT_MemoryAlloc.cpp\
	$(CODEC_UNITTEST_SRCDIR)/EncUT_MotionEstimate.cpp\
	$(CODEC_UNITTEST_SRCDIR)/simple_test.cpp\

CODEC_UNITTEST_OBJS += $(CODEC_UNITTEST_CPP_SRCS:.cpp=.$(OBJ))

CODEC_UNITTEST_C_SRCS=\
	$(CODEC_UNITTEST_SRCDIR)/c_interface_test.c\
	$(CODEC_UNITTEST_SRCDIR)/sha1.c\

CODEC_UNITTEST_OBJS += $(CODEC_UNITTEST_C_SRCS:.c=.$(OBJ))

OBJS += $(CODEC_UNITTEST_OBJS)
$(CODEC_UNITTEST_SRCDIR)/%.$(OBJ): $(CODEC_UNITTEST_SRCDIR)/%.cpp
	$(QUIET_CXX)$(CXX) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(CODEC_UNITTEST_CFLAGS) $(CODEC_UNITTEST_INCLUDES) -c $(CXX_O) $<

$(CODEC_UNITTEST_SRCDIR)/%.$(OBJ): $(CODEC_UNITTEST_SRCDIR)/%.c
	$(QUIET_CC)$(CC) $(CFLAGS) $(INCLUDES) $(CODEC_UNITTEST_CFLAGS) $(CODEC_UNITTEST_INCLUDES) -c $(CXX_O) $<

codec_unittest$(EXEEXT): $(CODEC_UNITTEST_OBJS) $(LIBS) $(CODEC_UNITTEST_LIBS) $(CODEC_UNITTEST_DEPS)
	$(QUIET_CXX)$(CXX) $(CXX_LINK_O) $(CODEC_UNITTEST_OBJS) $(CODEC_UNITTEST_LDFLAGS) $(CODEC_UNITTEST_LIBS) $(LDFLAGS) $(LIBS)

binaries: codec_unittest$(EXEEXT)
BINARIES += codec_unittest$(EXEEXT)
