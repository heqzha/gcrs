#
# OMNeT++/OMNEST Makefile for GCRS
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I../mixim/src/base/messages -I../mixim/src/modules/utility -I../mixim/src/modules/phy -I../mixim/src/modules -I../mixim/src/base/connectionManager -I../mixim/src/modules/obstacle -I../mixim/src/modules/analogueModel -I../mixim/src/modules/messages -I../mixim/src/base/phyLayer -I../mixim/src/base/modules -I../mixim/src/modules/mac/ieee80211p -I../mixim/src/base/utils -I../mixim/src/modules/world/annotations -I../mixim/src/modules/mobility/traci -L/usr/lib/x86_64-linux-gnu -L../mixim/out/$(CONFIGNAME)/tests/testUtils -L../mixim/out/$(CONFIGNAME)/src/base -L../mixim/out/$(CONFIGNAME)/src/modules -lmiximtestUtils -lmiximbase -lmiximmodules -KMIXIM_PROJ=../mixim
#

# Name of target to be created (-o option)
TARGET = GCRS$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../mixim/src/base/messages \
    -I../mixim/src/modules/utility \
    -I../mixim/src/modules/phy \
    -I../mixim/src/modules \
    -I../mixim/src/base/connectionManager \
    -I../mixim/src/modules/obstacle \
    -I../mixim/src/modules/analogueModel \
    -I../mixim/src/modules/messages \
    -I../mixim/src/base/phyLayer \
    -I../mixim/src/base/modules \
    -I../mixim/src/modules/mac/ieee80211p \
    -I../mixim/src/base/utils \
    -I../mixim/src/modules/world/annotations \
    -I../mixim/src/modules/mobility/traci \
    -I. \
    -Iresults \
    -Isrc \
    -Isrc/base \
    -Isrc/base/analogueModel \
    -Isrc/base/app \
    -Isrc/base/collectionService \
    -Isrc/base/com \
    -Isrc/base/com/collection \
    -Isrc/base/com/geoInfo \
    -Isrc/base/com/lib \
    -Isrc/base/com/lib/tinyxml \
    -Isrc/base/com/task \
    -Isrc/base/com/vehicle \
    -Isrc/base/com/zone \
    -Isrc/base/connectionManager \
    -Isrc/base/const \
    -Isrc/base/mac \
    -Isrc/base/mobility \
    -Isrc/base/ned \
    -Isrc/base/net \
    -Isrc/base/nic \
    -Isrc/base/phy \
    -Isrc/base/pkt \
    -Isrc/base/traci \
    -Isrc/base/vehicleManager \
    -Isrc/base/world \
    -Isrc/modules \
    -Isrc/modules/com \
    -Isrc/modules/com/task \
    -Isrc/modules/com/task/drg \
    -Isrc/modules/com/task/dtsg \
    -Isrc/modules/com/task/flooding \
    -Isrc/modules/com/task/rover \
    -Isrc/modules/const \
    -Isrc/modules/net \
    -Isrc/modules/pkt

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L/usr/lib/x86_64-linux-gnu -L../mixim/out/$(CONFIGNAME)/tests/testUtils -L../mixim/out/$(CONFIGNAME)/src/base -L../mixim/out/$(CONFIGNAME)/src/modules  -lmiximtestUtils -lmiximbase -lmiximmodules
LIBS += -Wl,-rpath,`abspath /usr/lib/x86_64-linux-gnu` -Wl,-rpath,`abspath ../mixim/out/$(CONFIGNAME)/tests/testUtils` -Wl,-rpath,`abspath ../mixim/out/$(CONFIGNAME)/src/base` -Wl,-rpath,`abspath ../mixim/out/$(CONFIGNAME)/src/modules`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/src/base/analogueModel/GCRSBaseSimpleObstacleShadowing.o \
    $O/src/base/app/GCRSBaseAppLayer.o \
    $O/src/base/collectionService/GCRSBaseCollectionService.o \
    $O/src/base/com/collection/GCRSBaseComCollectStatistics.o \
    $O/src/base/com/collection/GCRSBaseComCollectNetworkController.o \
    $O/src/base/com/collection/GCRSBaseComCollectNode.o \
    $O/src/base/com/collection/GCRSBaseComCollectNetwork.o \
    $O/src/base/com/collection/GCRSBaseComCollectNetworkRange.o \
    $O/src/base/com/collection/GCRSBaseComCollectNetworkRangeController.o \
    $O/src/base/com/collection/GCRSBaseComCollectPrintOut.o \
    $O/src/base/com/collection/GCRSBaseComNin.o \
    $O/src/base/com/geoInfo/GCRSBaseComGeoInfoBuffer.o \
    $O/src/base/com/geoInfo/GCRSBaseComGeoInfo.o \
    $O/src/base/com/lib/GCRSBaseComTTL.o \
    $O/src/base/com/lib/GCRSBaseRealWorldTimer.o \
    $O/src/base/com/lib/GCRSBaseComMath.o \
    $O/src/base/com/lib/GCRSReadXml.o \
    $O/src/base/com/lib/Convert.o \
    $O/src/base/com/lib/GCRSBaseString.o \
    $O/src/base/com/lib/tinyxml/tinyxmlerror.o \
    $O/src/base/com/lib/tinyxml/tinystr.o \
    $O/src/base/com/lib/tinyxml/tinyxmlparser.o \
    $O/src/base/com/lib/tinyxml/tinyxml.o \
    $O/src/base/com/task/GCRSBaseComTask.o \
    $O/src/base/com/task/GCRSBaseComTaskManager.o \
    $O/src/base/com/vehicle/GCRSBaseComVehicleEvent.o \
    $O/src/base/com/vehicle/GCRSBaseComVehicleState.o \
    $O/src/base/com/vehicle/GCRSBaseComVehicleEventControl.o \
    $O/src/base/com/vehicle/GCRSBaseComVehicleControl.o \
    $O/src/base/com/vehicle/GCRSBaseComVin.o \
    $O/src/base/com/zone/GCRSBaseComCircle.o \
    $O/src/base/com/zone/GCRSBaseComZone.o \
    $O/src/base/com/zone/GCRSBaseComRectangle.o \
    $O/src/base/com/zone/GCRSBaseComEllipse.o \
    $O/src/base/com/zone/GCRSBaseComBaseShape.o \
    $O/src/base/connectionManager/GCRSBaseConnectionManager.o \
    $O/src/base/mac/GCRSBaseMacLayer.o \
    $O/src/base/mobility/GCRSBaseTraCIMobility.o \
    $O/src/base/net/GCRSBaseNetLayer.o \
    $O/src/base/phy/GCRSBasePhyLayer.o \
    $O/src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.o \
    $O/src/base/vehicleManager/GCRSBaseVehicleManager.o \
    $O/src/base/world/GCRSBaseWorldUtility.o \
    $O/src/modules/com/task/drg/GCRSDRGComTask.o \
    $O/src/modules/com/task/drg/GCRSDRGComTaskManager.o \
    $O/src/modules/com/task/dtsg/GCRSDTSGComTaskManager.o \
    $O/src/modules/com/task/dtsg/GCRSDTSGComTask.o \
    $O/src/modules/com/task/flooding/GCRSFloodingComTask.o \
    $O/src/modules/com/task/flooding/GCRSFloodingComTaskManager.o \
    $O/src/modules/com/task/rover/GCRSROVERComTaskManager.o \
    $O/src/modules/com/task/rover/GCRSROVERComTask.o \
    $O/src/modules/net/GCRSFloodingNetLayer.o \
    $O/src/modules/net/GCRSROVERNetLayer.o \
    $O/src/modules/net/GCRSDRGNetLayer.o \
    $O/src/modules/net/GCRSDummyNetLayer.o \
    $O/src/modules/net/GCRSDTSGNetLayer.o \
    $O/src/base/pkt/GCRSBaseNetPkt_m.o \
    $O/src/base/pkt/GCRSBasePkt_m.o \
    $O/src/modules/pkt/GCRSDTSGNetPkt_m.o

