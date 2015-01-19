ENCODER_UNITTEST_SRCDIR=test/encoder
ENCODER_UNITTEST_CPP_SRCS=\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_DecodeMbAux.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_EncoderExt.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_EncoderMb.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_EncoderMbAux.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_ExpGolomb.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_GetIntraPredictor.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_InterfaceTest.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_MBCopy.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_MemoryAlloc.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_MemoryZero.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_MotionEstimate.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_ParameterSetStrategy.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_Reconstruct.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_Sample.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_SVC_me.cpp\

ENCODER_UNITTEST_OBJS += $(ENCODER_UNITTEST_CPP_SRCS:.cpp=.$(OBJ))

OBJS += $(ENCODER_UNITTEST_OBJS)

$(ENCODER_UNITTEST_SRCDIR)/%.$(OBJ): $(ENCODER_UNITTEST_SRCDIR)/%.cpp
	$(QUIET_CXX)$(CXX) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(ENCODER_UNITTEST_CFLAGS) $(ENCODER_UNITTEST_INCLUDES) -c $(CXX_O) $<

