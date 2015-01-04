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
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/JMC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/JMC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/API/API.c src/Java/JavaClass.c src/Java/JavaClassNVM.c src/JVM/JVM.c src/JVM/Heap.c src/JVM/Stack.c src/Loader/Loader.c src/Loader/LoaderNVM.c src/MemoryManagement/MemoryManagement.c src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.c src/SerialPort/SerialPort.c src/Timer/Timer.c src/Main.c src/API/MicroApplication/APIMicroApplication.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/API/API.p1 ${OBJECTDIR}/src/Java/JavaClass.p1 ${OBJECTDIR}/src/Java/JavaClassNVM.p1 ${OBJECTDIR}/src/JVM/JVM.p1 ${OBJECTDIR}/src/JVM/Heap.p1 ${OBJECTDIR}/src/JVM/Stack.p1 ${OBJECTDIR}/src/Loader/Loader.p1 ${OBJECTDIR}/src/Loader/LoaderNVM.p1 ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1 ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1 ${OBJECTDIR}/src/SerialPort/SerialPort.p1 ${OBJECTDIR}/src/Timer/Timer.p1 ${OBJECTDIR}/src/Main.p1 ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/src/API/API.p1.d ${OBJECTDIR}/src/Java/JavaClass.p1.d ${OBJECTDIR}/src/Java/JavaClassNVM.p1.d ${OBJECTDIR}/src/JVM/JVM.p1.d ${OBJECTDIR}/src/JVM/Heap.p1.d ${OBJECTDIR}/src/JVM/Stack.p1.d ${OBJECTDIR}/src/Loader/Loader.p1.d ${OBJECTDIR}/src/Loader/LoaderNVM.p1.d ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1.d ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1.d ${OBJECTDIR}/src/SerialPort/SerialPort.p1.d ${OBJECTDIR}/src/Timer/Timer.p1.d ${OBJECTDIR}/src/Main.p1.d ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/API/API.p1 ${OBJECTDIR}/src/Java/JavaClass.p1 ${OBJECTDIR}/src/Java/JavaClassNVM.p1 ${OBJECTDIR}/src/JVM/JVM.p1 ${OBJECTDIR}/src/JVM/Heap.p1 ${OBJECTDIR}/src/JVM/Stack.p1 ${OBJECTDIR}/src/Loader/Loader.p1 ${OBJECTDIR}/src/Loader/LoaderNVM.p1 ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1 ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1 ${OBJECTDIR}/src/SerialPort/SerialPort.p1 ${OBJECTDIR}/src/Timer/Timer.p1 ${OBJECTDIR}/src/Main.p1 ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1

