Filecalibur
-----------

Download and Compile
--------------------

Download and install Git for Windows:
https://git-scm.com/download/win

Install Qt:
https://www.qt.io/download

Open Git Bash:
`git clone https://github.com/untergasser/filecalibur.git filecalibur

Open and compile in Qt:
filecalibur/src/Filecalibur.pro


Introduction
------------
Filecalibur is a tool that can serve many purposes, as long 
as files and folder structures are involved. The key to 
understand Filecaliburs capabilities is to separate the 
concept of a file and its associated hash:

File
----
A file is a sequence of binary 0/1 numbers (Bits) on a 
storage system. Usually the files are structured in folders 
for a better overview. Files can be short as a few Byte 
(Byte = 8 0/1 binary numbers) or large as several Gigabyte 
(1 Gigabyte = 1 000 000 000 Byte). We should consider that 
each single Byte is important and if it's modified the 
content of the file will change. Worst case, the file will 
be corrupt and the content will be useless.

Hash
----
I keep things simple here, so let's think of a Hash as a 
fingerprint of a file. Actually, it is a mathematical 
function that sums up the entire file and the result is a 
cryptic number/letter combination. There are several hash 
functions which return different results, for example a 
hash with the function md5 might look as 
d41d8cd98f00b204e9800998ecf8427e and a hash of the function 
sha1 like da39a3ee5e6b4b0d3255bfef95601890afd80709.
  
Three things are essential here:
1) The hash of a certain function is always of the same 
length independent of the file size.  
2) Each single Bit is part of the hash and if it is 
changed, the hash will be totally different.  
3) The hash is unique for each file, but identical for 
copies of the file, independent of the file name.  
  
Actually, in extreme rare cases different files can have 
the same hash, what is called a collision. For this 
application collisions can be ignored.  
  
Filecalibur can calculate these hashes for all files of a 
certain folder even including all the files in subfolders. 
To be accurate, Filecalibur only collects your input and 
runs an independent software hashDeep which performs the 
hash calculation and writes its results in a text file, 
which I name a collection. In this collection, each line 
corresponds to one file. It has the information on the file 
size, the different hash information and the filename with 
the path. A nice feature is the independence of this 
information from the software used to calculate them. A 
file will have the same size, hash or path/name information 
if it's calculated with any other software. Filecalibur can 
display this information and manipulate them.  
At this point, we stop working with the real files and focus 
on the text document with the fingerprints of the files, 
the hashes, instead. Identical files can be identified by 
screening for identical hashes calculated by different files. 
Subfolder can be extracted or removed based on the path/name 
information. But the real power is in comparison of different 
collections by positive and negative matching:

Positive Matching
-----------------
One collection A is checked hash by hash if the hash IS 
present in collection B. Only if the hash IS present, the 
file information is written in collection C. This function 
is useful to identify identical files between different 
collections.

Negative Matching
-----------------
One collection A is checked hash by hash if the hash is NOT 
present in collection B. Only if the hash is NOT present, 
the file information is written in collection C. This 
function is useful to identify unique files in collection A. 
Be aware that in the example above we only find files 
present in collection A but not present in collection B. 
Files present in collection B that are not present in 
collection A are lost/ignored. If these files are of 
interest, the collections have to be switched.  
  
The power of Filecalibur lies in the unlimited possibilities 
to combine these operations to extract exactly what you 
want even with big data collections.  
  
Finally Dangerous Functions allow manipulating your files. 
Filecalibur can use a collection to delete each single file 
in the collection from the storage system. At this point the 
files are looked up and files are removed from the storage 
system.

Important:
----------
I develop software in my spare time for fun and without any 
financial interest. This software is provided under Gnu 
Public License (GPL) conditions and might have bugs. There 
is no guarantee for anything - use at own risk! I use this 
tool since years without any error, but different computers 
may result in strange stuff. Try it out on uncritical data 
before and use it for anything important only if you are 
confident it works as intended. If you find bugs contact 
me with a description so I can reproduce the bug.  
  
It also uses hashDeep, rsync and WinMerge which are provided 
under their licenses available in the respective folder of 
Filecalibur.

Functions
---------
In this section we walk through the essential functionality 
of Filecalibur.

hashDeep - Calculate Hashes
---------------------------
Select hashDeep » Calculate Hashes from the menu. In the 
dialog window you have to provide the folder with the files 
to hash and the file were to save the collection data. 
Based on this information hashDeep calculates the hashes. 
Filecalibur will display the collection once hashDeep is 
ready. Be aware that each file has to be read completely to 
calculate the hash information. If Terabytes of data are 
processed this calculation may run several hours or days. In 
this case it may be appropriate to run the hash calculation 
overnight.

Collection - Modify Path
------------------------
Select Collection » Modify Path from the menu. In the dialog 
window you have to provide the collection file which is 
usually prefilled with the current file. Last the file where 
to save the collection data needs to be provided. The fields 
in between can be used to modify the path/name information 
by removing or adding something to it. Keep in mind that you 
work on the left part of the text which corresponds to the 
top-level folders. This can be used to modify the root folder 
name or remove it to get relative path information. Or the 
letter of the drive can be changed.  
  
Finally the order of the files can be sorted. This is useful 
because files may get out of order due to the time required 
for hashing. Sorting in combination with switching the 
slashes can get the file into order suitable for comparison.

Collection - Remove Path
------------------------
Select Collection » Remove Path from the menu. In the dialog 
window you have to provide the collection file which is 
usually prefilled with the current file. Last the file where 
to save the collection data needs to be provided. The fields 
in the middle you have to provide with the path to remove. 
All entries with the same path/name information are removed 
and only the non-matching are saved in the new collection. 
Useful to remove a subfolder from a collection and keep the 
rest.

Collection - Extract Path
-------------------------
Select Collection » Extract Path from the menu. In the dialog 
window you have to provide the collection file which is 
usually prefilled with the current file. Last the file where 
to save the collection data needs to be provided. The fields 
in the middle you have to provide with the path to extract. 
All entries with the same path/name information are saved in 
the new collection and all non-matching are discarded. Useful 
to extract only one subfolder into a new collection.

Collection - Join Files
-----------------------
Select Collection » Join Files from the menu. In the dialog 
window you have to provide the collection file which is 
usually prefilled with the current file and a second input 
file. Last the file where to save the collection data needs 
to be provided. Both files are joined and saved in the new 
collection. Useful to add a folder to a collection.

Collection - Positive Hashing
-----------------------------
Select Collection » Positive Hashing from the menu. In the 
dialog window you have to provide the test collection file 
which is usually prefilled with the current file. Second you 
have to provide the hash library collection. Last the file 
where to save the collection data needs to be provided. The 
test collection is checked hash by hash if the hash IS 
present in hash library collection. Only if the hash IS 
present, the file information is written in the new 
collection. Useful to identify identical files between 
different collections.

Collection - Negative Hashing
-----------------------------
Select Collection » Negative Hashing from the menu. In the 
dialog window you have to provide the test collection file 
which is usually prefilled with the current file. Second 
you have to provide the hash library collection. Last the 
file where to save the collection data needs to be provided. 
The test collection is checked hash by hash if the hash is 
NOT present in hash library collection. Only if the hash 
is NOT present, the file information is written in the new 
collection. Useful to identify unknown files in the test 
collection. Be aware that in the example above we only find 
files present in the test collection but not present in hash 
library collection. Files present in hash library collection 
that are not present in test collection are lost/ignored. 
If these files are of interest, the collections have to be 
switched.

Collection - Find Duplicates
----------------------------
Select Collection » Find Duplicates from the menu. In the 
dialog window you have to provide the collection file which 
is usually prefilled with the current file. Last the file 
where to save the collection data needs to be provided. The 
collection is checked hash by hash if a hash occurs more 
than once. Only if the hash is present more than once, the 
file information is written in the new collection. Useful to 
identify duplicate files within a collection.

Collection - Compare Files
--------------------------
Select Collection » Compare Files from the menu. In the 
dialog window you have to provide one collection file which 
is usually prefilled with the current file. Additionally, a 
second collection file needs to be provided. Both files are 
compared by the tool WinMerge. Useful to identify tiny 
changes between collections.  
For best success, the path information should be identical. 
If comparing two folders on different drives, remove first 
the absolute path information that differs with the Modify 
Path function to obtain relative path information. Sort also 
the files to have the same order in both collections. Now the 
comparison is more informative.

Dangerous Tools - Rsync Directories
-----------------------------------
Select Dangerous Tools » Rsync Directories from the menu. In 
the dialog window you have to provide a source folder and a 
target folder. Filecalibur will use rsync to copy all files 
from the source folder to the target folder. If "Delete 
Files..." is selected, all the files absent in source are 
deleted in the target folder. Useful to sync folders between 
backups. If only a few files changed rsync is much faster 
than copying folders.  
Be extremely cautious with this function, if the folders are 
confused and an empty folder (now source) is synced to your 
backup (now target) all your backup data is deleted! Both 
folders will be in sync as both will be empty now!

Dangerous Tools - Delete Files from List
----------------------------------------
Select Dangerous Tools » Delete Files from List from the 
menu. In the dialog window you have to provide the 
collection file. For security and to avoid the accidental 
selection of a wrong collection, the path has to be 
provided were Filecalibur is allowed to delete files. This 
path has to match the path of the files in the collection. 
Filcalibur will remove each single file provided in the 
collection from the storage system.  
Be extremely cautious with this function as there is no undo.

Dangerous Tools - Delete Empty Directories
------------------------------------------
Select Dangerous Tools » Delete Empty Directories from the 
menu. In the dialog window you have to provide a source 
folder. Filecalibur will search through all subfolders and 
delete them in case they are empty.  
This is handy in combination with Delete Files from List. 
After all files are deleted, many empty folders may exist 
and the folders with files may be hard to find. After the 
removal only folders with files remain.

Examples of Usage
-----------------
In this section we focus on scenarios were Filecalibur 
might be useful.

Backup
------
There are two types of backups in this world, one done with 
advanced programs and the other by copying files to an 
external drive without any special software. While the first 
is usually fast, automated and easy it comes at the 
disadvantage of the dependency of the software to access the 
files. The second approach is easy but you have to do it 
yourself and copying huge amounts of data may require quite 
some time. The advantage is that you created a second 
original copy of your data. It has the same usability as the 
original that can be accessed without any further software. 
   
Filecalibur can help with the second type of backup. If you 
don't have any backup on the external drive yet, just copy the 
files in the regular file manager - its faster than rsync. 
Once this is done, you just want to update the changes from 
your system to your external backup from now on. Here rsync 
is much faster and will copy only changed files to your 
external drive (see Dangerous Tools - Rsync Directories).  
  
Now the question remaining is - Are both copies identical? 
Therefor we calculate the hashes of the original drive/folder 
as well as the backup drive/folder (see hashDeep - Calculate 
Hashes). That takes time, but once done it can be saved to 
the backup drive as well. Now we remove the absolute path 
part in both files so the path/filename information of both 
locations is identical. Don't forget to sort the output (see 
Collection - Modify Path). Last, we can compare both files 
and the only difference should be within the header 
information (see Collection - Compare Files).

Crazy Ultrasafe Backup
----------------------
Imagine we have really valuable data like pictures of the kids 
when they were young and copies of our diploma. Here we don't 
want to miss anything ever ever. First, we need more than one 
backup drive, best would be three usb drives from different 
producers (to avoid processing errors). Store these backups at 
different places and update them one by one. Never bring them 
back to the same place (to avoid disasters as fire).  
  
The very first backup is performed as described in Backup above. 
Save the result of the hash calculation (the collection file) on 
the drive as well.  
  
Next time we perform a backup, we are really careful. This is 
done in four steps:  
  
1) Is the data we want to copy still OK? We calculate the hash 
for the source data (see hashDeep - Calculate Hashes). We 
remove the extra path information (see Collection - Modify 
Path) and do negative Hashing with the collection file of 
the old Backup (see Collection - Negative Hashing). Only the 
new files and the changed files which will be overwritten 
are displayed using the current collection as test collection 
and the old backup collection as hash library collection. The 
old files which will be deleted in the backup as well as the 
changed files which will be overwritten are displayed using 
the old backup collection as test collection and the current 
collection as hash library collection. We can also compare 
the old collection with the current version using WinMerge 
and jump from change to change (see Collection - Compare 
Files). If we are happy with the result (no files modified 
that should be identical, no files missing that should be 
there and only new files present which were added by us), we 
can move to the next step.  
  
Step 2 and 4 are performed for each external drive 
independently:  
  
2) Are there errors on the data of the external drive? The 
answer should be no, so you might skip this step, but its 
best to catch errors early before the drive stops working. 
So we calculate the hashes of the drive/folder (see hashDeep - 
Calculate Hashes). Now we remove the absolute path part in 
the file and sort the output (see Collection - Modify Path). 
Finally we compare the current file with the old collection 
saved on the backup volume (see Collection - Compare Files). 
All difference should be within the header information or the 
backup was changed during storage, which is not a good sign. 
With this step you also confirmed that the entire backup is 
still readable without errors.  
  
3) Now we sync the data. We use rsync to copy the changes to 
your external drive (see Dangerous Tools - Rsync Directories). 
Be really careful with the source and target folder. If you 
go wrong, you sync your backup to the new folder and lose 
all new changes.  
  
4) Again the question remaining is - Is the copy identical? 
Therefor we calculate the hashes of the external 
drive/folder (see hashDeep - Calculate Hashes), remove the 
absolute path part in the file and sort the output (see 
Collection - Modify Path). Now we can compare the external 
drive collection file with the original collection file and 
the only difference should be within the header information 
(see Collection - Compare Files). Don't forget to save this 
file on the external drive for the next backup.  
  
Using this method for backup a loss of data is almost 
impossible. The downside is that it takes a few days to get 
things in order, luckily not hands-on-time but calculation 
time. I do this every 6 Month or if I have new important 
data.  

Find Duplicates
---------------
Many times, duplicates exist due to copied files or folders. 
To find duplicates, calculate the hash of the folder where 
you expect duplicates in subfolders (see hashDeep - Calculate 
Hashes). Then keep only the files were a hash was found more 
than one (see Collection - Find Duplicates). Now you can go 
through all duplicates.

Find Changes
------------
Sometimes you want to know if some files changed. Maybe you 
want to see which files are changed once you run certain 
software. You can also use it to visualize the difference 
between two software package releases.  
  
First calculate the hash of the drive where you expect 
changes in subfolders and save the collection as "initial" 
(see hashDeep - Calculate Hashes). Then do the change or run 
the software in doubt. Calculate the hash of the drive where 
you expect changes in subfolders a second time and save the 
collection as "after" (see hashDeep - Calculate Hashes). 
Sort the collections to get identical file order in both 
files (see Collection - Modify Path) and do negative Hashing 
with the collection file "initial" and collection file 
"after" (see Collection - Negative Hashing). Only the new 
files and the changed files are displayed using the "after" 
collection as test collection and the "initial" collection 
as hash library collection. The files which were deleted as 
well as the changed files are displayed using the "initial" 
collection as test collection and the "after" collection as 
hash library collection. We can also compare both 
collections using WinMerge and jump from change to change 
(see Collection - Compare Files).

Sort the Folder Mess
--------------------
Computers have the tendency to get messy and the user has 
the tendency to lose control. Imagine you have pictures 
from your last vacation. You copied them from your camera 
to your computer at home. Some you renamed and modified to 
change the colors a bit. Then you copied it to the computer 
at work. Some were changed there in lunch break and some 
were changed at home. A friend gave you some more pics which 
were added as well. So how to sort this mess out when you 
try to merge the folders into one with all the pictures?  
  
First, I would make a copy of all folders to avoid data loss 
in case this goes terribly wrong. Then we calculate the hash 
of each folder and save the collections (see hashDeep - 
Calculate Hashes). Then we do positive matching with the 
"work" collection using the "camera" collection as hash 
library collection (see Collection - Positive Hashing). The 
resulting file contains only files of the "work" collection 
that are identical to the once in the camera folder, the 
unchanged ones. We delete them from the storage using the 
result collection of the positive matching (see Dangerous 
Tools - Delete Files from List). If folders remain empty 
they can be removed as well (see Dangerous Tools - Delete 
Empty Directories). Now the steps are repeated with the "home" 
folder instead of the "work" folder. Last the files now 
present in the "home" folder can be compared in a similar 
fashion to the files in the "work" folder. As a result, all 
identical files are gone and only the modified or new files 
remain in their respective folder. They still need to be 
viewed and selected by hand to combine them in one folder, 
but the burden of the duplicate files was removed.

Frequently Asked Questions - FAQ
--------------------------------
The file did not change, why does it have a different hash?  
  
Microsoft Word/Excel, graphics files and mp3 files collect 
meta information additional to the content. So the content 
may be identical, but maybe some extra notes in word or the 
artist name in an mp3 file was changed. If only a bit 
changes, the hash will be totally different.  
  