# Message files
MSGFILES = \
    src/base/pkt/GCRSBaseNetPkt.msg \
    src/base/pkt/GCRSBasePkt.msg \
    src/modules/pkt/GCRSDTSGNetPkt.msg

# Other makefile variables (-K)
MIXIM_PROJ=../mixim

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f GCRS GCRS.exe libGCRS.so libGCRS.a libGCRS.dll libGCRS.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f results/*_m.cc results/*_m.h
	$(Q)-rm -f src/*_m.cc src/*_m.h
	$(Q)-rm -f src/base/*_m.cc src/base/*_m.h
	$(Q)-rm -f src/base/analogueModel/*_m.cc src/base/analogueModel/*_m.h
	$(Q)-rm -f src/base/app/*_m.cc src/base/app/*_m.h
	$(Q)-rm -f src/base/collectionService/*_m.cc src/base/collectionService/*_m.h
	$(Q)-rm -f src/base/com/*_m.cc src/base/com/*_m.h
	$(Q)-rm -f src/base/com/collection/*_m.cc src/base/com/collection/*_m.h
	$(Q)-rm -f src/base/com/geoInfo/*_m.cc src/base/com/geoInfo/*_m.h
	$(Q)-rm -f src/base/com/lib/*_m.cc src/base/com/lib/*_m.h
	$(Q)-rm -f src/base/com/lib/tinyxml/*_m.cc src/base/com/lib/tinyxml/*_m.h
	$(Q)-rm -f src/base/com/task/*_m.cc src/base/com/task/*_m.h
	$(Q)-rm -f src/base/com/vehicle/*_m.cc src/base/com/vehicle/*_m.h
	$(Q)-rm -f src/base/com/zone/*_m.cc src/base/com/zone/*_m.h
	$(Q)-rm -f src/base/connectionManager/*_m.cc src/base/connectionManager/*_m.h
	$(Q)-rm -f src/base/const/*_m.cc src/base/const/*_m.h
	$(Q)-rm -f src/base/mac/*_m.cc src/base/mac/*_m.h
	$(Q)-rm -f src/base/mobility/*_m.cc src/base/mobility/*_m.h
	$(Q)-rm -f src/base/ned/*_m.cc src/base/ned/*_m.h
	$(Q)-rm -f src/base/net/*_m.cc src/base/net/*_m.h
	$(Q)-rm -f src/base/nic/*_m.cc src/base/nic/*_m.h
	$(Q)-rm -f src/base/phy/*_m.cc src/base/phy/*_m.h
	$(Q)-rm -f src/base/pkt/*_m.cc src/base/pkt/*_m.h
	$(Q)-rm -f src/base/traci/*_m.cc src/base/traci/*_m.h
	$(Q)-rm -f src/base/vehicleManager/*_m.cc src/base/vehicleManager/*_m.h
	$(Q)-rm -f src/base/world/*_m.cc src/base/world/*_m.h
	$(Q)-rm -f src/modules/*_m.cc src/modules/*_m.h
	$(Q)-rm -f src/modules/com/*_m.cc src/modules/com/*_m.h
	$(Q)-rm -f src/modules/com/task/*_m.cc src/modules/com/task/*_m.h
	$(Q)-rm -f src/modules/com/task/drg/*_m.cc src/modules/com/task/drg/*_m.h
	$(Q)-rm -f src/modules/com/task/dtsg/*_m.cc src/modules/com/task/dtsg/*_m.h
	$(Q)-rm -f src/modules/com/task/flooding/*_m.cc src/modules/com/task/flooding/*_m.h
	$(Q)-rm -f src/modules/com/task/rover/*_m.cc src/modules/com/task/rover/*_m.h
	$(Q)-rm -f src/modules/const/*_m.cc src/modules/const/*_m.h
	$(Q)-rm -f src/modules/net/*_m.cc src/modules/net/*_m.h
	$(Q)-rm -f src/modules/pkt/*_m.cc src/modules/pkt/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc results/*.cc src/*.cc src/base/*.cc src/base/analogueModel/*.cc src/base/app/*.cc src/base/collectionService/*.cc src/base/com/*.cc src/base/com/collection/*.cc src/base/com/geoInfo/*.cc src/base/com/lib/*.cc src/base/com/lib/tinyxml/*.cc src/base/com/task/*.cc src/base/com/vehicle/*.cc src/base/com/zone/*.cc src/base/connectionManager/*.cc src/base/const/*.cc src/base/mac/*.cc src/base/mobility/*.cc src/base/ned/*.cc src/base/net/*.cc src/base/nic/*.cc src/base/phy/*.cc src/base/pkt/*.cc src/base/traci/*.cc src/base/vehicleManager/*.cc src/base/world/*.cc src/modules/*.cc src/modules/com/*.cc src/modules/com/task/*.cc src/modules/com/task/drg/*.cc src/modules/com/task/dtsg/*.cc src/modules/com/task/flooding/*.cc src/modules/com/task/rover/*.cc src/modules/const/*.cc src/modules/net/*.cc src/modules/pkt/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/src/base/analogueModel/GCRSBaseSimpleObstacleShadowing.o: src/base/analogueModel/GCRSBaseSimpleObstacleShadowing.cc \
	src/base/analogueModel/GCRSBaseSimpleObstacleShadowing.h \
	$(MIXIM_PROJ)/src/base/messages/AirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/analogueModel/SimpleObstacleShadowing.h \
	$(MIXIM_PROJ)/src/modules/obstacle/Obstacle.h \
	$(MIXIM_PROJ)/src/modules/obstacle/ObstacleControl.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/base/app/GCRSBaseAppLayer.o: src/base/app/GCRSBaseAppLayer.cc \
	src/base/app/GCRSBaseAppLayer.h \
	src/base/collectionService/GCRSBaseCollectionService.h \
	src/base/com/collection/GCRSBaseComCollectNetwork.h \
	src/base/com/collection/GCRSBaseComCollectNetworkController.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRange.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRangeController.h \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/collection/GCRSBaseComCollectPrintOut.h \
	src/base/com/collection/GCRSBaseComCollectStatistics.h \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/geoInfo/GCRSBaseComGeoInfo.h \
	src/base/com/geoInfo/GCRSBaseComGeoInfoBuffer.h \
	src/base/com/lib/Convert.h \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/lib/GCRSBaseComNetwControlInfo.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/lib/GCRSBaseRealWorldTimer.h \
	src/base/com/lib/GCRSReadXml.h \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/connectionManager/GCRSBaseConnectionManager.h \
	src/base/const/GCRSBaseConst.h \
	src/base/mobility/GCRSBaseTraCIMobility.h \
	src/base/pkt/GCRSBasePkt_m.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	src/base/vehicleManager/GCRSBaseVehicleManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIMobility.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/base/collectionService/GCRSBaseCollectionService.o: src/base/collectionService/GCRSBaseCollectionService.cc \
	src/base/collectionService/GCRSBaseCollectionService.h \
	src/base/com/collection/GCRSBaseComCollectNetwork.h \
	src/base/com/collection/GCRSBaseComCollectNetworkController.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRange.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRangeController.h \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/collection/GCRSBaseComCollectPrintOut.h \
	src/base/com/collection/GCRSBaseComCollectStatistics.h \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/lib/Convert.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/lib/GCRSBaseRealWorldTimer.h \
	src/base/com/lib/GCRSReadXml.h \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/connectionManager/GCRSBaseConnectionManager.h \
	src/base/const/GCRSBaseConst.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	src/base/vehicleManager/GCRSBaseVehicleManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/base/com/collection/GCRSBaseComCollectNetwork.o: src/base/com/collection/GCRSBaseComCollectNetwork.cc \
	src/base/com/collection/GCRSBaseComCollectNetwork.h \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/collection/GCRSBaseComCollectNetworkController.o: src/base/com/collection/GCRSBaseComCollectNetworkController.cc \
	src/base/com/collection/GCRSBaseComCollectNetwork.h \
	src/base/com/collection/GCRSBaseComCollectNetworkController.h \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/collection/GCRSBaseComCollectNetworkRange.o: src/base/com/collection/GCRSBaseComCollectNetworkRange.cc \
	src/base/com/collection/GCRSBaseComCollectNetworkRange.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/base/com/collection/GCRSBaseComCollectNetworkRangeController.o: src/base/com/collection/GCRSBaseComCollectNetworkRangeController.cc \
	src/base/com/collection/GCRSBaseComCollectNetworkRange.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRangeController.h \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/base/com/collection/GCRSBaseComCollectNode.o: src/base/com/collection/GCRSBaseComCollectNode.cc \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/vehicle/GCRSBaseComVin.h
$O/src/base/com/collection/GCRSBaseComCollectPrintOut.o: src/base/com/collection/GCRSBaseComCollectPrintOut.cc \
	src/base/com/collection/GCRSBaseComCollectPrintOut.h \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h
$O/src/base/com/collection/GCRSBaseComCollectStatistics.o: src/base/com/collection/GCRSBaseComCollectStatistics.cc \
	src/base/com/collection/GCRSBaseComCollectStatistics.h
$O/src/base/com/collection/GCRSBaseComNin.o: src/base/com/collection/GCRSBaseComNin.cc \
	src/base/com/collection/GCRSBaseComNin.h
$O/src/base/com/geoInfo/GCRSBaseComGeoInfo.o: src/base/com/geoInfo/GCRSBaseComGeoInfo.cc \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/geoInfo/GCRSBaseComGeoInfo.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/geoInfo/GCRSBaseComGeoInfoBuffer.o: src/base/com/geoInfo/GCRSBaseComGeoInfoBuffer.cc \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/geoInfo/GCRSBaseComGeoInfo.h \
	src/base/com/geoInfo/GCRSBaseComGeoInfoBuffer.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/lib/Convert.o: src/base/com/lib/Convert.cc \
	src/base/com/lib/Convert.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/lib/GCRSBaseComMath.o: src/base/com/lib/GCRSBaseComMath.cc \
	src/base/com/lib/GCRSBaseComMath.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/lib/GCRSBaseComTTL.o: src/base/com/lib/GCRSBaseComTTL.cc \
	src/base/com/lib/GCRSBaseComTTL.h
$O/src/base/com/lib/GCRSBaseRealWorldTimer.o: src/base/com/lib/GCRSBaseRealWorldTimer.cc \
	src/base/com/lib/GCRSBaseRealWorldTimer.h
$O/src/base/com/lib/GCRSBaseString.o: src/base/com/lib/GCRSBaseString.cc \
	src/base/com/lib/GCRSBaseString.h
$O/src/base/com/lib/GCRSReadXml.o: src/base/com/lib/GCRSReadXml.cc \
	src/base/com/lib/GCRSBaseString.h \
	src/base/com/lib/GCRSReadXml.h
$O/src/base/com/lib/tinyxml/tinystr.o: src/base/com/lib/tinyxml/tinystr.cc \
	src/base/com/lib/tinyxml/tinystr.h
$O/src/base/com/lib/tinyxml/tinyxml.o: src/base/com/lib/tinyxml/tinyxml.cc \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h
$O/src/base/com/lib/tinyxml/tinyxmlerror.o: src/base/com/lib/tinyxml/tinyxmlerror.cc \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h
$O/src/base/com/lib/tinyxml/tinyxmlparser.o: src/base/com/lib/tinyxml/tinyxmlparser.cc \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h
$O/src/base/com/task/GCRSBaseComTask.o: src/base/com/task/GCRSBaseComTask.cc \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/task/GCRSBaseComTaskManager.o: src/base/com/task/GCRSBaseComTaskManager.cc \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/vehicle/GCRSBaseComVehicleControl.o: src/base/com/vehicle/GCRSBaseComVehicleControl.cc \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/vehicle/GCRSBaseComVehicleEvent.o: src/base/com/vehicle/GCRSBaseComVehicleEvent.cc \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/vehicle/GCRSBaseComVehicleEventControl.o: src/base/com/vehicle/GCRSBaseComVehicleEventControl.cc \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/vehicle/GCRSBaseComVehicleState.o: src/base/com/vehicle/GCRSBaseComVehicleState.cc \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/vehicle/GCRSBaseComVin.o: src/base/com/vehicle/GCRSBaseComVin.cc \
	src/base/com/vehicle/GCRSBaseComVin.h
$O/src/base/com/zone/GCRSBaseComBaseShape.o: src/base/com/zone/GCRSBaseComBaseShape.cc \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/zone/GCRSBaseComCircle.o: src/base/com/zone/GCRSBaseComCircle.cc \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/zone/GCRSBaseComEllipse.o: src/base/com/zone/GCRSBaseComEllipse.cc \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/zone/GCRSBaseComRectangle.o: src/base/com/zone/GCRSBaseComRectangle.cc \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/com/zone/GCRSBaseComZone.o: src/base/com/zone/GCRSBaseComZone.cc \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/const/GCRSBaseConst.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h
$O/src/base/connectionManager/GCRSBaseConnectionManager.o: src/base/connectionManager/GCRSBaseConnectionManager.cc \
	src/base/connectionManager/GCRSBaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/mac/GCRSBaseMacLayer.o: src/base/mac/GCRSBaseMacLayer.cc \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/const/GCRSBaseConst.h \
	src/base/mac/GCRSBaseMacLayer.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/messages/AirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/ChannelSenseRequest_m.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMacLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BaseDecider.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Decider.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyControlInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/analogueModel/JakesFading.h \
	$(MIXIM_PROJ)/src/modules/analogueModel/LogNormalShadowing.h \
	$(MIXIM_PROJ)/src/modules/analogueModel/SimplePathlossModel.h \
	$(MIXIM_PROJ)/src/modules/mac/ieee80211p/Mac80211pToPhy11pInterface.h \
	$(MIXIM_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(MIXIM_PROJ)/src/modules/phy/Decider80211p.h \
	$(MIXIM_PROJ)/src/modules/phy/Decider80211pToPhy80211pInterface.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer80211p.h \
	$(MIXIM_PROJ)/src/modules/phy/SNRThresholdDecider.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h
$O/src/base/mobility/GCRSBaseTraCIMobility.o: src/base/mobility/GCRSBaseTraCIMobility.cc \
	src/base/com/lib/GCRSReadXml.h \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/mobility/GCRSBaseTraCIMobility.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	src/base/vehicleManager/GCRSBaseVehicleManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIMobility.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h
$O/src/base/net/GCRSBaseNetLayer.o: src/base/net/GCRSBaseNetLayer.cc \
	src/base/collectionService/GCRSBaseCollectionService.h \
	src/base/com/collection/GCRSBaseComCollectNetwork.h \
	src/base/com/collection/GCRSBaseComCollectNetworkController.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRange.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRangeController.h \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/collection/GCRSBaseComCollectPrintOut.h \
	src/base/com/collection/GCRSBaseComCollectStatistics.h \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/lib/GCRSBaseComNetwControlInfo.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/lib/GCRSBaseRealWorldTimer.h \
	src/base/com/lib/GCRSReadXml.h \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/connectionManager/GCRSBaseConnectionManager.h \
	src/base/const/GCRSBaseConst.h \
	src/base/mobility/GCRSBaseTraCIMobility.h \
	src/base/net/GCRSBaseNetLayer.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	src/base/vehicleManager/GCRSBaseVehicleManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIMobility.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/base/phy/GCRSBasePhyLayer.o: src/base/phy/GCRSBasePhyLayer.cc \
	src/base/analogueModel/GCRSBaseSimpleObstacleShadowing.h \
	src/base/phy/GCRSBasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/messages/AirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/ChannelSenseRequest_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BaseDecider.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Decider.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/analogueModel/JakesFading.h \
	$(MIXIM_PROJ)/src/modules/analogueModel/LogNormalShadowing.h \
	$(MIXIM_PROJ)/src/modules/analogueModel/SimpleObstacleShadowing.h \
	$(MIXIM_PROJ)/src/modules/analogueModel/SimplePathlossModel.h \
	$(MIXIM_PROJ)/src/modules/mac/ieee80211p/Mac80211pToPhy11pInterface.h \
	$(MIXIM_PROJ)/src/modules/obstacle/Obstacle.h \
	$(MIXIM_PROJ)/src/modules/obstacle/ObstacleControl.h \
	$(MIXIM_PROJ)/src/modules/phy/Decider80211p.h \
	$(MIXIM_PROJ)/src/modules/phy/Decider80211pToPhy80211pInterface.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer80211p.h \
	$(MIXIM_PROJ)/src/modules/phy/SNRThresholdDecider.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/base/pkt/GCRSBaseNetPkt_m.o: src/base/pkt/GCRSBaseNetPkt_m.cc \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/base/pkt/GCRSBasePkt_m.o: src/base/pkt/GCRSBasePkt_m.cc \
	src/base/pkt/GCRSBasePkt_m.h
$O/src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.o: src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.cc \
	src/base/com/lib/Convert.h \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/lib/GCRSBaseString.h \
	src/base/com/lib/GCRSReadXml.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIConstants.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h
$O/src/base/vehicleManager/GCRSBaseVehicleManager.o: src/base/vehicleManager/GCRSBaseVehicleManager.cc \
	src/base/com/lib/Convert.h \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/lib/GCRSReadXml.h \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	src/base/vehicleManager/GCRSBaseVehicleManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h
$O/src/base/world/GCRSBaseWorldUtility.o: src/base/world/GCRSBaseWorldUtility.cc \
	src/base/world/GCRSBaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/modules/com/task/drg/GCRSDRGComTask.o: src/modules/com/task/drg/GCRSDRGComTask.cc \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/modules/com/task/drg/GCRSDRGComTask.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/modules/com/task/drg/GCRSDRGComTaskManager.o: src/modules/com/task/drg/GCRSDRGComTaskManager.cc \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/modules/com/task/drg/GCRSDRGComTask.h \
	src/modules/com/task/drg/GCRSDRGComTaskManager.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/modules/com/task/dtsg/GCRSDTSGComTask.o: src/modules/com/task/dtsg/GCRSDTSGComTask.cc \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/modules/com/task/dtsg/GCRSDTSGComTask.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/modules/com/task/dtsg/GCRSDTSGComTaskManager.o: src/modules/com/task/dtsg/GCRSDTSGComTaskManager.cc \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/modules/com/task/dtsg/GCRSDTSGComTask.h \
	src/modules/com/task/dtsg/GCRSDTSGComTaskManager.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/modules/com/task/flooding/GCRSFloodingComTask.o: src/modules/com/task/flooding/GCRSFloodingComTask.cc \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/modules/com/task/flooding/GCRSFloodingComTask.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/modules/com/task/flooding/GCRSFloodingComTaskManager.o: src/modules/com/task/flooding/GCRSFloodingComTaskManager.cc \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/modules/com/task/flooding/GCRSFloodingComTask.h \
	src/modules/com/task/flooding/GCRSFloodingComTaskManager.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/modules/com/task/rover/GCRSROVERComTask.o: src/modules/com/task/rover/GCRSROVERComTask.cc \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/modules/com/task/rover/GCRSROVERComTask.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/modules/com/task/rover/GCRSROVERComTaskManager.o: src/modules/com/task/rover/GCRSROVERComTaskManager.cc \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/modules/com/task/rover/GCRSROVERComTask.h \
	src/modules/com/task/rover/GCRSROVERComTaskManager.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h
$O/src/modules/net/GCRSDRGNetLayer.o: src/modules/net/GCRSDRGNetLayer.cc \
	src/base/collectionService/GCRSBaseCollectionService.h \
	src/base/com/collection/GCRSBaseComCollectNetwork.h \
	src/base/com/collection/GCRSBaseComCollectNetworkController.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRange.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRangeController.h \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/collection/GCRSBaseComCollectPrintOut.h \
	src/base/com/collection/GCRSBaseComCollectStatistics.h \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/lib/GCRSBaseComNetwControlInfo.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/lib/GCRSBaseRealWorldTimer.h \
	src/base/com/lib/GCRSReadXml.h \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/connectionManager/GCRSBaseConnectionManager.h \
	src/base/mobility/GCRSBaseTraCIMobility.h \
	src/base/net/GCRSBaseNetLayer.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	src/base/vehicleManager/GCRSBaseVehicleManager.h \
	src/modules/com/task/drg/GCRSDRGComTask.h \
	src/modules/com/task/drg/GCRSDRGComTaskManager.h \
	src/modules/net/GCRSDRGNetLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIMobility.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/modules/net/GCRSDTSGNetLayer.o: src/modules/net/GCRSDTSGNetLayer.cc \
	src/base/collectionService/GCRSBaseCollectionService.h \
	src/base/com/collection/GCRSBaseComCollectNetwork.h \
	src/base/com/collection/GCRSBaseComCollectNetworkController.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRange.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRangeController.h \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/collection/GCRSBaseComCollectPrintOut.h \
	src/base/com/collection/GCRSBaseComCollectStatistics.h \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/lib/GCRSBaseComNetwControlInfo.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/lib/GCRSBaseRealWorldTimer.h \
	src/base/com/lib/GCRSReadXml.h \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/connectionManager/GCRSBaseConnectionManager.h \
	src/base/const/GCRSBaseConst.h \
	src/base/mobility/GCRSBaseTraCIMobility.h \
	src/base/net/GCRSBaseNetLayer.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	src/base/vehicleManager/GCRSBaseVehicleManager.h \
	src/modules/com/task/dtsg/GCRSDTSGComTask.h \
	src/modules/com/task/dtsg/GCRSDTSGComTaskManager.h \
	src/modules/net/GCRSDTSGNetLayer.h \
	src/modules/pkt/GCRSDTSGNetPkt_m.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIMobility.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/modules/net/GCRSDummyNetLayer.o: src/modules/net/GCRSDummyNetLayer.cc \
	src/base/collectionService/GCRSBaseCollectionService.h \
	src/base/com/collection/GCRSBaseComCollectNetwork.h \
	src/base/com/collection/GCRSBaseComCollectNetworkController.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRange.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRangeController.h \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/collection/GCRSBaseComCollectPrintOut.h \
	src/base/com/collection/GCRSBaseComCollectStatistics.h \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/lib/GCRSBaseComNetwControlInfo.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/lib/GCRSBaseRealWorldTimer.h \
	src/base/com/lib/GCRSReadXml.h \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/connectionManager/GCRSBaseConnectionManager.h \
	src/base/mobility/GCRSBaseTraCIMobility.h \
	src/base/net/GCRSBaseNetLayer.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	src/base/vehicleManager/GCRSBaseVehicleManager.h \
	src/modules/com/task/flooding/GCRSFloodingComTask.h \
	src/modules/com/task/flooding/GCRSFloodingComTaskManager.h \
	src/modules/net/GCRSDummyNetLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIMobility.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/modules/net/GCRSFloodingNetLayer.o: src/modules/net/GCRSFloodingNetLayer.cc \
	src/base/collectionService/GCRSBaseCollectionService.h \
	src/base/com/collection/GCRSBaseComCollectNetwork.h \
	src/base/com/collection/GCRSBaseComCollectNetworkController.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRange.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRangeController.h \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/collection/GCRSBaseComCollectPrintOut.h \
	src/base/com/collection/GCRSBaseComCollectStatistics.h \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/lib/GCRSBaseComNetwControlInfo.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/lib/GCRSBaseRealWorldTimer.h \
	src/base/com/lib/GCRSReadXml.h \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/connectionManager/GCRSBaseConnectionManager.h \
	src/base/mobility/GCRSBaseTraCIMobility.h \
	src/base/net/GCRSBaseNetLayer.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	src/base/vehicleManager/GCRSBaseVehicleManager.h \
	src/modules/com/task/flooding/GCRSFloodingComTask.h \
	src/modules/com/task/flooding/GCRSFloodingComTaskManager.h \
	src/modules/net/GCRSFloodingNetLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIMobility.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/modules/net/GCRSROVERNetLayer.o: src/modules/net/GCRSROVERNetLayer.cc \
	src/base/collectionService/GCRSBaseCollectionService.h \
	src/base/com/collection/GCRSBaseComCollectNetwork.h \
	src/base/com/collection/GCRSBaseComCollectNetworkController.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRange.h \
	src/base/com/collection/GCRSBaseComCollectNetworkRangeController.h \
	src/base/com/collection/GCRSBaseComCollectNode.h \
	src/base/com/collection/GCRSBaseComCollectPrintOut.h \
	src/base/com/collection/GCRSBaseComCollectStatistics.h \
	src/base/com/collection/GCRSBaseComNin.h \
	src/base/com/lib/GCRSBaseComMath.h \
	src/base/com/lib/GCRSBaseComNetwControlInfo.h \
	src/base/com/lib/GCRSBaseComTTL.h \
	src/base/com/lib/GCRSBaseRealWorldTimer.h \
	src/base/com/lib/GCRSReadXml.h \
	src/base/com/lib/tinyxml/tinystr.h \
	src/base/com/lib/tinyxml/tinyxml.h \
	src/base/com/task/GCRSBaseComTask.h \
	src/base/com/task/GCRSBaseComTaskManager.h \
	src/base/com/vehicle/GCRSBaseComVehicleControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleEvent.h \
	src/base/com/vehicle/GCRSBaseComVehicleEventControl.h \
	src/base/com/vehicle/GCRSBaseComVehicleState.h \
	src/base/com/vehicle/GCRSBaseComVin.h \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/connectionManager/GCRSBaseConnectionManager.h \
	src/base/mobility/GCRSBaseTraCIMobility.h \
	src/base/net/GCRSBaseNetLayer.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/base/traci/GCRSBaseTraCIScenarioManagerLaunchd.h \
	src/base/vehicleManager/GCRSBaseVehicleManager.h \
	src/modules/com/task/rover/GCRSROVERComTask.h \
	src/modules/com/task/rover/GCRSROVERComTaskManager.h \
	src/modules/net/GCRSROVERNetLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManager.h \
	$(MIXIM_PROJ)/src/base/connectionManager/NicEntry.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIMobility.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(MIXIM_PROJ)/src/modules/mobility/traci/TraCIScenarioManagerLaunchd.h \
	$(MIXIM_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/src/modules/pkt/GCRSDTSGNetPkt_m.o: src/modules/pkt/GCRSDTSGNetPkt_m.cc \
	src/base/com/zone/GCRSBaseComBaseShape.h \
	src/base/com/zone/GCRSBaseComCircle.h \
	src/base/com/zone/GCRSBaseComEllipse.h \
	src/base/com/zone/GCRSBaseComRectangle.h \
	src/base/com/zone/GCRSBaseComZone.h \
	src/base/pkt/GCRSBaseNetPkt_m.h \
	src/modules/pkt/GCRSDTSGNetPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h

