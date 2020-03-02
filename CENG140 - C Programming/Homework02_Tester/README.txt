			---USAGE OF TESTER---



!!!THİS TESTER CANNOT WORK ON ANY ENVIRONMENT OTHER THAN LINUX BECAUSE IT USES 
SOME LINUX SYSTEM FUNCTİONS.(I hope it works properly on inek machines.)

!!! 

!!!IF YOU SEE SOMETHİNG WRONG ABOUT TESTER ,PLEASE LET ME KNOW.



!!!ALSO,IF YOU HAVE ANY COMMENT OR RECOMMENDATION,PLEASE LET ME KNOW.



1-In order to use the tester , firstly you should change the "cb" executable.
The executable this file contains is the Selim Hoca's provided one.



2-In your executable , author shouldn't be changed.(I mean it is left as "Selim Temizer".)

Otherwise, your test results may not be successful since it recognizes differences between 
two ".txt" file.



3-Do not change name of any ".txt" files.If you change,tester will not work.



4-In your implementation , quit function(commandQuit) should work. 
Otherwise,
tester will not work as well.(You should press ^c for 14 times 
to close every test case.) If test cases are closed unexpectedly , they are 
counted as "TEST FAIL".



5-There exist basic test cases for each function.If they don't work properly ,
other cases also crash most probably.



6-You can run tester with "./test" command in the terminal.



7-Then lots of ".txt" files will appear :(



8-
   "output_of_xxxxx_" is the file which contains the outputs of your program.

     "result_of_xxxxx_" is the file which shows the difference between your executable
and Selim Hoca's provided one's outputs 'side to side'.
Appeared on left are your outputs,
whereas right is correct way of that.

     "result_of_xxxxx2" is the file which shows the difference between your executable
and Selim Hoca's provided one's outputs with line and column number.

Use whatever you like.



9-If the result_of___ file is empty,then two implementations outputs are same exactly.
Any difference between two outputs causes to make "TEST FAIL".
So, you have to be careful 
about even the newlines and punctiation.



10-Testcases are in the "tests" file.You can change its content if you want(it should be end with
"quit").



11-If you want to try some cases and don't want to run tester, you can do it like following way:

(test cases and "cb" executable should be in the same directory)


For example we want to call cb with "10 10 10",then


	./cb 10 10 10 < testcasename.txt


If you don't want to see in terminal , you can direct outputs with


 	./cb 10 10 10 < testcasename.txt > outputfilename.txt



12-Answers directory holds outputs of test cases from Selim Hoca's executable.If you wan't to
 compare yours with this,


	diff filename1 filename2 

can be used.
 	

diff -y filename1 filename2 --suppress-common-lines 

will show you side by side.



13-I don't take any responsibility if the tester is wrong about something and that will lead you to
change your implementation,causes change in your grade. 	
       


14-If I forget some cases( most probably I did ) please let me know.



                           ---->>>>KOLAYGELSİN!!! <<<<<-------	
			
   

