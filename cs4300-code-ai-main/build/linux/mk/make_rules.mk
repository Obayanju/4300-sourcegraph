MAKE_RULES_MK := ../../../cs4300-code-ai-main/build/linux/mk/make_rules.mk
RULES_MK := ../../../cs4300-code-ai-main/build/linux/mk/rules.mk
DEP_MK := ../../../cs4300-code-ai-main/build/linux/mk/dep.mk
TOP_MK := ../../../cs4300-code-ai-main/build/linux/mk/top.mk
CONFIG_IN_MK := ../../../cs4300-code-ai-main/build/linux/mk/config_in.mk
CONFIGURE_RULES_MK := ../../../cs4300-code-ai-main/build/linux/mk/configure_rules.mk

make: Makefile.make_rules Makefile.rules Makefile.dep Makefile.top Makefile.config.in Makefile.config Makefile.configure_rules

$(MAKE_CONFIG): $(MAKE_CONFIG_IN)
	cp $^ $@

ifneq ($(wildcard $(MAKE_RULES_MK)),) 
Makefile.make_rules: $(MAKE_RULES_MK)
	cp $^ $@
endif
ifneq ($(wildcard $(RULES_MK)),) 
Makefile.rules: $(RULES_MK)
	cp $^ $@
endif
ifneq ($(wildcard $(DEP_MK)),) 
Makefile.dep: $(DEP_MK)
	cp $^ $@
endif
ifneq ($(wildcard $(TOP_MK)),) 
Makefile.top: $(TOP_MK)
	cp $^ $@
endif
ifneq ($(wildcard $(CONFIG_IN_MK)),) 
Makefile.config.in: $(CONFIG_IN_MK)
	cp $^ $@
endif
ifneq ($(wildcard $(CONFIGURE_RULES_MK)),) 
Makefile.configure_rules: $(CONFIGURE_RULES_MK)
	cp $^ $@
endif

# Local Variables:
# mode:makefile
# End:
