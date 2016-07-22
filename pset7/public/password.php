<?php
    require("../includes/config.php");
    if($_SERVER["REQUEST_METHOD"] == "GET") {
        render("password_form.php", ["title" => "PASSWORD CHANGE"]);
    }
    
    //user submits password change
    else if($_SERVER["REQUEST_METHOD"] == "POST") {
        //checks if passwords is empty
        if(empty($_POST["currPassword"]) || empty($_POST["newPassword"]) || empty($_POST["confirmation"])) {
            apologize("Not information was given!");
            return;
        }
        
        $inputCurrPassword = $_POST["currPassword"];
        $selected = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $userCurrPassword = $selected[0]["hash"];
        //checks if user's password matches
        if (!password_verify($inputCurrPassword, $userCurrPassword)) {
            apologize("You did not have the correct current Password!");
            return;
        }
        $newPassword = $_POST["newPassword"];
        $confirmation = $_POST["confirmation"];
        //make sure user confirmed password
        if(!($newPassword == $confirmation)) {
            apologize("Passwords do no match.");
            return;
        }
        
        //update password
        $updated = CS50::query("UPDATE users SET hash = ? WHERE id = ?", password_hash($newPassword, PASSWORD_DEFAULT), $_SESSION["id"]);
        if(!updated) {
            apologize("Did not change passwords successfully.");
            return;
        }
        redirect("/");
    }
?>