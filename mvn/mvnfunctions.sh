# mvnrc 
# 
# Author: gpg
#
# Usage:
#  $ source ./mvnfunctions.sh 
#  $ borala  
JAVARUN="java -cp"
MVNDL="java -jar MvnPcs4_wDumperLoader.jar"
MLR="$JAVARUN PCS2302_MLR.jar"
MONTA="$MLR montador.MvnAsm"
LINKA="$MLR linker.MvnLinker"
RELOCA="$MLR relocator.MvnRelocator"

MVNFILES=mvnfiles 
# Usage:
# makelib lib.asm 
function mvn_makelib () {
    $MONTA $1 && {
        echo `basename $1 .asm`.mvn >> $MVNFILES
        return 0
    }
    return 1
}

function mvn_prog_size() {
    lines=$(cat $1 | wc -l)
    echo $lines*2 | bc
}

function mvn_clean_reloca() {
    rm -f relocados.list
}

function mvn_reloca_var() {
    OUTNAME=`basename $1 .mvn`_relocado.mvn
    OUTSIZE=$(prog_size $1)
    echo RELOCANDO $1, comeco: $2, tamanho: $OUTSIZE 1>&2 
    START=$(printf "%X\n" $2)
    $RELOCA $1 $OUTNAME $2 1>&2 || return 1
    cat $OUTNAME 1>&2
    echo $OUTNAME >> relocados.list
    echo $OUTSIZE | bc
}

function mvn_makemain () {
    OUTNAME=`basename $1 .asm`.out 
    MAIN=`basename $1 .asm`.mvn 
    BINARY=`basename $1 .asm`

    # make main or die 
    $MONTA $1 || {
        return 1
    }
    {
        mvn_clean_reloca 

        SIZEREL=$(mvn_prog_size $MAIN) || return 1
        BUTTER=$(cat $MVNFILES | sort -u)
        echo Ligando as bagaca
        $LINKA $MAIN $BUTTER -s $OUTNAME 
        echo Jogando tudo pra baixo da main 
        $RELOCA $OUTNAME $BINARY $SIZEREL 
        echo "AAA LEK LEK"
        read -p "RODO os Paranaue (s/n)?" choice
        case "$choice" in 
            s|S ) echo "Your binary is called: $BINARY"; mvn_borala;;
            n|N ) return 0;;
            * ) echo "invalid";;
        esac
    }
}

function mvn_cleanlib () {
    rm -f $MVNFILES
}

function mvn_borala () {
    rlwrap $MVNDL
}
