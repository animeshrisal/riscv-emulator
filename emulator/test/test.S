.global _boot
.text

_boot:                    /* x0  = 0    0x000 */
    /* Test ADDI */
    addi x1 , x0,   2000  /* x1  = 1000 0x3E8 */
  addi x2 , x1,   2000  /* x2  = 3000 0xBB8 */
    addi x3, x0, -500
    add x5, x1, x2 

