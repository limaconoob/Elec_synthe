#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Synthe_Final_06-07.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Synthe_Final_06-07.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=configBits.c Init_pins.c Display.c Main.c Encodeur.c Preset.c AudioBuffer.c DAC.c MIDI.c menus.c Boutons.c Create_tab_freq.c tab_sinus.c TabCreate.c Filter_control.c Enveloppe.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/configBits.o ${OBJECTDIR}/Init_pins.o ${OBJECTDIR}/Display.o ${OBJECTDIR}/Main.o ${OBJECTDIR}/Encodeur.o ${OBJECTDIR}/Preset.o ${OBJECTDIR}/AudioBuffer.o ${OBJECTDIR}/DAC.o ${OBJECTDIR}/MIDI.o ${OBJECTDIR}/menus.o ${OBJECTDIR}/Boutons.o ${OBJECTDIR}/Create_tab_freq.o ${OBJECTDIR}/tab_sinus.o ${OBJECTDIR}/TabCreate.o ${OBJECTDIR}/Filter_control.o ${OBJECTDIR}/Enveloppe.o
POSSIBLE_DEPFILES=${OBJECTDIR}/configBits.o.d ${OBJECTDIR}/Init_pins.o.d ${OBJECTDIR}/Display.o.d ${OBJECTDIR}/Main.o.d ${OBJECTDIR}/Encodeur.o.d ${OBJECTDIR}/Preset.o.d ${OBJECTDIR}/AudioBuffer.o.d ${OBJECTDIR}/DAC.o.d ${OBJECTDIR}/MIDI.o.d ${OBJECTDIR}/menus.o.d ${OBJECTDIR}/Boutons.o.d ${OBJECTDIR}/Create_tab_freq.o.d ${OBJECTDIR}/tab_sinus.o.d ${OBJECTDIR}/TabCreate.o.d ${OBJECTDIR}/Filter_control.o.d ${OBJECTDIR}/Enveloppe.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/configBits.o ${OBJECTDIR}/Init_pins.o ${OBJECTDIR}/Display.o ${OBJECTDIR}/Main.o ${OBJECTDIR}/Encodeur.o ${OBJECTDIR}/Preset.o ${OBJECTDIR}/AudioBuffer.o ${OBJECTDIR}/DAC.o ${OBJECTDIR}/MIDI.o ${OBJECTDIR}/menus.o ${OBJECTDIR}/Boutons.o ${OBJECTDIR}/Create_tab_freq.o ${OBJECTDIR}/tab_sinus.o ${OBJECTDIR}/TabCreate.o ${OBJECTDIR}/Filter_control.o ${OBJECTDIR}/Enveloppe.o

# Source Files
SOURCEFILES=configBits.c Init_pins.c Display.c Main.c Encodeur.c Preset.c AudioBuffer.c DAC.c MIDI.c menus.c Boutons.c Create_tab_freq.c tab_sinus.c TabCreate.c Filter_control.c Enveloppe.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Synthe_Final_06-07.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX575F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/configBits.o: configBits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configBits.o.d 
	@${RM} ${OBJECTDIR}/configBits.o 
	@${FIXDEPS} "${OBJECTDIR}/configBits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configBits.o.d" -o ${OBJECTDIR}/configBits.o configBits.c   
	
${OBJECTDIR}/Init_pins.o: Init_pins.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Init_pins.o.d 
	@${RM} ${OBJECTDIR}/Init_pins.o 
	@${FIXDEPS} "${OBJECTDIR}/Init_pins.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Init_pins.o.d" -o ${OBJECTDIR}/Init_pins.o Init_pins.c   
	
${OBJECTDIR}/Display.o: Display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Display.o.d 
	@${RM} ${OBJECTDIR}/Display.o 
	@${FIXDEPS} "${OBJECTDIR}/Display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Display.o.d" -o ${OBJECTDIR}/Display.o Display.c   
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Main.o.d" -o ${OBJECTDIR}/Main.o Main.c   
	
${OBJECTDIR}/Encodeur.o: Encodeur.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Encodeur.o.d 
	@${RM} ${OBJECTDIR}/Encodeur.o 
	@${FIXDEPS} "${OBJECTDIR}/Encodeur.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Encodeur.o.d" -o ${OBJECTDIR}/Encodeur.o Encodeur.c   
	
