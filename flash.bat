@echo off
@echo ================================================
@echo ^|^|         Shortcut of Hex Flashing           ^|^|
@echo ^|^|        By Kenneth Au (02/02/2015)          ^|^|
@echo ================================================
@echo.
@echo Checking *.hex file...
@echo.

@if not exist "output/*.hex" (
	@echo ERROR: The *.hex file does not exist. Please check the followings:
	@echo - The project has been compiled successfully
	@echo - In Keil, under the 'Options for Targets...' ^=^> 'Output', 'Create HEX File' has been checked
) else if [%1] == [] (
	@echo ERROR: Missing argument 1 (the *.hex file location^). In Keil, use "./output/@H.hex".
	@goto missing_arg
) else if [%2] == [] (
	@echo ERROR: Missing argument 2 (COM Port number^). Please input the argument (e.g., COM30^). 
	@goto missing_arg
) else if [%3] == [] (
	@echo ERROR: Missing argument 3 (baudrate^). Please input the argument (e.g., 115200^).
	@goto missing_arg
) else if [%4] == [] (
	@echo ERROR: Missing argument 4 (target device^). Please input the target device (e.g., STM32F1_XL-density_768K^). You may check it through the GUI version. 
	@goto missing_arg
) else (
	@echo Checking the Flash Loader executable...
	@echo.
	@echo Prepare to flash...
	@echo.
	@echo Flash file "%1"
	@echo COM Port: %2
	@echo Baudrate: %3
	@echo Target: %4
	@echo. 
	
	@if exist "C:\Program Files\STMicroelectronics\Software\Flash Loader Demo\STMFlashLoader.exe" (
		@echo Start flashing...
		@echo.
		start "" /b /wait "C:\Program Files\STMicroelectronics\Software\Flash Loader Demo\STMFlashLoader.exe" -c --pn %2 --br %3 --to 1000 -i %4 -e --all -p --dwp --drp -d --a 8000000 --fn %1 
		@exit
	) else if exist "C:\Program Files (x86)\STMicroelectronics\Software\Flash Loader Demo\STMFlashLoader.exe" (
		@echo Start flashing...
		@echo.
		start "" /b /wait "C:\Program Files (x86)\STMicroelectronics\Software\Flash Loader Demo\STMFlashLoader.exe" -c --pn %2 --br %3 --to 1000 -i %4 -e --all -p --dwp --drp -d --a 8000000 --fn %1 
		@exit
	) else (
		@echo ERROR: The Flash Loader executable does not exist. Please check the followings:
		@echo - You have already installed Flash Loader Demonstrator 2.7.0
		@echo - You have installed Flash Loader Demonstrator under one of the following paths:
		@echo     - C^:\Program Files\STMicroelectronics\Software\Flash Loader Demo\
		@echo     - C^:\Program Files (x86^)\STMicroelectronics\Software\Flash Loader Demo\
		@echo - There exists an executable file called "STMFlashLoader.exe" under the path
	)
)

timeout /t 10
@exit

:missing_arg
@echo.
@echo This batch file requires FOUR arguments:
@echo    Arg1: The *.hex file location. In Keil, use "./output/@H.hex".
@echo    Arg2: The COM Port number (e.g., COM30^). 
@echo    Arg3: Baudrate (e.g., 115200, 256000^).
@echo    Arg4: Target device (e.g., STM32F1_XL-density_768K^). It may be auto detected from the Flash Loader GUI. 

timeout /t 10
@exit