<?php
require_once("docutil.php");

page_head("Compiling BOINC software");
echo "
Basics:
<ul>
<li> <a href=source_code.php>Getting source code</a>
<li> <a href=build.php>Software prerequisites</a>
<li> <a href=build_system.php>Building BOINC on Unix</a>
<li> <a href=road_map.php>Source code road map</a>
</ul>

Platform-specific cookbooks:
<ul>
<li> <a href=mac_build.html>Building BOINC and BOINC applications on Mac OS X</a>
<li> <a href=http://noether.vassar.edu/~myers/help/boinc/boinc-on-windows.html>Building BOINC applications on Windows</a>
<li> <a href=http://noether.vassar.edu/~myers/help/boinc/boinc-on-linux.html>Building BOINC and BOINC Applications on Linux</a>
<li> <a href=http://torque.oncloud8.com/archives/000124.html>Linux install notes</a> (out of date).
<li> <a href=debian_linux_install.txt>Debian Linux packages needed</a> (out of date)
</ul>

Other information
<ul>
<li> <a href=test.php>Test applications and scripts</a>
<li> <a href=ssl_build.txt>Build instructions for SSL (Secure Socket Layer) client</a>
</ul>
";
page_tail();

?>
