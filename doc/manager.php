<?php
require_once("docutil.php");
page_head("The BOINC manager");
echo "
<p>
The <b>BOINC manager</b> program is available for Windows, Mac OS X
and Linux.  It controls the use of your computer's disk, network, and 
processor resources, and is normally started at boot time.
<br>On Windows, the BOINC Manager is represented by an icon in the system tray.
<br>On Mac OS X, it is represented by icons in both the menubar and the Dock.
</p>
<!-- ** ROM ** is there an equivalent on Linux to the system tray icon? -->
</p>

<img src=mgrsystraymenu.png>

<p>
On Windows:
    <ul>
    <li>Double-click on the icon to open the BOINC manager window.
    <li>Right-click on the icon to access its menu.
    </ul>
On Mac OS X:
    <ul>
    <li>Click on the icon in the menubar or Dock and hold the 
    button down until the menu appears.
    </ul>
</p>
<p>
The icon menu choices are:
<ul>
<li> <b>Open BOINC Manager</b>: opens the current BOINC Manager.
<li> <b>Run always</b>: do work, regardless of preferences.
<li> <b>Run based on preferences</b>: do work
    when your <a href=prefs.php>preferences</a> allow it.
<li> <b>Suspend</b>: stop work (computation and file transfer).
<li> <b>Network activity always available</b>: always allow BOINC to 
contact the project servers when it needs to.
<li> <b>Network activity based on preferences</b>: allow BOINC to contact 
the project servers only when your <a href=prefs.php>preferences</a> 
allow it.
<li> <b>Network activity suspended</b>: setting this keeps BOINC
from attempting to contact any of the project servers.  It is useful
for those on dial-up connections who do not want to be bothered with
BOINC prompting to connect or disconnect for a time.
<li> <b>About BOINC Manager</b>:  displays useful information about the
BOINC Manager.
<li> <b>Exit</b>:  exit the BOINC manager and all running BOINC applications.
No further work will take place until you run the BOINC manager again. 
<br>(On Mac OS X, this menu item is called <b>Quit</b>.)
</ul>
</p>
<img src=mgrsystrayballoon.png>
<p>
Hovering over the BOINC icon will display a status balloon which contains
the project it is currently working on, how far along it is, and which
computer it is connected to (Windows only).
</p>
<h1>BOINC Manager Tabs</h1>
<h2>Projects</h2>
<p>Shows the projects in which this computer is participating.</p>
<img src=mgrprojects.png>

<ul>
<li>Suspended: 
    The project is currently suspended.
<li>Retry in ...:
    The client will wait the specified amount of time before attempting
    to contact the project server again.
<li>Won't get new work:
    The project will not fill the cache for this project 
    when it runs out of work.
</ul>

<p>Click on a project name to enable the following additional buttons:</p>
<ul>
<li> <b>Allow new work</b>:
    Allow the project to download additional work, if needed.
<li> <b>Detach</b>:
    Your computer will stop working for the project.
<li> <b>No new work</b>:
    Do not download any additional work for this project.
<li> <b>Reset project</b>:
    Stop the project's current work, if any,
    and start from scratch.
    Use this if BOINC has become stuck for some reason.
<li> <b>Resume</b>:
    Resumes processing of a previous suspended project.
<li> <b>Suspend</b>:
    Suspends any further processing of this project.
<li> <b>Update</b>:
    Connect to the project;
    report all completed results,
    get more work if necessary,
    and get your latest <a href=prefs.php>preferences</a>.
</ul>

<p>Project administrators can add <a href=gui_urls.php>buttons</a> 
   to the manager to quickly navigate the project website.</p>

<h2>Work</h2>
<p>Shows the work units currently on your computer.
</p>
<img src=mgrwork.png>

<p>Each work unit is either:
    <ul>
<li>Aborted: 
    Result has been aborted and will be reported to the project server
    as a computational error.
<li>Downloading: 
    Input files are being downloaded.
<li>Paused: 
    Result has been suspended by the client-side scheduler and will be
    resumed the next time the project comes up in the processing rotation.
<li>Ready to report: 
    Waiting to notify the scheduling server.
<li>Ready to run:
    An estimate of the total CPU time is shown.
<li>Running:
    Elapsed CPU time and estimated percent done is shown.
<li>Suspended: 
    Result has been suspended.
<li>Uploading: 
    Output files are being uploaded.
</ul>
</p>

<p>Click on a result name to enable the following additional buttons:</p>
<ul>
<li> <b>Abort</b>: 
    Abort processing for a result. NOTE: This will prevent you from receiving
    credit for any work already completed.
<li> <b>Resume</b>:
    Resumes processing of a previous suspended result.
<li> <b>Show graphics</b>: 
    Open a window showing application graphics.
<li> <b>Suspend</b>:
    Suspends any further processing of this result.
</ul>

<h2>Transfers</h2>
<p>Shows file transfers (uploads and downloads).
    These may be ready to start, in progress, and completed.</p>
<img src=mgrtransfers.png>

<ul>
<li>Aborted: 
    Result has been aborted and will be reported to the project server
    as a computational error.
<li>Downloading: 
    Input files are being downloaded.
<li>Retry in ...:
    The client will wait the specified amount of time before attempting
    to contact the project server again.
<li>Uploading: 
    Output files are being uploaded.
</ul>

