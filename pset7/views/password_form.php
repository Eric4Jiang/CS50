<form action="password.php" method = post>
    <fieldset>
        <div>
            <input class="form-control" autocomplete="off" name="currPassword" placeholder="Current Password" type="password"/> 
        </div>
        <div>
            <input class="form-control" autocomplete="off" name="newPassword" placeholder=" New Password" type="password"/> 
        </div>
        <div>
            <input class="form-control" autocomplete="off" name="confirmation" placeholder="Confirm Password" type="password"/> 
        </div>
        <div>
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Change Password
            </button>
        </div>
    </fieldset>
</form>