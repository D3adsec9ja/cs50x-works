import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/cash_add", methods=["GET", "POST"])
@login_required
def cash_add():
    if request.method == "POST":
        db.execute("""UPDATE users
            SET cash = cash + :amount
            WHERE id=:user_id
        """, amount = request.form.get("cash"),
        user_id = session["user_id"])
        flash("Topped up")
        return redirect("/")
    else:
        return render_template("cash_add.html")

@app.route("/")
@login_required
def index():
    rows = db.execute("""
        SELECT symbol, SUM(shares) as totalshares
        FROM transactions
        WHERE user_id = :user_id
        GROUP BY symbol
        HAVING totalshares > 0;
    """, user_id=session["user_id"])
    holdings = []
    grand_total = 0
    for row in rows:
        stocks = lookup(row["symbol"])
        holdings.append({
            "symbol": stocks["symbol"],
            "name": stocks["name"],
            "shares": row["totalshares"],
            "price": usd(stocks["price"]),
            "totalshares": usd(stocks["price"] * row["totalshares"])

        })
        grand_total += stocks["price"] * row["totalshares"]
    rows = db.execute("SELECT cash FROM users WHERE id= :user_id", user_id = session["user_id"])
    cash = rows[0]["cash"]
    grand_total += cash


    return render_template("index.html", holdings=holdings, cash = usd(cash), grand_total = usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stocks"""
    if request.method == "POST":
        find_errors = is_provided("symbol") or is_provided("shares")
        if find_errors:
            return find_errors
        elif not request.form.get("shares").isdigit():
            return apology("not valid amount of shares")
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        stocks = lookup(symbol)
        if stocks is None:
         return apology("not valid symbols")
        rows = db.execute("SELECT cash from  users WHERE id=:id", id=session["user_id"])
        cash = rows[0]["cash"]

        new_cash = int(cash - shares * stocks["price"])
        if new_cash < 0:
            return apology("cant afford this")
        db.execute("UPDATE users SET cash=:new_cash WHERE id=:id",
                    new_cash=new_cash,
                    id=session["user_id"])

        db.execute("""
            INSERT INTO transactions
            (user_id, symbol, shares, price)
            VALUES (:user_id, :symbol, :shares, :price)
            """,
            user_id = session["user_id"],
            symbol = stocks["symbol"],
            shares = shares,
            price = stocks["price"]
        )
        flash("Bought")
        return redirect("/")
       # return render_template("bought.html",symbol=symbol["name"], price=int(symbol["price"]), value_of_holding=shares * int(symbol["price"]), cash=int(remaining_cash[0]["cash"]))
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    transactions = db.execute("""
        SELECT symbol, shares, price, transacted
        FROM transactions
        WHERE user_id=:user_id
    """, user_id=session["user_id"])
    for i in range(len(transactions)):
        transactions[i]["price"] = usd(transactions[i]["price"])
    return render_template("history.html", transactions=transactions)

def is_provided(field):
    if not request.form.get(field):
        return apology(f"must provide {field}", 403)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username and pass was submitted
        result_passed = is_provided("password") or is_provided("username")

        if result_passed is not None:
            return result_passed

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                            username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")



@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        result_passed = is_provided("symbol")
        if result_passed is not None:
            return result_passed
        symbol = request.form.get("symbol").upper()
        stocks = lookup(symbol)
        if stocks is None:
            return apology("symbol not valid", 400)
        return render_template("quoted.html", stocksnames={
            'name': stocks['name'],
            'symbol': stocks['symbol'],
            'price': usd(stocks['price'])
        })
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
    #    result_passed = is_provided("username") or is_provided("password") or is_provided("confirmation")
    #   if result_passed != None:
    #      return result_passed
    #    if request.form.get("password") != request.form.get("confirmation"):
    #        return apology("mismatched passwords")
    #    if request.form.get("password") is None:
    #        return apology(" username needed")
    #    try:

    #        primary_key = db.execute("INSERT INTO users (username, hash) VALUES( :username, :hash)",
    #                    username=request.form.get("username"),
    #                    hash= generate_password_hash(request.form.get("password")))
    #    except:
    #        return apology("username already entered", 403)

    #    if primary_key is None:
    #        return apology("register error", 403)
    #   session["user_id"] = primary_key

        if not request.form.get("username"):
            return apology(" username needed")

        elif not request.form.get("password"):
            return apology("password needed")

        elif not request.form.get("confirmation"):
            return apology(" password confirmation needed")

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("The passwords do not match")

        hash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)

        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username = request.form.get("username"), hash = hash)

        if not result:
            return apology("The username is already taken")

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username = request.form.get("username"))

        # Remember which user has registered
        session["user_id"] = rows[0]["id"]

        return redirect ("/")
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "POST":

        find_errors = is_provided("symbol") or is_provided("shares")
        if find_errors:
            return find_errors
        elif not request.form.get("shares").isdigit():
            return apology("not valid amount of shares")
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        stocks = lookup(symbol)
        if stocks is None:
         return apology("not valid symbols")

        rows = db.execute("""
            SELECT symbol, SUM(shares) as totalshares
            FROM transactions
            WHERE user_id=:user_id
            GROUP BY symbol
            HAVING totalshares > 0;

        """, user_id=session["user_id"])
        for row in rows:
            if row["symbol"] == symbol:
                if shares > row["totalshares"]:
                    return apology("too many shares")


        rows = db.execute("SELECT cash from  users WHERE id=:id", id=session["user_id"])
        cash = rows[0]["cash"]

        new_cash = cash + shares * stocks['price']

        db.execute("UPDATE users SET cash=:new_cash WHERE id=:id",
                    new_cash=new_cash,
                    id=session["user_id"])

        db.execute("""
            INSERT INTO transactions
            (user_id, symbol, shares, price)
            VALUES (:user_id, :symbol, :shares, :price)
            """,
            user_id = session["user_id"],
            symbol = stocks["symbol"],
            shares = -1 * shares,
            price = stocks["price"]
        )
        flash("Sold")
        return redirect("/")
    else:

        rows = db.execute("""
            SELECT symbol
            FROM transactions
            WHERE user_id=:user_id
            GROUP  BY symbol
            HAVING SUM(shares) > 0;
        """, user_id = session["user_id"])
        return render_template("sell.html", symbols =[ row["symbol"] for row in rows ])



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
