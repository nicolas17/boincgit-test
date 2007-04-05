<?php
require_once("docutil.php");
require_once("../html/inc/translation.inc");


function show_participant() {
    global $light_blue;
    $i = rand(0, 99);
    $j = $i+1;
    echo "
        <tr><td bgcolor=$light_blue>
            <font size=4>&nbsp;Featured volunteer</font>
        </td></tr>
        <tr><td>
        <center>
        <table border=0 cellpadding=6><tr><td>
    ";
    include("piecharts/$i.html");
    echo "
        <br>
        <center>
        <a href=chart_list.php><b>Top 100</a> |
        <a href=http://boinc.netsoft-online.com/rankings.php?list=rac_p1c1><b>Single-computer</a> |
        <a href=http://boinc.netsoft-online.com/rankings.php><b>Other lists</a>
        </center>
        </td></tr></table>
        </td></tr>
    ";
}

function show_news_items() {
    global $light_blue;
    require_once("boinc_news.php");
    require_once("../html/inc/news.inc");
    echo "
        <table border=2 cellpadding=8><tr><td bgcolor=$light_blue>
        <font size=4>News</font>
        <br>
    ";
    $nnews_items = 8;
    show_news($project_news, $nnews_items);
    if (count($project_news) > $nnews_items) {
        echo "<a href=old_news.php>... more</a>\n";
    }

    echo "
        <p><font size=-2>News is available as an
        <a href=rss_main.php>RSS feed</a> <img src=xml.gif></font>
        </td></tr></table>
        <p>
    ";
}

function show_participate() {
    global $light_blue;
    echo "
        <tr><td bgcolor=$light_blue>
            <font size=4>&nbsp;".tr(HOME_HEADING1)."</font>
        </td></tr>
        <tr><td>
        <p>
        ".sprintf(tr(HOME_P1), "<ol> <li> <a href=projects.php><font size=+1>", "</font></a>", "<li> <a href=download.php><font size=+1>", "</font></a>", "<li> <font size=+1>", "</font>")."
        </ol>
        <p>
        ".sprintf(tr(HOME_P2), "<a href=acct_mgrs.php>", "</a>", "<a href=http://gridrepublic.org>", "</a>", "<a href=http://bam.boincstats.com/>", "</a>")."
        <p>
        ".sprintf(tr(HOME_P3), "<a href=help.php>", "</a>")."
        <center>
        <a href=download.php><b>".tr(HOME_DOWNLOAD)."</b></a>
        | <a href=participate.php><b><nobr>".tr(HOME_MORE_INFO)."</nobr></b></a> 
        | <a href=links.php><b><nobr>".tr(HOME_WEB_SITES)."</nobr></b></a>
        | <a href=addons.php><b>".tr(HOME_ADD_ONS)."</b></a>
        | <a href=poll.php><b><nobr>".tr(HOME_SURVEY)."</nobr></b></a>
        </center>
        </td></tr>
    ";
}

function show_create() {
    global $light_blue;
    echo "
        <tr><td bgcolor=$light_blue><font size=4>Compute with BOINC</font></td></tr>
        <tr><td>
        A BOINC project with a single Linux server
        can provide computing power equivalent
        to a cluster with tens of thousands of CPUs.
        Learn how to <a href=create_project.php>create
        and operate a BOINC project</a>.
        <ul>
        <li> <b>Scientists</b>: if your group has moderate
        programming, web, sysadmin, and hardware resources,
        you can create your own BOINC project.
        Otherwise, organizations such as World Community Grid may be able
        to host your project
        (please <a href=contact.php>contact us</a> for information).
        <li> <b>Universities</b>: use BOINC to create a
            <a href=vcsc.php>Virtual Campus Supercomputing Center</a>.
        <li> <b>Companies</b>:
            use BOINC for <a href=dg.php>Desktop Grid Computing</a>.
        </ul>
        </td></tr>
    ";
}

function show_other() {
    global $light_blue;
    echo "
        <tr><td bgcolor=$light_blue><font size=4>Other info</font></td></tr>
        <tr><td>
            <ul>
            <li> <a href=intro.php>Overview</a>
            <li> <a href=boinc_dev.php>Software development</a>
            <li> <a href=translation.php>Translation</a> of web and GUI text
            <li> <a href=contact.php>Personnel and contributors</a>
            <li> BOINC <a href=email_lists.php>email lists</a>
            <li> BOINC <a href=dev/>message boards</a>
            <li> <a href=papers.php>Papers and talks</a> about BOINC
            <li> <a href=logo.php>Logos and graphics</a>
            <li> <a href=events.php>Events</a>
            </ul>
            <br>
        </td></tr>
    ";
}

function show_nsf() {
    echo "
        <tr><td>
        <img align=left src=nsf.gif>
        BOINC is supported by the
        <a href=http://nsf.gov>National Science Foundation</a>
        through awards SCI/0221529, SCI/0438443 and SCI/0506411.
        <font size=-2>
        Any opinions, findings, and conclusions or recommendations expressed in
        this material are those of the author(s)
        and do not necessarily reflect the views of the National Science Foundation.
        </font>
        </td></tr>
    ";
}

html_tag();
echo "
<head>
<link rel=\"shortcut icon\" href=\"iconsmall.ico\">
<link rel=\"stylesheet\" type=text/css href=white.css>
<title>BOINC</title>
<meta name=description content=\"BOINC is an open-source software platform for computing using volunteered resources\">
<meta name=keywords content=\"distributed scientific computing supercomputing grid SETI@home public computing volunteer computing \">
</head>
<body bgcolor=#ffffff>
<img hspace=30 vspace=10 align=left src=logo/logo_small.png>
<h1>
Berkeley Open Infrastructure for Network Computing
</h1>
<font size=+1>
Open-source software for
<a href=volunteer.php>volunteer computing</a> and <a href=dg.php>desktop grid computing</a>.</font>
<p>
";
search_form();
echo "
<br clear=all>

<table width=100% border=0 cellspacing=0 cellpadding=4>
<tr>
<td valign=top>
<table width=100% border=0 cellspacing=0 cellpadding=8>
";
show_participate();
show_participant();
show_create();
show_other();
show_nsf();
echo "
</table>
</td>
";
echo " <td valign=top width=390>
";

show_news_items();
echo "<table>";
echo "</table>";

echo "
</td></tr>
</table>
";

page_tail(true, true);
echo "
    <script language=\"JavaScript\" type=\"text/javascript\" src=\"wz_tooltip.js\"></script>
    </body>
    </html>
";
?>
