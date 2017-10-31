@ECHO OFF
"E:\SOFTWARE\ATMEL\AvrAssembler2\avrasm2.exe" -S "F:\_avr_studio\KFAD\labels.tmp" -fI -W+ie -o "F:\_avr_studio\KFAD\KFAD.hex" -d "F:\_avr_studio\KFAD\KFAD.obj" -e "F:\_avr_studio\KFAD\KFAD.eep" -m "F:\_avr_studio\KFAD\KFAD.map" "F:\_avr_studio\KFAD\KFAD.asm"