<p>Click on a file name to enable the following additional buttons:</p>
<ul>
<li> <b>Retry Now</b>: 
    Retry the file transfer now.
<li> <b>Abort Transfer</b>:
    Abort the file transfer. NOTE: This will prevent you from receiving credit
    for any work already completed.
</ul>

<h2>Messages</h2>
<p>Shows status and error messages.
    Messages can be sorted by project or time.
    You can <a href=client_msgs.php>control what messages are shown</a>.
    Messages are also written to a file 'stdoutdae.txt'.</p>
<img src=mgrmessages.png>

<p>Click on one or more messages to enable the following additional buttons:</p>
<ul>
<li> <b>Copy all messages</b>: 
    Copies all the messages to the clipboard.
<li> <b>Copy selected messages</b>:
    Copies the highlighted messages to the clipboard. NOTE: To highlight a message
    hold down the CTRL key and then click on the messages you want to store in the
    clipboard.  When done click on the 'Copy selected messages' button to copy them
    to the clipboard.
</ul>

<h2>Statistics</h2>
<p>Shows some simple charts and graphs about the user and host progress</p>
<img src=mgrstatistics.png>
<p>NOTE: This feature requires three connections to each project scheduler on three
   different days before it starts to work properly.</p>
<p>Click on any of the buttons to change to a different chart:</p>
<ul>
<li> <b>Show user total</b>: 
    Shows the user's credit totals for each project.
<li> <b>Show user average</b>:
    Shows the users's credit averages for each project.
<li> <b>Show host total</b>: 
    Shows the host's credit totals for each project.
<li> <b>Show host average</b>:
    Shows the host's credit averages for each project.
</ul>

<h2>Disk</h2>
<p>This shows how much disk space is currently being used by each project.</p>
<img src=mgrdisk.png>

<h1>BOINC Manager Menus</h1>

The BOINC manager has the following menus:
<ul>
<li> <b>File</b>
    <ul>
    <li><b>Select Computer</b>: Allows you to control BOINC on a different 
        computer
<!--  ** ROM ** is this correct?  Please add more details as appropriate -->
    <li> <b>Exit</b>:  exit the BOINC manager and all running BOINC applications.
        No further work will take place until you run the BOINC manager again. 
        <br>(On Mac OS X, this is under the BOINC menu as <b>Quit BOINC</b>.)
    </ul>
        
<li> <b>Commands</b>
    <ul>
    <li> <b>Run always</b>: do work, regardless of preferences.
    <li> <b>Run based on preferences</b>: do work
        when your <a href=prefs.php>preferences</a> allow it.
    <li> <b>Suspend</b>: stop work (computation and file transfer).
    <li> <b>Network activity always available</b>: always allow BOINC to 
        contact the project servers when it needs to.
    <li> <b>Network activity based on preferences</b>: allow BOINC to contact 
        the project servers only when your <a href=prefs.php>preferences</a> 
        allow it.
    <li> <b>Network activity suspended</b>: setting this keeps BOINC
        from attempting to contact any of the project servers.  It is useful
        for those on dial-up connections who do not want to be bothered with
        BOINC prompting to connect or disconnect for a time.
    <li><b>Retry Communications</b>: retry any deferred communications.
    <li><b>Run Benchmarks</b>:
        run benchmark functions, which measure the speed of your processor.
        BOINC does this automatically,
        but you can repeat it whenever you want.
        The results are shown in the Messages tab.
    </ul>
    
<li> <b>Projects</b>
    <ul>
    <li> <b>Attach to new project</b>:
        enroll this computer in a project.
        You must have already created an account with the project.
        You will be asked to enter the project's URL and either your account key
        or your email address and password, depending on the project.
<!-- ** ROM ** Please add a link to a page with details on using the Wizard. -->
    <li> <b>Account Manager</b>: attach to one or more new projects using an 
        account manager web site.  See <a href=/acct_mgrs.php>Account managers</a>
    </ul>

<li> <b>Options</b>
    <ul>
    <li> <b>Options</b>: opens a dialog allowing you to select your preferred 
        language, how often you wish to be reminded of the need to connect to 
        the project servers (for dial-up users), etc.
        <br>If you connect to the web through an HTTP or SOCKS proxy,
        use this dialog to enter its address and port.
        <br>Windows only: use this dialog to tell BOINC your method of connecting 
        to the Internet.
<!--  ** ROM ** Please add a link to a page with details on using this dialog. -->
    </ul>
<li> <b>Help</b>
    <ul>
    <li> <b>BOINC Manager</b>: open a web page with instructions for using the 
        BOINC manager.  The F1 function key also does this.
    <li> <b>BOINC Manager</b>: open the main BOINC web page.
    <li> <b>About</b>: show BOINC manager version number (on Mac OS X, 
        this command is under the BOINC menu.)
    </ul>
</ul>

<p>
Menu names and other text in the BOINC manager can be displayed in
<a href=language.php>languages other than English</a>.
<p>
To select the <b>BOINC screensaver</b>:
    <ul>
    <li> <b>Windows</b>: use the Display Properties dialog.
    <li> <b>Mac OS X</b>: select System Preferences under the Apple menu and 
        click on \"Screen Saver\".
    </ul>
The BOINC screensaver draws graphics from a running application,
if any is available.
Otherwise it draws the BOINC logo bouncing around the screen (Windows) or 
displays a scrolling message (Mac OS X).
";
page_tail();
?>
