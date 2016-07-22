<?php

    // configuration
    require("../includes/config.php"); 
    
    //finds all rows in users that have the specific username
    $selected = CS50::query("SELECT username, cash FROM users WHERE id = ?", $_SESSION["id"]);
    if (!$selected) {
        apologize("Wasn't able to get user info");
        return;
    }
    $username = $selected[0]["username"];
    $cash = $selected[0]["cash"];
    $rows = CS50::query("SELECT * FROM portfolios WHERE username = ?", $username);
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    render("portfolio.php", ["positions" => $positions, "cash"=>$cash, "title" => "Portfolio"]);
?>
