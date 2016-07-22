<table class="table table-striped">
    <thead>
        <th stlye-"text-align: center">Time</th>
        <th style="text-align: center">Bought or Sold</th>
        <th style="text-align: center">Symbol</th>
        <th style="text-align: center">Shares</th>
        <th style="text-align: center">Price</th>
    </thead>
    <?php
        foreach ($history as $position)
        {
            print("<tr>");
            print("<td>" . $position["time"] . "</td>");
            print("<td>" . $position["BorS"] . "</td>");
            print("<td>" . $position["symbol"] . "</td>");
            print("<td>" . $position["shares"] . "</td>");
            print("<td>" . $position["price"] . "</td>");
            print("</tr>");
        }
    ?>
</table>