<?php
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $selected = CS50::query("SELECT username FROM users WHERE id = ?", $_SESSION["id"]);
        if(!$selected) {
            apologize("No username selected.");
            return;
        }
        $username = $selected[0]["username"];
        
        //gets all inputs from a username, their history in other words
        $history = CS50::query("SELECT * FROM history WHERE username = ?", $username);
        if(!$history) {
            apologize("No recent history.");
            return;
        }
        render("history_form.php", ["history" => $history, "title" => "History"]);
    }
?>