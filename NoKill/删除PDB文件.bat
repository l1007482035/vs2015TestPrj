@FOR /R %%i IN (*.pdb) DO @DEL /F /S /Q "%%i"
@FOR /R %%i IN (*.ipdb) DO @DEL /F /S /Q "%%i"
@FOR /R %%i IN (*.iobj) DO @DEL /F /S /Q "%%i"
@FOR /R %%i IN (*.log) DO @DEL /F /S /Q "%%i"
