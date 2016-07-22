<table class="table table-striped">
    <thead>
        <th style="text-align: center">Symbol</th>
        <th style="text-align: center">Share</th>
        <th style="text-align: center">Price</th>
    </thead>
    <?php
        foreach ($positions as $position)
        {
            print("<tr>");
            print("<td>" . $position["symbol"] . "</td>");
            print("<td>" . $position["shares"] . "</td>");
            print("<td>" . $position["price"] . "</td>");
            print("</tr>");
        }
    ?>
</table>
<div>
    <?php
        print("Cash = ". $cash);
    ?>
</div>
<div>
    <iframe allowfullscreen frameborder="0" height="315" src="https://www.youtube.com/embed/oHg5SJYRHA0?autoplay=1&iv_load_policy=3&rel=0" width="420"></iframe>
</div>

