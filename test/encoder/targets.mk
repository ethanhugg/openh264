ENCODER_UNITTEST_SRCDIR=test/encoder
ENCODER_UNITTEST_CPP_SRCS=\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_EncoderMbTest.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_ExpandPic.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_ExpGolomb.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_MemoryAlloc.cpp\
	$(ENCODER_UNITTEST_SRCDIR)/EncUT_MotionEstimate.cpp\

ENCODER_UNITTEST_OBJS += $(ENCODER_UNITTEST_CPP_SRCS:.cpp=.$(OBJ))

OBJS += $(ENCODER_UNITTEST_OBJS)
$(ENCODER_UNITTEST_SRCDIR)/%.$(OBJ): $(ENCODER_UNITTEST_SRCDIR)/%.cpp
	$(QUIET_CXX)$(CXX) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(ENCODER_UNITTEST_CFLAGS) $(ENCODER_UNITTEST_INCLUDES) -c $(CXX_O) $<

