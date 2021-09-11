README

This is a logging program which will take in errors and display 
the full log as well as save them into a .log file.
------------------------------------------------------------------
Instructions:
./driver [-h] [-t seconds] <filename>

-h Will invoke the help which will display usage and
parameter usage. NOTE: This will also cause the program to end
after displaying help message, regardless of other parameters entered.

-t The log will display errors at an
intervals of seconds as indicated in the parameter.
<default value is: 1>

-filename this is an optional parameter. This will give a filename
for the program to save in. This filename will be appended with a
.log extension. <default filename is: message>

NOTE: In fact, you could just enter this parameter alone 
on program execution.

------------------------------------------------------------------

Program execution:
The program will randomly roll different errors for the
logging program. Classification will be: I(INFO), E(ERROR), 
W(WARN), and F(FATAL).

The errors will be logged into a list and this list will display
upon the end of the program. The entire log will also be saved
before the program end in a .log file.