${OBJECTDIR}/Preset.o: Preset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Preset.o.d 
	@${RM} ${OBJECTDIR}/Preset.o 
	@${FIXDEPS} "${OBJECTDIR}/Preset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Preset.o.d" -o ${OBJECTDIR}/Preset.o Preset.c   
	
${OBJECTDIR}/AudioBuffer.o: AudioBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AudioBuffer.o.d 
	@${RM} ${OBJECTDIR}/AudioBuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/AudioBuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/AudioBuffer.o.d" -o ${OBJECTDIR}/AudioBuffer.o AudioBuffer.c   
	
${OBJECTDIR}/DAC.o: DAC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DAC.o.d 
	@${RM} ${OBJECTDIR}/DAC.o 
	@${FIXDEPS} "${OBJECTDIR}/DAC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DAC.o.d" -o ${OBJECTDIR}/DAC.o DAC.c   
	
${OBJECTDIR}/MIDI.o: MIDI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MIDI.o.d 
	@${RM} ${OBJECTDIR}/MIDI.o 
	@${FIXDEPS} "${OBJECTDIR}/MIDI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/MIDI.o.d" -o ${OBJECTDIR}/MIDI.o MIDI.c   
	
${OBJECTDIR}/menus.o: menus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menus.o.d 
	@${RM} ${OBJECTDIR}/menus.o 
	@${FIXDEPS} "${OBJECTDIR}/menus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/menus.o.d" -o ${OBJECTDIR}/menus.o menus.c   
	
${OBJECTDIR}/Boutons.o: Boutons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Boutons.o.d 
	@${RM} ${OBJECTDIR}/Boutons.o 
	@${FIXDEPS} "${OBJECTDIR}/Boutons.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Boutons.o.d" -o ${OBJECTDIR}/Boutons.o Boutons.c   
	
${OBJECTDIR}/Create_tab_freq.o: Create_tab_freq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Create_tab_freq.o.d 
	@${RM} ${OBJECTDIR}/Create_tab_freq.o 
	@${FIXDEPS} "${OBJECTDIR}/Create_tab_freq.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Create_tab_freq.o.d" -o ${OBJECTDIR}/Create_tab_freq.o Create_tab_freq.c   
	
${OBJECTDIR}/tab_sinus.o: tab_sinus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tab_sinus.o.d 
	@${RM} ${OBJECTDIR}/tab_sinus.o 
	@${FIXDEPS} "${OBJECTDIR}/tab_sinus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/tab_sinus.o.d" -o ${OBJECTDIR}/tab_sinus.o tab_sinus.c   
	
${OBJECTDIR}/TabCreate.o: TabCreate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TabCreate.o.d 
	@${RM} ${OBJECTDIR}/TabCreate.o 
	@${FIXDEPS} "${OBJECTDIR}/TabCreate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TabCreate.o.d" -o ${OBJECTDIR}/TabCreate.o TabCreate.c   
	
${OBJECTDIR}/Filter_control.o: Filter_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Filter_control.o.d 
	@${RM} ${OBJECTDIR}/Filter_control.o 
	@${FIXDEPS} "${OBJECTDIR}/Filter_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Filter_control.o.d" -o ${OBJECTDIR}/Filter_control.o Filter_control.c   
	
${OBJECTDIR}/Enveloppe.o: Enveloppe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Enveloppe.o.d 
	@${RM} ${OBJECTDIR}/Enveloppe.o 
	@${FIXDEPS} "${OBJECTDIR}/Enveloppe.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Enveloppe.o.d" -o ${OBJECTDIR}/Enveloppe.o Enveloppe.c   
	
else
${OBJECTDIR}/configBits.o: configBits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configBits.o.d 
	@${RM} ${OBJECTDIR}/configBits.o 
	@${FIXDEPS} "${OBJECTDIR}/configBits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configBits.o.d" -o ${OBJECTDIR}/configBits.o configBits.c   
	
${OBJECTDIR}/Init_pins.o: Init_pins.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Init_pins.o.d 
	@${RM} ${OBJECTDIR}/Init_pins.o 
	@${FIXDEPS} "${OBJECTDIR}/Init_pins.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Init_pins.o.d" -o ${OBJECTDIR}/Init_pins.o Init_pins.c   
	
