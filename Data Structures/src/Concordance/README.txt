#	------ Instructions: ------
#
#	Pay attention to the fact that the default paths that
#	are in Program.java need to be changed according to which directory
#	you running the project from.
#
#	Processing your own text files:
#		- Please use Only UTF-8 plain text files
#		- Enter The File Path (Or Just Its Name When Running From Same Path) When Prompted By The CLI
#
#   Running:
#	1) Compile And Run Program
#	2) Navigate Using The CLI Menu
#	3) Use Accurate File Paths
#
#	Default output file is specified in Program.java
#
#
#	------ Complexity Analysis: ------
#
#	Default Run (build tree + output file) Complexity:
#		Average Case -> O(n*(lgn + m) + m)
#		Worst Case -> O(n*(n + m) + m)
#
#		> n - number of total words in the file
#		> m - number of total characters in the file
#
#
#	Complexity of Building The Structure:
#
#	    Average Case -> O(n * [(m * lg(m*n)) + c])
#		Worst Case -> O([n*m]^2 + n*c) - (in case in which the words in the file are sorted)
#
#	    > n - number of lines
#	    > m - number of words in each line
#	    > c - number of characters in each line
#
#	Or In Another Words:
#
#		Average Case -> O(nlgn + m)
#		Worst Case -> O(n^2 + m) - (in case in which the words in the file are sorted)
#
#		> n - number of total words in the file
#		> m - number of total characters in the file
#
#		O(m) - going through all the chars and leaving only letters and spaces + splitting by spaces
#		O(nlgn)/O(n) - for each word (O(n)) insert it into the tree (O(lgn)/O(n))
#
#
#	Complexity Of Printing/Creating Output File:
#
#		= O(n * m)
#
#		> n - number of total words in the file
#		> m - number of lines the word appears in
#
#		O(n * m) - for each word print all line numbers it's in
#
#
#	Complexity Of Searching For A Specific Word:
#
#		Average Case -> O(lgn)
#		Worst Case -> O(n) - (in case in which the words in the file are sorted)
#
#		> n - number of total unique words in the file
#
#		O(lgn)/O(n) - BST Search Complexity is height dependant. height on average is <lgn> and worst case <n>
#
#
#	Complexity Of Searching For A Specific Word + Displaying It:
#
#		Average Case -> O(lgn + m)
#		Worst Case -> O(n + m) - (in case in which the words in the file are sorted)
#
#		+ n - number of total unique words in the file
#		+ m - number of lines the word appears in
#
#		O(lgn)/O(n) - BST Search Complexity - height dependant, height is on average <lgn> and worst case <n>
#		O(m) - for the found word print all the lines in which it appears
#
#
#