This program is a simple implementation of a FIFO manager written in C. It allows the user to create, initialize, input new data into and display a first-in, first-out (FIFO) queue.

#Usage
The program can be compiled using a C compiler, such as GCC, and then run from the command line.

When the program is running, it displays a menu of options to the user, as follows:

'N'ew Pile: creates a new queue and initializes it to all zeros.
'A'fficher la Pile: displays the current contents of the queue.
'I'nitialiser une Pile: reinitializes an existing queue to all zeros.
'E'ntrer une nouvelle valeur: allows the user to enter new data into the queue.
'L'ire la prochaine valeur: removes and displays the next value from the queue.
'Q'uitter: quits the program.


#Code Overview
The program consists of several subroutines, each responsible for a different task:

sp_ini(): initializes a Tpile structure.
sp_mpr(): displays the main menu and gets user input.
sp_ecr(): writes new data to the queue.
sp_aff(): displays the contents of the queue.
The Tpile structure represents a FIFO queue, and contains the following fields:

value: an array of integers that holds the queue data.
point_wr: an integer that represents the current write pointer position.
point_rd: an integer that represents the current read pointer position.


Limitations
The maximum number of elements in the queue is defined by the NB_ELT_MAX constant, which is set to 20.
The program does not handle errors or exceptions very well, so it may crash or behave unexpectedly if the user enters incorrect or unexpected input.
