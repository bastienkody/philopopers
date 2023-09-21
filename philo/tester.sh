#! /bin/bash

# -------------------------------------------------------------------------------------------------------------------------------------
#  INTRO - CONST
# -------------------------------------------------------------------------------------------------------------------------------------
EXEC_N=philo

# const
ITA="\033[3m"
UNDERL="\033[4m"
GREEN="\033[32m"
RED="\033[31m"
YEL="\033[33m"
END="\033[m"
BLU_BG="\033[44m"
YEL_BG="\033[43;1m"
RED_BG="\033[41;1m"

# machine spec
uname -s | grep -qi darwin && os=mac
uname -s | grep -qi linux && os=linux
[[ $os != "linux" ]] && echo -e "${ITA}No valgrind testing (uncompatible os)${END}"
[[ $os != "linux" ]] && [[ $(which timeout ; echo $?) == 1 ]] && echo -e "${ITA}Please install coreutils via homebrew${END}" && exit 1

# -------------------------------------------------------------------------------------------------------------------------------------
#  NORMINETTE
# -------------------------------------------------------------------------------------------------------------------------------------
echo -ne "${BLU_BG}Test norminette:${END} \t\t-->"
norm=$(find . | egrep ".*(\.c|\.h)$" | norminette)
if [[ $(echo "$norm" | egrep -v "OK\!$") ]] ;
then
	echo -e "${RED} norme errors${END}"
	#echo -e "$norm" | egrep -v "OK\!$"
else
	echo -e "${GREEN} norm ok${END}"
fi

# -------------------------------------------------------------------------------------------------------------------------------------
#  MAKEFILE (no bonus)
# -------------------------------------------------------------------------------------------------------------------------------------
echo -ne "${BLU_BG}Test Makefile:${END} \t\t\t-->"
make re 1>/dev/null 2> stderrmake.txt
make > stdoutmakebis.txt 2>&1
[[ -s stderrmake.txt ]] && echo -ne "${RED} make wrote on std err${END}" || echo -ne "${GREEN} no make error${END}" 
echo -n " -- "
cat stdoutmakebis.txt | egrep -viq "(nothin|already|date)" && echo -ne "${RED}makefile relink?${END}" || echo -ne "${GREEN}no relink${END}"
echo -n " -- "
[[ -f $EXEC_N && -x $EXEC_N ]] && echo -e "${GREEN}exec == ${EXEC_N}${END}" || echo -e "${RED}no exec file found named ${EXEC_N}${END}"
rm -rf stderrmake.txt stdoutmakebis.txt

[[ ! -f ${EXEC_N} ]] && { echo -e "${RED_BG}No exec ${EXEC_N}. Tester exiting.${END}" ; make fclean >/dev/null 2>&1 ; exit ; }
[[ ! -x ${EXEC_N} ]] && { echo -e "${RED_BG}No exec rights on ${EXEC_N}. Tester exiting.${END}" ; make fclean >/dev/null 2>&1 ; exit ; }

# -------------------------------------------------------------------------------------------------------------------------------------
#  ARGUMENTS BAD NUMBER
# -------------------------------------------------------------------------------------------------------------------------------------
echo -ne "${BLU_BG}Test arg nb (<4 && >5):${END} \t-->"
timeout 1 ./${EXEC_N} > no_arg.txt 2> no_arg_err.txt
timeout 1 ./${EXEC_N} 1 > one_arg.txt 2> one_arg_err.txt
timeout 1 ./${EXEC_N} 1 800 > two_arg.txt 2> two_arg_err.txt
timeout 1 ./${EXEC_N} 1 800 200 > three_arg.txt 2> three_arg_err.txt
timeout 1 ./${EXEC_N} 5 800 200 200 7 56 > six_arg.txt 2> six_arg_err.txt
if [[ -s no_arg.txt || -s one_arg.txt || -s two_arg.txt || -s three_arg.txt || -s six_arg_.txt ]] ; then
	echo -e "${YEL} ${EXEC_N} wrote on std out (fd 1)${END} "
fi
if [[ -s no_arg_err.txt && -s one_arg_err.txt && -s two_arg_err.txt && -s three_arg_err.txt && six_arg_err.txt ]] ; then
	echo -e "${GREEN} ${EXEC_N} wrote on std err (fd 2)${END} "
fi
rm -rf *arg*.txt

# -------------------------------------------------------------------------------------------------------------------------------------
#  ARGUMENTS NEGATIVE VALUES 
# -------------------------------------------------------------------------------------------------------------------------------------
echo -ne "${BLU_BG}Negative values arg:${END} \t\t-->"

timeout 1 ./${EXEC_N} -2 800 200 200  >stdout1.txt 2> stderr1.txt
timeout 1 ./${EXEC_N} -2 800 200 200 4  >stdout2.txt 2> stderr2.txt
timeout 1 ./${EXEC_N} 2 -800 200 200 >stdout3.txt 2> stderr3.txt
timeout 1 ./${EXEC_N} 2 -800 200 200 4 >stdout4.txt 2> stderr4.txt
timeout 1 ./${EXEC_N} 2 800 -200 200 >stdout5.txt 2> stderr5.txt
timeout 1 ./${EXEC_N} 2 800 -200 200 4 >stdout6.txt 2> stderr6.txt
timeout 1 ./${EXEC_N} 2 800 200 -200 >stdout7.txt 2> stderr7.txt
timeout 1 ./${EXEC_N} 2 800 200 -200 4 >stdout8.txt 2> stderr8.txt
timeout 1 ./${EXEC_N} 2 800 200 200 -4 >stdout9.txt 2> stderr9.txt
if [[ -s stdout1.txt || -s stdout2.txt || -s stdout3.txt || -s stdout4.txt || -s stdout5.txt || -s stdout6.txt || -s stdout7.txt || -s stdout8.txt || -s stdout9.txt ]] ; then
	echo -ne "${YEL} ${EXEC_N} wrote on std out (fd 1)${END} "
