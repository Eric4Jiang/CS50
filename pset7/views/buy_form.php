<form action="buy.php" method="post">
    <fieldset>
        <div>
            <h1>
                <?php
                    print("Cash = ". $cash);
                ?>
            </h1>
        </div>
        <div>
            <input class="form-control" autocomplete="off" name="symbol" placeholder="Stock to Buy" type="text"/> 
        </div>
        <div>
            <input class="form-control" autocomplete="off" name="shares" placeholder="Number Of Shares" type = "text"/>
        </div>
        <div>
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Buy
            </button>
        </div>
    </fieldset>
</form>