${OBJECTDIR}/Display.o: Display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Display.o.d 
	@${RM} ${OBJECTDIR}/Display.o 
	@${FIXDEPS} "${OBJECTDIR}/Display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Display.o.d" -o ${OBJECTDIR}/Display.o Display.c   
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Main.o.d" -o ${OBJECTDIR}/Main.o Main.c   
	
${OBJECTDIR}/Encodeur.o: Encodeur.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Encodeur.o.d 
	@${RM} ${OBJECTDIR}/Encodeur.o 
	@${FIXDEPS} "${OBJECTDIR}/Encodeur.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Encodeur.o.d" -o ${OBJECTDIR}/Encodeur.o Encodeur.c   
	
${OBJECTDIR}/Preset.o: Preset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Preset.o.d 
	@${RM} ${OBJECTDIR}/Preset.o 
	@${FIXDEPS} "${OBJECTDIR}/Preset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Preset.o.d" -o ${OBJECTDIR}/Preset.o Preset.c   
	
${OBJECTDIR}/AudioBuffer.o: AudioBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AudioBuffer.o.d 
	@${RM} ${OBJECTDIR}/AudioBuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/AudioBuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/AudioBuffer.o.d" -o ${OBJECTDIR}/AudioBuffer.o AudioBuffer.c   
	
${OBJECTDIR}/DAC.o: DAC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DAC.o.d 
	@${RM} ${OBJECTDIR}/DAC.o 
	@${FIXDEPS} "${OBJECTDIR}/DAC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DAC.o.d" -o ${OBJECTDIR}/DAC.o DAC.c   
	
${OBJECTDIR}/MIDI.o: MIDI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MIDI.o.d 
	@${RM} ${OBJECTDIR}/MIDI.o 
	@${FIXDEPS} "${OBJECTDIR}/MIDI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/MIDI.o.d" -o ${OBJECTDIR}/MIDI.o MIDI.c   
	
${OBJECTDIR}/menus.o: menus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menus.o.d 
	@${RM} ${OBJECTDIR}/menus.o 
	@${FIXDEPS} "${OBJECTDIR}/menus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/menus.o.d" -o ${OBJECTDIR}/menus.o menus.c   
	
${OBJECTDIR}/Boutons.o: Boutons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Boutons.o.d 
	@${RM} ${OBJECTDIR}/Boutons.o 
	@${FIXDEPS} "${OBJECTDIR}/Boutons.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Boutons.o.d" -o ${OBJECTDIR}/Boutons.o Boutons.c   
	
${OBJECTDIR}/Create_tab_freq.o: Create_tab_freq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Create_tab_freq.o.d 
	@${RM} ${OBJECTDIR}/Create_tab_freq.o 
	@${FIXDEPS} "${OBJECTDIR}/Create_tab_freq.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Create_tab_freq.o.d" -o ${OBJECTDIR}/Create_tab_freq.o Create_tab_freq.c   
	
${OBJECTDIR}/tab_sinus.o: tab_sinus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tab_sinus.o.d 
	@${RM} ${OBJECTDIR}/tab_sinus.o 
	@${FIXDEPS} "${OBJECTDIR}/tab_sinus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/tab_sinus.o.d" -o ${OBJECTDIR}/tab_sinus.o tab_sinus.c   
	
${OBJECTDIR}/TabCreate.o: TabCreate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TabCreate.o.d 
	@${RM} ${OBJECTDIR}/TabCreate.o 
	@${FIXDEPS} "${OBJECTDIR}/TabCreate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TabCreate.o.d" -o ${OBJECTDIR}/TabCreate.o TabCreate.c   
	
${OBJECTDIR}/Filter_control.o: Filter_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Filter_control.o.d 
	@${RM} ${OBJECTDIR}/Filter_control.o 
	@${FIXDEPS} "${OBJECTDIR}/Filter_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Filter_control.o.d" -o ${OBJECTDIR}/Filter_control.o Filter_control.c   
	
${OBJECTDIR}/Enveloppe.o: Enveloppe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Enveloppe.o.d 
	@${RM} ${OBJECTDIR}/Enveloppe.o 
	@${FIXDEPS} "${OBJECTDIR}/Enveloppe.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Enveloppe.o.d" -o ${OBJECTDIR}/Enveloppe.o Enveloppe.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Synthe_Final_06-07.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Synthe_Final_06-07.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Synthe_Final_06-07.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Synthe_Final_06-07.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Synthe_Final_06-07.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
