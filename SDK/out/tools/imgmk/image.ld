MEMORY
{
    BOT : ORIGIN = 0x0 , LENGTH = 0x8000
    BT1 : ORIGIN = 0x8000 , LENGTH = 0x1000
    BT2 : ORIGIN = 0x9000 , LENGTH = 0x1000
    CFG  : ORIGIN = 0xb000 , LENGTH = 0x8000
    MAN  : ORIGIN = 0x12000 , LENGTH = 0x1000
    IMG  : ORIGIN = 0x13000 , LENGTH = 0x500000
}

SECTIONS
{
     .data : {
           boot.o(.data)
     }>BOT
     .data1 : {
           btupdate1.o(.data)
     }>BT1
     .data2 : {
           btupdate2.o(.data)
     }>BT2
     .data3 : {
           bootcfg.o(.data)
     }>CFG
     .data4 : {
           manifest.o(.data)
     }>MAN
     .data5 : {
           image.o(.data)
     }>IMG

}
