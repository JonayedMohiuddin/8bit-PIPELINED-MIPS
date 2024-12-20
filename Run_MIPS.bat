@echo off
:: Display the options
echo Logisim might give The required library file 'ALUjar' is missing. Please select the file from the following dialog. error. Just select the ALU.jar from directory.
echo Choose a circuit to run:
echo 1. MIPS
echo 2. Pipelined MIPS
echo 3. Extended IO MIPS
echo 4. Extended IO Pipelined MIPS

:: Get the user input
set /p choice="Enter your choice (1-4): "

:: Check if the user input is valid
if "%choice%"=="1" (
    set circuit="MIPS_Normal\MIPS_NonPipelined.circ"
) else if "%choice%"=="2" (
    set circuit="MIPS_Normal\MIPS_Pipelined.circ"
) else if "%choice%"=="3" (
    set circuit="MIPS_Extended\MIPS_NonPipelined_Extended.circ"
) else if "%choice%"=="4" (
    set circuit="MIPS_Extended\MIPS_Pipelined_Extended.circ"
) else (
    echo Invalid choice! Exiting...
    exit /b
)

:: Check if the Logisim JAR and the selected circuit exist
if not exist "%circuit%" (
    echo The selected circuit file "%circuit%" does not exist!
    exit /b
)
if not exist "logisim-generic-2.7.1.jar" (
    echo logisim-generic-2.7.1.jar not found!
    exit /b
)

:: Run Logisim with the selected .circ file
java -jar logisim-generic-2.7.1.jar "%circuit%"
