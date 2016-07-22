<?php
    require("../includes/config.php"); 
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell_form.php", ["title" => "Sell"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $symbol = $_POST["symbol"];
        //check if stock exists
        $stock = lookup($symbol); 
        if(!$stock) {
            apologize("Stock does not exist!");
        }
        //finds all rows in users that have the specific username
        $selected = CS50::query("SELECT username, cash FROM users WHERE id = ?", $_SESSION["id"]);
        $username = $selected[0]["username"];
        $rows = CS50::query("SELECT * FROM portfolios WHERE username = ? AND symbol = ?", $username, $symbol);
        //checks if user has the stocks
        if(!$rows) {
            apologize("You do not own any shares from this stock.");
        }
        else { 
            $shares = $rows[0]["shares"];
            
            //make sure user have share to sell
            if($shares == 0) {
                apologize("You have 0 shares!");
                
            }
            //calculate money after you sell your share
            $price = $stock["price"];
            $moneyBack = $price * $shares;
                
            //delete and update database with error checking
            $deleted = CS50::query("DELETE FROM portfolios WHERE username = ? AND symbol = ?", $username, $_POST["symbol"]);
            if(!$deleted) {
                apologize("Not deleted.");
            }
            $updated = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $moneyBack, $_SESSION["id"]);
            if(!$updated) {
                apologize("Not updated.");
            }
            
            //insert actions into log
            $S = "Sold";
            $history = CS50::query("INSERT INTO history (username, BorS, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?, NOW())", 
                                                            $username, $S, $_POST["symbol"], $shares, $price);
            if(!$history) {
                apologize("Actions were not stored in history log.");
            }
            //send back to homepage to look at portfolio
            redirect("/");
        }
    }
?>