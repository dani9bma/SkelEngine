# Generated by Sharpmake -- Do not edit !
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  CXX        = g++
  AR         = ar
  OBJDIR     = ../../bin/imgui
  TARGETDIR  = libs
  TARGET     = $(TARGETDIR)/libimgui.lib
  DEFINES   += 
  INCLUDES  += -Isrc
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) -g -Wall 
  CXXFLAGS  += $(CFLAGS) -fno-exceptions -fno-rtti 
  LDFLAGS   += 
  LIBS      +=  
  RESFLAGS  += $(DEFINES) $(INCLUDES)
  LDDEPS    += 
  LINKCMD    = $(AR) -rcs $(TARGET) $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
  define POSTFILECMDS
  endef
endif

ifeq ($(config),debug)
  CXX        = g++
  AR         = ar
  OBJDIR     = ../../bin/imgui
  TARGETDIR  = libs
  TARGET     = $(TARGETDIR)/libimgui.lib
  DEFINES   += 
  INCLUDES  += -Isrc
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) -g -Wall 
  CXXFLAGS  += $(CFLAGS) -fno-exceptions -fno-rtti 
  LDFLAGS   += 
  LIBS      +=  
  RESFLAGS  += $(DEFINES) $(INCLUDES)
  LDDEPS    += 
  LINKCMD    = $(AR) -rcs $(TARGET) $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
  define POSTFILECMDS
  endef
endif

ifeq ($(config),release)
  CXX        = g++
  AR         = ar
  OBJDIR     = ../../bin/imgui
  TARGETDIR  = libs
  TARGET     = $(TARGETDIR)/libimgui.lib
  DEFINES   += 
  INCLUDES  += -Isrc
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) -g -O3 -Wall 
  CXXFLAGS  += $(CFLAGS) -fno-exceptions -fno-rtti 
  LDFLAGS   += 
  LIBS      +=  
  RESFLAGS  += $(DEFINES) $(INCLUDES)
  LDDEPS    += 
  LINKCMD    = $(AR) -rcs $(TARGET) $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
  define POSTFILECMDS
  endef
endif

ifeq ($(config),release)
  CXX        = g++
  AR         = ar
  OBJDIR     = ../../bin/imgui
  TARGETDIR  = libs
  TARGET     = $(TARGETDIR)/libimgui.lib
  DEFINES   += 
  INCLUDES  += -Isrc
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) -g -O3 -Wall 
  CXXFLAGS  += $(CFLAGS) -fno-exceptions -fno-rtti 
  LDFLAGS   += 
  LIBS      +=  
  RESFLAGS  += $(DEFINES) $(INCLUDES)
  LDDEPS    += 
  LINKCMD    = $(AR) -rcs $(TARGET) $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
  define POSTFILECMDS
  endef
endif

ifeq ($(config),debug)
  OBJECTS += $(OBJDIR)/imgui.o
  OBJECTS += $(OBJDIR)/imgui_demo.o
  OBJECTS += $(OBJDIR)/imgui_draw.o
  OBJECTS += $(OBJDIR)/imgui_impl_dx11.o
  OBJECTS += $(OBJDIR)/imgui_impl_win32.o

endif

ifeq ($(config),debug)
  OBJECTS += $(OBJDIR)/imgui.o
  OBJECTS += $(OBJDIR)/imgui_demo.o
  OBJECTS += $(OBJDIR)/imgui_draw.o
  OBJECTS += $(OBJDIR)/imgui_impl_dx11.o
  OBJECTS += $(OBJDIR)/imgui_impl_win32.o

endif

ifeq ($(config),release)
  OBJECTS += $(OBJDIR)/imgui.o
  OBJECTS += $(OBJDIR)/imgui_demo.o
  OBJECTS += $(OBJDIR)/imgui_draw.o
  OBJECTS += $(OBJDIR)/imgui_impl_dx11.o
  OBJECTS += $(OBJDIR)/imgui_impl_win32.o

endif

ifeq ($(config),release)
  OBJECTS += $(OBJDIR)/imgui.o
  OBJECTS += $(OBJDIR)/imgui_demo.o
  OBJECTS += $(OBJDIR)/imgui_draw.o
  OBJECTS += $(OBJDIR)/imgui_impl_dx11.o
  OBJECTS += $(OBJDIR)/imgui_impl_win32.o

endif

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES) | $(TARGETDIR)
	@echo Linking ImGUI
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) if not exist $(subst /,\\,$(TARGETDIR)) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) if not exist $(subst /,\\,$(OBJDIR)) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning ImGUI
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)
endif

$(OBJDIR)/imgui.o: src/ImGUI/imgui.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/imgui_demo.o: src/ImGUI/imgui_demo.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/imgui_draw.o: src/ImGUI/imgui_draw.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/imgui_impl_dx11.o: src/ImGUI/imgui_impl_dx11.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/imgui_impl_win32.o: src/ImGUI/imgui_impl_win32.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

-include $(OBJECTS:%.o=%.d)
