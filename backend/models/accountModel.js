const db = require("../database");

const account = {
  getAll: function (callback) {
    return db.query("select * from account", callback);
  },
  getById: function (id, callback) {
    return db.query("select * from account where idaccount=?", [id], callback);
  },
  add: function (account, callback) {
    return db.query(
      "insert into account (idaccount, iduser, accountNumber,creditLimit,balance,currentDebt) values(?,?,?,?,?,?)",
      [
        account.idaccount,
        account.iduser,
        account.accountNumber,
        account.creditLimit,
        account.balance,
        account.currentDebt,
      ],
      callback
    );
  },
  delete: function (id, callback) {
    return db.query("delete from account where idaccount=?", [id], callback);
  },
  update: function (id, account, callback) {
    return db.query(
      "update account set creditLimit=?,balance=?,currentDebt=? where idaccount=?",
      [account.creditLimit, account.balance, account.currentDebt, id],
      callback
    );
  },
  makeTransaction: function (id, paymentType, data, callback) {
    if (paymentType == "debit") {
      return db.query(
        `update account set balance=balance-? where idaccount=?`,
        [data.amount, id],
        callback
      );
    } else {
      console.log(data);
      return db.query(
        `update account set balance=balance+?, creditLimit=creditLimit-?,currentDebt=currentDebt+? where idaccount=?`,
        [data.creditAmount, data.creditAmount, data.creditAmount, id],
        callback
      );
    }
  },
  checkBalanceAndCreditLimit: function (id, callback) {
    return db.query(
      "select balance, creditLimit from account where idaccount=?",
      [id],
      callback
    );
  },
};
module.exports = account;