# Source Files
SOURCEFILES=src/API/API.c src/Java/JavaClass.c src/Java/JavaClassNVM.c src/JVM/JVM.c src/JVM/Heap.c src/JVM/Stack.c src/Loader/Loader.c src/Loader/LoaderNVM.c src/MemoryManagement/MemoryManagement.c src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.c src/SerialPort/SerialPort.c src/Timer/Timer.c src/Main.c src/API/MicroApplication/APIMicroApplication.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/JMC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4520
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/API/API.p1: src/API/API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/API 
	@${RM} ${OBJECTDIR}/src/API/API.p1.d 
	@${RM} ${OBJECTDIR}/src/API/API.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/API/API.p1  src/API/API.c 
	@-${MV} ${OBJECTDIR}/src/API/API.d ${OBJECTDIR}/src/API/API.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/API/API.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Java/JavaClass.p1: src/Java/JavaClass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/Java 
	@${RM} ${OBJECTDIR}/src/Java/JavaClass.p1.d 
	@${RM} ${OBJECTDIR}/src/Java/JavaClass.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Java/JavaClass.p1  src/Java/JavaClass.c 
	@-${MV} ${OBJECTDIR}/src/Java/JavaClass.d ${OBJECTDIR}/src/Java/JavaClass.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Java/JavaClass.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Java/JavaClassNVM.p1: src/Java/JavaClassNVM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/Java 
	@${RM} ${OBJECTDIR}/src/Java/JavaClassNVM.p1.d 
	@${RM} ${OBJECTDIR}/src/Java/JavaClassNVM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Java/JavaClassNVM.p1  src/Java/JavaClassNVM.c 
	@-${MV} ${OBJECTDIR}/src/Java/JavaClassNVM.d ${OBJECTDIR}/src/Java/JavaClassNVM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Java/JavaClassNVM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/JVM/JVM.p1: src/JVM/JVM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/JVM 
	@${RM} ${OBJECTDIR}/src/JVM/JVM.p1.d 
	@${RM} ${OBJECTDIR}/src/JVM/JVM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/JVM/JVM.p1  src/JVM/JVM.c 
	@-${MV} ${OBJECTDIR}/src/JVM/JVM.d ${OBJECTDIR}/src/JVM/JVM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/JVM/JVM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/JVM/Heap.p1: src/JVM/Heap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/JVM 
	@${RM} ${OBJECTDIR}/src/JVM/Heap.p1.d 
	@${RM} ${OBJECTDIR}/src/JVM/Heap.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/JVM/Heap.p1  src/JVM/Heap.c 
	@-${MV} ${OBJECTDIR}/src/JVM/Heap.d ${OBJECTDIR}/src/JVM/Heap.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/JVM/Heap.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/JVM/Stack.p1: src/JVM/Stack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/JVM 
	@${RM} ${OBJECTDIR}/src/JVM/Stack.p1.d 
	@${RM} ${OBJECTDIR}/src/JVM/Stack.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/JVM/Stack.p1  src/JVM/Stack.c 
	@-${MV} ${OBJECTDIR}/src/JVM/Stack.d ${OBJECTDIR}/src/JVM/Stack.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/JVM/Stack.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Loader/Loader.p1: src/Loader/Loader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/Loader 
	@${RM} ${OBJECTDIR}/src/Loader/Loader.p1.d 
	@${RM} ${OBJECTDIR}/src/Loader/Loader.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Loader/Loader.p1  src/Loader/Loader.c 
	@-${MV} ${OBJECTDIR}/src/Loader/Loader.d ${OBJECTDIR}/src/Loader/Loader.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Loader/Loader.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Loader/LoaderNVM.p1: src/Loader/LoaderNVM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/Loader 
	@${RM} ${OBJECTDIR}/src/Loader/LoaderNVM.p1.d 
	@${RM} ${OBJECTDIR}/src/Loader/LoaderNVM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Loader/LoaderNVM.p1  src/Loader/LoaderNVM.c 
	@-${MV} ${OBJECTDIR}/src/Loader/LoaderNVM.d ${OBJECTDIR}/src/Loader/LoaderNVM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Loader/LoaderNVM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1: src/MemoryManagement/MemoryManagement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/MemoryManagement 
	@${RM} ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1.d 
	@${RM} ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1  src/MemoryManagement/MemoryManagement.c 
	@-${MV} ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.d ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1: src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/MemoryManagement/PIC18F4520 
	@${RM} ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1.d 
	@${RM} ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1  src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.c 
	@-${MV} ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.d ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/SerialPort/SerialPort.p1: src/SerialPort/SerialPort.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/SerialPort 
	@${RM} ${OBJECTDIR}/src/SerialPort/SerialPort.p1.d 
	@${RM} ${OBJECTDIR}/src/SerialPort/SerialPort.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/SerialPort/SerialPort.p1  src/SerialPort/SerialPort.c 
	@-${MV} ${OBJECTDIR}/src/SerialPort/SerialPort.d ${OBJECTDIR}/src/SerialPort/SerialPort.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/SerialPort/SerialPort.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Timer/Timer.p1: src/Timer/Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/Timer 
	@${RM} ${OBJECTDIR}/src/Timer/Timer.p1.d 
	@${RM} ${OBJECTDIR}/src/Timer/Timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Timer/Timer.p1  src/Timer/Timer.c 
	@-${MV} ${OBJECTDIR}/src/Timer/Timer.d ${OBJECTDIR}/src/Timer/Timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Timer/Timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Main.p1: src/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/Main.p1.d 
	@${RM} ${OBJECTDIR}/src/Main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Main.p1  src/Main.c 
	@-${MV} ${OBJECTDIR}/src/Main.d ${OBJECTDIR}/src/Main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1: src/API/MicroApplication/APIMicroApplication.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/API/MicroApplication 
	@${RM} ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1.d 
	@${RM} ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1  src/API/MicroApplication/APIMicroApplication.c 
	@-${MV} ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.d ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/API/API.p1: src/API/API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/API 
	@${RM} ${OBJECTDIR}/src/API/API.p1.d 
	@${RM} ${OBJECTDIR}/src/API/API.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/API/API.p1  src/API/API.c 
	@-${MV} ${OBJECTDIR}/src/API/API.d ${OBJECTDIR}/src/API/API.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/API/API.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Java/JavaClass.p1: src/Java/JavaClass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/Java 
	@${RM} ${OBJECTDIR}/src/Java/JavaClass.p1.d 
	@${RM} ${OBJECTDIR}/src/Java/JavaClass.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Java/JavaClass.p1  src/Java/JavaClass.c 
	@-${MV} ${OBJECTDIR}/src/Java/JavaClass.d ${OBJECTDIR}/src/Java/JavaClass.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Java/JavaClass.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Java/JavaClassNVM.p1: src/Java/JavaClassNVM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/Java 
	@${RM} ${OBJECTDIR}/src/Java/JavaClassNVM.p1.d 
	@${RM} ${OBJECTDIR}/src/Java/JavaClassNVM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Java/JavaClassNVM.p1  src/Java/JavaClassNVM.c 
	@-${MV} ${OBJECTDIR}/src/Java/JavaClassNVM.d ${OBJECTDIR}/src/Java/JavaClassNVM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Java/JavaClassNVM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/JVM/JVM.p1: src/JVM/JVM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/JVM 
	@${RM} ${OBJECTDIR}/src/JVM/JVM.p1.d 
	@${RM} ${OBJECTDIR}/src/JVM/JVM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/JVM/JVM.p1  src/JVM/JVM.c 
	@-${MV} ${OBJECTDIR}/src/JVM/JVM.d ${OBJECTDIR}/src/JVM/JVM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/JVM/JVM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/JVM/Heap.p1: src/JVM/Heap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/JVM 
	@${RM} ${OBJECTDIR}/src/JVM/Heap.p1.d 
	@${RM} ${OBJECTDIR}/src/JVM/Heap.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/JVM/Heap.p1  src/JVM/Heap.c 
	@-${MV} ${OBJECTDIR}/src/JVM/Heap.d ${OBJECTDIR}/src/JVM/Heap.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/JVM/Heap.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/JVM/Stack.p1: src/JVM/Stack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/JVM 
	@${RM} ${OBJECTDIR}/src/JVM/Stack.p1.d 
	@${RM} ${OBJECTDIR}/src/JVM/Stack.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/JVM/Stack.p1  src/JVM/Stack.c 
	@-${MV} ${OBJECTDIR}/src/JVM/Stack.d ${OBJECTDIR}/src/JVM/Stack.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/JVM/Stack.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Loader/Loader.p1: src/Loader/Loader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/Loader 
	@${RM} ${OBJECTDIR}/src/Loader/Loader.p1.d 
	@${RM} ${OBJECTDIR}/src/Loader/Loader.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Loader/Loader.p1  src/Loader/Loader.c 
	@-${MV} ${OBJECTDIR}/src/Loader/Loader.d ${OBJECTDIR}/src/Loader/Loader.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Loader/Loader.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Loader/LoaderNVM.p1: src/Loader/LoaderNVM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/Loader 
	@${RM} ${OBJECTDIR}/src/Loader/LoaderNVM.p1.d 
	@${RM} ${OBJECTDIR}/src/Loader/LoaderNVM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Loader/LoaderNVM.p1  src/Loader/LoaderNVM.c 
	@-${MV} ${OBJECTDIR}/src/Loader/LoaderNVM.d ${OBJECTDIR}/src/Loader/LoaderNVM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Loader/LoaderNVM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1: src/MemoryManagement/MemoryManagement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/MemoryManagement 
	@${RM} ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1.d 
	@${RM} ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1  src/MemoryManagement/MemoryManagement.c 
	@-${MV} ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.d ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/MemoryManagement/MemoryManagement.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1: src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/MemoryManagement/PIC18F4520 
	@${RM} ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1.d 
	@${RM} ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1  src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.c 
	@-${MV} ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.d ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/MemoryManagement/PIC18F4520/MemoryManagement_PIC18F4520.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/SerialPort/SerialPort.p1: src/SerialPort/SerialPort.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/SerialPort 
	@${RM} ${OBJECTDIR}/src/SerialPort/SerialPort.p1.d 
	@${RM} ${OBJECTDIR}/src/SerialPort/SerialPort.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/SerialPort/SerialPort.p1  src/SerialPort/SerialPort.c 
	@-${MV} ${OBJECTDIR}/src/SerialPort/SerialPort.d ${OBJECTDIR}/src/SerialPort/SerialPort.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/SerialPort/SerialPort.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Timer/Timer.p1: src/Timer/Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/Timer 
	@${RM} ${OBJECTDIR}/src/Timer/Timer.p1.d 
	@${RM} ${OBJECTDIR}/src/Timer/Timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Timer/Timer.p1  src/Timer/Timer.c 
	@-${MV} ${OBJECTDIR}/src/Timer/Timer.d ${OBJECTDIR}/src/Timer/Timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Timer/Timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/Main.p1: src/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/Main.p1.d 
	@${RM} ${OBJECTDIR}/src/Main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/Main.p1  src/Main.c 
	@-${MV} ${OBJECTDIR}/src/Main.d ${OBJECTDIR}/src/Main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/Main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1: src/API/MicroApplication/APIMicroApplication.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/API/MicroApplication 
	@${RM} ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1.d 
	@${RM} ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" -L-pnvm=4000h    -o${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1  src/API/MicroApplication/APIMicroApplication.c 
	@-${MV} ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.d ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/API/MicroApplication/APIMicroApplication.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/JMC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/JMC.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        -odist/${CND_CONF}/${IMAGE_TYPE}/JMC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/JMC.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/JMC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/JMC.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/JVM" -I"src/Java" -I"src/Timer" -I"src/Loader" -I"src/Platform" -I"src/SerialPort" -I"src/MemoryManagement" -I"src/MemoryManagement/PIC18F4520" -I"src/API" -I"src/API/MicroApplication" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -odist/${CND_CONF}/${IMAGE_TYPE}/JMC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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
