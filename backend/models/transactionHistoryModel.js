const db = require('../database');

const transactionhistory = {
  getAll: function(callback) {
    return db.query('select * from transactionhistory', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from transactionhistory where idtransactionHistory=?', [id], callback);
  },
  getByAccountId: function(idaccount, callback) {
    console.log(idaccount, "jaa")
    return db.query('select * from transactionhistory where idaccount=?', [idaccount], callback);
  },
  addTransaction: function(transactionhistory, callback) {
    console.log(transactionhistory)
    
    return db.query(
      'insert into transactionhistory (idaccount, date,amount) values(?,CURDATE(),?)',
      [transactionhistory.idaccount, transactionhistory.amount],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from transactionhistory where idtransactionHistory=?', [id], callback);
  },
  update: function(id, transactionhistory, callback) {
    return db.query(
      'update transactionhistory set amount=?,balance=? where idtransactionHistory=?',
      [transactionhistory.amount, transactionhistory.balance, id],
      callback
    );
  }
};
module.exports = transactionhistory;