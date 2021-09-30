# Jumbot
#### Video Demo:  https://youtu.be/uTH4Qz_BZ64
#### Description: Search for highlighted words on jumia

** Environment **:  JavaScript
## About ##
For my CS50 Final Project, I wanted to build something that would enable ease of access to my shopping website of choice without the nedd to not only
open multiple tabs but to also cut down the time taken to open new tabs,load up said site and search up what i need.
this way, any part of a web page could be used as my search bar.

#### Structure/design of program  ####
 This project is an extension which will search up selected words on jumia.com cutting out the process needed to open the site
and searching it up by yourself.
##### In the manifest.json file:
  The context menu permission is granted so that the extension can popup upon any right clicks and
  I also made sure not to give it too many permissions which could come off as unnecessary and unsafe.

#####    For the eventpage.js file, the first part of the code creates a row for jumbot on the list of options whenyou right click.
while the other half opens up a tab and searches up the highlighted word.

#####  How to use ####
or search bar of your choice,
simply type out what you want/need if its not already on your screen,
highlight it then right click it and then click on the Jumbot option which will pop up along side your other options as shown below.
![drink1](/project/drink1.png)

and with the result shown below

![drink2](/project/drink2.png)


##### FUTURE DEVELOPMENT ####
If done right, i plan on letting the user choose between more than one search option
and if possible implement shortcut keys also, that way instead of having to right click all the time,
a few seconds could shaved off the time spent through the entire process.

#####  ISSUES FACED ####
Some of the issues faced while working with javascript were:
 Familiarising myself with it while trying to avoid rookie mistakes in my code,
getting the right permissions to use on the search bar such that it wont be unnecessary ones that are loaded into it
such as storage instead of tabs and contextMenus, and making sure that the right url was used as it kept sliping my mind.

#### problems noted ####
im not sure the extent to which this applies but the website used is one which ends/ended with a .ng which is set to my locale being nigeria
and with that being the case, you may or may not need a vpn to access the site as i wasnt able to test that part out.

#####  LINK ####
To see the code in action,
you can visit https://youtu.be/uTH4Qz_BZ64 on youtube as shown above.

#####  INSTALLATION ####
This extenstion requires no installation and once downloaded, is good to go.
Alternatively, if you are versed in javascript, you are welcome to edit the code to your liking.


