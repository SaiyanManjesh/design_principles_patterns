# File Operations in C and C++

## File Definition

A file is a sequence of bytes stored on disk.

Example:

Hello

Stored as:

48 65 6C 6C 6F

---

# File Workflow

OPEN → READ/WRITE → CLOSE

Example:

FILE *fp = fopen("data.txt","r");

read data

fclose(fp);

---

# FILE *

FILE* is a control structure used by the C runtime library.

Concept:

FILE*
↓
buffer
↓
file descriptor
↓
actual file

---

# Opening Files

FILE *fopen(const char *filename,const char *mode);

Example:

FILE *fp = fopen("data.txt","r");

---

# File Modes

r  → read  
w  → write (truncate)  
a  → append  
r+ → read/write  
w+ → read/write truncate  
a+ → read/write append  

---

# Writing Characters

fputc()

Example:

fputc('A',fp);

---

# Reading Characters

fgetc()

Example:

while((ch = fgetc(fp)) != EOF)
{
printf("%c",ch);
}

---

# String Operations

fgets()

fputs()

Example:

fgets(buffer,100,fp);

fputs("Hello",fp);

---

# Formatted IO

fprintf()

fscanf()

Example:

fprintf(fp,"Age:%d",age);

---

# Binary IO

fwrite()

fread()

Example:

fwrite(&data,sizeof(data),1,fp);

fread(&data,sizeof(data),1,fp);

---

# File Pointer

Each file has a cursor position.

Functions:

fseek()

ftell()

rewind()

Example:

fseek(fp,10,SEEK_SET);

---

# Buffering

Program
↓
Buffer
↓
Disk

Flush buffer:

fflush(fp);

---

# Closing Files

fclose(fp);

Always close files to avoid resource leaks.

---

# Low Level File IO

open()

read()

write()

close()

Example:

int fd = open("data.txt",O_RDONLY);

read(fd,buffer,100);

close(fd);

---

# C++ File Operations

Header:

#include <fstream>

Classes:

ifstream → read

ofstream → write

fstream → read/write

Example:

std::ofstream file("data.txt");

file<<"Hello";

---

# Binary in C++

file.write((char*)&data,sizeof(data));

file.read((char*)&data,sizeof(data));

---

# Golden Rules

Always check fopen()

Always close files

Use binary for structures

Handle EOF properly

Avoid character-by-character reads