###############################################################################
# $URL: http://svn/svn/VAPSXT178/branches/XT/4.1/VAPSXT_DIR/src/Examples/UserIntegration/C/make/makefile.mak $
#
# Desc: Make file for CApplication
#
# Version: $Revision: 44818 $
#
# Last Revision $Author: mdosogne $
#
# Last Revision $Date: 2015-02-04 17:13:14 -0500 (Wed, 04 Feb 2015) $
#
# IMPORTANT NOTICE: This software program ("Software") including the source
# code is a confidential and/or proprietary product of Presagis Canada Inc.
# and/or its subsidiaries and affiliated companies. ("Presagis") and is
# protected by copyright laws. The use of the Software is subject to the
# terms of the Presagis Software License Agreement.
#
# (c) Copyright 2008 - 2015, Presagis Canada Inc. All Rights Reserved.
#
# AVIS IMPORTANT: Ce logiciel incluant le code source est de l'information
# confidentielle et/ou propriete de Presagis Canada Inc. et/ou ses filiales
# et compagnies affiliees ("Presagis") et est protege par les lois sur le
# droit d'auteur. L'utilisation de ce logiciel est sujet aux termes d'une
# licence de Presagis.
#
# (c) Copyright 2008 - 2015, Presagis Canada Inc. Tous Droits Reserves.
#
###############################################################################

include $(VAPSXT_ENV)

###############################################################################
COMPONENT_NAME = CApplication

APPLICATION = $(COMPONENT_NAME)$(EXE_EXT)

ALL_C = \
	CSampleMain.c 

ALL_LIBS = \
	$(VAPSXT_LIBS_DIR)$(DIR_SEP)vxtRTCUserIntegration$(LIB_SUFFIX)$(LIB_EXT) \
	$(VAPSXT_LIBS_DIR)$(DIR_SEP)vxtRTUserIntegration$(LIB_SUFFIX)$(LIB_EXT) \
	$(VAPSXT_LIBS_DIR)$(DIR_SEP)vxtRTGenericIntegration$(LIB_SUFFIX)$(LIB_EXT) \
	$(USER_INTEGRATION_APPLICATION_PATH)$(DIR_SEP)$(USER_INTEGRATION_APPLICATION_NAME)_$(TARGET_NAME)$(LIB_SUFFIX)$(LIB_EXT) \
	$(XTCORE_LIBS) \
	$(DEFAULT_LIBS) \
	$(USER_LIBS) \
	$(PLAT_LIBS) \
	$(GENERICMODE_USER_OBJS)

# Customize this path
SOURCE_PATH = $(SRC_DIR)$(DIR_SEP)Examples$(DIR_SEP)UserIntegration$(DIR_SEP)C

HEADER_PATH = \
	$(INCLUDE_DIR_COPTION)$(SOURCE_PATH) \
	$(INCLUDE_DIR_COPTION)$(OSPORT_DIR)$(DIR_SEP)include \
	$(INCLUDE_DIR_COPTION)$(DISPLAYPORT_DIR)$(DIR_SEP)include \
	$(INCLUDE_DIR_COPTION)$(SRC_DIR)$(DIR_SEP)Main$(DIR_SEP)Default$(DIR_SEP)Utils \
	$(INCLUDE_DIR_COPTION)$(USER_INTEGRATION_APPLICATION_PATH)

###############################################################################

ALL_OBJS_WITH_PATH = $(patsubst %.c, $(OBJS_DEST_DIR)$(OBJ_DIR_SEP)%$(OBJ_EXT), $(ALL_C))

OBJS_DEST_DIR = $(INT_DIR)$(COMPONENT_NAME)

$(APPLICATION): $(ALL_OBJS_WITH_PATH)
	$(LD) $(LDOPTIONS) $(ALL_OBJS_WITH_PATH) $(ALL_LIBS) $(LD_DIR_OPTION)$(LD_DEST_DIR)$@

$(OBJS_DEST_DIR)$(OBJ_DIR_SEP)%$(OBJ_EXT) : $(SOURCE_PATH)$(DIR_SEP)%.c
	$(CPLUSPLUS) $(CFLAGS) $(HEADER_PATH) $< $(if $(INSERT_SPACE_CONDITION), $(OBJ_DIR_COPTION) $@, $(OBJ_DIR_COPTION)$@) $(if $(PDB_DIR_COPTION), $(PDB_DIR_COPTION)$(OBJS_DEST_DIR)$(OBJ_DIR_SEP)$*$(PDB_EXT)) 

$(ALL_OBJS_WITH_PATH) : | $(OBJS_DEST_DIR)

clean:
	-$(RMDIR) $(RMDIROPTIONS) $(subst $(DIR_SEP),$(RM_DIR_SEP),$(OBJS_DEST_DIR))
	-$(RM) $(RMOPTIONS) $(subst $(DIR_SEP),$(RM_DIR_SEP),.$(DIR_SEP)$(APPLICATION))
	-$(RM) $(RMOPTIONS) $(subst $(DIR_SEP),$(RM_DIR_SEP),.$(DIR_SEP)$(APPLICATION).manifest)

$(OBJS_DEST_DIR):
	$(MKDIR) $(MDOPTIONS) $(subst $(DIR_SEP),$(MD_DIR_SEP),$(OBJS_DEST_DIR))
