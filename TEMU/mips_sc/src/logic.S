#include "trap.h"
   .set noat
   .globl main
   .text
main:

   ori		$t0, $t1,0x0000ffff		# $t0 = $t1 | 0
   sll		$t3, $t0,15			      # $t0 = $t1 << 0
   sll	   $t2, $t0,15     
   add		$t4, $t2, $t3		# $t0 = $t1 + $t2
   li $at, 0x10101010           #$at = 0x10101010
   li $v0, 0x01011111           #$v0 = 0x01011111
   and $t0, $at, $v0            #$t0 = 0x00001010
   
   HIT_GOOD_TRAP		#stop temu
