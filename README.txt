==========================================================================

           OOP2 - ex4
=================================
by: David Sapir & Shimson Polak 
id: David - 208917351
    Shimshon - 315605642 


			     Plumber 
==========================================================================

  			   Description
                        =================	
Gameplay description:
Puzzle game based on 'Pipe' game.
You can rotate different pipes except for the Target pipe,
and connections between different types of pipes, If a pipe is connected
to the 'Source' pipe water will flow through the connected pipes.

The Goal:
Connect all the pipes from the 'Source' pipe to the 'Target' pipe

Notes:
There might be different routes from Source to Target,
 but there is one solution at least guaranteed.

The pipes map is built randomly and on each completion,
 the map size will be increased.


The pipes Description:
Source pipe(Red wheel) - Allowing water to flow between pipes
(through one output)connected to it directly and not directly

Target pipe(Circle container) - Allowing to receive water(through one output)

T Pipe(T shape pipe) - A pipe with  1 input and 2 outputs.

I Pipe(I shape pipe - A pipe with 1 input and 1 output in direct line.

L Pipe(L shape pipe) - A pipe whith 1 input and 1 output not in direct line.

=============================================================================

                       	   Design
                      =================
Controller
==========
Role: Manage the different screens and control the game run.
      The Controller Holds the board and checks whenever a pipe 
      route is connected between Source and Target.

Board
========
Role: Container of the pipes existed in the world, the class first 
	built randomly NxN generated map of chars and than built 
	the Pipes world according to the map.
       The class also built an adjacency list,
	according to the pipes that existed on board.
	The board allowing the Controller to make changes 
	by using the access function to the relevant data accordingly.

Pipe
====
Role: Base class of the different pipes, the class allowing the rotation the
	same way to all pipes except the target, the rotation changes the input
	and output of the pipe according to the direction rotated to.
	The entrances saved in a 4 size array which represents direction,
	[0] - left,[1] - up,[2] - right,[3] - down
	On each direction the pipe is heading, the value will be 1, and the
	direction which the pipe not directed will be 0.


SourcePipe
==========
Inherit from:Pipe
Role: Have one output,established water flow through the pipes connected.


TargetPipe
==========
Inherit from:Pipe
Role: Have one input and cannot be rotated.
 The role is to be connect not directly through other pipes to SourcePipe.


T_Pipe
======
Inherit from:Pipe
Role: Have 3 input/output paths  to other pipes and can be rotated.

I_Pipe
======
Inherit from:Pipe
Role: Have 2 input/output paths ,on straight line,
to other pipes and can be rotated.

L_Pipe
======
Inherit from:Pipe
Role: Have 2 input/output paths, not on straight line, 
to other pipes and can be rotated.


Resources
=========
Role:Using Singleton design pattern to hold all the assets used in the 
game.Such as sounds, textures, text font, etc...

Screens in the game:
====================
	Menu:
	====
	Role: Allowing the user: Start the game,See the instruction,exit the game.

	InstructionScreen:
	=================
	Role: Showing the user info about the game.

	EndGameScreen:
	=============
	Role: Show the stats achived in the game, such as: 
		-How much time passed since started.
		-How many taps was made.
		-Which stage he finished.
	
	NextStagePopUp
	==============
	Role: Note the user, he finished the current stage.

=======================================================================

                          Included files
                        =================
1) Controller.cpp - Run the screen and the game.

2) Board.cpp	- Hold the game data map and data structures used.

3) Pipe.cpp - Base class of differents Pipes in the game.

4) SourcePipe.cpp - The source pipe in the game.

5) TargetPipe.cpp - The target pipe in the game.

6) T_Pipe.cpp - T pipe shape in the game.

7) I_Pipe.cpp - I pipe shape in the game.

8) L_Pipe.cpp - L pipe shape in the game.

9) Resources.cpp - Hold all the assets used in the game.

10) Menu.cpp - Menu screen of the game.

11) InstructionScreen.h/cpp - Instruction of the game screen.

12) EndGameScreen.cpp - End game screen.

13) NextStagePopUp.cpp - Small window show not the user succeed in the stage.

14) Macros.h - Hold the consts used in the program.

13 source + 14 header = 27 files in total.

main.cpp was given.
=====================================================================

                           Data Structure
                          =================
-Map(2d vector NxN):
- Reprasant the map of the pipes existed in the game.
The chars used:
's' - Source pipe
't' - Target pipe
'x' - Forbiden pipes'

-Route(deque):
- hold specific route from Source to Target

Pipes board(2d vector NxN of shared ptr Pipes):
-Hold the Pipes object in the game built according the
-Map and the Route from source to target.

Adjacency list
(Map< key:index positon of pipe , value: list of neighbours pipes pointer>):
- Hold index of all pipes existed in the game,for each 
  index stored save the list,
  of existed pipes to check if there is a connection 
  thorugh them(if they connected to source).


=====================================================================

                        Algorithms worth mention:
                      =============================
1.Path from Source to Targert using backtracking:
Save the Route from Source to Target by the following algorithm:
	1.Insert Source index
	2.Check each node connected to the current node
	 and mark it as a visited node
	3.if the node is the target return true and save the route used.
	4.if not continue to the next connected node,if a connected 
	returned true,save in deque the current node and return true,
	else check the next node connected.
	5.if there are no connected nodes or they were already visited.
	return false.


2.Random map generator-
Set the pipes according to the following algorithm:
	 1.On the matrix(NxN) of chars, which represent the pipes on the board,
	 choose 'source' 'target' nodes.
	 2.Put the 'forbiden' nodes which cant be part of the route through
	 3.find and save route from 'source' to 'target' using 
	"Path from Source to Target using backtracking" as described.
	 if a route is found go to stage 5.
	 4.If no route found, set new 'Target''Source' and run and
	 return to stage 2 again.
 	 5.put the pipes according to the route found.
 	 6.put the unfilled pipes randomly.


3.Check if source connected to 'Source' to 'Target':
	Find if the Source connected to Target:
	1.Pick the existed source location.
	2.Run BFS from the source pipe to adjacency pipes,
	that are connected.
	3.If the target is found, stop.
=====================================================================

			      Known bugs
      		         ===================
=====================================================================

			       Comments
=====================================================================
1.The program generate random map according to size given.

2.For each map generated ,a solution is guaranteed so each map
is solvable,but there might be more than one solution.

3.There can be empty places in the board which there are no pipes.

4.On each stage complated, a small pop up will be shown to continue to 
the next stage.

5.The time will show how much time passed since the user had started,and
not how much time he has.

6.Adjency list is calculated during the runtime.

7.When pipes are connected to the 'Source' pipe,The color will be changed
to exhibit water flow to note the user that the pipes are connected to
'Source'.

8.There are five stages overall which each start in different size.

9.On each stage complated, the size of the map will be increased the dimension
 of the coloumn and rows by one.

10.On completion of the game, the record of overall taps and time passed 
   will be displayed. The counting of the taps and time passed, is
   accumulated from the beggining.



