<?php
    require("../includes/config.php"); 
    //if user comes to page via GET
    if ($_SERVER["REQUEST_METHOD"] == "GET") {
        render("deposit_form.php", ["title" => "Deposit"]);
    } 
    else if($_SERVER["REQUEST_METHOD"] == "POST") {
        $depositCash = $_POST["deposit"];
        $deposited = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $depositCash, $_SESSION["id"]);
        if(!$deposited) {
            apologize("Did not deposit correctly!");
        }
        redirect("/");
    }
?>