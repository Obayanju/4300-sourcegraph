#
# deals with depends.
#
DEPFLAGS     := -M
DEPENDFILE   := .depend
ifneq ($(strip $(DIR_POSTFIX)),)
DEPENDFILE   := $(DEPENDFILE)-$(DIR_POSTFIX)
endif

# This amendment must be here, because top.mk is included before REMOTE_INC_DIR is known
ifneq ($(strip $(REMOTE_INC_DIR)),)
DEPCXXFLAGS := $(DEPCXXFLAGS) -I$(REMOTE_INC_DIR)
endif


CXX_SRC_DEPS    := ${CXX_SRC:%.cpp=$(DEPENDFILE).%.d}
REMOTE_SRC_DEPS := ${REMOTE_SRC:%.cpp=$(DEPENDFILE).%.d}

$(CXX_SRC_DEPS) : $(DEPENDFILE).%.d: $(LOCAL_SRC_DIR)/%.cpp $(BUILD_DIR)/Makefile.dep
	@echo "building $@"
	@$(SHELL) -ec '$(CXX) $(DEPFLAGS) $(DEPCXXFLAGS) $< | sed '\''s?^\($*\)\.o:?$(OBJ_BASE)/\1.o $(DEPENDFILE).\1.d : ?g'\'' > $@'
	@echo '$(OBJ_BASE)/$*.o: $(FORCE_OBJ_BASE)' >> $@
	@echo '$(OBJ_BASE)/$*.o:' >> $@
	@echo '	$$(CXX) $$(CXXFLAGS) -c $$(LOCAL_SRC_DIR)/$*.cpp -o $$@' >> $@

$(REMOTE_SRC_DEPS) : $(DEPENDFILE).%.d: $(REMOTE_SRC_DIR)/%.cpp $(BUILD_DIR)/Makefile.dep
	@echo "building $@"
	@$(SHELL) -ec '$(CXX) $(DEPFLAGS) $(DEPCXXFLAGS) $< | sed '\''s?^\($*\)\.o:?$(OBJ_BASE)/\1.o $(DEPENDFILE).\1.d : ?g'\'' > $@'
	@echo '$(OBJ_BASE)/$*.o: $(FORCE_OBJ_BASE)' >> $@
	@echo '$(OBJ_BASE)/$*.o:' >> $@
	@echo '	$$(CXX) $$(CXXFLAGS) -c $$(REMOTE_SRC_DIR)/$*.cpp -o $$@' >> $@

ifneq ($(strip $(CXX_SRC)),)
include $(CXX_SRC_DEPS)
endif
ifneq ($(strip $(REMOTE_SRC)),)
include $(REMOTE_SRC_DEPS)
endif
# Local Variables:
# mode:makefile
# End:
