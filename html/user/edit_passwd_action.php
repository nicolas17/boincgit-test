<?php

require_once("../inc/db.inc");
require_once("../inc/util.inc");
require_once("../inc/user.inc");

db_init();

$auth = process_user_text(post_str("auth", true));
$email_addr = strtolower(process_user_text(post_str("email_addr", true)));

// Note: don't call process_user_text() on passwords.
// This is not needed, and will break passwords containing punctuation

$old_passwd = post_str("old_passwd", true);
$passwd = post_str("passwd");
$passwd2 = post_str("passwd2");

if ($passwd != $passwd2) {
    error_page("New passwords are different");
}
if ($auth) {
    $user = lookup_user_auth($auth);
    if (!$user) {
        error_page("Invalid account key");
    }
} else {
    $user = lookup_user_email_addr($email_addr);
    if (!$user) {
        error_page("No account with that email address was found");
    }
    $passwd_hash = md5($old_passwd.$email_addr);
    if ($user->passwd_hash != $passwd_hash) {
        error_page("Invalid password");
    }
}

page_head("Change password");
$passwd_hash = md5($passwd.$user->email_addr);
$query = "update user set passwd_hash='$passwd_hash' where id=$user->id";
$result = mysql_query($query);
if ($result) {
    echo "Your password has been changed.";
} else {
    echo "
        We can't update your password due to a database problem.
        Please try again later.
    ";
}

page_tail();
?>
