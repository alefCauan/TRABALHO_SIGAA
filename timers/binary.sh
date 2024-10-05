#!/bin/bash

# Definindo os caminhos dos arquivos .c
SRC_COURSE="../binary_tree/course/course.c"
SRC_ENROLLMENT="../binary_tree/enrollment/enrollment.c"
SRC_STUDENT="../binary_tree/student/student.c"
SRC_DISC="../binary_tree/discipline/discipline.c"
SRC_ERROR="../binary_tree/error.c"

# Nome do arquivo de saída
OUT="sigaa_program"

# Verificação para garantir que os arquivos existem
if [ ! -f "$SRC_COURSE" ]; then
    echo "Erro: Arquivo $SRC_COURSE não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_ENROLLMENT" ]; then
    echo "Erro: Arquivo $SRC_ENROLLMENT não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_STUDENT" ]; then
    echo "Erro: Arquivo $SRC_STUDENT não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_DISC" ]; then
    echo "Erro: Arquivo $SRC_DISC não encontrado!"
    exit 1
fi

# Compilar os arquivos .c em .o
gcc -g -c $SRC_ENROLLMENT -Istudent -o enrollment.o
gcc -g -c $SRC_STUDENT -Ienrollment -Icourse -o student.o
gcc -g -c $SRC_COURSE -Isubjetc -o course.o
gcc -g -c $SRC_DISC -Icourse -o discipline.o
gcc -g -c $SRC_ERROR -o error.o

# Linkar os arquivos .o em um executável
gcc -g course.o enrollment.o student.o discipline.o error.o -o $OUT binary.c

# Limpar os arquivos .o (opcional)
rm *.o

./$OUT

rm $OUT

# valgrind --leak-check=full ./sigaa_program
# tui enable 
# Mostrar mensagem de sucesso
echo "COMPILAÇÃO BEM SUCEDIDA"


