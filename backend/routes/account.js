const express = require("express");
const router = express.Router();
const account = require("../models/accountModel");

router.get("/", function (request, response) {
  account.getAll(function (err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      console.log(dbResult);
      response.json(dbResult);
    }
  });
});

router.get("/:id", function (request, response) {
  account.getById(request.params.id, function (err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.post("/", function (request, response) {
  account.add(request.body, function (err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.delete("/:id", function (request, response) {
  account.delete(request.params.id, function (err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

router.put("/:id", function (req, res) {
  account.update(req.params.id, req.body, function (err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
});

router.put("/:id/:paymentType", function (req, res) {
  account.checkBalanceAndCreditLimit(req.params.id, function (err, dbResult) {
    let balance = dbResult[0].balance;
    let creditLimit = dbResult[0].creditLimit;
    if (balance >= req.body.amount || creditLimit >= req.body.creditAmount) {
      account.makeTransaction(
        req.params.id,
        req.params.paymentType,
        req.body,
        function (err, dbResult) {
          if (err) {
            res.json(err);
          } else {
            res.json(dbResult);
          }
        }
      );
    } else {
      res.json([{ success: "false" }]);
    }
  });
});

module.exports = router;
