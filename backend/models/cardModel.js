const db = require("../database");
const bcrypt = require("bcrypt");

const card = {
  getAll: function (callback) {
    return db.query("select * from card", callback);
  },
  getById: function (id, callback) {
    return db.query("select * from card where idcard=?", [id], callback);
  },
  addNewCard: function (card, callback) {
    bcrypt.hash(card.pinNumber, 10, function (err, hashedPinNumber) {
      try {
        return db.query(
          "insert into card (idcard, idaccount, pinNumber,cardNumber,cardExpiration,cardReader) values(?,?,?,?,?,?)",
          [
            card.idcard,
            card.idaccount,
            hashedPinNumber,
            card.cardNumber,
            card.cardExpiration,
            card.cardReader,
          ],
          callback
        );
      } catch (err) {
        console.log(err);
      }
    });
  },
  login(cardNumber, callback) {
    return db.query(
      "SELECT pinNumber FROM card WHERE cardNumber=?",
      [cardNumber],
      callback
    );
  },
  delete: function (id, callback) {
    return db.query("delete from card where idcard=?", [id], callback);
  },
  update: function (id, card, callback) {
    return db.query(
      "update card set pinNumber=? where idcard=?",
      [card.pinNumber, id],
      callback
    );
  },
};
module.exports = card;
