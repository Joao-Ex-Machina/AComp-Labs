#1. CONSIDERAR UM PROCESSADOR SEM FORWARDING (5-stage processor w/o forwarding or hazard detection)
#    1A. Identificar os hazards [2 pontos]
#    1B. Resolver com NOPs [1 ponto]
#    1C. Reordenar as instruções de forma a reduzir o numero de NOPs [1 ponto]
# 
# 2. CONSIDERAR UM PROCESSADOR COM FORWARDING
#    Comparar a estatística (IPC, racio instruções uteis/total) de 1B, 1C no processador original (5-stage processor w/o forwarding or hazard detection) e completo (5-stage processor) [1 ponto]


# Computer Architectures
# Lab: Pipelining

# The following program processes two arbitrarily sized one-dimensional
# vectors composed by N integer elements, in order to execute
# the following pseudo-code algorithm:

#    int a[N] = { ..... }
#    int b[N] = { ..... }
#    int N = /* Vectors Size */
#    int res = 0, tmp = 0;
#    register int i = 0;
#
#    while (a[N-i-1] > b[i] ) {
#    //it is assumed that this condition isn't verified for an arbitrairy i < N
#        tmp += a[i] / b[i];
#        res+= a[N-i-1] * b[i];
#        i+2;
#    }

.data
# IMPORTANT: do not change this section
a:    .word 1, 5, 9, 2, 3, 34, 4, 7, 9, 5, 3, 3
b:    .word 2, 1, 1, 6, 5, 2, 3, 4, 2, 4, 7, 1
res:  .word 0
tmp:  .word 0

.text
# NOTE: Upon start, the Global-Pointer (gp=x3) points to the beginning of .data section
addi x12, x3, 0 #x12 = a's left index

addi x11, x12, 44 #x11 = a's right index
addi x13, x12, 48 #13 = b's left index

lw x14, 96(x3) #x14 = res
lw x15, 52(x13) #x15 = tmp
li x16, 0 #x16 = i
li x17 48 #N*size

while:

    add x18, x13, x16 #x18 = &b[i]
    lw x18, 0(x18) #x18 = b[i]

    sub x19, x11, x16 #x19 = &a[N-i-1]
    lw x19, 0(x19) #x19 = a[N-i-1]
    
    slt x22 x18 x19 #a[N-i-1] > b[i]?
    slt x23 x16 x17 #i < N/2?
    and x23 x22 x23 
    li x20 0
 
    beq x23, x20, end #if !(a[N-i-1] > b[i] && i < N) exit loop
    
    add x20, x12, x16 #x20 = &a[i]

    lw x20, 0(x20) #x20 = a[i]

    div x20, x20, x18 #x20 = a[i] / b[i]
    mul x21, x19, x18 #x21 = a[N-i-1] * b[i]

    add x15, x15, x21 #res += x20
    add x14, x14, x20 #tmp += x21
    
    addi x16, x16, 4 #i
    
    jal x0, while
    
    
end:
    sw x14, 96(x3)
    sw x15, 52(x13)
    
    
# Expected result: M[res] = d5h
#                  M[tmp] = 20h

