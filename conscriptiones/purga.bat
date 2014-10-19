@ECHO OFF

SET NOMEN_SOLUTIONIS=ROSARIO

PUSHD ..
CALL :PURGA_TABULAM rosario
CALL :PURGA_TABULAM destinatum

IF EXIST IPCH RD /Q /S IPCH
IF EXIST %NOMEN_SOLUTIONIS%.SDF DEL /Q %NOMEN_SOLUTIONIS%.SDF
IF EXIST %NOMEN_SOLUTIONIS%.SUO (
	ATTRIB -H %NOMEN_SOLUTIONIS%.SUO
	DEL /Q %NOMEN_SOLUTIONIS%.SUO
)

POPD
EXIT /B 0

:PURGA_TABULAM
SETLOCAL

ECHO Purog tabulam, "%1" nominatur...

PUSHD %1
CALL :PURGA_STELLAM_SI_EST *.USER
IF EXIST WIN32 RD /Q /S WIN32
IF EXIST X64 RD /Q /S X64
POPD

ENDLOCAL
EXIT /B

:PURGA_STELLAM_SI_EST
SETLOCAL

FOR %%F IN ("%1") DO (
	DEL /Q "%%~nxF"
)

ENDLOCAL
EXIT /B