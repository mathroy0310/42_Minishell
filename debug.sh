#	Author: Mathieu Roy
#	Debug.sh
#	Small Script to build and run the minishell
# 		- make fclean:		removes all object files and the executable
#		- make debug:		compiles the project with the DEBUG flag
# 		- make clean:		removes all object files
#		- clear:			clears the terminal
#		- ./minishell:		runs the executable
#

make fclean;
make debug;
make clean;
clear;
./minishell;