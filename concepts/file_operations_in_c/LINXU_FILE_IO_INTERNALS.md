# Linux File I/O Internals for C/C++ Engineers

## File I/O Stack

Program
↓
glibc
↓
System Call
↓
Linux Kernel
↓
VFS
↓
Filesystem driver
↓
Disk

---

# File Descriptor

File descriptors are integers.

0 → stdin  
1 → stdout  
2 → stderr  

Example:

int fd = open("data.txt",O_RDONLY);

---

# Process File Descriptor Table

Each process maintains:

FD → Kernel File Object

Example:

0 → stdin  
1 → stdout  
2 → stderr  
3 → data.txt  

---

# Kernel File Object

struct file {
 inode *f_inode;
 position;
 flags;
};

FD → file object → inode → disk blocks

---

# inode

Stores metadata:

size  
permissions  
timestamps  
disk block locations  

Filename is NOT stored in inode.

Directories map:

filename → inode

---

# VFS

Virtual File System allows Linux to support multiple filesystems.

Application
↓
VFS
↓
ext4 / xfs / btrfs

---

# fopen vs open

fopen() is implemented in glibc and internally calls:

open()

Example:

FILE *fp = fopen("data.txt","r");

↓

int fd = open("data.txt",O_RDONLY)

---

# Buffering

Disk access is slow.

Data flow:

Disk
↓
Kernel page cache
↓
glibc buffer
↓
Program

---

# Page Cache

Linux caches file data in RAM.

First read:
Disk → Cache → Program

Second read:
Cache → Program

---

# mmap()

Maps file into virtual memory.

void *data = mmap(NULL,size,PROT_READ,MAP_SHARED,fd,0);

Access:

data[0]

Page loaded on demand via page fault.

---

# Journaling Filesystem

ext4 uses journaling.

write journal
↓
write data
↓
commit transaction

Crash recovery by replaying journal.

---

# Database IO

Databases read fixed pages:

4KB / 8KB / 16KB

Disk → Page → Rows

Techniques:

mmap  
write ahead logging  
direct IO  

---

# Redis File Storage

Redis uses Append Only File (AOF).

Commands are logged and replayed on restart.

Example:

SET key value

---

# Zero Copy Transfer

sendfile()

Disk → Kernel → Network

Avoids copying data to user space.

Used by:

nginx  
apache  
high performance servers

---

# Mental Model

FILE*
↓
fd
↓
process fd table
↓
kernel file object
↓
inode
↓
disk blocks