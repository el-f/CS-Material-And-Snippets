#	------ Structure Overview ------
#
#	Structure: a BinarySearchTree, in which each node holds a string for the word
#	and a LinkedList containing all the line numbers in which the word appears in.
#	
#
#	------ Instructions: ------
#
#	In order to process the included input files and output to the default output file path,
#   	pay attention to the fact that the default project directory path in Program.java
#   	may need to change according to which directory you are running the project from.
#   	To change simply change the field PROJECT_DIR in Program.java according to your environment.
#
#	Processing your own text files:
#		- Please use Only UTF-8 plain text files
#		- Enter The File Path (Or Just Its Name When Running From Same Path) When Prompted By The CLI
#
#   	Running:
#		1) Compile Project And Run Program.class
#		2) Navigate Using The CLI Menu
#		3) Open Created Output File Using Your Preferred Text Editor
#
#	Default input/output files are specified in Program.java
#
#
#	------ Complexity Analysis: ------
#
#	Complexity of Building The Structure:
#
#		Average Case -> O(nlgn + c)
#		Worst Case -> O(n^2 + c) - (in case in which the words in the file are sorted/reverse sorted)
#
#		> n - total number of words in the file
#		> c - total number of characters in the file
#
#       When considering that c ~ n * (k = average of chars per word):
#
#		Average Case -> ~O(n*(lgn+k)) ~ O(nlgn)
#		Worst Case -> ~O(n*(n+k)) ~ O(n^2) - (in case in which the words in the file are sorted/reverse sorted)
#
#		O(c) - going through all the chars and leaving only letters and spaces + splitting by spaces
#		O(nlgn)/O(n^2) - for each word (O(n)) insert it into the tree (O(lgn)/O(n)), (tree insertion is O(lgn)/O(n)).
#		O(1) - for each repeating word insert the current line number after the tail of the existing LinkedList,
#               {
#                   MyLinkedList Analysis: (the list that holds the linenumbers)
#
#                   Insertion - O(1) (inserting after tail)
#                   Printing - O(size) - O(n) (going over each one and printing it)
#
#                   The list is inherently sorted since we insert each word to the tree by increasing lines indexes.
#                   No other operations are need in this implementation.
#               }
#
#
#	Complexity Of Printing/Creating Output File:
#
#		All Cases: O(n)
#
#		> n - total number of words in the text file
#
#		O(n) - for each word in the tree print it and all line numbers it appears in.
#              total num of operations sums to the total number of words in the original file.
#
#
#	Complexity Of A Default Program Run (building structure + creating output file):
#
#		Average Case -> O(n*(lgn + 1) + c)
#		Worst Case -> O(n*(n + 1) + c) - (in case in which the words in the file are sorted/reverse sorted)
#
#		> n - total number of words in the file
#		> c - total number of characters in the file
#
#       When considering that c ~ n * (k = average of chars per word):
#
#		Average Case -> ~O(n*(lgn + 1 + k)) ~ O(nlgn)
#		Worst Case -> ~O(n*(n + 1 + k)) ~ O(n^2) - (in case in which the words in the file are sorted/reverse sorted)
#
#		O(nlgn + c)/O(n^2 + c) + O(n) - building structure + creating file
#
#
#	Complexity Of Searching For A Specific Word:
#
#		Average Case -> O(lgn)
#		Worst Case -> O(n) - (in case in which the words in the file are sorted/reverse sorted)
#
#		> n - total number of words in the tree (number of unique words in the text file)
#
#		O(lgn)/O(n) - BST Search Complexity is height proportional, height on average is <lgn> and worst case <n>
#
#
#	Complexity Of Searching For A Specific Word + Displaying It and Its Line Numbers:
#
#		Average Case -> O(lgn + l)
#		Worst Case -> O(n + l) - (in case in which the words in the file are sorted)
#
#		> n - total number of words in the tree (number of unique words in the text file)
#		> l - total number of lines the word appears in
#
#		O(lgn)/O(n) - BST Search Complexity - height proportional, height on average is <lgn> and worst case <n>
#		O(l) - for the found word print all the lines in which it appears
#
#
#