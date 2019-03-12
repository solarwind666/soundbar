target jtag jtag://127.0.0.1:1025
reset
b trap
b alignment
b up_assert
set $cr18=1
set $psr=0x80000100
set *0xba090000=0
set *0xba0a000c=0
set *0xba000018=0xf7ffffff
lo
restore dsp_firmware.bin binary 0xa1c00000
#restore mhdfw.bin binary 0xa1a00000
restore en16dst.fnt binary 0xa1b00000
restore ch16dst.fnt binary 0xa1b02000
c
