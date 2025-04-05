
INSTALL_PREFIX         = 
CONFIG_EMBEDDED        = 0
CONFIG_IPHONE          = 0
CONFIG_IPHONE_SIMULATOR= 0
KERNEL_SYLINKS         = install_kernel_symlinks
DO_CARBON_CORE_FILES   = 

SRCROOT ?= $(shell pwd)
OBJROOT ?= $(SRCROOT)/obj
SYMROOT ?= $(SRCROOT)/sym
DSTROOT ?= $(SRCROOT)/dst

# These files in SRCROOT will get copied into /usr/include/
FILES=TargetConditionals.h AssertMacros.h

# These files in SRCROOT get copied into /usr/include/ only for the phone builds
CCFILES=ConditionalMacros.h Endian.h MacErrors.h MacTypes.h 
DEST=$(INSTALL_PREFIX)/usr/include


installhdrs: install

install: $(DSTROOT) $(KERNEL_SYLINKS) $(DO_CARBON_CORE_FILES)
	mkdir -p $(DSTROOT)/$(DEST)
	for i in $(FILES); do \
		sed -e "s/@CONFIG_EMBEDDED@/$(CONFIG_EMBEDDED)/g" \
			-e "s/@CONFIG_IPHONE_SIMULATOR@/$(CONFIG_IPHONE_SIMULATOR)/g" \
			-e "s/@CONFIG_IPHONE@/$(CONFIG_IPHONE)/g" \
			$(SRCROOT)/$$i > $(DSTROOT)/$(DEST)/$$i; \
		chmod 644 $(DSTROOT)/$(DEST)/$$i; \
	done

install_carbon_core_headers:
	mkdir -p $(DSTROOT)/$(DEST)
	for i in $(CCFILES); do \
		cp $(SRCROOT)/$$i  $(DSTROOT)/$(DEST)/$$i; \
		chmod 644 $(DSTROOT)/$(DEST)/$$i; \
	done

install_kernel_symlinks:
	mkdir -p $(DSTROOT)/$(INSTALL_PREFIX)/System/Library/Frameworks/Kernel.framework/Versions/A/Headers
	cd $(DSTROOT)/$(INSTALL_PREFIX)/System/Library/Frameworks/Kernel.framework/Versions/A/Headers && \
	ln -s ../../../../../../../usr/include/AssertMacros.h && \
	ln -s ../../../../../../../usr/include/ConditionalMacros.h && \
	ln -s ../../../../../../../usr/include/Endian.h && \
	ln -s ../../../../../../../usr/include/MacErrors.h && \
	ln -s ../../../../../../../usr/include/MacTypes.h &&  \
	ln -s ../../../../../../../usr/include/TargetConditionals.h 
	


installsrc: $(SRCROOT)
	pax -rw . $(SRCROOT)


clean:



$(SRCROOT) $(OBJROOT) $(SYMROOT) $(DSTROOT):
	mkdir -p $@


