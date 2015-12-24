

REM To use:  MKS_make_foundations_gen6.bat AppType Target [RC]

@ECHO This batfile: %~dpfx0
@ECHO BUILDS the following GEN6 directory:

@REM do not display to screen
@ECHO OFF

BREAK=ON

REM begin localisation of Environment Variables
setlocal

REM set MKS make variable for characters that you can use to separate components in a path name \/:
set  DIRSEPSTR=\/:

REM choose toolset to make
set TOOLSET=RVDS

REM choose application to make (BOOT or APP)
set APPTYPE=%1

REM set name of boot target if building boot, must also set APPTYPE to BOOT above
REM see Mks_project_target_mx27.mk for list of projects
set BOOTTARGET=%2

REM set name of app target if building application, must also set APPTYPE to APP above
REM see Mks_project_target_mx27.mk for list of projects
set APPTARGET=%2

REM if BUILD_TYPE is BuildRelease the makefile will use release Software Version number.  Anything else (or nothing) will use the release candidate Software Bersion number.
REM By default, this batch file builds for release.  Any text whatsoever for option 3 will create a release candidate.
if "%3" == "" set BUILD_TYPE=BuildRelease


REM Set your root sand box working directory -THIS IS THE ONLY PATH YOU NEED TO CHANGE IN MOST CASES FOR YOUR SANDBOX,
REM Set to where the .pj s are, but only if you do not run this batch file from the same .pj directory (batch placed in different location) -
@ECHO ON
set DIR_SBOX_ROOT=%CD%
@ECHO OFF
@ECHO The Date: %DATE%
@ECHO The Time: %TIME%
@IF /I %APPTYPE%==BOOT @ECHO THE BOOT TARGET NAME: %BOOTTARGET%
@IF /I %APPTYPE%==APP @ECHO THE APP TARGET NAME: %APPTARGET%
@IF /I %APPTYPE%==SANITIZE @ECHO THE SANITIZE TARGET NAME: %APPTARGET%
@IF /I %APPTYPE%==SAN_APP @ECHO THE SAN_APP TARGET NAME: %APPTARGET%
set  make_target=MATRIX
if  '%1'=='SANITIZE'	set  make_target=SANITIZED_SANDBOX
@ECHO Running The %make_target% MAKE Operation:

REM *** you may need to change this path to MKS make ***
set MKSMAKE=".\tools\make"

REM call make.exe
REM -r must be first parameter so we do not call startup.mk
REM target appears after all -D specifications
%MKSMAKE% -r -DAPPTYPE=%APPTYPE%  -DBOOTTARGET=%BOOTTARGET% -DAPPTARGET=%APPTARGET% -DBUILD_TYPE=%BUILD_TYPE%  %make_target%
@ECHO The End Time: %TIME%

