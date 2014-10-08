##CSCI 104 Team Project Repository

###Student Information
**Developer 1**:
  + Name: Jessica Lai
  + USC Email: laijessi@usc.edu
  + USC ID: 9356642257

**Developer 2**:
  + Name: Kabir Gupta
  + USC Email: kabirgup@usc.edu
  + USC ID: 5957478548

***

###Make instructions: 

>To make our project, first `cd login` then `make`. All `make` commands must be done inside the `login` folder.
>If you redo `qmake -project` please make sure to include the following into your `login.pro` before doing `qmake`:

	DESTDIR = ../bin
	OBJECTS_DIR = ../bin
	CONFIG += console
	CONFIG -= app_bundle
	QMAKE_CXX = g++-4.8
	QMAKE_LINK = g++-4.8
	QMAKE_CXXFLAGS += -std=c++11
	QMAKE_CXXFLAGS -= -stdlib=libc++
	QMAKE_LFLAGS -= -stdlib=libc++
	QT += webkit
	QT += webkitwidgets`

***

###Run Instructions:

+ General run instructions: `bin/login datafile.txt adfile.txt billfile.txt`
+ Run Instructions with our test files: `bin/login data/index.txt data/adtest.txt data/bill.txt` 

>Please run from inside the general team_project_154 directory
>Note: the data files, ad file, and bill file should all be within the same directory.

+ argv[0] is the executable. The makefile stores the executable into `bin` directory. 
+ argv[1] is the name of the file with the WebPage names in it. It is generally located inside the data folder but in the case for the grader, it's wherever the files you're testing are
+ argv[2] is the name of the file with the ad information in it.
+ argv[3] is the name of the file that the bill for the companies will be written into. This is currently being written into our data directory

+ For single word search, ONLY INPUT ONE WORD. So, "Adele" or "Satin" would be just dandy. If you try "ADELE SATIN WOW OKAY COOL SO MANY WORDS" the results list will clear itself and you will get no results. The terminal will also output a message saying you've inputted incorrectly. 
+ For AND or OR, do the following: Separate words from each other using COMMAS. Follow the LAST WORD you're searching with a period. Good example: "Hello, okay, I, understand." 
+ If you attempt something such as "No, I, DO, NOT understand " my list will again clear itself and the terminal will print an error message. 

***

####Additional Class Explanations: 

+ DefWin: The DefWin is the same one that we had to make for lab9. I re-used the implementation and changed the link to open up xkcd as one of the easter eggs. 
+ Popup: This is the class that displays what ad you've clicked on. 
+ Ad: This class is used to store each one of the ads, their company, and their bid value. 
+ Profile: This is a class that opens up the User info into a separate window. It displays their top viewed pages, web history and visited companies. Top viewed pages and visited companies are saved between runs of the program. Web history resets with each run of the program. Also, if you leave the profile window open, it'll run in real time (it'll update as you have it open).
+ Login: This class allows the user to create a profile and log in to the search engine. When the user hits the 'create account' button, they will be allowed to make a username and password (which must be non-empty!). Once they have a matching password, it passes the information back to the login page via a signal/slot mechanism to update the text file (`accountInfo.txt`) holding the login information. They can then log in; the search engine uses this information to load the user's profile.
+ User: This is a class that holds the user's information, which includes their browsing history, most visited pages, and the ads they've clicked on. These are all interfaced with using get and set functions.

***

####Data Directory Explanations: 

+ The `qt` directory holds the MainWin, profile, searchwin, and popup. The MainWin is the main search engine window that you can run the search from. The profile is the window that opens up when you click view profile that loads up the users information. The searchwin opens up the page you were searching for. The popup opens up the message informing you that you've opened up the ad. 
+ The `login` directory holds the login and account creation pages, which pass information to the MainWin once the user has logged in successfully. The usernames and passwords are stored in this directory in a text file which is automatically updated when new accounts are created.
+ The `user` directory holds the User class and its related files. The user information is stored in the `users` subfolder, which has a separate text file for each person who uses the search engine. These files have the pages they've visited and number of times they've visited them, as well as the companies they've visited. These are automatically read into the search engine when someone logs in, and a new text file is automatically created if this is the first time they are using the engine. The user's text file is automatically updated when they close the search engine. 

***

####Implementation Need To Knows: 

+ When first running the project, you will need to create an account before you can log in and access the search engine.
+ Alphabetization is done based on ASCII value. Since ASCII considers lowercase and uppercase differently and we are considering company names case-sensitively, AMAZON and amazon would be considered alphabetically different.
+ Since I created an Ad class instead of a company class, I add the total bill costs for each occurence of an Ad with the same company name and then add that final total as the bill total for the company on the bill.txt. 
+ When closing the profile window, you can either hit the x in the corner or the 'close' button, they will both do the same thing

***

####Easter Eggs: 

+ READ THROUGH THE CODE/TEST IT TO FIND THE MAGICAL EASTER EGGS... (Hint: searching "pink" or "blue" with alphabetical single word search, or "joke" with single word pagerank will do something). This feature was inspired by Google's random easter egg features. While we couldn't do anything cool like Google Gravity, it was an attempt. 


###Compiler Warning:

We have this compiler warning:

	../web/web.cpp: In member function 'void WebPage::cleanUp(std::string&)':
	../web/web.cpp:139:49: warning: comparison is always true due to limited range of data type [-Wtype-limits]
       if(temporary[i] >= 123 && temporary[i] <= 127){

This changes certain ASCII values to spaces for part of the cleanup, not sure why this warning comes up because it is not always true