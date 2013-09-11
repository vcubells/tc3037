##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=t6c2e1
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/alumno/Desktop/Parallels Shared Folders/Home/svn/vcn/itesm/tc3037/trunk"
ProjectPath            := "/home/alumno/Desktop/Parallels Shared Folders/Home/svn/vcn/itesm/tc3037/trunk/t6c2e1"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Alumno
Date                   :=10/08/2012
CodeLitePath           :="/home/alumno/.codelite"
LinkerName             :=gcc
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=gcc
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/alumno/Desktop/Parallels Shared Folders/Home/svn/vcn/itesm/tc3037/trunk/t6c2e1/t6c2e1.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -O0 -Wall $(Preprocessors)
C_CmpOptions           := -g -O0 -Wall $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/t6c2e1_main$(ObjectSuffix): main.c $(IntermediateDirectory)/t6c2e1_main$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/media/psf/Home/svn/vcn/itesm/tc3037/trunk/t6c2e1/main.c" $(C_CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/t6c2e1_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/t6c2e1_main$(DependSuffix): main.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/t6c2e1_main$(ObjectSuffix) -MF$(IntermediateDirectory)/t6c2e1_main$(DependSuffix) -MM "/media/psf/Home/svn/vcn/itesm/tc3037/trunk/t6c2e1/main.c"

$(IntermediateDirectory)/t6c2e1_main$(PreprocessSuffix): main.c
	@$(C_CompilerName) $(C_CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/t6c2e1_main$(PreprocessSuffix) "/media/psf/Home/svn/vcn/itesm/tc3037/trunk/t6c2e1/main.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/t6c2e1_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/t6c2e1_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/t6c2e1_main$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/alumno/Desktop/Parallels Shared Folders/Home/svn/vcn/itesm/tc3037/trunk/.build-debug/t6c2e1"


