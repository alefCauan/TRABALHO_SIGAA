#!/bin/bash

# Definindo os caminhos dos arquivos .c
SRC_COURSE="course/course.c"
SRC_ENROLLMENT="enrollment/enrollment.c"
SRC_STUDENT="student/student.c"
SRC_SUBJECT="subject/subjetc.c"
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

if [ ! -f "$SRC_SUBJECT" ]; then
    echo "Erro: Arquivo $SRC_SUBJECT não encontrado!"
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
gcc -c $SRC_SUBJECT -Icourse -o subject.o
gcc -c $SRC_MAIN -o sigaa.o

# Linkar os arquivos .o em um executável
gcc course.o enrollment.o student.o subject.o sigaa.o -o $OUT -g

# Limpar os arquivos .o (opcional)
rm *.o

# Mostrar mensagem de sucesso
echo "COMPILAÇÃO BEM SUCEDIDA"

# Roda o programa
./$OUT

# Remover o executável (opcional)
# rm $OUT
