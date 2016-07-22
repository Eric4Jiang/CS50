<?php
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = $rows[0]["cash"];
        // else render form
        render("buy_form.php", ["cash" => $cash, "title" => "Buy"]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //only share is a non-negative inetger
        if(!preg_match("/^\d+$/", $_POST["shares"])) {
            apologize("Invalid number of shares. Has to be whole shares.");
            return;
        }
        $shares = $_POST["shares"];
        //find price of stock
        $stock = lookup($_POST["symbol"]);
        if(!$stock) {
            apologize("Invalid Symbol.");
            return;
        }
        $price = $stock["price"];
        
        //find cost of buying the shares
        $cost = $shares * $price;
        
        //check if user has enough money
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = $rows[0]["cash"];
        if($cost > $cash) {
            apologize("You do not have enough money to buy the stock!");
            return;
        }
        //subtract cash from user account
        $subtract = CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
        if(!$subtract) {
            apologize("Not updated.");
            return;
        }
        $selected = CS50::query("SELECT username FROM users WHERE id = ?", $_SESSION["id"]);
        $username = $selected[0]["username"];
        //add stock shares to user account
        $added = CS50::query("INSERT INTO portfolios (username, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $username, $_POST["symbol"], $shares);
        if(!$added) {
            apologize("Shares were not added!");
            return;
        }
        //store actions in the history log
        //insert actions into log
        $B = "Bought";
        $history = CS50::query("INSERT INTO history (username, BorS, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?, NOW())", 
                                                    $username, $B, $_POST["symbol"], $shares, $price);
        if(!$history) {
           apologize("Actions were not stored in history log.");
        }
        redirect("/");
    }
?>