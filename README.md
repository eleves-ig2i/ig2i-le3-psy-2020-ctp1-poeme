# ig2i-le3-psy-2020-ctp1-poeme
CTP 1er session 2019/2020 de PSY LE3, le but étant d'écrire un poeme en utilisant les threads


compilation : 
gcc karaOK_vX.c -o karaokVX -pthread

compilation pour aficher le refrain (pas dasn le CR) :
gcc karaOK_vX.c -o karaOKVX -pthread -D _REFRAIN_

Contient le sujet de DS et le sujet de CTP

Axes d'améliorations :
corriger les fautes d'orthographes,
Gerer la fin des processus fils avec des SIGCHLD,
divers choses
