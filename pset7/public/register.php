<?php
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //checks if username or password is empty. checks if password is confirmed
        if(empty($_POST["username"]) || empty($_POST["password"])) {
            apologize("Not information was given!");
            return;
        }
        if(!($_POST["password"] == $_POST["confirmation"])) {
            apologize("Passwords do no match.");
            return;
        }
        else {
            //stores information inside database
            $result = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
            if($result == false) {
                apologize("Username Taken.");
            }
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            $_SESSION["id"] = $id;
            redirect("/");
        }
    }
?>