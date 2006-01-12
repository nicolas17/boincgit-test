<?php

require_once("../inc/db.inc");
require_once("../inc/xml.inc");
require_once("../inc/team.inc");
require_once("../inc/email.inc");

function reply($x) {
    echo "<am_set_info_reply>
    $x
</am_set_info_reply>
";
    exit();
}

function error($x) {
    reply("<error>$x</error>");
}

function success($x) {
    reply("<success/>\n$x");
}

db_init();

xml_header();

$auth = process_user_text($_GET["account_key"]);
$user = lookup_user_auth($auth);
if (!$user) {
    error("no such user");
}

$name = process_user_text($_GET["name"]);
$country = $_GET["country"];
if ($country && !is_valid_country($country)) {
    error("invalid country");
}
$postal_code = process_user_text($_GET["postal_code"]);
$global_prefs = process_user_text($_GET["global_prefs"]);
$project_prefs = process_user_text($_GET["project_prefs"]);
$url = process_user_text($_GET["url"]);
$send_email = process_user_text($_GET["send_email"]);
$show_hosts = process_user_text($_GET["show_hosts"]);
$teamid = get_int("teamid", true);
$venue = process_user_text($_GET["venue"]);
$email_addr = strtolower(process_user_text($_GET["email_addr"]));
$password_hash = process_user_text($_GET["password_hash"]);

$query = "";
if ($name) {
    $query .= " name='$name', ";
}
if ($country) {
    $query .= " country='$country', ";
}
if ($postal_code) {
    $query .= " postal_code='$postal_code', ";
}
if ($global_prefs) {
    $query .= " global_prefs='$global_prefs', ";
}
if ($project_prefs) {
    $query .= " project_prefs='$project_prefs', ";
}
if ($url) {
    $query .= " url='$url', ";
}
if ($send_email != null) {
    $query .= " send_email='$send_email', ";
}
if ($show_hosts != null) {
    $query .= " show_hosts='$show_hosts', ";
}

if ($teamid) {
    $team = lookup_team($teamid);
    if ($team) {
        user_join_team($team, $user);
    }
}

if ($venue) {
    $query .= " venue='$venue', ";
}
if ($email_addr && $email_addr!=$user->email_addr) {
    $old_email_addr = $user->email_addr;
    $query .= " email_addr='$email_addr', ";
}
if ($password_hash) {
    $query .= " passwd_hash='$password_hash', ";
}

// the seti_id=seti_id is to make it legal if no fields updated
//
$query = "update user set $query seti_id=seti_id where id=$user->id";
$result = mysql_query($query);
if ($result) {
    if ($old_email_addr) {
        send_verify_email($old_email_addr, $email_addr, $user);
    }
    success("");
} else {
    error("database error: ".mysql_error());
}

?>
