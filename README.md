## In-Memory-File-System-in-C++ ##
Winbash is a bash based In-Memory File System in C++ for Windows. 
User can specify max heap-memory-size to prevent dynamic growth and subsequent program crash. 
Default file-block-size is 100bytes and default heap-memory-size is 10000bytes. 
Winbash can be saved to disk for later use. Saved content can be mounted back to Winbash

Supported commands:

"ls": Displays the list of directories and files in the current directory.

"mkdir directoryname": Creates a new directory 'directoryname' in the current directory. 

"cd directoryname": Navigate to the directory 'directoryname'.

"cd ..": Go to the parent directory.

"history" : View command history

"savefs" : Save the filesystem to disk

"resetfs" : Reset the filesystem

"mountfs" : Mount filesystem from disk

"> filename.txt": Creates a new file with name 'filename.txt'in the current directory.

"touch filename.txt": Creates a new file with name 'filename.txt'in the current directory.

"cat filename.txt": View the contents of the file 'filename.txt'.

"vi filename.txt "input String"": Append content to the file 'filename.txt'.

"rm filename.txt": Delete the file 'filename.txt'

"rmdir directoryname": Delete the directory 'directoryname'

"clear": Clear screen

"exit":Exit the program.
