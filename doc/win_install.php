<?php

require_once("docutil.php");

page_head("BOINC Windows installer");
echo "

BOINC can be installed in any of several modes:

<ul>
<li>
<h3>Single-user installation</h3>
<p>
This is the recommended mode.
If you check the 'run on startup' box,
BOINC will run while you (the installing user) are logged in.
<p>
BOINC is listed in the Start menu of the installing user,
but not other users.
<p>
The 'Show graphics' command in the BOINC manager
works only for the installing user.
The BOINC screensaver only shows application
graphics only for the installing user
(other users can run the screensaver but will see textual information only).

<li>
<h3>Shared installation</h3>
<p>
If you check the 'run on startup' box,
BOINC runs whenever any user is logged in.
<p>
BOINC is listed in the Start menu of all users.
<p>
While BOINC is running, it runs as a particular user
(either the first user to log in, or the first to run BOINC).
The 'Show graphics' command in the BOINC manager
works only for this user.
The BOINC screensaver shows application graphics only for this user
(other users can run the screensaver but will see textual information only).

<li>
<h3>Service installation</h3>
<p>
If you check the 'run on startup' box,
BOINC runs all the time (even when no one is logged in).
<p>
BOINC is listed in the Start menu of the installing user,
but not other users.  
<p>
The 'Show graphics' command in the BOINC manager will not work for any user.
The BOINC screensaver will only show textual information.

</ul>

The Windows BOINC client can be
<a href=win_deploy.php>deployed across a Windows network
using Active Directory</a>.

<hr>
<h2>Technical details</h2>
<p>
BOINC's Windows installer installs several programs:
<ul>
<li> <b>core client</b>: the program that manages file transfers
and execution of applications.
<li> <b>manager</b>: the GUI to the core client.
<li> <b>screensaver</b>: a program that runs when the machine is idle.
Typically it sends a message to the core client,
telling it to do screensaver graphics.
</ul>

<h3>Single-user installation</h3>
<p>
Say the install is done by user X.
The manager runs automatically when X logs in.
The manager starts up the core client.
The core client it runs as a regular process, not a service.
If the manager crashes the core client continues to run.
The user can re-run the manager.
When the user logs out, the manager, the core client,
and any running applications exit.
<p>
Files (in the BOINC directory) are owned by user X.
<p>
Detection of mouse/keyboard is done by the manager.
<p>
The screensaver works as it currently does,
except that we'll pass window-station/desktop info
so that the password-protected screensaver mechanism will work.
<p>
Other users can't run the BOINC manager.

<h3>Shared installation</h3>

<p>
Processes run as whoever is logged in.
If someone logs in while BOINC is already running,
it will not start a new instance of BOINC.


<h3>Service installation</h3>
<p>
The core client runs as a service, started at boot time.
On Windows 2003 and greater is runs under the 'network service' account.
Otherwise it runs as the installing user.
<p>
The manager checks mouse/keyboard input
and conveys idle state to the core client.
Only the installing user can run the BOINC manager.
Files are accessable only to the installing user.



";
page_tail();
?>
