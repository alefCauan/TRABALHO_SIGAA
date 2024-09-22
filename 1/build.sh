#!/bin/bash

# Definindo os caminhos dos arquivos .c
SRC_COURSE="course/course.c"
SRC_ENROLLMENT="enrollment/enrollment.c"
SRC_STUDENT="student/student.c"
SRC_DISC="discipline/discipline.c"
SRC_MAIN="sigaa.c"

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

if [ ! -f "$SRC_MAIN" ]; then
    echo "Erro: Arquivo $SRC_MAIN não encontrado!"
    exit 1
fi

# Compilar os arquivos .c em .o
gcc -g -c $SRC_ENROLLMENT -Istudent -o enrollment.o
gcc -g -c $SRC_STUDENT -Ienrollment -Icourse -o student.o
gcc -g -c $SRC_COURSE -Isubjetc -o course.o
gcc -g -c $SRC_DISC -Icourse -o discipline.o
gcc -g -c $SRC_MAIN -o sigaa.o
gcc -g -c error.c -o error.o

# Linkar os arquivos .o em um executável
gcc -g course.o enrollment.o student.o discipline.o sigaa.o error.o -o $OUT 

# Limpar os arquivos .o (opcional)
rm *.o

./$OUT

# valgrind --leak-check=full ./sigaa_program
# tui enable 
# Mostrar mensagem de sucesso
echo "COMPILAÇÃO BEM SUCEDIDA"


