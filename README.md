The Folding@Home GPU Statistics Database's HFM.NET Custom Parser
================================================================
Overview
--------
This program (or source code) was designed to take CSV file formats of some of HFM.NET's files and format an output suitable for submission into [The Folding@Home GPU Statistics Database](http://www.compdewddevelopment.com/redirect.php?target=fah-gpu-database).

It is important to note that this code does not incorporate serious error checking and was never intended to have any. The program compiled from this code was intended for the author's personal use. The reason this code was made public is because the author feels that it may be beneficial for others or the author's self if others could access the code. Constructive criticism is always welcome, and modification, use, and redistribution of the code for one's purposes is welcome as well (as long as it is not for used for commercial purposes or redistributed without proper licensing without permission from the author (please see the license distributed with this code)).

How to Use
----------
There are some preliminary steps that must be taken before one can properly use the program compiled from this source code.
Here are EXACTLY 9 easy steps to get this program to actually work rather than be a pile of source code:
(-4) Own a graphics card powerful enough for Folding@Home.
(-3) Own and successfully run a copy of Folding@Home using your graphics card. (For support see [The Folding@Home Support Forum](http://foldingforum.org/index.php).)
(-2) Own a copy of [HFM.NET](http://code.google.com/p/hfm-net/) and run Folding@Home and HFM.NET long enough to get some data.
(-1) Own a copy of some software that can read and export a SQLite database file to a CSV formatted file (I use [SQLite Database Browser](https://sourceforge.net/projects/sqlitebrowser/).
(1) Compile this source code into a directory that you name whatever you want.
(2) Open HFM.NET, click on the menu "Help", and click on "View HFM.NET Data Files".
(3) In the folder that is opened, open the "WuHistory.db3" file with the software you downloaded to export SQLite database files and export to a CSV format into the directory where you compiled this source code into an ".exe" file.
(NOTE: make sure the CSV format does not contain quotes around the fields, does not have a comma at the end of every line, and ends with an empty line. If those conditions are not met, this program will not work. To fix a CSV format error, try using a macro in a text editor such as [Notepad++](http://notepad-plus-plus.org/).)
(4) Make sure the CSV file of the "WuHistory.db3" file is named "WuHistory.csv"
(5) While still in HFM.NET's data files directory, open the "ProjectInfo.tab" file in your favorite text editor and find-and-replace every tab with a comma making sure that the conditions mentioned for the "WuHistory.csv" file are also met with this file.
(6) Save the file in the same directory that the "WuHistory.csv" file is located (which should be the same directory as the ".exe" file that was produced by compiling this source code).
(7) Run this program and select THE NUMBER of the core type you want to have output and the WU data averaged.
(8) The program should output two CSV files, of which the one containing the averaged data is the one that contains the averaged data.
(9) Be nice and submit your data to [The Folding@Home GPU Statistics Database](http://www.http://compdewddevelopment.com/projects/fah-gpu-statistics-database/add.php) :D
