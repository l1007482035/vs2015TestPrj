@ECHO OFF
%1 %2
VER|FIND "5.">NUL&&GOTO GotPrivileges
mshta vbscript:createobject("shell.application").shellexecute("%~S0","GOTO GotPrivileges","","RUNAS",1)(window.close)&GOTO :EOF
:GotPrivileges
CD /D %~DP0 & GOTO Start
:Start
ECHO %~DP0Release\InjectDLL - Service.exe
sc create NoKill binPath= "%~DP0Release\InjectDLL - Service.exe" type= own
sc start NoKill
sc delete NoKill
PAUSE
GOTO :EOF
