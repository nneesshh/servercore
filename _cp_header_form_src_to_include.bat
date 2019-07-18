if not exist ".\include\servercore\" mkdir ".\include\servercore\"
xcopy ".\src\*.h*" ".\include\servercore\" /D /E /I /F /Y
rmdir /s /q "./include/servercore/thirdparty"