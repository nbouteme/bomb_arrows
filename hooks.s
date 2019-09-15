.text

.global onArrowHit
onArrowHit:
 	lis %r3, arr@ha
 	addi %r3, %r3, arr@l
 	stw %r31, 0(%r3)      # arr = $r31

	lwz        %r3,0x54(%r30) # restore overwritten instruction
	b arrowhithook
