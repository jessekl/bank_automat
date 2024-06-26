const express = require("express");
const router = express.Router();
const card = require("../models/cardModel");
const bcrypt = require("bcryptjs");
const jwt = require("jsonwebtoken");
var crypto = require("crypto");
var co = require("co");
const dotenv = require("dotenv");
dotenv.config();

router.get("/", function (request, response) {
  card.getAll(function (err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      console.log(dbResult);
      response.json(dbResult);
    }
  });
});

router.get("/:id", function (request, response) {
  card.getById(request.params.id, function (err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.post("/", function (request, response) {
  card.addNewCard(request.body, function (err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.delete("/:id", function (request, response) {
  card.delete(request.params.id, function (err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.put("/:id", function (request, response) {
  card.update(request.params.id, request.body, function (err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.post("/login", function (req, res) {
  const data = req.body;
  console.log(data.cardNumber, data.pinNumber);
  if (data.cardNumber && data.pinNumber) {
    card.login(data.cardNumber, function (err, result) {
      if (err) {
        console.log("error");
        console.log(err.errno);
        res.json(err.errno);
      } else {
        if (result.length > 0) {
          bcrypt.compare(
            data.pinNumber,
            result[0].pinNumber,
            function (err, compareResult) {
              if (compareResult) {
                console.log("Login successful");
                spawnTokenBuf();
                const token = genToken({ cardNumber: data.cardNumber });
                const pinNumber = result[0].pinNumber;
                const responseBody = { token, pinNumber };
                res.send(responseBody);
              } else {
                console.log("Wrong pin number");
                res.send(false);
              }
            }
          );
        } else {
          console.log("Account doesnt exist");
          res.send(false);
        }
      }
    });
  } else {
    console.log("Missing pin or card number");
    res.send(false);
  }
});

function spawnTokenBuf() {
  return function (callback) {
    crypto.randomBytes(64, callback);
  };
}

co(function* () {
  process.env.MY_TOKEN = (yield spawnTokenBuf()).toString("base64");
});

function genToken(value) {
  console.log(value);
  return jwt.sign(value, process.env.MY_TOKEN, { expiresIn: "2000s" });
}

module.exports = router;
