const db = require('../database');

const user = {
  getAll: function(callback) {
    return db.query('select * from user', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from user where iduser=?', [id], callback);
  },
  add: function(user, callback) {
    return db.query(
      'insert into user (iduser, fname, lname,personalId,phoneNumber,Address) values(?,?,?,?,?,?)',
      [user.iduser, user.fname, user.lname, user.personalId, user.phoneNumber, user.address],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from user where iduser=?', [id], callback);
  },
  update: function(id, user, callback) {
    return db.query(
      'update user set fname=?,lname=?,phoneNumber=?,Address=? where iduser=?',
      [user.personalId, user.phoneNumber, id],
      callback
    );
  }
};
module.exports = user;