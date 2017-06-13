## In-Memory-File-System-in-C++ ##
An in-memory File System in C++ which allows all the basic operations like creating, deleting and moving of files and directories, reading and writing of files etc. It uniquely allow users to specify the memory size limit for the system to prevent dynamic growth and provided an option to write the data from the file system to disk at periodic intervals. To restrict the memory size limit, "<sys/resource.h>" library was used.  Also, "<experimental/filesystem>" library was used to write to disk.  "<boost.filesystem>" can also be used for the same purpose.

Example commands:

"ls": Displays a list of directories and files in the current directory.

"mkdir path": Creates intermediate directories in the 'path', if needed.

"mkdir directoryname": Creates a new directory 'directoryname' in the current directory. 

"cd directoryname": Navigate to the directory 'directoryname'.

"cd ..": Go to the parent directory.

"> filename.txt": Creates a new file with name 'filename.txt'in the current directory.

"cat filename.txt": View the contents of the file 'filename.txt'.

"vi filename.txt "input String"": Add content to the file 'filename.txt'.

"rm filename.txt": Delete the file 'filename.txt'

"rm directoryname": Delete the directory 'directoryname'

"cls": Clear screen

"exit":Exit the program.
