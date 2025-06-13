# .jpg Recovery Utility

This program scans through a given storage container to find .jpg signatures. Once a signature is found, the utility copies the file information until either the end of the file is found or until another .jpg file signature is detected, at which point a new file is created to copy the next picture.

NOTE: This program is written for the standard FAT file system block size of 512 bytes. The program can easily be rewritten to suit other block sizes by altering the value in the fread() function used. However, if the file system size is incorrect this can prevent the program from accurately detecting .jpg signatures.
