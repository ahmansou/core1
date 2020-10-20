.name "batman"
.comment "This city needs me"
	
live:
sti	r1, %:live, %1			;change live by the right value
# 1 1 1 2 2		7
sti	r1, %:live2, %1			;change live by the right value
# 1 1 1 2 2		14
ld	%1, r3
# 2 1 4 1 		22		
ld	%33, r6
# 2 1 4 1 		30
#While (r2 < 10)
forks:
# 30
add	r2, r3, r2		;increment r2
# 1 1 1 1 1		35
xor	r2, %15, r4		;if (r4) {carry = 0}
# 1 1 1 1 1		40
live2: live 	%4
# 40
# 1 4		45
	zjmp	%:endwhile		;if (carry)
# 1 2		48
	fork	%:forks
# 1 2		51
	ld	%0, r4			;carry = 1
# 2 1 4 1 	59

	zjmp	%:forks
# 1 2		52
#EndWhile
endwhile:
	ld	%0, r4			;carry = 1
# 2 1 4 1 	60

live:
# 60
	live %4
	zjmp %:live