fi
if [[ -s stderr1.txt && -s stderr2.txt && -s stderr3.txt && -s stderr4.txt && -s stderr5.txt && -s stderr6.txt && -s stderr7.txt && -s stderr8.txt && -s stderr9.txt ]] ; then
	echo -e "${GREEN} ${EXEC_N} wrote on std err (fd 2)${END} "
else
	echo -e "${YEL} ${EXEC_N} did not wrote on std err (fd 2)${END} "
fi
rm -rf stdout*.txt stderr*.txt

# -------------------------------------------------------------------------------------------------------------------------------------
#  ARGUMENTS NON DIGIT VALUES 
# -------------------------------------------------------------------------------------------------------------------------------------
echo -ne "${BLU_BG}Non digit values arg:${END} \t\t-->"

timeout 1 ./${EXEC_N} 2a 800 200 200  >stdout1.txt 2> stderr1.txt
timeout 1 ./${EXEC_N} A2 800 200 200 4  >stdout2.txt 2> stderr2.txt
timeout 1 ./${EXEC_N} 2 +800 200 200 >stdout3.txt 2> stderr3.txt
timeout 1 ./${EXEC_N} 2 80+0 200 200 4 >stdout4.txt 2> stderr4.txt
timeout 1 ./${EXEC_N} 2 800 200az 200 >stdout5.txt 2> stderr5.txt
timeout 1 ./${EXEC_N} 2 800 yoPI 200 4 >stdout6.txt 2> stderr6.txt
timeout 1 ./${EXEC_N} 2 800 200 ù >stdout7.txt 2> stderr7.txt
timeout 1 ./${EXEC_N} 2 800 200 %__ 4 >stdout8.txt 2> stderr8.txt
timeout 1 ./${EXEC_N} 2 800 200 200 456r >stdout9.txt 2> stderr9.txt
if [[ -s stdout1.txt || -s stdout2.txt || -s stdout3.txt || -s stdout4.txt || -s stdout5.txt || -s stdout6.txt || -s stdout7.txt || -s stdout8.txt || -s stdout9.txt ]] ; then
	echo -ne "${YEL} ${EXEC_N} wrote on std out (fd 1)${END} "
fi
if [[ -s stderr1.txt && -s stderr2.txt && -s stderr3.txt && -s stderr4.txt && -s stderr5.txt && -s stderr6.txt && -s stderr7.txt && -s stderr8.txt && -s stderr9.txt ]] ; then
	echo -e "${GREEN} ${EXEC_N} wrote on std err (fd 2)${END} "
else
	echo -e "${YEL} ${EXEC_N} did not wrote on std err (fd 2)${END} "
fi
rm -rf stdout*.txt stderr*.txt

# -------------------------------------------------------------------------------------------------------------------------------------
#  ARGUMENTS OVER / UNDER - FLOW
# -------------------------------------------------------------------------------------------------------------------------------------
echo -ne "${BLU_BG}Over/Under flows values arg:${END} \t-->"

timeout 1 ./${EXEC_N} 2 2147483648 200 200  >stdout1.txt 2> stderr1.txt
timeout 1 ./${EXEC_N} 2 -2147483649 200 200 4  >stdout2.txt 2> stderr2.txt
timeout 1 ./${EXEC_N} 2 800 4294967296 200 >stdout3.txt 2> stderr3.txt
timeout 1 ./${EXEC_N} 2 800 -4294967297 200 4 >stdout4.txt 2> stderr4.txt
timeout 1 ./${EXEC_N} 2 800 200 6442450944 >stdout5.txt 2> stderr5.txt
timeout 1 ./${EXEC_N} 2 800 300 -6442450945 4 >stdout6.txt 2> stderr6.txt
timeout 1 ./${EXEC_N} 6442450944 800 200 3 >stdout7.txt 2> stderr7.txt
timeout 1 ./${EXEC_N} 2 800 200 5 10737418240 >stdout8.txt 2> stderr8.txt
timeout 1 ./${EXEC_N} 2 800 200 200 -10737418240 >stdout9.txt 2> stderr9.txt
if [[ -s stdout1.txt || -s stdout2.txt || -s stdout3.txt || -s stdout4.txt || -s stdout5.txt || -s stdout6.txt || -s stdout7.txt || -s stdout8.txt || -s stdout9.txt ]] ; then
	echo -ne "${YEL} ${EXEC_N} wrote on std out (fd 1)${END} "
fi
if [[ -s stderr1.txt && -s stderr2.txt && -s stderr3.txt && -s stderr4.txt && -s stderr5.txt && -s stderr6.txt && -s stderr7.txt && -s stderr8.txt && -s stderr9.txt ]] ; then
	echo -e "${GREEN} ${EXEC_N} wrote on std err (fd 2)${END} "
else
	echo -e "${YEL} ${EXEC_N} did not wrote on std err (fd 2)${END} "
fi
rm -rf stdout*.txt stderr*.txt




# -------------------------------------------------------------------------------------------------------------------------------------
#  ENDING
# -------------------------------------------------------------------------------------------------------------------------------------
make fclean >/dev/null 2>&1
