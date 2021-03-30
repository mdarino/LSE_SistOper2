##  Real time system II - (RTOS)

Personal resolution of the different practices required in the Subject.

Curse program ([link](http://laboratorios.fi.uba.ar/lse/cursos.html#Oferta_cursos_2020)) 
LSE ([link](http://laboratorios.fi.uba.ar/lse/))
University ([link](http://www.fi.uba.ar/)) Universidad de Buenos Aires

This is the root directory of the CIAA Firmware Project

<b>git clone <i>--recursive</i> https://github.com/ciaa/Firmware.git</b>

## Supported boards:
- CIAA-NXP and EDU-CIAA-NXP (www.proyecto-ciaa.com.ar)

## Supported toolchains:
- gcc-arm-none-eabi

## Usage
* Copy ```project.mk.template``` to ```project.mk```.
* Define ```PROJECT```, ```TARGET``` and ```BOARD``` (optional) variables in ```project.mk``` according to the project you want to compile.
* Compile with ```make```.
* Clean with ```make clean```.
* Download to target via OpenOCD with ```make download```.

