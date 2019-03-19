# people_app
Framework/System info:
Application was written in C++ in QT framework (QtCreator ver. 3.5.1, Qt ver. 5.5.1) under Ubuntu 16.04v. system.

Description:
This application allows user to manage data of people in GUI view. At initial settings (which can be change by editing 'model-skeleton.ini') application allows to manage the following types of data:
First Name, Last Name, Street Name, House Number, Apartment Number (optional), Postal Code, Phone Number, Day Of Birth, Age (read-only).
The file 'model-skeleton.ini' should be located in the same directory as compiled application executing file. IF not, application will not work properly. 

Application possibilities:
- Editing, adding and deleting data in table view by clicking on table cells.
- Change data bases by choose the one from list contained in combo-box.
- Save current changes by "Save" button.
- Load last version of data stored in XML file by "Cancel" button.
- Delete unwanted records by selecting all cells of chosen records and pushing "Delete Records" button.

Application code description:
main.cpp creates main window (Dialog class), which constructor calls own and other objects initialization. Next main window is showed. 

Dialog - contains all GUI objects (beyond same Message Box dynamicly created while app running). There is possible to view and edit these GUI object in dialog.ui file. Dialog also contains implementation of signal function, which react on user activities on widgets. Dialog posts execution of user orders to Model Manager.

ModelManager - responsible for creating and edditing data model. It uses XmlWriter abstract class to save current data to xml file, and XmlReader abstract class to load xml file to current view. 

Delegate - View is dynamicly changed by changing model thanks to linking Model to Window and heart of behaviour data on user activities are specified here.

DialogSave - Supporting Class for Dialog. Showed when User wants to save file, but no text is placed in combo-box widget. It happens when there is not any xml files in application exec file location while launching application (Dialog can't read any matching files).

Date - Class was created for checking date validation and calculating current age of person.