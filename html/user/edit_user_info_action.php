<?php
// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

require_once("../inc/boinc_db.inc");
require_once("../inc/user.inc");
require_once("../inc/util.inc");
require_once("../inc/countries.inc");

$user = get_logged_in_user();
check_tokens($user->authentictor);

$name = boinc_htmlentities(post_str("user_name"));
if ($name != strip_tags($name)) {
    error_page("HTML tags not allowed in name");
}
if (strlen($name) == 0) {
   error_page("You must supply a name for your account.");
}
$url = post_str("url", true);
$url = strip_tags($url);
$country = post_str("country");
if ($country == "") {
    $country = "International";
}
if (!is_valid_country($country)) {
    error_page("bad country");
}
$postal_code = post_str("postal_code", true);
$postal_code = strip_tags($postal_code);

$name = process_user_text($name);
$url = process_user_text($url);
$postal_code = process_user_text($postal_code);

$result = $user->update(
    "name='$name', url='$url', country='$country', postal_code='$postal_code'"
);
if ($result) {
    Header("Location: home.php");
} else {
    error_page("Couldn't update user info.");
}

?>
