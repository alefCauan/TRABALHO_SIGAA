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
gcc -c $SRC_ENROLLMENT -Istudent -o enrollment.o
gcc -c $SRC_STUDENT -Ienrollment -Icourse -o student.o
gcc -c $SRC_COURSE -Isubjetc -o course.o
gcc -c $SRC_DISC -Icourse -o discipline.o
gcc -c $SRC_MAIN -o sigaa.o
gcc -c error.c -o error.o

# Linkar os arquivos .o em um executável
gcc course.o enrollment.o student.o discipline.o sigaa.o error.o -o $OUT -g

# Limpar os arquivos .o (opcional)
rm *.o

# Mostrar mensagem de sucesso
echo "COMPILAÇÃO BEM SUCEDIDA"

# Roda o programa
./$OUT

# Remover o executável (opcional)
# rm $OUT
