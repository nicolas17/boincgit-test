<?php
require_once("../inc/cache.inc");
require_once("../inc/util.inc");
require_once("../inc/boinc_db.inc");
require_once("../inc/team.inc");

$teamid = get_int("teamid");
$team = BoincTeam::lookup_id($teamid);

$get_from_db = false;

$user = get_logged_in_user(false);

// always show fresh copy to admins; they might be editing info
//
if (is_team_admin($user, $team)) {
    echo "foo";
    $get_from_db = true;
}

// Cache the team record, its forum record, its new members,
// its admins, and its member counts

$cache_args = "teamid=$teamid&sort_by=$sort_by&offset=$offset";
if (!$get_from_db) {
    $cached_data = get_cached_data(TEAM_PAGE_TTL, $cache_args);
    if ($cached_data) {
        // We found some old but non-stale data, let's use it
        $team = unserialize($cached_data);
    } else {
        $get_from_db = true;
    }
}
if ($get_from_db) {
    $team->nusers = BoincUser::count("teamid=$teamid");
    $team->nusers_worked = BoincUser::count("teamid=$teamid and total_credit>0");
    $team->nusers_active = BoincUser::count("teamid=$teamid and expavg_credit>0.1");
    $team->forum = BoincForum::lookup("parent_type=1 and category=$team->id");
    $team->new_members = new_member_list($teamid);
    $team->admins = admin_list($teamid);
    $team->founder = BoincUser::lookup_id($team->userid);
    set_cache_data(serialize($team), $cache_args);
}

if (!$team) {
    error_page("No such team");
}

display_team_page($team, $user);

page_tail(true);

?>
