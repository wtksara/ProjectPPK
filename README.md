# ProjectPPK
First project in C++, which is using binary tree to collate words from text by alphabetic order and show numer of the line where the word occured.

Using a binary tree and a list, write a program that reads a text file and lists in the output file all words in alphabetical order, including the line numbers where the word occurs.
The program is launched from the command line using the following switches:
-i input file with text.
-o the output file with the word list.

The program uses a binary search tree to store words read from the input file. The binary tree stores data in nodes. A node may have from 0 to 2 children, with children on the left side of the node holding values not greater than the parent node, and on the right side with more children. This data structure allows you to easily sort words in alphabetical (ascending) order.
In addition, each node in the tree has a pointer to the head and tail of a one-way list that contains the line numbers of a given word in the node.

<img src="/1.png" width="666" height="474">

The program is run from the command line. The file names should be passed to the program after the appropriate switches, respectively: -i for the input file and -o for the output file, e.g.
Project.exe -i Text.txt -o Words.txt
Project.exe -o Words.txt -i Text.txt
