var express = require("express");
var path = require("path");
var cookieParser = require("cookie-parser");
var logger = require("morgan");
const jwt = require("jsonwebtoken");

const accountRouter = require("./routes/account");
const cardRouter = require("./routes/card");
const transactionHistoryRouter = require("./routes/transactionHistory");
const userRouter = require("./routes/user");

var app = express();

app.use(logger("dev"));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, "public")));

app.use("/account", authenticateToken, accountRouter);
app.use("/card", cardRouter);
app.use("/transactionHistory", authenticateToken, transactionHistoryRouter);
app.use("/user", authenticateToken, userRouter);

function authenticateToken(req, res, next) {
  try {
    const authHeader = req.headers["authorization"];
    const token = authHeader;
    console.log("Token = " + token);

    if (token == null) return res.sendStatus(401);
    jwt.verify(token, process.env.MY_TOKEN, function (err, user) {
      if (err) return res.sendStatus(403);

      req.user = user;

      next();
    });
  } catch (err) {
    console.log(err);
  }
}

module.exports = app;
