SOURCES = test/runtests.cpp \
          test/fake_serial.cpp \
          test/mock_arduino.cpp \
          libraries/q_learning/StateController.cpp \
          libraries/q_learning/QLearningMachine.cpp \
          libraries/q_learning/State.cpp \
          libraries/q_learning/RestState.cpp \
          libraries/q_learning/MockState.cpp

OBJECTS := $(addsuffix .o, $(addprefix .build/, $(basename $(SOURCES))))
DEPFILES := $(subst .o,.dep, $(subst .build/,.deps/, $(OBJECTS)))
TESTCPPFLAGS = -D_TEST_ -D_INFO_ -D_DEBUG_ -D_ERROR_ -Itest -Ilibraries/q_learning -Iarduino
CPPDEPFLAGS = -MMD -MP -MF .deps/$(basename $<).dep
RUNTEST := $(if $(COMSPEC), runtest.exe, runtest)

all: runtests

.build/%.o: %.cpp
	mkdir -p .deps/$(dir $<)
	mkdir -p .build/$(dir $<)
	$(COMPILE.cpp) $(TESTCPPFLAGS) $(CPPDEPFLAGS) -o $@ $<

runtests: $(OBJECTS)
	$(CC) $(OBJECTS) -lstdc++ -o $@

clean:
	@rm -rf runtests .deps/ .build/ $(RUNTEST)

-include $(DEPFILES)
