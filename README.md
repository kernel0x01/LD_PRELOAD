#Installation
<h4>Compile the shared library by running the following command:</h4>

        gcc -shared -fPIC -o libfilehook.so filehook.c -ldl
Set the LD_PRELOAD environment variable to the full path of the libfilehook.so shared library:

        export LD_PRELOAD=/full/path/to/libfilehook.so
#Usage
        Create a file called king.txt with the contents "bhaisd"

Run any program that opens and writes to king.txt, and the open and write functions in your shared library will be called instead of the real open and write functions. If the file descriptor is for king.txt, the write function will replace all occurrences of "bhaisd" with "goodboy" before writing to the file.
